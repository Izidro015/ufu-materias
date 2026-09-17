# =============================================================================
# entidades.py — Classes dos objetos do jogo: Projetil e Asteroide
# =============================================================================

import math
import random

from config import (
    W, H,
    WHITE, GRAY, BLACK,
    COMPRIMENTO_PROJETIL,
    VERTICES_ASTEROIDE,
)
from bruto import (
    desenhar_linha_dda,
    escalar_rotacionar_transladar,
    preencher_poligono_scanline,
    desenhar_poligono_bresenham,
)


# =============================================================================
# PROJÉTIL
# =============================================================================

class Projetil:
    """
    Representa um tiro disparado pela nave.

    O projétil é desenhado como uma linha curta (via DDA) alinhada com
    a direção do tiro, dando a impressão visual de um traçador.

    Atributos:
        x, y        — posição atual do centro do projétil
        vx, vy      — velocidade em pixels/frame
        angulo      — ângulo herdado da nave no momento do disparo
        vida        — contador regressivo; quando chega a 0 o projétil some
    """

    VELOCIDADE = 10.0   # pixels por frame

    def __init__(self, x, y, angulo):
        # O projétil nasce 22 pixels à frente da nave (fora do triângulo)
        direcao = angulo - math.pi / 2   # converte ângulo da nave para direção de voo
        self.x      = x + math.cos(direcao) * 22
        self.y      = y + math.sin(direcao) * 22
        self.vx     = math.cos(direcao) * self.VELOCIDADE
        self.vy     = math.sin(direcao) * self.VELOCIDADE
        self.angulo = angulo
        self.vida   = 60   # dura 60 frames (pra chegar quase até o final da tela)

    def atualizar(self):
        """Avança a posição e decrementa o tempo de vida."""
        self.x    += self.vx
        self.y    += self.vy
        self.vida -= 1

    def desenhar(self, tela):
        """
        Desenha o projétil como uma linha curta usando DDA.

        A linha vai da 'cauda' até a 'ponta', ambas calculadas a partir
        do centro (self.x, self.y) na direção do voo.
        """
        direcao = self.angulo - math.pi / 2

        # Extremidades da linha (COMPRIMENTO_PROJETIL pixels para cada lado)
        ponta_x = self.x + math.cos(direcao) * COMPRIMENTO_PROJETIL
        ponta_y = self.y + math.sin(direcao) * COMPRIMENTO_PROJETIL
        cauda_x = self.x - math.cos(direcao) * COMPRIMENTO_PROJETIL
        cauda_y = self.y - math.sin(direcao) * COMPRIMENTO_PROJETIL

        desenhar_linha_dda(tela, WHITE, (cauda_x, cauda_y), (ponta_x, ponta_y))

    @property
    def morto(self):
        """
        Retorna True quando o projétil deve ser removido da lista.
        Isso acontece quando o tempo de vida esgota OU sai da tela.
        """
        fora_da_tela = (
            self.x < -10 or self.x > W + 10 or
            self.y < -10 or self.y > H + 10
        )
        return self.vida <= 0 or fora_da_tela


# =============================================================================
# ASTEROIDE
# =============================================================================

class Asteroide:
    """
    Representa um asteroide inimigo que entra pela borda da tela.

    A forma é um quadrado unitário (VERTICES_ASTEROIDE) escalado e
    rotacionado a cada frame, dando a aparência de um bloco girando.

    Atributos:
        x, y        — posição do centro
        vx, vy      — velocidade de translação
        tamanho     — metade do lado do quadrado (= raio de colisão)
        raio        — cópia de tamanho, usada em colisao_circulo()
        angulo      — ângulo de rotação atual (em radianos)
        vel_rotacao — velocidade angular (radianos/frame), pode ser negativa
    """

    def __init__(self, nivel=1):
        # Velocidade base cresce com o nível e tem uma parcela aleatória
        vel = 1.0 + nivel * 0.25 + random.uniform(0, 1.0)

        # Escolhe aleatoriamente por qual lado da tela o asteroide entra
        lado = random.randint(0, 3)

        if lado == 0:   # entra pelo topo → desce
            self.x, self.y = random.uniform(0, W), -30
            self.vx = random.uniform(-0.5, 0.5) * vel
            self.vy = vel
        elif lado == 1:   # entra pela direita → vai para a esquerda
            self.x, self.y = W + 30, random.uniform(0, H)
            self.vx = -vel
            self.vy = random.uniform(-0.5, 0.5) * vel
        elif lado == 2:   # entra pelo fundo → sobe
            self.x, self.y = random.uniform(0, W), H + 30
            self.vx = random.uniform(-0.5, 0.5) * vel
            self.vy = -vel
        else:             # entra pela esquerda → vai para a direita
            self.x, self.y = -30, random.uniform(0, H)
            self.vx = vel
            self.vy = random.uniform(-0.5, 0.5) * vel

        self.tamanho    = random.uniform(18, 30)   # tamanho visual
        self.raio       = self.tamanho             # raio de colisão
        self.angulo     = random.uniform(0, math.pi * 2)
        self.vel_rotacao = random.uniform(-0.03, 0.03)   # giro horário ou anti-horário

    def atualizar(self):
        """Move o asteroide e atualiza sua rotação."""
        self.x      += self.vx
        self.y      += self.vy
        self.angulo += self.vel_rotacao

    def desenhar(self, tela):
        """
        Rasteriza o asteroide em duas etapas:
            1. Preenchimento preto via scanline — cobre objetos que
               estejam atrás do asteroide (efeito de opacidade).
            2. Borda cinza via Bresenham — define o contorno visível.

        Os vértices unitários são primeiro escalados, depois rotacionados
        e finalmente transladados para a posição do asteroide.
        """
        # Transforma os vértices unitários para as coordenadas de tela
        mundo = escalar_rotacionar_transladar(
            VERTICES_ASTEROIDE, self.tamanho, self.angulo, self.x, self.y
        )

        preencher_poligono_scanline(tela, (0, 0, 50), mundo)    # interior azulado
        desenhar_poligono_bresenham(tela, GRAY,  mundo)    # borda cinza

    @property
    def fora_dos_limites(self):
        """
        Retorna True quando o asteroide está longe o suficiente da tela
        para ser descartado sem impacto visual (margem de 200 pixels).
        """
        return (
            self.x < -200 or self.x > W + 200 or
            self.y < -200 or self.y > H + 200
        )