#include <iostream>
#include <windows.h>
#include <thread>
#include <stdio.h>
#include <SDL.h>

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void DrawBox(int32_t _x, int32_t _y, int32_t _w, int32_t _h, int32_t BorderRadius);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool RunStatus  = true;
bool DrawStatus = false;

SDL_Event	  Events;
SDL_Surface*  screen_surface = NULL;
SDL_Window*   window		 = NULL;
SDL_Renderer* Renderer       = NULL;

int x = 0;
int y = 0;

#undef main
int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		printf_s(" SDL_Init Error!\n\r");
	}
	else
	{
		printf_s(" SDL_Init Successful!\n\r");		

		window		   = SDL_CreateWindow( "Note_it", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		screen_surface = SDL_GetWindowSurface(window);
		Renderer	   = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 31, 35, 36));
		SDL_UpdateWindowSurface(window);

		while (RunStatus)
		{

			if (DrawStatus)
			{
				SDL_GetMouseState(&x, &y);
				printf_s(" X:%d Y:%d \n\r", x, y);

				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				DrawBox(x, y, 200, 100, 15);
				SDL_RenderPresent(Renderer);

				DrawStatus = false;
			}

			while (SDL_PollEvent(&Events) != 0)
			{
				if (Events.type == SDL_QUIT)
				{
					RunStatus = false;
				}

				if (Events.type == SDL_MOUSEBUTTONDOWN)
				{
					DrawStatus = !DrawStatus;
					printf_s(" DrawStatus \n\r");
				}
			}
		}

		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();
	}

	return 0;
}

void DrawBox(int32_t _x, int32_t _y, int32_t _w, int32_t _h, int32_t BorderRadius)
{

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	int HomeX = _x;
	int HomeY = _y;
	int RightX = _x + _w;
	int RightY = _y;
	int BottomHomeX = _x;
	int BottomHomeY = _y + _h;
	int BottomRightX = _x + _w;
	int BottomRightY = _y +_h;


	DrawCircle(Renderer,
		HomeX, HomeY, BorderRadius);
	DrawCircle(Renderer,
		RightX, RightY, BorderRadius);
	DrawCircle(Renderer,
		BottomHomeX, BottomHomeY, BorderRadius);
	DrawCircle(Renderer,
		BottomRightX, BottomRightY, BorderRadius);

	SDL_RenderDrawLine(Renderer,
		(HomeX),  (HomeY - BorderRadius),
		(RightX), (HomeY - BorderRadius)
	);
	SDL_RenderDrawLine(Renderer,
		(RightX + BorderRadius),	   (RightY),
		(BottomRightX + BorderRadius), (BottomRightY)
	);
	SDL_RenderDrawLine(Renderer,
		(BottomRightX), (BottomRightY + BorderRadius),
		(BottomHomeX),  (BottomHomeY + BorderRadius)
	);
	SDL_RenderDrawLine(Renderer,
		(BottomHomeX - BorderRadius), (BottomHomeY),
		(HomeX - BorderRadius), (HomeY)
	);

	SDL_Rect DataArea;
	DataArea.x = HomeX;
	DataArea.y = HomeY;
	DataArea.w = _w;
	DataArea.h = _h;
	//SDL_RenderFillRect(Renderer, &DataArea);

	SDL_Rect FillAreaH;
	FillAreaH.x = (HomeX);
	FillAreaH.y = (HomeY - BorderRadius);
	FillAreaH.w = (_w);
	FillAreaH.h = (_h + BorderRadius*2);
	SDL_RenderFillRect(Renderer, &FillAreaH);

	SDL_Rect FillAreaW;
	FillAreaW.x = (HomeX - BorderRadius);
	FillAreaW.y = (HomeY);
	FillAreaW.w = (_w + BorderRadius * 2);
	FillAreaW.h = (_h);
	SDL_RenderFillRect(Renderer, &FillAreaW);
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		// Each of the following renders an octant of the circle
		// SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		// SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		// SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		// SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		// SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		// SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		// SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		// SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		SDL_RenderDrawLine(renderer, centreX, centreY, centreX + x, centreY - y);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX + x, centreY + y);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX - x, centreY - y);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX - x, centreY + y);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX + y, centreY - x);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX + y, centreY + x);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX - y, centreY - x);
		SDL_RenderDrawLine(renderer, centreX, centreY, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}