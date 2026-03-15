import pygame
import sys
import math

pygame.init()

WINDOW_WIDTH = 1380
WINDOW_HEIGHT = 840
PANEL_WIDTH = 380
CANVAS_WIDTH = WINDOW_WIDTH - PANEL_WIDTH

BACKGROUND = (248, 249, 251)
PANEL_BG = (237, 240, 244)
WHITE = (255, 255, 255)
BLACK = (20, 20, 20)
DARK = (45, 55, 72)
GRAY = (140, 150, 165)
LIGHT_GRAY = (200, 205, 215)
GRID_COLOR = (225, 228, 235)
BLUE = (52, 120, 246)
GREEN = (46, 170, 90)
RED = (210, 70, 70)

LINE_COLORS = [
    (220, 70, 70),
    (230, 120, 40),
    (220, 180, 40),
    (70, 170, 90),
    (50, 130, 220),
    (130, 90, 200),
    (30, 170, 170)
]

screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption("Лабораторная работа 1 — Брезенхем и Ву")
clock = pygame.time.Clock()

canvas = pygame.Surface((CANVAS_WIDTH, WINDOW_HEIGHT))
canvas.fill(BACKGROUND)

SCALE = 8


font_title = pygame.font.Font(None, 34)
font_main = pygame.font.Font(None, 24)
font_small = pygame.font.Font(None, 20)


def draw_text(surface, text, x, y, color=DARK, font=font_main):
    txt = font.render(text, True, color)
    surface.blit(txt, (x, y))


def clamp(value, left, right):
    return max(left, min(right, value))


def screen_to_grid(x, y):
    return x // SCALE, y // SCALE


def grid_to_screen(x, y):
    return x * SCALE, y * SCALE


def draw_grid(surface):
    if SCALE < 2:
        return

    for x in range(0, CANVAS_WIDTH, SCALE):
        pygame.draw.line(surface, GRID_COLOR, (x, 0), (x, WINDOW_HEIGHT))
    for y in range(0, WINDOW_HEIGHT, SCALE):
        pygame.draw.line(surface, GRID_COLOR, (0, y), (CANVAS_WIDTH, y))



