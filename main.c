#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<stdlib.h>

int isInside(int x, int y, SDL_Rect rect) {
    return (x > rect.x) && (x < rect.x + rect.w) &&
           (y > rect.y) && (y < rect.y + rect.h);
}

void renderText(SDL_Renderer *renderer, const char *text, int x, int y, TTF_Font *font, SDL_Color color){
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dsRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dsRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void resetGame(char current_squares[3][3], char squareState[9], int *count, int *empty_spaces, int *running) {
    for (int i = 0; i < 9; i++) {
        squareState[i] = 'N';
        int row = i / 3;
        int col = i % 3;
        current_squares[row][col] = 'N';
    }
    *count = 0;
    *empty_spaces = 9;
    *running = 1;
}

void CheckWin(char current_squares[3][3], int empty_spaces, int *showRestart) {
    for(int row = 0; row < 3; row++) {
        if(current_squares[row][0] != 'N' && current_squares[row][1] == current_squares[row][0] && current_squares[row][2] == current_squares[row][0]) {
            printf("Win Horizontal side\n");
            *showRestart = 1;
        }
    }

    for(int col = 0; col < 3; col++) {
        if(current_squares[0][col] != 'N' && current_squares[1][col] == current_squares[0][col] && current_squares[2][col] == current_squares[0][col]) {
            printf("Win Vertical side\n");           
            *showRestart = 1;
        }
    }

    if(current_squares[0][0] != 'N' && current_squares[1][1] == current_squares[0][0] && current_squares[2][2] == current_squares[0][0]) {
        printf("Win Diagonal 1\n");        
        *showRestart = 1;
    }

    if(current_squares[0][2] != 'N' && current_squares[1][1] == current_squares[0][2] && current_squares[2][0] == current_squares[0][2]) {
        printf("Win Diagonal 2\n");
        *showRestart = 1;
    }

    if(empty_spaces <= 0 && *running) {
        printf("Tie\n");
        *showRestart = 1;
    }
}

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error\n");
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Error\n");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("Error\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Color textColor = {0, 0, 0};

    SDL_Rect squares[9];
    int square_size = 100;
    int margin = 20;

    for (int row = 0; row < 3; row++){
        for(int col = 0; col < 3; col++){
            int index = row * 3 + col;
            squares[index].x = 100 + col * (square_size + margin);
            squares[index].y = 100 + row * (square_size + margin);
            squares[index].w = square_size;
            squares[index].h = square_size;
        }
    }

    SDL_Rect restartButton = {250, 400, 140, 40};
    int count = 0;
    int running = 1;
    int showRestart = 0;

    SDL_Event event;
    char squareState[9];
    char current_state[3][3];

    resetGame(current_state, squareState, &count, &running, &running);

    int empty_spaces = 9;

    while (running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 178, 190, 181, 255);
        for (int i = 0; i < 9; i++) {
            SDL_RenderFillRect(renderer, &squares[i]);
            if (squareState[i] == 'X') {
                renderText(renderer, "X", squares[i].x + square_size / 4, squares[i].y, font, textColor);
            } else if (squareState[i] == 'O') {
                renderText(renderer, "O", squares[i].x + square_size / 4, squares[i].y, font, textColor);
            }
        }

        if (showRestart) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 250, 255);
            SDL_RenderFillRect(renderer, &restartButton);
            renderText(renderer, "Restart", restartButton.x + 20, restartButton.y + 10, font, textColor);
        } else {
            if (count % 2 == 0) {
                renderText(renderer, "Player 1 turn", 250, 50, font, textColor);
            } else {
                renderText(renderer, "Player 2 turn", 250, 50, font, textColor);
            }
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (showRestart && isInside(x, y, restartButton)) {
                    resetGame(current_state, squareState, &count, &empty_spaces, &running);
                    showRestart = 0;
                    break;
                }

                for (int i = 0; i < 9; i++) {
                    if (isInside(x, y, squares[i]) && squareState[i] == 'N' && !showRestart) {
                        count++;
                        empty_spaces--;
                        if (count % 2 != 0) {
                            squareState[i] = 'X';
                        } else {
                            squareState[i] = 'O';
                        }

                        int row = i / 3;
                        int col = i % 3;
                        current_state[row][col] = squareState[i];
                    }
                }

                CheckWin(current_state, empty_spaces, &showRestart);
            }
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}