#include "Graphics.h"

SDL_Window* Graphics::window;
SDL_Renderer* Graphics::renderer;
TTF_Font* Graphics::font;

bool Graphics::Init()
{
	// create little window with minimize and x to close 
	window = SDL_CreateWindow("Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		return false;
	}

	// fill in that window with a virtual canvas to draw on called a renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		return false;
	}

	TTF_Init();

	font = TTF_OpenFont("arialbd.ttf", 24);

	return true;
}

void Graphics::StartRender()
{
}

void Graphics::SetColor(Colour color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
}

void Graphics::DrawRect(Transform2D transform, Vec2D dimensions, bool isFilled)
{
	SDL_Rect Bounds;
	Bounds.x = transform.position.x;
	Bounds.y = transform.position.y;
	Bounds.w = dimensions.x;
	Bounds.h = dimensions.y;

	if (isFilled)
	{
		SDL_RenderFillRect(renderer, &Bounds);
	}
	else
	{
		SDL_RenderDrawRect(renderer, &Bounds);
	}
}

void Graphics::DrawCircle(Transform2D transform, float radius, float lineThickness, int precision, bool filled)
{
	// this function essentially draws a whole bunch of lines around a central point to form our circle.
	const double ANGLE_OFF = 2.0 * M_PI / precision;

	for (int i = 0; i < precision; i++)
	{
		double angle1 = ANGLE_OFF * i;
		double angle2 = ANGLE_OFF * (i + lineThickness * 10);
		int x1 = transform.position.x + (int)(radius * cos(angle1));
		int y1 = transform.position.y + (int)(radius * sin(angle1));
		int x2 = transform.position.x + (int)(radius * cos(angle2));
		int y2 = transform.position.y + (int)(radius * sin(angle2));

		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		if (filled)
		{
			SDL_RenderDrawLine(renderer, x1, y1, transform.position.x, transform.position.y);
		}
	}
}

void Graphics::DrawLine(Transform2D transform, Vec2D dimensions)
{
	SDL_Rect Bounds;
	Bounds.x = transform.position.x;
	Bounds.y = transform.position.y;
	Bounds.w = dimensions.x;
	Bounds.h = dimensions.y;

	SDL_RenderDrawLine(renderer, transform.position.x, transform.position.y, dimensions.x, dimensions.y);
}

void Graphics::EndRender()
{
}

// example based on the code from: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void Graphics::DrawText(const char* text, float x, float y, int width, int height)
{
	DrawText(text, x, y, width, height, 255, 0, 0);
}

void Graphics::DrawText(const char* text, float x, float y, int width, int height, int r, int g, int b)
{
	SDL_Color color = { r, g, b };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = width;
	Message_rect.h = height;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Graphics::Shutdown()
{
}