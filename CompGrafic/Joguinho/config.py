# =============================================================================
# config.py — Classes das configurações do jogo
# =============================================================================
import math

# Dimensões e frames
W, H = 800, 600
FPS = 60

# Cores (RGB)
BLACK  = (  0,   0,   0)
WHITE  = (255, 255, 255)
GRAY   = (160, 160, 160)
RED    = (220,  50,  50)
YELLOW = (255, 220,   0)
DIM    = ( 60,  60,  60)

# Vértices Locais e Raios
VERTICES_NAVE = [(0, -18), (-12, 14), (12, 14)]
RAIO_NAVE = 13

COMPRIMENTO_PROJETIL = 10
RAIO_PROJETIL = 3

VERTICES_ASTEROIDE = [(-1, -1), (1, -1), (1, 1), (-1, 1)]