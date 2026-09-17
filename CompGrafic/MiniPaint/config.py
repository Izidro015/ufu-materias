LARGURA_CANVAS, ALTURA_CANVAS = 800, 600
LARGURA_PAINEL = 190
LARGURA_JANELA = LARGURA_CANVAS + LARGURA_PAINEL
ALTURA_JANELA = ALTURA_CANVAS        
ALTURA_TOTAL = ALTURA_JANELA     
FPS = 60

# Cores pré-definidas (R, G, B)
PALETA = [
    (0,   0,   0),    # Preto
    (255, 255, 255),  # Branco
    (220,  30,  30),  # Vermelho
    ( 30, 180,  30),  # Verde
    ( 30,  80, 220),  # Azul
    (240, 210,   0),  # Amarelo
    (  0, 210, 210),  # Ciano
    (210,   0, 210),  # Magenta
    (255, 140,   0),  # Laranja
    (140,   0, 200),  # Roxo
    (139,  90,  43),  # Marrom
    (128, 128, 128),  # Cinza
]

COR_FUNDO = (255, 255, 255)  

ESPESSURAS = {"fino": 1, "médio": 3, "grosso": 6}
OPCOES_ESPESSURA = ["fino", "médio", "grosso"]

FERRAMENTAS = [
    "lapis", "borracha", "linha", "retangulo", "retangulo_f",
    "circulo", "circulo_f", "balde", "poligono",
]

NOMES_FERRAMENTAS = {
    "lapis":       "✏ Lápis",
    "borracha":    "⬜ Borracha",
    "linha":       "╱ Linha",
    "retangulo":   "▭ Ret. Vazado",
    "retangulo_f": "▬ Ret. Cheio",
    "circulo":     "○ Círc. Vazado",
    "circulo_f":   "● Círc. Cheio",
    "balde":       "🪣 Balde",
    "poligono":    "⬡ Polígono",
}