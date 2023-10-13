// Framebuffer.h
#pragma once

#include <vector>
#include <string> // Add this line to include <string>
#include <fstream> // Add this line to include <fstream>
#include "ColorRGB.h"
#include "Vertex2.h"
#include <SDL2/SDL.h>

class Framebuffer {
public:
    Framebuffer(int width, int height);
    void clear();
    void setCurrentColor(ColorRGB myColor);
    void point(Vertex2 myVertex);
    void renderBuffer(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void CLife();
    void AddGlider(int x, int y);
    void AddLWSS(int x, int y);

private:
    int width;
    int height;
    std::vector<ColorRGB> framebuffer;
    ColorRGB clearColor;
    ColorRGB currentColor;
};