class RasterAlgorithms:
    @staticmethod
    def put_pixel(surface, x, y, color, alpha=1.0):
        x = int(x)
        y = int(y)

        screen_x, screen_y = grid_to_screen(x, y)

        if screen_x >= CANVAS_WIDTH or screen_y >= WINDOW_HEIGHT or screen_x < 0 or screen_y < 0:
            return

        alpha = max(0.0, min(1.0, alpha))

        if alpha >= 1.0:
            draw_color = color
        else:
            draw_color = (
                int(color[0] * alpha + BACKGROUND[0] * (1 - alpha)),
                int(color[1] * alpha + BACKGROUND[1] * (1 - alpha)),
                int(color[2] * alpha + BACKGROUND[2] * (1 - alpha))
            )

        pygame.draw.rect(surface, draw_color, (screen_x, screen_y, SCALE, SCALE))

        if SCALE >= 2:
            pygame.draw.rect(surface, GRID_COLOR, (screen_x, screen_y, SCALE, SCALE), 1)

    @staticmethod
    def bresenham_line(surface, x0, y0, x1, y1, color):
        x0 = int(round(x0))
        y0 = int(round(y0))
        x1 = int(round(x1))
        y1 = int(round(y1))

        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        sx = 1 if x0 < x1 else -1
        sy = 1 if y0 < y1 else -1
        err = dx - dy

        while True:
            RasterAlgorithms.put_pixel(surface, x0, y0, color)
            if x0 == x1 and y0 == y1:
                break

            e2 = 2 * err
            if e2 > -dy:
                err -= dy
                x0 += sx
            if e2 < dx:
                err += dx
                y0 += sy

    @staticmethod
    def wu_line(surface, x0, y0, x1, y1, color):
        def fpart(x):
            return x - math.floor(x)

        def rfpart(x):
            return 1 - fpart(x)

        steep = abs(y1 - y0) > abs(x1 - x0)

        if steep:
            x0, y0 = y0, x0
            x1, y1 = y1, x1

        if x0 > x1:
            x0, x1 = x1, x0
            y0, y1 = y1, y0

        dx = x1 - x0
        dy = y1 - y0

        if dx == 0:
            y_start = int(min(y0, y1))
            y_end = int(max(y0, y1))
            for y in range(y_start, y_end + 1):
                if steep:
                    RasterAlgorithms.put_pixel(surface, y, x0, color)
                else:
                    RasterAlgorithms.put_pixel(surface, x0, y, color)
            return

        gradient = dy / dx

        xend = round(x0)
        yend = y0 + gradient * (xend - x0)
        xgap = rfpart(x0 + 0.5)
        xpxl1 = int(xend)
        ypxl1 = int(math.floor(yend))

        if steep:
            RasterAlgorithms.put_pixel(surface, ypxl1, xpxl1, color, rfpart(yend) * xgap)
            RasterAlgorithms.put_pixel(surface, ypxl1 + 1, xpxl1, color, fpart(yend) * xgap)
        else:
            RasterAlgorithms.put_pixel(surface, xpxl1, ypxl1, color, rfpart(yend) * xgap)
            RasterAlgorithms.put_pixel(surface, xpxl1, ypxl1 + 1, color, fpart(yend) * xgap)

        intery = yend + gradient

        xend = round(x1)
        yend = y1 + gradient * (xend - x1)
        xgap = fpart(x1 + 0.5)
        xpxl2 = int(xend)
        ypxl2 = int(math.floor(yend))

        if steep:
            RasterAlgorithms.put_pixel(surface, ypxl2, xpxl2, color, rfpart(yend) * xgap)
            RasterAlgorithms.put_pixel(surface, ypxl2 + 1, xpxl2, color, fpart(yend) * xgap)
        else:
            RasterAlgorithms.put_pixel(surface, xpxl2, ypxl2, color, rfpart(yend) * xgap)
            RasterAlgorithms.put_pixel(surface, xpxl2, ypxl2 + 1, color, fpart(yend) * xgap)

        if steep:
            for x in range(xpxl1 + 1, xpxl2):
                RasterAlgorithms.put_pixel(surface, int(math.floor(intery)), x, color, rfpart(intery))
                RasterAlgorithms.put_pixel(surface, int(math.floor(intery)) + 1, x, color, fpart(intery))
                intery += gradient
        else:
            for x in range(xpxl1 + 1, xpxl2):
                RasterAlgorithms.put_pixel(surface, x, int(math.floor(intery)), color, rfpart(intery))
                RasterAlgorithms.put_pixel(surface, x, int(math.floor(intery)) + 1, color, fpart(intery))
                intery += gradient

    @staticmethod
    def bresenham_circle(surface, xc, yc, radius, color):
        xc = int(round(xc))
        yc = int(round(yc))
        radius = int(round(radius))

        x = 0
        y = radius
        d = 3 - 2 * radius

        while y >= x:
            points = [
                (xc + x, yc + y), (xc - x, yc + y),
                (xc + x, yc - y), (xc - x, yc - y),
                (xc + y, yc + x), (xc - y, yc + x),
                (xc + y, yc - x), (xc - y, yc - x)
            ]
            for px, py in points:
                RasterAlgorithms.put_pixel(surface, px, py, color)

            x += 1
            if d > 0:
                y -= 1
                d = d + 4 * (x - y) + 10
            else:
                d = d + 4 * x + 6


