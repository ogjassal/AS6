#pragma once

#include "SDL.h"
#include "../Source/Objects/ObjData.h"
#include <SDL_ttf.h>

class Graphics
{
public:
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;
	// should be called only once on boot.
	static bool Init();

	// needs to be called once at the start and end of game loops rendering
	static void StartRender();
	static void EndRender();

	static void Shutdown();

	//drawing specific functions
	static void SetColor(Colour color);
	static void DrawCircle(Transform2D transform, float radius, float lineThickness = 1.0f, int precision = 100, bool isFilled = false);
	static void DrawRect(Transform2D transform, Vec2D dimensions, bool isFilled = false);
	static void DrawLine(Transform2D transform, Vec2D dimensions);
	static void DrawText(const char* text, float x, float y, int width, int height);
	static void DrawText(const char* text, float x, float y, int width, int height, int r, int g, int b);
private:
	// some SDL specific variables:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static TTF_Font* font;
};

