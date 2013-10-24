#include <sdl.h>
#include <string>

#include "constante.h"
#include "Fonct_Main.h"
#include "Classe_Timer.h"

#ifndef MISSILE_HPP
#define MISSILE_HPP
class Missile
{
    private:
        int x, y, w, h, xVel, yVel;

        //annimation
        Timer timeFrame;
        int timeFramePast;
        static const int MISSILE_WIDTH = 24;
        static const int MISSILE_HEIGHT = 56;
        static const int MAX_FRAME = 3;
        int frame;
        int speed;
        int status;
        SDL_Rect clipsNormal[6];
        SDL_Surface* surfMissile;

    public:
        //Initializes the variables
        Missile();
        Missile(Missile const& copy);
        ~Missile();

        //Moves
        void move();

        //Show on the screen
        void show(SDL_Surface *screen);

        void newXPosition();

        void reset();

        //accessor
        int getX(){return x;}
        int getY(){return y;}
        int getW(){return w;}
        int getH(){return h;}

        //static
        static int iNewMissiles;
        int getINewMissile(){return iNewMissiles;}
};
#endif
