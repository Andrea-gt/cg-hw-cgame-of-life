// Framebuffer.cpp
#include "Framebuffer.h"
#include <cmath>
#include <vector>

Framebuffer::Framebuffer(int width, int height) : width(width), height(height), framebuffer(width * height) {
    clearColor = ColorRGB(0, 0, 0);
    currentColor = ColorRGB(255, 255, 255);
}

void Framebuffer::clear() {
    for (size_t i = 0; i < framebuffer.size(); ++i) {
        framebuffer[i] = clearColor;
    }
}

void Framebuffer::setCurrentColor(ColorRGB myColor) {
    currentColor = myColor;
}

void Framebuffer::point(Vertex2 myVertex) {
    if (myVertex.x >= 0 && myVertex.x < width && myVertex.y >= 0 && myVertex.y < height) {
        framebuffer[(width * myVertex.y) + myVertex.x] = currentColor;
    }
}

void Framebuffer::CLife() {
    // Create a copy of the framebuffer to store the next generation of pixels
    std::vector<ColorRGB> nextGeneration = framebuffer;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int liveNeighbors = 0;

            // Check the 8 neighboring pixels
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) {
                        // Skip the current pixel
                        continue;
                    }

                    int nx = x + dx;
                    int ny = y + dy;

                    // Check if the neighboring pixel is within bounds
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        if (framebuffer[ny * width + nx].r == currentColor.r) {
                            liveNeighbors++;
                        }
                    }
                }
            }

            // Apply Conway's Game of Life rules
            if (framebuffer[y * width + x].r == currentColor.r) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    // Rule 1 and Rule 3: Fewer than 2 or more than 3 live neighbors
                    nextGeneration[y * width + x] = clearColor;
                }
                // Rule 2: 2 or 3 live neighbors (no change)
            } else {
                if (liveNeighbors == 3) {
                    // Rule 4: Exactly 3 live neighbors for a dead cell
                    nextGeneration[y * width + x] = currentColor;
                }
                // Dead cells with other than 3 live neighbors remain dead (no change)
            }
        }
    }

    // Update the framebuffer with the next generation
    framebuffer = nextGeneration;
}

void Framebuffer::AddGlider(int x, int y) {
    // Check if the specified position (x, y) is within the framebuffer bounds
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Define a larger glider pattern
        std::vector<std::pair<int, int>> glider = {
                {0, 0},
                {1, 0},
                {2, 0},
                {0, 1},
                {3, 1},
                {0, 2},
                {1, 3},
                {2, 4}
        };

        // Set the pixels in the framebuffer to match the glider pattern
        for (const auto& cell : glider) {
            int nx = x + cell.first;
            int ny = y + cell.second;

            // Check if the new position is within bounds
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                framebuffer[ny * width + nx] = currentColor;
            }
        }
    }
}

void Framebuffer::AddLWSS(int x, int y) {
    // Check if the specified position (x, y) is within the framebuffer bounds
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Define a larger LWSS pattern
        std::vector<std::pair<int, int>> lwss = {
                {0, 0},
                {1, 0},
                {2, 0},
                {3, 0},
                {0, 1},
                {4, 1},
                {4, 2},
                {4, 3},
                {3, 4},
                {0, 3},
                {1, 4},
                {2, 4},
                {3, 4},
                {1, 5},
                {2, 6},
                {3, 7},
                {1, 8},
                {0, 9},
                {1, 9}
        };

        // Set the pixels in the framebuffer to match the LWSS pattern
        for (const auto& cell : lwss) {
            int nx = x + cell.first;
            int ny = y + cell.second;

            // Check if the new position is within bounds
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                framebuffer[ny * width + nx] = currentColor;
            }
        }
    }
}

void Framebuffer::renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
            texture,
            NULL,
            framebuffer.data(),
            width * sizeof(ColorRGB)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void Framebuffer::render(SDL_Renderer* renderer) {
    // Call CLife function to update the framebuffer based on Conway's Game of Life rules
    CLife();
    // Render the framebuffer to the screen
    renderBuffer(renderer);
};