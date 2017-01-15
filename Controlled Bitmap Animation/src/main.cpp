// https://wiki.libsdl.org/SDL_CreateRenderer

#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

int main(int, char**){

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Window title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

	// SDL_Surface* surface = SDL_LoadBMP("image.bmp");

	SDL_Surface* surface = IMG_Load("image.png");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect rect = SDL_Rect();
	rect.w = 100;
	rect.h = 100;

	int x = 50, y = 50;

	SDL_Event event;

	bool running = true;

	bool direction = true;

	bool moving = false;

	while(running) {
		SDL_Delay(5);

		SDL_RenderClear(renderer);

		rect.x = x;
		rect.y = y;

		SDL_RenderCopy(renderer, texture, NULL, &rect);

		SDL_RenderPresent(renderer);

		if(moving) {
			if(direction) {
				x++;
			} else {
				x--;
			}
		}

		while( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				SDL_DestroyTexture(texture);

					SDL_DestroyRenderer(renderer);

					SDL_DestroyWindow(window);

					SDL_Quit();

					running = false;
			} else if(event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
				case SDLK_RIGHT:
					moving = true;
					direction = true;
					break;
				case SDLK_LEFT:
					moving = true;
					direction = false;
				}
			} else if(event.type == SDL_KEYUP) {
				moving = false;
			}
		}
	}

	return 0;
}