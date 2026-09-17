"""
Mini Paint - Trabalho 1: Editor Gráfico Raster
Implementa manualmente: colocar_pixel, pegar_pixel, Bresenham (linha e círculo),
flood fill, retângulo, polígono, transformações geométricas.
Usa Pygame APENAS para janela, eventos e copiar framebuffer para tela.
"""

import pygame
import sys
import math
import os

from config import *
from framebuffer import Framebuffer
from rasterisacao import *

# ─────────────────────────────────────────────────────────────
#  INTERFACE  (toolbar + lógica principal)
# ─────────────────────────────────────────────────────────────
class MiniPaint:
    def __init__(self):
        pygame.init()
        pygame.display.set_caption("Mini Paint — CG")
        self.tela = pygame.display.set_mode((LARGURA_JANELA, ALTURA_TOTAL))
        self.relogio = pygame.time.Clock()

        self.fb = Framebuffer(LARGURA_CANVAS, ALTURA_CANVAS)

        # estado da ferramenta
        self.ferramenta  = "lapis"
        self.cor         = PALETA[0]   # preto
        self.cor_fundo   = COR_FUNDO
        self.espessura   = "fino"
        self.desenhando  = False
        self.pos_inicial = None
        self.pos_previa  = None

        # polígono: vértices acumulados
        self.pontos_poli = []
        self.poli_pronto = False

        # preview buffer (cópia do fb para mostrar shape em construção)
        self._buffer_previa = None

        # UI
        self._montar_interface()

    # ── construção da toolbar ─────────────────────────────────
    def _montar_interface(self):
        self.fonte_peq = pygame.font.SysFont("monospace", 11)
        self.fonte_med = pygame.font.SysFont("monospace", 12, bold=True)

        self.botoes = {}   
        ox = LARGURA_CANVAS + 8
        y  = 6

        self._rect_titulo = pygame.Rect(ox, y, LARGURA_PAINEL - 16, 20)
        y += 22

        for ferramenta in FERRAMENTAS:
            r = pygame.Rect(ox, y, LARGURA_PAINEL - 16, 22)
            self.botoes[ferramenta] = r
            y += 24

        y += 4
        self._y_texto_espessura = y;  y += 15
        self._rects_espessura = {}
        for nome in OPCOES_ESPESSURA:
            r = pygame.Rect(ox, y, (LARGURA_PAINEL - 16) // 3 - 2, 20)
            ox2 = ox + OPCOES_ESPESSURA.index(nome) * ((LARGURA_PAINEL - 16) // 3)
            r.x = ox2
            self._rects_espessura[nome] = r
        y += 26

        y += 4
        self._y_texto_paleta = y;  y += 15
        self._rects_paleta = []
        colunas = 6
        tam   = (LARGURA_PAINEL - 16) // colunas - 2
        for i, c in enumerate(PALETA):
            col = i % colunas
            lin = i // colunas
            r = pygame.Rect(LARGURA_CANVAS + 8 + col * (tam + 2),
                            y + lin * (tam + 2), tam, tam)
            self._rects_paleta.append(r)
        y += ((len(PALETA) - 1) // colunas + 1) * (tam + 2) + 4

        y += 4
        self._y_cor_atual = y;  y += 30

        y += 4
        self._botao_novo     = pygame.Rect(LARGURA_CANVAS + 8, y, (LARGURA_PAINEL - 20) // 2, 24);  y += 28
        self._botao_salvar   = pygame.Rect(LARGURA_CANVAS + 8, y, LARGURA_PAINEL - 16, 24);         y += 28
        self._botao_desfazer = pygame.Rect(LARGURA_CANVAS + 8, y, LARGURA_PAINEL - 16, 24);         y += 32

        self._botao_fechar_poli = pygame.Rect(LARGURA_CANVAS + 8, y, LARGURA_PAINEL - 16, 24)

        self._historico = []
        self._salvar_estado()

    # ── snapshot para undo ────────────────────────────────────
    def _salvar_estado(self):
        self._historico.append(list(self.fb._buffer))
        if len(self._historico) > 20:
            self._historico.pop(0)

    def _desfazer(self):
        if len(self._historico) > 1:
            self._historico.pop()
            self.fb._buffer = list(self._historico[-1])
            self.fb._sujo = True

    # ── raio de espessura (em pixels ao redor do centro) ──────
    @property
    def _raio(self):
        return {k: (0, 1, 3) for k in ["fino","médio","grosso"]}[self.espessura][
            OPCOES_ESPESSURA.index(self.espessura)]

    # ── converte posição de janela → canvas ───────────────────
    def _para_canvas(self, pos):
        return (pos[0], pos[1])  

    # ── salva preview do framebuffer ──────────────────────────
    def _salvar_previa(self):
        self._buffer_previa = list(self.fb._buffer)

    def _restaurar_previa(self):
        if self._buffer_previa:
            self.fb._buffer = list(self._buffer_previa)
            self.fb._sujo = True

    # ── draw preview de shape em construção ───────────────────
    def _desenhar_previa(self, pos_atual):
        if self.pos_inicial is None or self._buffer_previa is None:
            return
        self._restaurar_previa()
        x0, y0 = self.pos_inicial
        x1, y1 = pos_atual
        f = self.ferramenta
        r = self._raio
        if f == "linha":
            linha_bresenham(self.fb, x0, y0, x1, y1, self.cor, r)
        elif f == "retangulo":
            desenhar_retangulo(self.fb, x0, y0, x1, y1, self.cor, r)
        elif f == "retangulo_f":
            retangulo_preenchido(self.fb, x0, y0, x1, y1, self.cor)
        elif f in ("circulo", "circulo_f"):
            raio_circ = int(math.hypot(x1 - x0, y1 - y0))
            if f == "circulo":
                circulo_bresenham(self.fb, x0, y0, raio_circ, self.cor, r)
            else:
                circulo_preenchido(self.fb, x0, y0, raio_circ, self.cor)

    # ── renderiza toolbar ─────────────────────────────────────
    def _desenhar_painel(self):
        pygame.draw.rect(self.tela, (30, 30, 35),
                         (LARGURA_CANVAS, 0, LARGURA_PAINEL, ALTURA_TOTAL))
        pygame.draw.line(self.tela, (80, 80, 90),
                         (LARGURA_CANVAS, 0), (LARGURA_CANVAS, ALTURA_TOTAL), 2)

        txt = self.fonte_med.render("Mini Paint", True, (200, 220, 255))
        self.tela.blit(txt, (LARGURA_CANVAS + 8, 10))

        for nome, rect in self.botoes.items():
            ativo = (nome == self.ferramenta)
            fundo_btn = (60, 130, 200) if ativo else (50, 50, 58)
            pygame.draw.rect(self.tela, fundo_btn, rect, border_radius=4)
            txt = self.fonte_peq.render(NOMES_FERRAMENTAS[nome], True,
                                      (255, 255, 255) if ativo else (180, 180, 190))
            self.tela.blit(txt, (rect.x + 4, rect.y + 6))

        txt = self.fonte_peq.render("Espessura:", True, (160, 160, 170))
        self.tela.blit(txt, (LARGURA_CANVAS + 8, self._y_texto_espessura))
        for nome, rect in self._rects_espessura.items():
            ativo = (nome == self.espessura)
            fundo_btn = (60, 130, 200) if ativo else (50, 50, 58)
            pygame.draw.rect(self.tela, fundo_btn, rect, border_radius=3)
            rotulo = nome[0].upper()
            txt = self.fonte_peq.render(rotulo, True, (255,255,255))
            self.tela.blit(txt, (rect.x + 5, rect.y + 5))

        txt = self.fonte_peq.render("Paleta:", True, (160, 160, 170))
        self.tela.blit(txt, (LARGURA_CANVAS + 8, self._y_texto_paleta))
        for i, (rect, cor) in enumerate(zip(self._rects_paleta, PALETA)):
            pygame.draw.rect(self.tela, cor, rect, border_radius=2)
            if cor == self.cor:
                pygame.draw.rect(self.tela, (255, 255, 100), rect, 2, border_radius=2)

        pygame.draw.rect(self.tela, (60, 60, 70),
                         (LARGURA_CANVAS + 8, self._y_cor_atual, LARGURA_PAINEL - 16, 34),
                         border_radius=4)
        pygame.draw.rect(self.tela, self.cor,
                         (LARGURA_CANVAS + 12, self._y_cor_atual + 4, 26, 26),
                         border_radius=3)
        txt = self.fonte_peq.render(f"RGB{self.cor}", True, (200, 200, 200))
        self.tela.blit(txt, (LARGURA_CANVAS + 42, self._y_cor_atual + 10))

        def desenhar_btn(rect, rotulo, cor=(70, 70, 80)):
            pygame.draw.rect(self.tela, cor, rect, border_radius=4)
            t = self.fonte_peq.render(rotulo, True, (220, 220, 230))
            self.tela.blit(t, (rect.x + 4, rect.y + 7))

        desenhar_btn(self._botao_novo,     "Novo",    (80, 40, 40))
        desenhar_btn(self._botao_salvar,   "Salvar BMP")
        desenhar_btn(self._botao_desfazer, "Desfazer (Ctrl+Z)")

        if self.ferramenta == "poligono":
            texto_pts = f"Vértices: {len(self.pontos_poli)}"
            txt = self.fonte_peq.render(texto_pts, True, (180, 230, 180))
            self.tela.blit(txt, (LARGURA_CANVAS + 8, self._botao_fechar_poli.y - 16))
            desenhar_btn(self._botao_fechar_poli, "Fechar Polígono", (40, 100, 60))

    # ── lida com clique na toolbar ────────────────────────────
    def _clique_painel(self, pos):
        for nome, rect in self.botoes.items():
            if rect.collidepoint(pos):
                self.ferramenta = nome
                if nome == "poligono":
                    self.pontos_poli  = []
                    self.poli_pronto = False
                return True

        for nome, rect in self._rects_espessura.items():
            if rect.collidepoint(pos):
                self.espessura = nome;  return True

        for rect, cor in zip(self._rects_paleta, PALETA):
            if rect.collidepoint(pos):
                self.cor = cor;  return True

        if self._botao_novo.collidepoint(pos):
            self._salvar_estado()
            self.fb.limpar()
            return True
        if self._botao_salvar.collidepoint(pos):
            self._executar_salvar()
            return True

        if self._botao_desfazer.collidepoint(pos):
            self._desfazer();  return True

        if self.ferramenta == "poligono" and self._botao_fechar_poli.collidepoint(pos):
            self._finalizar_poligono()
            return True
        return False

    # ── salvar arquivo ────────────────────────────────────────
    def _executar_salvar(self):
        caminho = os.path.join(os.path.expanduser("~"), "mini_paint_output.bmp")
        self.fb.salvar_bmp(caminho)
        caminho_ppm = caminho.replace(".bmp", ".ppm")
        self.fb.salvar_ppm(caminho_ppm)
        pygame.display.set_caption(f"Mini Paint — Salvo em {caminho}")

    # ── finaliza polígono ─────────────────────────────────────
    def _finalizar_poligono(self):
        if len(self.pontos_poli) >= 3:
            self._salvar_estado()
            r = self._raio
            desenhar_poligono(self.fb, self.pontos_poli, self.cor, r)
        self.pontos_poli  = []
        self.poli_pronto = False

    # ── loop principal ────────────────────────────────────────
    def rodar(self):
        rodando = True
        while rodando:
            for evento in pygame.event.get():
                if evento.type == pygame.QUIT:
                    rodando = False

                # ── teclado ──
                elif evento.type == pygame.KEYDOWN:
                    ctrl = pygame.key.get_mods() & pygame.KMOD_CTRL
                    if ctrl and evento.key == pygame.K_z:
                        self._desfazer()
                    elif ctrl and evento.key == pygame.K_s:
                        self._executar_salvar()
                    elif evento.key == pygame.K_n:
                        self._salvar_estado();  self.fb.limpar()
                    
                    teclas = {pygame.K_p:"lapis", pygame.K_e:"borracha",
                            pygame.K_l:"linha", pygame.K_r:"retangulo",
                            pygame.K_f:"retangulo_f", pygame.K_c:"circulo",
                            pygame.K_o:"circulo_f", pygame.K_b:"balde",
                            pygame.K_g:"poligono"}
                    if evento.key in teclas:
                        self.ferramenta = teclas[evento.key]
                        if self.ferramenta == "poligono":
                            self.pontos_poli = [];  self.poli_pronto = False

                # ── mouse ──
                elif evento.type == pygame.MOUSEBUTTONDOWN:
                    if evento.button != 1:
                        continue 
                    pos = evento.pos
                    if pos[0] >= LARGURA_CANVAS:
                        self._clique_painel(pos)
                    else:
                        cx, cy = self._para_canvas(pos)
                        if self.ferramenta == "balde":
                            self._salvar_estado()
                            balde_preenchimento(self.fb, cx, cy, self.cor)
                        elif self.ferramenta == "poligono":
                            self.pontos_poli.append((cx, cy))
                            self.fb.colocar_pixel_grosso(cx, cy, self.cor, 2)
                            if len(self.pontos_poli) >= 2:
                                x0, y0 = self.pontos_poli[-2]
                                linha_bresenham(self.fb, x0, y0, cx, cy, self.cor, self._raio)
                        else:
                            self.desenhando  = True
                            self.pos_inicial = (cx, cy)
                            self._salvar_previa()
                            if self.ferramenta in ("lapis", "borracha"):
                                cor_atual = self.cor if self.ferramenta == "lapis" else self.cor_fundo
                                self.fb.colocar_pixel_grosso(cx, cy, cor_atual, self._raio)

                elif evento.type == pygame.MOUSEBUTTONUP:
                    if evento.button == 1 and self.desenhando:
                        pos = evento.pos
                        f = self.ferramenta;  r = self._raio
                        if f in ("lapis", "borracha"):
                            self._salvar_estado()
                        elif pos[0] < LARGURA_CANVAS:
                            cx, cy = self._para_canvas(pos)
                            self._restaurar_previa()
                            x0, y0 = self.pos_inicial
                            self._salvar_estado()
                            if f == "linha":
                                linha_bresenham(self.fb, x0, y0, cx, cy, self.cor, r)
                            elif f == "retangulo":
                                desenhar_retangulo(self.fb, x0, y0, cx, cy, self.cor, r)
                            elif f == "retangulo_f":
                                retangulo_preenchido(self.fb, x0, y0, cx, cy, self.cor)
                            elif f == "circulo":
                                raio_circ = int(math.hypot(cx-x0, cy-y0))
                                circulo_bresenham(self.fb, x0, y0, raio_circ, self.cor, r)
                            elif f == "circulo_f":
                                raio_circ = int(math.hypot(cx-x0, cy-y0))
                                circulo_preenchido(self.fb, x0, y0, raio_circ, self.cor)
                        self.desenhando      = False
                        self.pos_inicial     = None
                        self._buffer_previa  = None

                elif evento.type == pygame.MOUSEMOTION:
                    pos = evento.pos
                    if pos[0] < LARGURA_CANVAS:
                        cx, cy = self._para_canvas(pos)
                        if self.desenhando:
                            if self.ferramenta in ("lapis", "borracha"):
                                cor_atual = self.cor if self.ferramenta == "lapis" else self.cor_fundo
                                if self.pos_previa:
                                    px, py = self.pos_previa
                                    linha_bresenham(self.fb, px, py, cx, cy, cor_atual, self._raio)
                                else:
                                    self.fb.colocar_pixel_grosso(cx, cy, cor_atual, self._raio)
                            else:
                                self._desenhar_previa((cx, cy))
                        self.pos_previa = (cx, cy)

            # ── renderização ──
            self.fb.atualizar_superficie()
            self.tela.blit(self.fb.superficie, (0, 0))

            self._desenhar_painel()

            mx, my = pygame.mouse.get_pos()
            if mx < LARGURA_CANVAS:
                status = f"({mx}, {my})  |  {NOMES_FERRAMENTAS[self.ferramenta]}  |  {self.espessura}"
                txt = self.fonte_peq.render(status, True, (180, 180, 200))
                pygame.draw.rect(self.tela, (20, 20, 25),
                                 (0, ALTURA_TOTAL - 16, LARGURA_CANVAS, 16))
                self.tela.blit(txt, (4, ALTURA_TOTAL - 14))

            pygame.display.flip()
            self.relogio.tick(FPS)

        pygame.quit()
        sys.exit()

# ─────────────────────────────────────────────────────────────
if __name__ == "__main__":
    app = MiniPaint()
    app.rodar()