class Button:
    def __init__(self, x, y, w, h, text, color=BLUE):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.color = color

    def draw(self, surface):
        mouse = pygame.mouse.get_pos()
        hover = self.rect.collidepoint(mouse)
        c = (
            min(self.color[0] + 15, 255),
            min(self.color[1] + 15, 255),
            min(self.color[2] + 15, 255)
        ) if hover else self.color

        pygame.draw.rect(surface, c, self.rect, border_radius=8)
        pygame.draw.rect(surface, DARK, self.rect, 2, border_radius=8)

        txt = font_main.render(self.text, True, WHITE)
        txt_rect = txt.get_rect(center=self.rect.center)
        surface.blit(txt, txt_rect)

    def clicked(self, pos):
        return self.rect.collidepoint(pos)


class RadioButton:
    def __init__(self, x, y, w, h, text, selected=False):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.selected = selected

    def draw(self, surface, disabled=False):
        border_color = LIGHT_GRAY if disabled else (BLUE if self.selected else DARK)
        text_color = LIGHT_GRAY if disabled else (BLUE if self.selected else DARK)

        pygame.draw.rect(surface, WHITE, self.rect, border_radius=8)
        pygame.draw.rect(surface, border_color, self.rect, 2, border_radius=8)

        txt = font_main.render(self.text, True, text_color)
        txt_rect = txt.get_rect(center=self.rect.center)
        surface.blit(txt, txt_rect)

    def clicked(self, pos, disabled=False):
        return (not disabled) and self.rect.collidepoint(pos)


class InputBox:
    def __init__(self, x, y, w, h, label, text=""):
        self.rect = pygame.Rect(x, y, w, h)
        self.label = label
        self.text = text
        self.active = False

    def draw(self, surface):
        draw_text(surface, self.label, self.rect.x, self.rect.y - 22, DARK, font_small)

        border_color = BLUE if self.active else LIGHT_GRAY
        pygame.draw.rect(surface, WHITE, self.rect, border_radius=6)
        pygame.draw.rect(surface, border_color, self.rect, 2, border_radius=6)

        draw_text(surface, self.text, self.rect.x + 8, self.rect.y + 8, BLACK, font_small)

        if self.active and pygame.time.get_ticks() % 1000 < 500:
            cursor_x = self.rect.x + 8 + font_small.size(self.text)[0]
            pygame.draw.line(surface, BLACK,
                             (cursor_x, self.rect.y + 7),
                             (cursor_x, self.rect.y + self.rect.height - 7), 2)

    def clicked(self, pos):
        self.active = self.rect.collidepoint(pos)
        return self.active

    def handle_key(self, event):
        if not self.active:
            return

        if event.key == pygame.K_BACKSPACE:
            self.text = self.text[:-1]
        elif event.unicode.isdigit() or (event.unicode == "-" and len(self.text) == 0):
            self.text += event.unicode


input_x0 = InputBox(CANVAS_WIDTH + 30, 90, 110, 36, "X0")
input_y0 = InputBox(CANVAS_WIDTH + 160, 90, 110, 36, "Y0")
input_x1 = InputBox(CANVAS_WIDTH + 30, 155, 110, 36, "X1")
input_y1 = InputBox(CANVAS_WIDTH + 160, 155, 110, 36, "Y1")

input_scale = InputBox(CANVAS_WIDTH + 30, 540, 110, 36, "Масштаб", "8")
btn_apply_scale = Button(CANVAS_WIDTH + 160, 540, 130, 36, "Применить", GREEN)

input_boxes = [input_x0, input_y0, input_x1, input_y1, input_scale]

algo_bres = RadioButton(CANVAS_WIDTH + 30, 240, 120, 36, "Брезенхем", True)
algo_wu = RadioButton(CANVAS_WIDTH + 170, 240, 100, 36, "Ву")

fig_line = RadioButton(CANVAS_WIDTH + 30, 310, 120, 36, "Линия", True)
fig_circle = RadioButton(CANVAS_WIDTH + 170, 310, 120, 36, "Окружность")

