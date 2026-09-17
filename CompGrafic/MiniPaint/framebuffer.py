import pygame
import struct
from config import COR_FUNDO

# ─────────────────────────────────────────────────────────────
#  FRAMEBUFFER  (matriz 2D de tuplas RGB)
# ─────────────────────────────────────────────────────────────
class Framebuffer:
    def __init__(self, largura: int, altura: int, fundo: tuple = COR_FUNDO):
        self.largura = largura
        self.altura  = altura
        self.fundo   = fundo
        # armazena pixels como inteiros 0xRRGGBB para eficiência
        self._buffer = [fundo[0] << 16 | fundo[1] << 8 | fundo[2]] * (largura * altura)
        # Surface pygame para blitting eficiente
        self.superficie = pygame.Surface((largura, altura))
        self._sujo = True  # precisa re-renderizar?

    # ── acesso primitivo ──────────────────────────────────────
    def colocar_pixel(self, x: int, y: int, cor: tuple):
        """Escreve um pixel no framebuffer (bounds-check incluído)."""
        if 0 <= x < self.largura and 0 <= y < self.altura:
            self._buffer[y * self.largura + x] = cor[0] << 16 | cor[1] << 8 | cor[2]
            self._sujo = True

    def pegar_pixel(self, x: int, y: int) -> tuple:
        """Lê um pixel do framebuffer. Retorna (0,0,0) fora dos limites."""
        if 0 <= x < self.largura and 0 <= y < self.altura:
            v = self._buffer[y * self.largura + x]
            return ((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF)
        return (0, 0, 0)

    def limpar(self, cor: tuple = None):
        c = cor or self.fundo
        v = c[0] << 16 | c[1] << 8 | c[2]
        self._buffer = [v] * (self.largura * self.altura)
        self._sujo = True

    def atualizar_superficie(self):
        """Copia framebuffer para pygame.Surface apenas quando necessário."""
        if not self._sujo:
            return
        pa = pygame.PixelArray(self.superficie)
        for y in range(self.altura):
            base = y * self.largura
            for x in range(self.largura):
                v = self._buffer[base + x]
                pa[x, y] = v  
        del pa
        self._sujo = False

    # ── put_pixel com espessura ───────────────────────────────
    def colocar_pixel_grosso(self, x: int, y: int, cor: tuple, raio: int = 0):
        """Pinta um quadrado de lado (2*raio+1) centrado em (x,y)."""
        if raio == 0:
            self.colocar_pixel(x, y, cor)
        else:
            for dy in range(-raio, raio + 1):
                for dx in range(-raio, raio + 1):
                    self.colocar_pixel(x + dx, y + dy, cor)

    # ── exportar PPM (P6 binário) ─────────────────────────────
    def salvar_ppm(self, caminho: str):
        with open(caminho, "wb") as f:
            cabecalho = f"P6\n{self.largura} {self.altura}\n255\n"
            f.write(cabecalho.encode())
            for v in self._buffer:
                f.write(bytes([(v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF]))

    # ── exportar BMP (24-bit, sem biblioteca) ─────────────────
    def salvar_bmp(self, caminho: str):
        w, h = self.largura, self.altura
        tamanho_linha = (w * 3 + 3) & ~3  
        preenchimento  = tamanho_linha - w * 3
        tam_dados_pixel = tamanho_linha * h
        tam_arquivo = 54 + tam_dados_pixel

        with open(caminho, "wb") as f:
            f.write(b'BM')
            f.write(struct.pack('<I', tam_arquivo))
            f.write(struct.pack('<HH', 0, 0))
            f.write(struct.pack('<I', 54))
            f.write(struct.pack('<I', 40))
            f.write(struct.pack('<ii', w, -h))  
            f.write(struct.pack('<HH', 1, 24))
            f.write(struct.pack('<I', 0))       
            f.write(struct.pack('<I', tam_dados_pixel))
            f.write(struct.pack('<iihh', 2835, 2835, 0, 0))
            for y in range(h):
                base = y * w
                for x in range(w):
                    v = self._buffer[base + x]
                    f.write(bytes([v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF]))
                f.write(b'\x00' * preenchimento)