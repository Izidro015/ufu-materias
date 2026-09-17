# =============================================================================
# main.py — Classes principal
# =============================================================================

import sys
import math
import pygame
from config import (W, H, FPS, BLACK, WHITE, GRAY, RED, DIM, 
                    VERTICES_NAVE, RAIO_NAVE, RAIO_PROJETIL)
from bruto import (rotacionar_transladar, colisao_circulo, 
                   preencher_poligono_scanline, desenhar_poligono_bresenham)
from entidades import Projetil, Asteroide


class Jogo:
    """Classe principal: mantém o estado do jogo e executa o game loop."""

    def __init__(self):
        """Inicializa o Pygame, a janela, o clock e as fontes."""
        pygame.init()
        self.tela = pygame.display.set_mode((W, H))
        pygame.display.set_caption("AstroShift — Trabalho 2")
        self.clock = pygame.time.Clock()
        self.fonte_gr = pygame.font.SysFont('Courier New', 52, bold=True)
        self.fonte_md = pygame.font.SysFont('Courier New', 22)
        self.fonte_pq = pygame.font.SysFont('Courier New', 13)
        self.reiniciar()

    def reiniciar(self):
        """Reseta todas as variáveis de estado para iniciar (ou recomeçar) uma partida."""
        self.estado = 'jogando'
        self.pontos = 0
        self.vidas = 3
        self.nivel = 1
        self.quadro = 0
        self.nave_x = W / 2
        self.nave_y = H / 2
        self.nave_vx = 0.0
        self.nave_vy = 0.0
        self.nave_angulo = 0.0
        self.nave_invencivel = 0
        self.recarga_tiro = 0
        self.projeteis = []
        self.asteroides = []
        self.temporizador_spawn = 0
        self.intervalo_spawn = 120

    def atirar(self):
        """Cria um projétil na direção atual da nave, respeitando o cooldown."""
        if self.estado != 'jogando' or self.recarga_tiro > 0:
            return
        self.projeteis.append(Projetil(self.nave_x, self.nave_y, self.nave_angulo))
        self.recarga_tiro = 12

    def atualizar(self):
        """Avança a lógica do jogo em um frame: entrada, física, spawn e colisões."""
        if self.estado != 'jogando':
            return

        self.quadro += 1
        keys = pygame.key.get_pressed()
        mouse_x, mouse_y = pygame.mouse.get_pos()

        # Aponta a nave para o cursor do mouse
        self.nave_angulo = math.atan2(mouse_y - self.nave_y, mouse_x - self.nave_x) + math.pi / 2

        velocidade = 3.5
        acel_x, acel_y = 0.0, 0.0
        if keys[pygame.K_w] or keys[pygame.K_UP]:    acel_y = -velocidade
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  acel_y =  velocidade
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:  acel_x = -velocidade
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]: acel_x =  velocidade
        if acel_x != 0 and acel_y != 0:
            acel_x *= 0.707; acel_y *= 0.707  # Normaliza diagonal

        # Aplica atrito e integra posição
        self.nave_vx = (self.nave_vx + acel_x) * 0.85
        self.nave_vy = (self.nave_vy + acel_y) * 0.85
        self.nave_x += self.nave_vx
        self.nave_y += self.nave_vy

        # Impede a nave de sair da tela
        self.nave_x = max(RAIO_NAVE, min(W - RAIO_NAVE, self.nave_x))
        self.nave_y = max(RAIO_NAVE, min(H - RAIO_NAVE, self.nave_y))

        if self.recarga_tiro > 0: self.recarga_tiro -= 1
        if self.nave_invencivel > 0: self.nave_invencivel -= 1

        for proj in self.projeteis:
            proj.atualizar()
        self.projeteis = [proj for proj in self.projeteis if not proj.morto]

        # Spawna asteroides em intervalos que diminuem com o nível
        self.temporizador_spawn += 1
        if self.temporizador_spawn >= self.intervalo_spawn:
            self.temporizador_spawn = 0
            self.asteroides.append(Asteroide(self.nivel))
            self.intervalo_spawn = max(40, 120 - self.nivel * 10)

        for ast in self.asteroides:
            ast.atualizar()

        # Colisões: projétil × asteroide e nave × asteroide
        sobreviventes = []
        for ast in self.asteroides:
            if ast.fora_dos_limites:
                continue

            acertou = False
            restantes = []
            for proj in self.projeteis:
                if not acertou and colisao_circulo(ast.x, ast.y, ast.raio, proj.x, proj.y, RAIO_PROJETIL):
                    self.pontos += 10
                    self.nivel = 1 + self.pontos // 100
                    acertou = True
                else:
                    restantes.append(proj)
            if acertou:
                self.projeteis = restantes
                continue

            if self.nave_invencivel == 0 and colisao_circulo(
                    ast.x, ast.y, ast.raio, self.nave_x, self.nave_y, RAIO_NAVE):
                self.vidas -= 1
                self.nave_invencivel = 90
                if self.vidas <= 0:
                    self.estado = 'fim_de_jogo'
                continue

            sobreviventes.append(ast)

        self.asteroides = sobreviventes

    def renderizar(self):
        """Desenha todos os elementos na tela a cada frame."""
        self.tela.fill(BLACK)

        for ast in self.asteroides:
            ast.desenhar(self.tela)

        for proj in self.projeteis:
            proj.desenhar(self.tela)

        if self.estado == 'jogando':
            # Pisca a nave durante a invencibilidade
            piscar = self.nave_invencivel == 0 or (self.nave_invencivel // 5) % 2 == 0
            if piscar:
                mundo = rotacionar_transladar(VERTICES_NAVE, self.nave_angulo, self.nave_x, self.nave_y)
                preencher_poligono_scanline(self.tela, BLACK, mundo)
                desenhar_poligono_bresenham(self.tela, WHITE, mundo)

        self._desenhar_hud()

        if self.estado == 'fim_de_jogo':
            self._desenhar_fim_de_jogo()

        pygame.display.flip()

    def _desenhar_hud(self):
        """Exibe pontos, vidas, nível e dicas de controles na tela."""
        self.tela.blit(self.fonte_md.render(f"PONTOS  {self.pontos}", True, WHITE), (12, 10))
        self.tela.blit(self.fonte_md.render(f"VIDAS  {'o ' * self.vidas}", True, GRAY), (12, 38))
        self.tela.blit(self.fonte_pq.render(f"NIVEL  {self.nivel}", True, DIM), (12, 66))
        self.tela.blit(self.fonte_pq.render("WASD = mover  |  Mouse = mirar  |  Clique/Espaco = atirar", True, DIM), (10, H - 20))

    def _desenhar_fim_de_jogo(self):
        """Sobrepõe a tela de Game Over com overlay semitransparente e pontuação final."""
        sobreposicao = pygame.Surface((W, H), pygame.SRCALPHA)
        sobreposicao.fill((0, 0, 0, 180))
        self.tela.blit(sobreposicao, (0, 0))

        go = self.fonte_gr.render("GAME OVER", True, RED)
        self.tela.blit(go, go.get_rect(center=(W // 2, H // 2 - 50)))

        sc = self.fonte_md.render(f"Pontuacao: {self.pontos}", True, GRAY)
        self.tela.blit(sc, sc.get_rect(center=(W // 2, H // 2 + 10)))

        r = self.fonte_pq.render("Pressione R para reiniciar", True, WHITE)
        self.tela.blit(r, r.get_rect(center=(W // 2, H // 2 + 52)))

    def executar(self):
        """Loop principal: processa eventos, atualiza lógica e renderiza a cada frame."""
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit(); sys.exit()
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_SPACE:  self.atirar()
                    if event.key == pygame.K_r:      self.reiniciar()
                    if event.key == pygame.K_ESCAPE: pygame.quit(); sys.exit()
                if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    self.atirar()

            self.atualizar()
            self.renderizar()
            self.clock.tick(FPS)


if __name__ == "__main__":
    jogo = Jogo()
    jogo.executar()