btn_draw = Button(CANVAS_WIDTH + 30, 390, 120, 42, "Построить", GREEN)
btn_clear = Button(CANVAS_WIDTH + 170, 390, 120, 42, "Очистить", RED)
btn_demo = Button(CANVAS_WIDTH + 30, 450, 260, 42, "Демо для отчёта", BLUE)

is_drawing = False
start_pos = None
demo_info = []


def get_selected_algorithm():
    return "bresenham" if algo_bres.selected else "wu"


def get_selected_figure():
    return "line" if fig_line.selected else "circle"


def clear_canvas_only():
    canvas.fill(BACKGROUND)
    draw_grid(canvas)


def draw_current_figure(surface, x0, y0, x1, y1, color=BLACK):
    algorithm = get_selected_algorithm()
    figure = get_selected_figure()

    if figure == "line":
        if algorithm == "bresenham":
            RasterAlgorithms.bresenham_line(surface, x0, y0, x1, y1, color)
        else:
            RasterAlgorithms.wu_line(surface, x0, y0, x1, y1, color)
    else:
        radius = int(math.hypot(x1 - x0, y1 - y0))
        if radius > 0:
            RasterAlgorithms.bresenham_circle(surface, x0, y0, radius, color)


def draw_demo():
    global demo_info
    clear_canvas_only()
    demo_info = []

    cx = 6
    cy = max(12, (WINDOW_HEIGHT // SCALE) // 2)
    length = max(8, min(22, (CANVAS_WIDTH // SCALE) // 6))
    angles = [0, 15, 30, 45, 60, 75, 90]

    for i, angle in enumerate(angles):
        rad = math.radians(angle)
        x1 = cx + int(length * math.cos(rad))
        y1 = cy - int(length * math.sin(rad))
        color = LINE_COLORS[i]

        if i % 2 == 0:
            RasterAlgorithms.bresenham_line(canvas, cx, cy, x1, y1, color)
            algo_name = "Брезенхем"
        else:
            RasterAlgorithms.wu_line(canvas, cx, cy, x1, y1, color)
            algo_name = "Ву"

        tx, ty = grid_to_screen(x1, y1)
        demo_info.append((f"{angle}°", algo_name, color))

    circle_x = cx + length + 16
    circle_r = max(5, min(12, length // 2 + 2))
    RasterAlgorithms.bresenham_circle(canvas, circle_x, cy, circle_r, BLACK)

    circle_tx, circle_ty = grid_to_screen(circle_x + circle_r + 2, cy - circle_r - 2)
    demo_info.append(("Окружность", "Брезенхем", BLACK))


def clear_all():
    global demo_info
    clear_canvas_only()
    demo_info = []
    for box in [input_x0, input_y0, input_x1, input_y1]:
        box.text = ""


def apply_scale():
    global SCALE, demo_info
    try:
        value = int(input_scale.text)
        if 1 <= value <= 40:
            SCALE = value
            input_scale.text = str(SCALE)
            clear_canvas_only()
            demo_info = []
        else:
            input_scale.text = str(SCALE)
    except ValueError:
        input_scale.text = str(SCALE)


def draw_ui(canvas_to_show=None):
    if canvas_to_show is None:
        canvas_to_show = canvas

    screen.blit(canvas_to_show, (0, 0))

    pygame.draw.rect(screen, PANEL_BG, (CANVAS_WIDTH, 0, PANEL_WIDTH, WINDOW_HEIGHT))
    pygame.draw.line(screen, LIGHT_GRAY, (CANVAS_WIDTH, 0), (CANVAS_WIDTH, WINDOW_HEIGHT), 3)

    draw_text(screen, "Алгоритмы Брезенхема и Ву", CANVAS_WIDTH + 20, 25, DARK, font_title)

    for box in [input_x0, input_y0, input_x1, input_y1]:
        box.draw(screen)

    draw_text(screen, "Выбор алгоритма", CANVAS_WIDTH + 30, 210, DARK, font_main)
    algo_bres.draw(screen)
    algo_wu.draw(screen, disabled=(get_selected_figure() == "circle"))

    draw_text(screen, "Выбор фигуры", CANVAS_WIDTH + 30, 280, DARK, font_main)
    fig_line.draw(screen)
    fig_circle.draw(screen)

    btn_draw.draw(screen)
    btn_clear.draw(screen)
    btn_demo.draw(screen)

    input_scale.draw(screen)
    btn_apply_scale.draw(screen)

    current_algo = "Брезенхем" if algo_bres.selected else "Ву"
    current_fig = "Линия" if fig_line.selected else "Окружность"
    draw_text(screen, f"Текущий режим: {current_fig} / {current_algo}", CANVAS_WIDTH + 30, 600, BLUE, font_small)
    draw_text(screen, f"Текущий масштаб: {SCALE}", CANVAS_WIDTH + 30, 625, BLUE, font_small)

    if SCALE == 1:
        draw_text(screen, "Сетка скрыта при масштабе 1", CANVAS_WIDTH + 30, 650, RED, font_small)



clear_canvas_only()


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            mx, my = event.pos

            if mx < CANVAS_WIDTH:
                gx, gy = screen_to_grid(mx, my)
                start_pos = (gx, gy)
                is_drawing = True
                input_x0.text = str(gx)
                input_y0.text = str(gy)
            else:
                for box in input_boxes:
                    box.active = False

                for box in input_boxes:
                    if box.clicked(event.pos):
                        if box == input_scale:
                            box.text = ""
                        break

                if algo_bres.clicked(event.pos):
                    algo_bres.selected = True
                    algo_wu.selected = False

                if algo_wu.clicked(event.pos, disabled=(get_selected_figure() == "circle")):
                    algo_bres.selected = False
                    algo_wu.selected = True

                if fig_line.clicked(event.pos):
                    fig_line.selected = True
                    fig_circle.selected = False

                if fig_circle.clicked(event.pos):
                    fig_line.selected = False
                    fig_circle.selected = True
                    algo_bres.selected = True
                    algo_wu.selected = False

                if btn_draw.clicked(event.pos):
                    try:
                        x0 = int(input_x0.text)
                        y0 = int(input_y0.text)
                        x1 = int(input_x1.text)
                        y1 = int(input_y1.text)
                        draw_current_figure(canvas, x0, y0, x1, y1, BLACK)
                    except ValueError:
                        pass

                if btn_clear.clicked(event.pos):
                    clear_all()

                if btn_demo.clicked(event.pos):
                    draw_demo()

                if btn_apply_scale.clicked(event.pos):
                    apply_scale()

        elif event.type == pygame.MOUSEBUTTONUP and event.button == 1:
            if is_drawing and start_pos is not None:
                mx, my = event.pos
                mx = clamp(mx, 0, CANVAS_WIDTH - 1)
                my = clamp(my, 0, WINDOW_HEIGHT - 1)

                gx, gy = screen_to_grid(mx, my)

                input_x1.text = str(gx)
                input_y1.text = str(gy)

                draw_current_figure(canvas, start_pos[0], start_pos[1], gx, gy, BLACK)

                is_drawing = False
                start_pos = None

        elif event.type == pygame.MOUSEMOTION:
            if is_drawing and start_pos is not None:
                mx, my = event.pos
                mx = clamp(mx, 0, CANVAS_WIDTH - 1)
                my = clamp(my, 0, WINDOW_HEIGHT - 1)

                gx, gy = screen_to_grid(mx, my)

                input_x1.text = str(gx)
                input_y1.text = str(gy)

                temp_canvas = canvas.copy()
                draw_current_figure(temp_canvas, start_pos[0], start_pos[1], gx, gy, GRAY)

                draw_ui(temp_canvas)
                pygame.display.flip()
                continue

        elif event.type == pygame.KEYDOWN:
            for box in input_boxes:
                box.handle_key(event)

    draw_ui()
    pygame.display.flip()
    clock.tick(60)
