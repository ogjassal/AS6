#include <ctime>        // Time library needed for randomization
#include <cstdlib>     // Standard library for C++ functions
#include "SDL.h"       // Graphics library for C++
#include <SDL_ttf.h>   // TrueType font library
#include <stdio.h>     // Standard input-output library for C

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int scorePlayer;
int scoreComputer;

SDL_Renderer* renderer;
SDL_Event event;
int mouse_x, mouse_y;

//speed variables of white ball in the x and y directions
int whitespeed_x, whitespeed_y;
int direction[2] = { -2,2 };

int redspeed_x, redspeed_y;  // Speed variables for the red ball


//AI Paddle speed
int AIspeed_y = 3;

//controls game loop running for ever
bool running = true;

//all game characters are declared here
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect WhiteBall;
SDL_Rect MiddleLine;
SDL_Rect RedBall;

//font related variables
TTF_Font* font;
SDL_Color color;
char message[100];
SDL_Surface* messageSurface;
SDL_Texture* messageTexture;
SDL_Rect messageRect;

//this function takes any two game characters and returns
//true or false if they overlap (collide)
bool check_collision(SDL_Rect A, SDL_Rect B) {
    int leftA = A.x, rightA = A.x + A.w, topA = A.y, bottomA = A.y + A.h;
    int leftB = B.x, rightB = B.x + B.w, topB = B.y, bottomB = B.y + B.h;
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) { return false; }
    return true;
}

//displays text to the screen
void displayGameStats(int x, int y, char* formattedString, int scoreP, int scoreC) {
    sprintf_s(message, formattedString, scoreP, scoreC);
    messageSurface = TTF_RenderText_Solid(font, message, color);
    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    int texW = 0, texH = 0;
    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
    messageRect = { x, y, texW, texH };
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
    SDL_DestroyTexture(messageTexture);
    SDL_FreeSurface(messageSurface);
}

//initialization code
void LoadGame() {

    //window created
    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { return; }

    //renderer created
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) { return; }

    //white color defined
    color = { 255, 255, 255 };

    // Red color for the red ball
    SDL_Color redColor = { 255, 0, 0 };  
    
    //initial scores of player and computer
    scorePlayer = 0;
    scoreComputer = 0;

    //all game characters are initialized (position and size)
    PlayerPaddle = { 20, 250, 20, 100 };
    AIPaddle = { 760, 250, 20, 300 };

    //white ball starts at 370, 290 and its shape is 20 by 20
    WhiteBall = { 370, 290, 20, 20 };
   
    // Red ball
    RedBall = { 390, 250, 20, 20 };

    //speed of white ball is initially -2 in x and -2 in the y
    whitespeed_x = -2;
    whitespeed_y = -2;

    // Set initial speed for red ball (1.5 times the white ball's speed)
    redspeed_x = whitespeed_x * 1.5;  // 1.5 times the speed of the white ball
    redspeed_y = whitespeed_y * 1.5;  // 1.5 times the speed of the white ball


    AIspeed_y = 1;

    MiddleLine = { 395, 0, 10, WINDOW_HEIGHT };

    //initialize SDL fonts
    TTF_Init();
    font = TTF_OpenFont("lazy.ttf", 25);
}

//event handling 
void Input() {
    while (SDL_PollEvent(&event)) {
        //mouse movement events
        if (event.type == SDL_MOUSEMOTION) 
        { 
            SDL_GetMouseState(&mouse_x, &mouse_y); 
        }
        //quitting game event
        if (event.type == SDL_QUIT) 
        { 
            running = false; 
        }
        //key down event
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
        }
    }
}

