//#include <ctime>        // Time library needed for randomization
//#include <cstdlib>     // Standard library for C++ functions
//#include "SDL.h"       // Graphics library for C++
//#include <SDL_ttf.h>   // TrueType font library
//#include <stdio.h>     // Standard input-output library for C
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//
//int scorePlayer;
//int scoreComputer;
//
//SDL_Renderer* renderer;
//SDL_Event event;
//int mouse_x, mouse_y;
//
//int speed_x, speed_y;
//int direction[2] = { -2,2 };
//int AIspeed_y = 3;
//bool running = true;
//
//SDL_Rect PlayerPaddle;
//SDL_Rect AIPaddle;
//SDL_Rect Ball;
//SDL_Rect MiddleLine;
//
//// New red ball variables
//SDL_Rect RedBall; // Second ball (red)
//int redSpeed_x, redSpeed_y; // Red ball speed, 1.5x faster than the white ball
//
//TTF_Font* font;
//SDL_Color color;
//char message[100];
//SDL_Surface* messageSurface;
//SDL_Texture* messageTexture;
//SDL_Rect messageRect;
//
//bool check_collision(SDL_Rect A, SDL_Rect B) {
//    int leftA = A.x, rightA = A.x + A.w, topA = A.y, bottomA = A.y + A.h;
//    int leftB = B.x, rightB = B.x + B.w, topB = B.y, bottomB = B.y + B.h;
//    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) { return false; }
//    return true;
//}
//
//void displayGameStats(int x, int y, char* formattedString, int scoreP, int scoreC) {
//    sprintf_s(message, formattedString, scoreP, scoreC);
//    messageSurface = TTF_RenderText_Solid(font, message, color);
//    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
//    int texW = 0, texH = 0;
//    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
//    messageRect = { x, y, texW, texH };
//    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
//    SDL_DestroyTexture(messageTexture);
//    SDL_FreeSurface(messageSurface);
//}
//
//void LoadGame() {
//    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    if (!window) { return; }
//    renderer = SDL_CreateRenderer(window, -1, 0);
//    if (!renderer) { return; }
//
//    color = { 255, 255, 255 };
//    scorePlayer = 0;
//    scoreComputer = 0;
//
//    PlayerPaddle = { 20, 250, 20, 100 };
//    AIPaddle = { 760, 250, 20, 300 };
//    Ball = { 370, 290, 20, 20 };
//    speed_x = -2;
//    speed_y = -2;
//    AIspeed_y = 1;
//    MiddleLine = { 395, 0, 10, WINDOW_HEIGHT };
//
//    // Initialize Red Ball (new)
//    RedBall = { 400, 300, 20, 20 };
//    redSpeed_x = speed_x * 1.5;
//    redSpeed_y = speed_y * 1.5;
//
//    TTF_Init();
//    font = TTF_OpenFont("lazy.ttf", 25);
//}
//
//void Input() {
//    while (SDL_PollEvent(&event)) {
//        if (event.type == SDL_MOUSEMOTION) { SDL_GetMouseState(&mouse_x, &mouse_y); }
//        if (event.type == SDL_QUIT) { running = false; }
//        if (event.type == SDL_KEYDOWN) {
//            switch (event.key.keysym.sym) {
//            case SDLK_ESCAPE:
//                running = false;
//                break;
//            }
//        }
//    }
//}
//
//void Update() {
//    PlayerPaddle.y = mouse_y;
//    Ball.x += speed_x;
//    Ball.y += speed_y;
//
//    // Red Ball Movement (new)
//    RedBall.x += redSpeed_x;
//    RedBall.y += redSpeed_y;
//
//    if (AIPaddle.y < 0) { AIspeed_y = 3; }
//    if (AIPaddle.y > WINDOW_HEIGHT - AIPaddle.h) { AIspeed_y = -3; }
//    AIPaddle.y += AIspeed_y;
//
//    if (Ball.x < 0) { scoreComputer += 1; }
//    if (Ball.x > WINDOW_WIDTH) { scorePlayer += 1; }
//    if (RedBall.x < 0) { scoreComputer += 2; } // Red ball scoring (new)
//    if (RedBall.x > WINDOW_WIDTH) { scorePlayer += 2; }
//
//    if (Ball.x < 0 || Ball.x > WINDOW_WIDTH) {
//        Ball.x = WINDOW_WIDTH / 2;
//        Ball.y = WINDOW_HEIGHT / 2;
//        speed_x = (rand() % 2 + 1) * direction[rand() % 2];
//        speed_y = (rand() % 2 + 1) * direction[rand() % 2];
//    }
//
//    if (RedBall.x < 0 || RedBall.x > WINDOW_WIDTH) { // Reset red ball (new)
//        RedBall.x = WINDOW_WIDTH / 2;
//        RedBall.y = WINDOW_HEIGHT / 2;
//        redSpeed_x = speed_x * 1.5;
//        redSpeed_y = speed_y * 1.5;
//    }
//
//    if (check_collision(Ball, AIPaddle) || check_collision(Ball, PlayerPaddle)) { speed_x = -speed_x; }
//    if (check_collision(RedBall, AIPaddle) || check_collision(RedBall, PlayerPaddle)) { redSpeed_x = -redSpeed_x; }
//
//    if (Ball.y < 0 || Ball.y >(WINDOW_HEIGHT - Ball.h)) { speed_y = -speed_y; }
//    if (RedBall.y < 0 || RedBall.y >(WINDOW_HEIGHT - RedBall.h)) { redSpeed_y = -redSpeed_y; }
//
//    SDL_Delay(10);
//}
//
//void DrawScreen() {
//    SDL_RenderClear(renderer);
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_Rect background = { 0, 0, 800, 600 };
//    SDL_RenderFillRect(renderer, &background);
//
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//    SDL_RenderFillRect(renderer, &PlayerPaddle);
//    SDL_RenderFillRect(renderer, &AIPaddle);
//    SDL_RenderFillRect(renderer, &Ball);
//    SDL_RenderFillRect(renderer, &MiddleLine);
//
//    // Draw Red Ball (new)
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    SDL_RenderFillRect(renderer, &RedBall);
//
//    char scoreMessage[100] = "             Player %2d                 Computer %2d";
//    displayGameStats(10, 10, scoreMessage, scorePlayer, scoreComputer);
//
//    SDL_RenderPresent(renderer);
//}
//
//int main(int argc, char* argv[]) {
//    LoadGame();
//    while (running) {
//        Input();
//        Update();
//        DrawScreen();
//    }
//    SDL_Quit();
//    return 0;
//}
