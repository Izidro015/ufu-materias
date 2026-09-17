# =============================================================================
# bruto.py — Matemática "bruta": transformações, colisão e rasterização
#
# Organização:
#   1. Transformações geométricas  (rotação, escala, translação)
#   2. Detecção de colisão         (círculo vs círculo)
#   3. Algoritmos de rasterização  (DDA, Bresenham)
#   4. Funções de desenho          (usam os algoritmos acima + tela.set_at)
# =============================================================================

import math
from config import W, H


# =============================================================================
# 1. TRANSFORMAÇÕES GEOMÉTRICAS
# =============================================================================

def rotacionar_transladar(verts, angulo, tx, ty):
    """
    Aplica rotação 2D seguida de translação em uma lista de vértices locais,
    convertendo-os para coordenadas de tela (mundo).

    Parâmetros:
        verts  — lista de (x, y) em coordenadas locais do objeto
        angulo — ângulo de rotação em radianos
        tx, ty — posição do objeto na tela (translação)
    """
    cos_ang = math.cos(angulo)
    sin_ang = math.sin(angulo)
    resultado = []
    for (x, y) in verts:
        xw = x * cos_ang - y * sin_ang + tx   # componente X rotacionada + deslocada
        yw = x * sin_ang + y * cos_ang + ty   # componente Y rotacionada + deslocada
        resultado.append((xw, yw))
    return resultado


def escalar_rotacionar_transladar(verts, escala, angulo, tx, ty):
    """
    Aplica escala + rotação 2D + translação em uma lista de vértices locais.
    Parâmetros:
        verts  — lista de (x, y) em coordenadas locais (unitárias)
        escala — fator de tamanho do objeto
        angulo — ângulo de rotação em radianos
        tx, ty — posição do objeto na tela
    """
    cos_ang = math.cos(angulo)
    sin_ang = math.sin(angulo)
    resultado = []
    for (x, y) in verts:
        xw = escala * (x * cos_ang - y * sin_ang) + tx
        yw = escala * (x * sin_ang + y * cos_ang) + ty
        resultado.append((xw, yw))
    return resultado


# =============================================================================
# 2. DETECÇÃO DE COLISÃO
# =============================================================================

def colisao_circulo(ax, ay, ar, bx, by, br):
    """
    Verifica se a nave e o asteróide se sobrepõem usando distância euclidiana.

    A colisão ocorre quando a distância entre os centros é menor
    do que a soma dos raios:
        distância = sqrt((ax-bx)² + (ay-by)²)
        colide    = distância < ar + br

    Parâmetros:
        ax, ay — centro do círculo A
        ar     — raio do círculo A
        bx, by — centro do círculo B
        br     — raio do círculo B
    """
    dx = ax - bx
    dy = ay - by
    return math.sqrt(dx * dx + dy * dy) < ar + br
    # dx*dx ((ax-bx)^2) e soma com dy*dy ((ay-by)^2)


# =============================================================================
# 3. ALGORITMOS DE RASTERIZAÇÃO
# =============================================================================

def dda_linha(x0, y0, x1, y1):# Pros tiros
    """
    Algoritmo DDA (Digital Differential Analyzer) — gera os pixels de uma linha.

    Ideia: divide a linha no número de passos igual à maior variação
    (em X ou Y) e avança em incrementos fracionários a cada passo.

    Exemplo para a linha (0,0)→(4,2):
        passos     = 4  (maior variação é em X)
        incremento_x = 4/4 = 1.0
        incremento_y = 2/4 = 0.5
        pixels gerados: (0,0) (1,0) (2,1) (3,1) (4,2)
    """
    pontos = []
    dx = x1 - x0
    dy = y1 - y0

    # O número de passos determina a resolução da linha
    passos = abs(dx) if abs(dx) > abs(dy) else abs(dy)

    # Impede divisão por zero se os pontos forem iguais:
    if passos == 0:
        return [(int(x0), int(y0))]

    incremento_x = dx / passos   # quanto X avança por passo
    incremento_y = dy / passos   # quanto Y avança por passo

    x, y = x0, y0
    for _ in range(int(passos) + 1):
        pontos.append((int(round(x)), int(round(y))))
        x += incremento_x
        y += incremento_y

    return pontos


