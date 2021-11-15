import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
from ctypes import *
import pygame
import math
import time
from ctypes import *

so_fil = "c_funktion.so"
c_xy = CDLL(so_fil)


SIZE = 900
BACKGROUND_COLOR = (50, 50, 50)
DEFAULT_SPHERE_COLOR = (0, 0, 0)
SHADOW_COLOR = (30, 30, 30)
TOP_COLOR = (20, 20, 20)
SPHERE_COLORS = ["blue", "green", "red", "purple", "orange", "yellow", "pink"]


class Klot:
    def __init__(self, window, x_mitt, y_mitt, radie, color):
        self.x_mitt = x_mitt + int(SIZE/2)
        self.y_mitt = -y_mitt + int(SIZE/2)
        self.radie = radie
        self.color = color
        self.window = window
        self.K = self.radie*2
        self.x0 = pygame.mouse.get_pos()[0] - self.x_mitt
        self.y0 = -pygame.mouse.get_pos()[1] + self.y_mitt
        if self.radie**2 - self.x0**2 - self.y0**2 >= 0:
            self.z0 = math.sqrt(self.radie ** 2 - self.x0 ** 2 - self.y0 ** 2)

    def color_calc(self, x, y):
        z = math.sqrt(self.radie**2 - x**2 - y**2)
        b = (x*self.x0 + y*self.y0 + z*self.z0) / self.radie**2
        if b > 0:
            base_color = int(255*b)
            if self.color == "green":
                return 0, base_color, int(base_color/1.7)
            elif self.color == "blue":
                return 0, int(base_color/1.7), base_color
            elif self.color == "red":
                return base_color, 0, int(base_color/2.6)
            elif self.color == "purple":
                return int(base_color/1.5), 0, base_color
            elif self.color == "orange":
                return base_color, int(base_color/2), 0
            elif self.color == "yellow":
                return base_color, base_color, 0
            elif self.color == "pink":
                return base_color, 0, base_color
            elif self.color == "white":
                return base_color, base_color, base_color
        else:
            return 0, 0, 0

    def sphere_drawer(self):
        if self.radie**2 - self.x0**2 - self.y0**2 < 0:
            pygame.draw.circle(self.window, DEFAULT_SPHERE_COLOR, (self.x_mitt, self.y_mitt), self.radie)
        else:
            for x in range(-self.radie, self.radie): #, int(2*self.radie/self.K)):
                for y in range(-self.radie, self.radie): #, int(2*self.radie/self.K)):
                    #for X in range(x, x + int(2*self.radie/self.K)):
                    #    for Y in range(y, y + int(2*self.radie/self.K)):
                    if x**2 + y**2 <= self.radie**2:
                        pixel_color = self.color_calc(x, y)
                        xy = (int(x+self.x_mitt), int(-y+self.y_mitt)) # ändra här till X/Y
                        self.window.set_at(xy, pixel_color)

    def shadow_drawer(self):
        k = int(-1.065 * self.radie)
        m = int(-3 * self.radie)
        if self.radie**2 - self.x0**2 - self.y0**2 >= 0:
            z0 = int(math.sqrt(self.radie**2 - self.x0**2 - self.y0**2))
            if z0 != 0:
                if self.y0/z0 > -k/m:
                    for x in range(-self.radie, self.radie):
                        for y in range(-self.radie, self.radie):
                            if x ** 2 + y ** 2 < self.radie ** 2:
                                for i in range(-1, 2, 2):
                                    z = i * math.sqrt(self.radie**2 - x**2 - y**2)
                                    t = (k*z + m*y*i - m*k)/(m*self.y0 + k*z0)
                                    xs = int(x * i - t * self.x0)
                                    ys = int(y * i - t * self.y0)
                                    if -ys+self.y_mitt >= SIZE/2.5:  # and xs**2 + ys**2 > self.radie**2:
                                        xy = (xs+self.x_mitt, -ys+self.y_mitt)
                                        self.window.set_at(xy, SHADOW_COLOR)

    def draw_total(self):
        start = time.time()
        self.shadow_drawer()
        mitt = time.time()
        self.sphere_drawer()
        slut = time.time()
        print("Skugga:", str(round(mitt-start, 2)) + "s",
              "\nKlot:  ", str(round(slut-mitt, 2)) + "s",
              "\nTotal: ", str(round(slut-start, 2)) + "s", "\n")


def simple(window):
    klot = Klot(window, 60, -50, 150, "red")
    klot.draw_total()


def setup(window, program):
    window.fill(BACKGROUND_COLOR)
    pygame.draw.rect(window, TOP_COLOR, (0, 0, SIZE, int(SIZE / 2.5)))
    program(window)


def main(program, mus_klick):
    pygame.init()
    pygame.display.set_caption("")
    window = pygame.display.set_mode((SIZE, SIZE))
    setup(window, program)
    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.MOUSEBUTTONDOWN and mus_klick:
                setup(window, program)
        if not mus_klick:
            setup(window, program)
        pygame.display.update()


main(simple, True)

