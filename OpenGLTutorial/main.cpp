#define _CRT_SECURE_NO_WARNINGS
#include "Display.h"
#include <iostream>
#include <thread>

#define SDL_CUSTOM_EVENT (SDL_USEREVENT+1)

#define REFRESH_EVENT  (SDL_USEREVENT + 1)

static int gTimeExit;

int refreshTimer(void *pArg)
{

    gTimeExit = 0;

    while (!gTimeExit) {
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(40);
    }

    gTimeExit = 0;

    return 0;
}


void yuvPlayer(const char *fileName, int videoWidth, int videoHeight)
{
    SDL_Window *pSDLWindow = NULL;
    SDL_Renderer *pSDLRender = NULL;
    SDL_Event SDLEvent;
    SDL_Texture *pSDLTexture = NULL;
    SDL_Rect SDLRect;
    SDL_Thread *pSDLThread;
    FILE *pFile = NULL;
    int quit = 0;
    int frameLen;
    int readLen;
    unsigned char *pBuf = NULL;

    frameLen = videoWidth * videoHeight * 3 / 2; /* 一帧数据的大小 */

    pBuf = static_cast<unsigned char*>(malloc(frameLen));
    if (!pBuf) {
        printf("malloc error!\n");
        goto end;
    }


    SDL_Init(SDL_INIT_VIDEO);

    pSDLWindow = SDL_CreateWindow("YUV Player", 0, 0, videoWidth, videoHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!pSDLWindow) {
        printf("SDL_CreateWindow error!\n");
        goto end;
    }

    pSDLRender = SDL_CreateRenderer(pSDLWindow, -1, 0);
    if (!pSDLRender) {
        printf("SDL_CreateRenderer error!\n");
        goto end;
    }

    /* 创建纹理     */
    pSDLTexture = SDL_CreateTexture(pSDLRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, videoWidth, videoHeight);
    if (!pSDLTexture) {
        printf("SDL_CreateTexture error!\n");
        goto end;
    }

    pFile = fopen(fileName, "r");
    if (!pFile) {
        printf("fopen error!\n");
        goto end;
    }

    SDL_SetRenderDrawColor(pSDLRender, 0, 255, 0, 255);

    SDL_RenderClear(pSDLRender);

    SDL_RenderPresent(pSDLRender);

    /* 创建一个线程 */
    pSDLThread = SDL_CreateThread(refreshTimer, "timer", NULL);

    while (!quit) {
        SDL_WaitEvent(&SDLEvent);

        switch (SDLEvent.type) {
        case SDL_QUIT:
            printf("quit!\n");
            gTimeExit = 1;
            quit = 1;
            break;

        case REFRESH_EVENT:
            /* 以下是显示图像 */
            readLen = fread(pBuf, 1, frameLen, pFile);
            if (readLen <= 0) {
                printf("fread error!\n");
                goto end;
            }

            SDL_UpdateTexture(pSDLTexture, NULL, pBuf, videoWidth);
            SDL_RenderClear(pSDLRender);
            SDL_RenderCopy(pSDLRender, pSDLTexture, NULL, NULL);
            SDL_RenderPresent(pSDLRender);
            //SDL_GetWindowSize(pSDLWindow, &videoWidth, &videoHeight); /* 获取窗口的宽度和高度 */
            break;

        default:

            break;
        }

    }

end:
    if (pBuf)
        free(pBuf);

    if (pSDLRender)
        SDL_DestroyRenderer(pSDLRender);

    if (pSDLWindow)
        SDL_DestroyWindow(pSDLWindow);

    SDL_Quit();

}

int main(int argc, char *argv[])
{
    char *fileName = NULL;
    int videoWidth, videoHeight;

    if (argc != 4) {
        printf("Usage: %s <file name> <video width> <video height>\n", argv[0]);
        return -1;
    }

    fileName = argv[1];
    videoWidth = atoi(argv[2]);
    videoHeight = atoi(argv[3]);

    printf("video :%s, video width:%d ,video height:%d \n", fileName, videoWidth, videoHeight);

    yuvPlayer(fileName, videoWidth, videoHeight);

    return 0;
}


/*
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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // 设置渲染器颜色
    SDL_RenderClear(renderer);                                  // 清除render
    SDL_RenderPresent(renderer);                                // 绘制render

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
*/