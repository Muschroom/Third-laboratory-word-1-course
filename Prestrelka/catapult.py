from ctypes import CDLL, c_double
import pygame, math

lib = CDLL("./lib.dll")

lib.bin_search.argtypes = [c_double, c_double, c_double]
lib.bin_search.restype = c_double

pygame.init()
height = 800
width = 600

scr = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()


WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)

x0 = width / 4
y0 = height * 0.8
dt = 0.05
scale = 20
x = x0
y = y0

t = 0
v = 50
x1 = 100
x2 = 100

run = True

is_running = False
step = 5
arr = []

def printMenu(x1 = 100, x2 = 300, v = 50, x = x0, y = y0):
    
    params = {
        "Speed": v,
        "X": int(x - x0),
        "Y": int(y0 - y),
        "X1": x1,
        "X2": x2
    }


    font = pygame.font.SysFont(None, 24)
    pygame.draw.rect(scr, BLACK, (50, 50, 100, 100))
    y_pos = 100
    for name, value in params.items():
        text = font.render(f"{name}: {value}", True, WHITE)
        scr.blit(text, (50, y_pos))
        y_pos += 15

def drawVector(start_x, start_y, angle, length, color):
    end_x = start_x + length * math.cos(angle)
    end_y = start_y + length * math.sin(angle)
    pygame.draw.line(scr, color, (start_x, start_y), (end_x, end_y), 2)
    arrow_angle1 = angle + math.pi * 0.8
    arrow_angle2 = angle - math.pi * 0.8
    arrow_length = 10
    pygame.draw.line(scr, color, (end_x, end_y), 
                    (end_x + arrow_length * math.cos(arrow_angle1), 
                    end_y + arrow_length * math.sin(arrow_angle1)), 2)
    pygame.draw.line(scr, color, (end_x, end_y), 
                    (end_x + arrow_length * math.cos(arrow_angle2), 
                    end_y + arrow_length * math.sin(arrow_angle2)), 2)


def drawBorder():
    pygame.draw.line(scr, (123,23,14), (x0 + x1, y0 - 20), (x0 + x1, y0 + 20), 2)
    font = pygame.font.SysFont(None, 24)
    text = font.render("x1", True, (123,23,14))
    scr.blit(text, (x0 + x1 - 10, y0 + 25))
    

    pygame.draw.line(scr, (123,23,14), (x0 + x2, y0 - 20), (x0 + x2, y0 + 20), 2)

    text = font.render("x2", True, (123,23,14))
    scr.blit(text, (x0 + x2 - 10, y0 + 25))

while run:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                t = 0
                x0 = width / 4 
                y0 = height * 0.8
                angle = lib.bin_search(v, x1, x2)
                is_running = True
                arr = []
            if event.key == pygame.K_q:
                x1 += step
                x1 = max(x1, 0)
            if event.key == pygame.K_w:
                x1 -= step
                x1 = min(x1, width)

            if event.key == pygame.K_e:
                x2 += step
                x2 = max(x2, 0)
            if event.key == pygame.K_r:
                x2 -= step
                x2 = min(x2, width)

            if event.key == pygame.K_a:
                v += step
            if event.key == pygame.K_s:
                v -= step
                v = max(v, 0)




    scr.fill(BLACK)
    pygame.draw.rect(scr, BLUE, pygame.Rect(x0, y0, 10, 10))
    pygame.draw.line(scr, GREEN, (0, y0 + 10), (800, y0 + 10), 2) # ox
    pygame.draw.line(scr, GREEN, (x0, 0), (x0, height), 2) # oy
    printMenu(x1, x2, v, x, y)

    if is_running and t < 2 * v * math.sin(angle) / 9.8:
        t += dt
        x = v * math.cos(angle) * t + x0
        y = -v * math.sin(angle) * t + (9.8 * (t ** 2)) / 2 + y0

        screen_x = int(x * scale)
        screen_y = y0 - int(y * scale)
        arr.append((x,y))
        scr.fill(BLACK)
        pygame.draw.rect(scr, RED, pygame.Rect(x, y, 10, 10))

        pygame.draw.line(scr, GREEN, (x0, 0), (x0, height), 2) 
        pygame.draw.line(scr, GREEN, (0, y0 + 10), (800, y0 + 10), 2)
        printMenu(x1, x2, v, x, y)

        cur_vx = v * math.cos(angle)
        cur_vy = -v * math.sin(angle) + 9.8 * t
        cur_angle = math.atan2(cur_vy, cur_vx)
        cur_speed = math.sqrt(cur_vx**2 + cur_vy**2)
        drawVector(x, y, cur_angle, cur_speed/2, (128, 128, 0))
        drawBorder()
        if len(arr) > 1:
            pygame.draw.lines(scr, WHITE, False, arr, 1)
    else:
        is_running = False


    pygame.display.flip()
    clock.tick(60)
   
pygame.quit()