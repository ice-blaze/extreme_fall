#include <sdl.h>
#include <string>

#include "constante.h"
#include "Fonct_Main.h"
#include "Classe_Timer.h"

#ifndef CLASSE_CHAR_H
#define CLASSE_CHAR_H

class Character
{
    private:
    //The X and Y offsets
    int x, y;
    int w, h;

    //The velocity
    int xVel, yVel;

    bool upPress,downPress,leftPress,rightPress;
    int upVel,downVel,leftVel,rightVel;

    //lorsqu'il est à l'arrêt le vent le fait un peu zigzager
    int snake;

    static const int MAX_SPEED=25;

    //annimation
    Timer timeFrame;
    int timeFramePast;
    static const int CHAR_WIDTH = 64;
    static const int CHAR_HEIGHT = 64;
    static const int CHAR_FALL = 1;
    static const int CHAR_NORMAL = 0;
    int frame;
    int status;
    SDL_Rect clipsNormal[6];
    SDL_Rect clipsFall[6];

    SDL_Surface* myChar;

    public:
    //Initializes the variables
    Character(std::string filename);

    //Takes key presses and adjusts the velocity
    void handle_input(SDL_Event &event);

    //Moves
    void move();

    //Show on the screen
    void show(SDL_Surface *screen);

    //reset for the end game
    void reset();

    //accessor
    int getX(){return x;}
    int getY(){return y;}
    int getW(){return w;}
    int getH(){return h;}
};
#endif
