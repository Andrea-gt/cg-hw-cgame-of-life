#include "Framebuffer.h"
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

int main()
{
    // Call our render function
    Framebuffer framebuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("cg-hw-cgame-of-life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    framebuffer.clear();

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Render a random number of patterns at random positions
    int numPatterns = std::rand() % 196 + 5; // Change the range as desired
    for (int i = 0; i < numPatterns; ++i) {
        int patternType = std::rand() % 2; // 0 for Glider, 1 for LWSS
        int x = std::rand() % WINDOW_WIDTH;
        int y = std::rand() % WINDOW_HEIGHT;

        if (patternType == 0) {
            framebuffer.AddGlider(x, y);
        } else {
            framebuffer.AddLWSS(x, y);
        }
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        framebuffer.render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}