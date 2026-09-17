from collections import deque
from framebuffer import Framebuffer

# ─────────────────────────────────────────────────────────────
#  ALGORITMOS DE RASTERIZAÇÃO (todos implementados à mão)
# ─────────────────────────────────────────────────────────────

def linha_bresenham(fb: Framebuffer, x0, y0, x1, y1, cor, raio=0):
    dx = abs(x1 - x0);  dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    erro = dx - dy
    while True:
        fb.colocar_pixel_grosso(x0, y0, cor, raio)
        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * erro
        if e2 > -dy:
            erro -= dy;  x0 += sx
        if e2 <  dx:
            erro += dx;  y0 += sy

def circulo_bresenham(fb: Framebuffer, cx, cy, r, cor, raio=0):
    x, y = 0, r
    d = 3 - 2 * r
    def _plotar8(px, py):
        for ox, oy in [(px,py),(-px,py),(px,-py),(-px,-py),
                       (py,px),(-py,px),(py,-px),(-py,-px)]:
            fb.colocar_pixel_grosso(cx+ox, cy+oy, cor, raio)
    _plotar8(x, y)
    while y >= x:
        x += 1
        if d > 0:
            y -= 1;  d += 4*(x - y) + 10
        else:
            d += 4*x + 6
        _plotar8(x, y)

def circulo_preenchido(fb: Framebuffer, cx, cy, r, cor):
    x, y = 0, r
    d = 3 - 2 * r
    def _linha_h(lx, rx, ly):
        for px in range(lx, rx + 1):
            fb.colocar_pixel(px, ly, cor)
    _linha_h(cx - y, cx + y, cy)
    while y >= x:
        x += 1
        if d > 0:
            y -= 1;  d += 4*(x - y) + 10
        else:
            d += 4*x + 6
        _linha_h(cx - x, cx + x, cy + y)
        _linha_h(cx - x, cx + x, cy - y)
        _linha_h(cx - y, cx + y, cy + x)
        _linha_h(cx - y, cx + y, cy - x)

def desenhar_retangulo(fb: Framebuffer, x0, y0, x1, y1, cor, raio=0):
    linha_bresenham(fb, x0, y0, x1, y0, cor, raio)
    linha_bresenham(fb, x1, y0, x1, y1, cor, raio)
    linha_bresenham(fb, x1, y1, x0, y1, cor, raio)
    linha_bresenham(fb, x0, y1, x0, y0, cor, raio)

def retangulo_preenchido(fb: Framebuffer, x0, y0, x1, y1, cor):
    lx, rx = (x0, x1) if x0 <= x1 else (x1, x0)
    ty, by = (y0, y1) if y0 <= y1 else (y1, y0)
    for y in range(ty, by + 1):
        for x in range(lx, rx + 1):
            fb.colocar_pixel(x, y, cor)

def desenhar_poligono(fb: Framebuffer, pontos, cor, raio=0):
    n = len(pontos)
    for i in range(n):
        x0, y0 = pontos[i]
        x1, y1 = pontos[(i + 1) % n]
        linha_bresenham(fb, x0, y0, x1, y1, cor, raio)

def balde_preenchimento(fb: Framebuffer, x, y, nova_cor):
    cor_antiga = fb.pegar_pixel(x, y)
    if cor_antiga == nova_cor:
        return
    fila = deque()
    fila.append((x, y))
    visitados = set()
    visitados.add((x, y))
    while fila:
        cx, cy = fila.popleft()
        if fb.pegar_pixel(cx, cy) != cor_antiga:
            continue
        fb.colocar_pixel(cx, cy, nova_cor)
        for nx, ny in [(cx+1,cy),(cx-1,cy),(cx,cy+1),(cx,cy-1)]:
            if (nx, ny) not in visitados and 0 <= nx < fb.largura and 0 <= ny < fb.altura:
                if fb.pegar_pixel(nx, ny) == cor_antiga:
                    visitados.add((nx, ny))
                    fila.append((nx, ny))