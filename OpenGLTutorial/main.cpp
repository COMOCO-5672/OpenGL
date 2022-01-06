#include "Display.h"
#include <iostream>
#include <thread>

#define SDL_CUSTOM_EVENT (SDL_USEREVENT+1)

int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "frist window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // …Ë÷√‰÷»æ∆˜—’…´
    SDL_RenderClear(renderer);                                  // «Â≥˝render
    SDL_RenderPresent(renderer);                                // ªÊ÷∆render

    std::thread th([]() {
        SDL_Delay(3000);
        SDL_Event event;
        event.type = SDL_CUSTOM_EVENT;
        SDL_PushEvent(&event);
        return 0;
    });

    SDL_Event windowsEvent;
    while (!quit) {
        while (SDL_PollEvent(&windowsEvent)) {
            switch (windowsEvent.type) {
            case  SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                std::cout << "key down event" << std::endl;
                break;;
            case SDL_KEYUP:
                std::cout << "key up event" << std::endl;
                break;
            case SDL_MOUSEBUTTONUP:
                std::cout << "mouse button up event" << std::endl;
                break;
            default:
                std::cout << "event type = " << windowsEvent.type << "come " << std::endl;
                break;
            }
        }
    }

    if (th.joinable()) {
        th.join();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
