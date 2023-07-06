/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "quakegeneric.h"

#include <SDL.h>
#include <stdint.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
uint32_t *rgbpixels;

#define ARGB(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

void QG_Init(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Quake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, QUAKEGENERIC_RES_X, QUAKEGENERIC_RES_Y, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, QUAKEGENERIC_RES_X, QUAKEGENERIC_RES_Y);
	rgbpixels = malloc(QUAKEGENERIC_RES_X * QUAKEGENERIC_RES_Y * sizeof(uint32_t));
}

void QG_Quit(void)
{
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (texture) SDL_DestroyTexture(texture);
	if (rgbpixels) free(rgbpixels);
	SDL_Quit();
}

void QG_DrawFrame(void *pixels, void *palette)
{
	// convert pixels
	for (int i = 0; i < QUAKEGENERIC_RES_X * QUAKEGENERIC_RES_Y; i++)
	{
		uint8_t pixel = ((uint8_t *)pixels)[i];
		uint8_t *entry = &((uint8_t *)palette)[pixel * 3];
		rgbpixels[i] = ARGB(*(entry), *(entry + 1), *(entry + 2), 255);
	}

	// blit
	SDL_UpdateTexture(texture, NULL, rgbpixels, QUAKEGENERIC_RES_X * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	int running = 1;

	QG_Create(argc, argv);

	while (running)
	{
		// get start of frame
		Uint64 start = SDL_GetPerformanceCounter();

		// poll events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
			}
		}

		QG_Tick();

		// wait for frametime
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(66.66666666666667 - elapsed));
	}

	return 0;
}