def bresenham_linha(x0, y0, x1, y1):# Pros asteroides e pra nave
    """
    Algoritmo de Bresenham — gera os pixels de uma linha usando só inteiros.

    A decisão de mover em X, Y ou ambos é feita pelo sinal de e2 = 2 * erro:
        e2 > -dy  → avança em X
        e2 <  dx  → avança em Y
    """
    pontos = []
    x0, y0, x1, y1 = int(x0), int(y0), int(x1), int(y1)

    dx = abs(x1 - x0)
    dy = abs(y1 - y0)

    # sx/sy definem a direção de caminhada (+1 ou -1) em cada eixo
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1

    erro = dx - dy   # variável de decisão inicializada com dx - dy
    x, y = x0, y0

    while True:
        pontos.append((x, y))

        if x == x1 and y == y1:
            break   # chegou ao ponto final

        e2 = 2 * erro

        if e2 > -dy:   # erro favorece movimento em X
            erro -= dy
            x    += sx

        if e2 < dx:    # erro favorece movimento em Y
            erro += dx
            y    += sy

    return pontos


# =============================================================================
# 4. FUNÇÕES DE DESENHO (usam os algoritmos acima + tela.set_at)
# =============================================================================

def desenhar_linha_dda(tela, cor, p0, p1):
    """
    Desenha um segmento de reta pixel a pixel usando o algoritmo DDA.

    Parâmetros:
        tela    — superfície Pygame onde os pixels são escritos
        cor     — tupla RGB da cor do traço
        p0, p1  — pontos inicial e final como (x, y) — podem ser float
    """
    # Converte para inteiro antes de passar ao DDA
    x0, y0 = int(round(p0[0])), int(round(p0[1]))
    x1, y1 = int(round(p1[0])), int(round(p1[1]))

    for (px, py) in dda_linha(x0, y0, x1, y1):
        # Só pinta pixels dentro dos limites da tela
        if 0 <= px < W and 0 <= py < H:
            tela.set_at((px, py), cor)


def desenhar_poligono_bresenham(tela, cor, pontos):
    """
    Desenha a borda (contorno) de um polígono pixel a pixel usando Bresenham.
    Percorre cada aresta (par de vértices consecutivos) e rasteriza.

    Parâmetros:
        tela   — superfície Pygame
        cor    — tupla RGB da cor da borda
        pontos — lista de (x, y) em coordenadas de tela (já transformados)
    """
    n = len(pontos)
    for i in range(n):
        # Vértice atual e o próximo (o último conecta de volta ao primeiro)
        x0, y0 = int(round(pontos[i][0])),           int(round(pontos[i][1]))
        x1, y1 = int(round(pontos[(i + 1) % n][0])), int(round(pontos[(i + 1) % n][1]))

        for (px, py) in bresenham_linha(x0, y0, x1, y1):
            if 0 <= px < W and 0 <= py < H:
                tela.set_at((px, py), cor)


def preencher_poligono_scanline(tela, cor, pontos):
    """
    Preenche o interior de um polígono usando o algoritmo de scanline.

    Funcionamento em 3 etapas:
        1. Rasteriza todas as arestas com Bresenham, guardando para cada
           linha horizontal (scanline) quais valores de X foram tocados.
        2. Para cada scanline, pinta todos os pixels entre o X mínimo
           e o X máximo encontrados — isso preenche o interior.
        3. Pixels fora dos limites da tela são ignorados.

    Parâmetros:
        tela   — superfície Pygame
        cor    — tupla RGB da cor de preenchimento
        pontos — lista de (x, y) em coordenadas de tela
    """
    if len(pontos) < 3:
        return   # precisa de ao menos 3 vértices para formar um polígono

    # Converte todos os vértices para inteiro de uma vez, por conta das contas que geram números quebrados
    pontos_int = [(int(round(x)), int(round(y))) for x, y in pontos]

    # Determina o intervalo vertical do polígono (clampado à tela)
    ys    = [p[1] for p in pontos_int]
    y_min = max(0, min(ys))
    y_max = min(H - 1, max(ys))

    # varredura_x: dicionário  y_linha → [lista de x que a aresta toca nessa linha]
    varredura_x = {}
    n = len(pontos_int)
    for i in range(n):
        x0, y0 = pontos_int[i]
        x1, y1 = pontos_int[(i + 1) % n]
        for (px, py) in bresenham_linha(x0, y0, x1, y1):
            if y_min <= py <= y_max:
                varredura_x.setdefault(py, []).append(px)

    # Para cada scanline, pinta do x mais à esquerda ao mais à direita
    for y, xs in varredura_x.items():
        x_esq = max(0, min(xs))          # borda esquerda (clampada)
        x_dir = min(W - 1, max(xs))      # borda direita  (clampada)
        for x in range(x_esq, x_dir + 1):
            tela.set_at((x, y), cor)