#include "input.h"

void handleInput(void) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        SDL_GetWindowSize(game_display.window, &window_width, &window_height);
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window Resized -> w: %d h: %d", window_width, window_height);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) { // Exiting game--
                    if (game_state == PLAYING) game_state = PAUSED;
                    else if (game_state == MAIN_MENU) game_state = EXITING;
                    else if (game_state == PAUSED || game_state == LOADING) game_state = MAIN_MENU;
                }
                else if (game_state == MAIN_MENU || game_state == LOADING) { // Entering game--
                    initializing = SDL_TRUE;
                    game_state++;
                }
                else if (game_state == PAUSED) {
                    game_state = PLAYING;
                } 
                if (game_state == PLAYING) { // During game--
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                            moveEntity(player, 1, -1);
                            break;
                        case SDLK_s:
                            moveEntity(player, 1, 1);
                            break;
                        case SDLK_w:
                            moveEntity(player, -1, -1);
                            break;
                        case SDLK_a:
                            moveEntity(player, -1, 1);
                            break;
                        case SDLK_r:
                            if (!(player->x == 0 && player->y == 0)) {
                                player->x = 0;
                                player->y = 0;
                                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Player position reset to (0, 0)");
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;
            case SDL_QUIT:
                game_state = EXITING;
                break;
            default:
                break;
        }
    }
}