void Update() {

    //Player Paddle moves with the vertical y of mouse
    PlayerPaddle.y = mouse_y;

    //White Ball position incremented by speed in each axis
    WhiteBall.x += whitespeed_x;
    WhiteBall.y += whitespeed_y;

    // Red ball movement logic (moving 1.5 times faster than white ball)
    RedBall.x += redspeed_x;  // 1.5 times the speed of the white ball
    RedBall.y += redspeed_y;  // 1.5 times the speed of the white ball



    //code to manage AI paddle speed and make
    //sure it does not go out of bounds
    if (AIPaddle.y < 0) { 
        AIspeed_y = 3; 
    }
    if (AIPaddle.y > WINDOW_HEIGHT - AIPaddle.h) { 
        AIspeed_y = -3; 
    }
    AIPaddle.y += AIspeed_y;


    //computer score increases by 1 when white ball 
    // passes Player Paddle
    if (WhiteBall.x < 0) { 
        scoreComputer += 1; 
    }
    //Player score increases by 1 when white ball
    // passes AI paddle
    if (WhiteBall.x > WINDOW_WIDTH) { 
        scorePlayer += 1; 
    }

    // Red ball scoring logic
    if (RedBall.x < 0) {  // Red ball passed the Player Paddle (left side)
        scoreComputer += 2;  // Give 2 points to the computer
    }
    if (RedBall.x > WINDOW_WIDTH) {  // Red ball passed the AI Paddle (right side)
        scorePlayer += 2;  // Give 2 points to the player
    }

    //if White Ball goes off on either side, it then gets
    //placed in center of screen, with random speed and direction
    if (WhiteBall.x < 0 || WhiteBall.x > WINDOW_WIDTH) {
        WhiteBall.x = WINDOW_WIDTH / 2;
        WhiteBall.y = WINDOW_HEIGHT / 2;
        whitespeed_x = (rand() % 2 + 1) * direction[rand() % 2];
        whitespeed_y = (rand() % 2 + 1) * direction[rand() % 2];
    }

    // Red ball reset if it goes out of bounds
    if (RedBall.x < 0 || RedBall.x > WINDOW_WIDTH) {
        RedBall.x = WINDOW_WIDTH / 2;
        RedBall.y = WINDOW_HEIGHT / 2;
        redspeed_x = (rand() % 2 + 1) * direction[rand() % 2] * 1.5;  // 1.5 times the white ball speed
        redspeed_y = (rand() % 2 + 1) * direction[rand() % 2] * 1.5;  // 1.5 times the white ball speed
    }

    //when white ball hits either paddle it reverves direction
    if (check_collision(WhiteBall, AIPaddle) || check_collision(WhiteBall, PlayerPaddle)) { 
        whitespeed_x = -whitespeed_x; 
    }

    // Check for collisions with paddles (red ball)
    if (check_collision(RedBall, AIPaddle) || check_collision(RedBall, PlayerPaddle)) {
        redspeed_x = -redspeed_x;
    }
    
    //when white ball goes to high or too low it bounces 
    // back in, so never goes off screen (top and bottom)
    if (WhiteBall.y < 0 || WhiteBall.y >(WINDOW_HEIGHT - WhiteBall.h)) { whitespeed_y = -whitespeed_y; }
    
    // Bounce red ball off top and bottom edges
    if (RedBall.y < 0 || RedBall.y >(WINDOW_HEIGHT - RedBall.h)) {
        redspeed_y = -redspeed_y;
    }

    SDL_Delay(10);
}

//render all game obkjects to the window
void DrawScreen() {
    
    SDL_RenderClear(renderer);
    //set black color for window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //background rect, size of window
    SDL_Rect background = { 0, 0, 800, 600 };
    //apply black color to the background object
    SDL_RenderFillRect(renderer, &background);

    //set white color for all game objects that are white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //apply white color to all those objects that need it
    SDL_RenderFillRect(renderer, &PlayerPaddle);
    SDL_RenderFillRect(renderer, &AIPaddle);
    SDL_RenderFillRect(renderer, &WhiteBall);
    SDL_RenderFillRect(renderer, &MiddleLine);

    // Set red color for the red ball
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &RedBall);  // Draw the red ball

    //create score text to display
    char scoreMessage[100] = "             Player %2d                 Computer %2d";
    //display the text
    displayGameStats(10, 10, scoreMessage, scorePlayer, scoreComputer);

    //push all images to the screen.
    //This line must come last otherwise you will not see 
    // what comes after it
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    LoadGame();
    while (running) {
        Input();
        Update();
        DrawScreen();
    }
    SDL_Quit();
    return 0;
}
