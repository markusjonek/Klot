
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <string>

int HEIGHT = 900;
int WIDTH = 900;

void pixelRita(SDL_Surface *surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
	SDL_LockSurface(surface);
	uint8_t *PixelArray = (uint8_t*)surface->pixels;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+0] = b;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+1] = g;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+2] = r;
	SDL_UnlockSurface(surface);

}

long double map(long double x, long double in_min, long double in_max, long double out_min, long double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void mandelbrot(SDL_Surface *surface, long double min, long double max){
    //std::cout << max << " " << min << std::endl;

    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            long double a = map(x, 0, WIDTH, min, max);
            long double b = map(y, 0, HEIGHT, min, max);
            long double ai = a;
            long double bi = b;
            int n = 0;
            for (int i = 0; i < 200; i++){
                long double a1 = a * a - b * b;
                long double b1 = 2 * a * b;
                a = a1 + ai;
                b = b1 + bi;
                if ((a + b) > 2){
                    break;
                }
                n++;
            }
            int color = map(n, 0, 200, 0, 255);
            if (n == 200){
                color = 0;
            }

            pixelRita(surface, x, y, 0, color, color);
            
            
        }
    }
}



int main(){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface *screen;
    screen = SDL_GetWindowSurface(window);
    long double max = 1.0;
    long double min = -2.84;
    long double hej = 1.0;
	bool quit = false;
	while (!quit){
        SDL_Event event;
	    while (SDL_PollEvent(&event)){
	        if (event.type == SDL_QUIT){
	            quit = true;
	        }
            if (event.key.keysym.sym == SDLK_UP){
	        	max -= 0.1 * hej;
                min += 0.15 * hej;
                hej *= 0.9349;
                //std::cout << min << " " << max << std::endl;
	    }
        }
    mandelbrot(screen, min, max);
    SDL_UpdateWindowSurface(window);
    }
}

