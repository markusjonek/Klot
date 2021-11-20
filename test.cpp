
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <string>

void pixelRita(SDL_Surface *surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
	SDL_LockSurface(surface);
	uint8_t *PixelArray = (uint8_t*)surface->pixels;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+0] = b;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+1] = g;
	PixelArray[y*surface->pitch + x*surface->format->BytesPerPixel+2] = r;
	SDL_UnlockSurface(surface);

}

void klot(SDL_Surface *surface, int x_mitt, int y_mitt, int radie, std::string klot_color, int WIDTH, int HEIGHT){

	x_mitt += WIDTH/2;
	y_mitt = -y_mitt + HEIGHT/2;

	int x0, y0;
	Uint32 buttons;
	buttons = SDL_GetMouseState(&x0,&y0);
	x0 = x0 - x_mitt;
	y0 = -y0 + y_mitt;

	for (int x = 0; x <= WIDTH; x++){
		for (int y = 0; y < (int)(HEIGHT/3); y++){
			pixelRita(surface, x, y, 20, 20, 20);
            //SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
            //SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	if (pow(pow(radie,2) - pow(x0,2) - pow(y0,2), 0.5) > 0){
		float z0 = pow(pow(radie,2) - pow(x0,2) - pow(y0,2), 0.5);
		float m = -3*radie;
		float k = -1.065*radie;
		if (y0/z0 > -k/m){
			for (int x = -radie; x < radie; x++){
				for (int y = -radie; y < radie; y++){
					if (pow(radie,2) >= pow(x,2) + pow(y,2)){
						for (int i = -1; i < 2; i+=2){
							float z = i * sqrt(pow(radie,2) - pow(x,2) - pow(y,2));
							float t = (k*z + m*y*i - m*k)/(m*y0 + k*z0);
							int xs = (int)(x*i-t*x0);
							int ys = (int)(y*i-t*y0);
							if (xs+x_mitt > 0 && xs+x_mitt < WIDTH && -ys+y_mitt > 0 && -ys+y_mitt < HEIGHT && -ys+y_mitt >= HEIGHT/3){
								pixelRita(surface, xs+x_mitt, -ys+y_mitt, 30, 30, 30);
                                //SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                                //SDL_RenderDrawPoint(renderer, xs+x_mitt, -ys+y_mitt);
							}
						}
					}
				}
			}
		}
		for (int x = -radie; x < radie; x++){
			for (int y = -radie; y < radie; y++){
				if (pow(radie,2) >= pow(x,2) + pow(y,2)){
					float z = sqrt(pow(radie,2) - pow(x,2) - pow(y,2));
					float b = (x*x0 + y*y0 + z*z0) / pow(radie, 2);
					if (b > 0){
						int color = (int)(255*b);
						int x_kord = (int)(x + x_mitt);
						int y_kord = (int)(-y + y_mitt);
						if (klot_color == "green"){
							pixelRita(surface, x_kord, y_kord, 0, color, (int)(color/2.3));
                            //SDL_SetRenderDrawColor(renderer, 0, color, (int)(color/2.3), 255);
                            //SDL_RenderDrawPoint(renderer, x_kord, y_kord);
						}
						if (klot_color == "red"){
							pixelRita(surface, x_kord, y_kord, color, 0, (int)(color/2.3));
                            //SDL_SetRenderDrawColor(renderer, color, 0, (int)(color/2.3), 255);
                            //SDL_RenderDrawPoint(renderer, x_kord, y_kord);
						}
						if (klot_color == "blue"){
							pixelRita(surface, x_kord, y_kord, 0, (int)(color/2), color);
                            //SDL_SetRenderDrawColor(renderer, 0, (int)(color/2), color, 255);
                            //SDL_RenderDrawPoint(renderer, x_kord, y_kord);
						}
					}
					else {
						int color = 0;
						int x_kord = (int)(x + x_mitt);
						int y_kord = (int)(-y + y_mitt);
						pixelRita(surface, x_kord, y_kord, 0, 0, 0);
                        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        //SDL_RenderDrawPoint(renderer, x_kord, y_kord);
					}
				}
			}
		}
	}
	else {
		for (int x = -radie; x < radie; x++){
			for (int y = -radie; y < radie; y++){
				if (pow(radie,2) >= pow(x,2) + pow(y,2)){
					pixelRita(surface, x+x_mitt, y+y_mitt, 0, 0, 0);
                    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    //SDL_RenderDrawPoint(renderer, x+x_mitt, y+y_mitt);
				}
			}
		}
	}
}


int main(int argc, char *argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);

    int HEIGHT = 900;
    int WIDTH = 1400;

    SDL_Window* window;
    //SDL_Renderer* renderer;
    //SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    //SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface *screen;
    screen = SDL_GetWindowSurface(window);

    std::string sphere_color = "green";
	int counter = 0;
	int radie = 200;
	int x_k = 100;
	//std::cout << "Radie: " << radie << "\n" << "Mitt:  " << x_k << "\n\n";
	bool quit = false;
	while (!quit){
        //SDL_RenderPresent(renderer);
		SDL_Event event;

	    while (SDL_PollEvent(&event)){
	        if (event.type == SDL_QUIT){
	            quit = true;
	        }

	        if (event.type == SDL_MOUSEBUTTONDOWN){
	        	if (counter % 2 == 0){
	        		sphere_color = "green";
	        	}
	        	if (counter % 2 == 1){
	        		sphere_color = "red";
	        	}
	        	if (counter % 3 == 0){
	        		sphere_color = "blue";
	        	}
	        	counter++;
	        }

	        if (event.key.keysym.sym == SDLK_UP && 2*radie < HEIGHT){
	        	radie+=5;
	        }
	        if (event.key.keysym.sym == SDLK_DOWN && radie > 10){
	        	radie-=5;
	        }
	        if (event.key.keysym.sym == SDLK_RIGHT && x_k + radie + 10 < WIDTH/2){
	        	x_k+=10;
	        }
	        if (event.key.keysym.sym == SDLK_LEFT && x_k - radie - 10 > -WIDTH/2){
	        	x_k-=10;
	        }
	        if (event.type == SDL_KEYDOWN){
	        	//std::cout << "Radie: " << radie << "\n" << "Mitt:  " << x_k << "\n\n";
	        }
	    }

	    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 50,50,50));
		klot(screen, x_k, 0, radie, sphere_color, WIDTH, HEIGHT);
		SDL_UpdateWindowSurface(window);

	}
}
