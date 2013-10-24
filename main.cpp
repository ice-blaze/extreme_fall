#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

#include <sdl/SDL.h>

#include "Fonct_Main.h"
#include "Classe_Timer.h"
#include "Char.h"

int iScore=0;//accessible de partout
#include "Missile.hpp"

using namespace std;

void addMissile(vector<Missile*> &_listMissile);
void removeMissile(vector<Missile*> &_listMissile);

int main ( int argc, char** argv )
{
    //il faudrait le mettre dans la fonction main !!!
    srand(time(NULL));

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(800, 400, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* surfBeam = load_image("sprite/red_beam.png");
    SDL_Surface* surfBack1 = load_image("sprite/sky.png");
    SDL_Surface* surfBack2 = load_image("sprite/city.png");

    Character myChar("sprite/hero.png");

    vector<Missile*> listMissile;

//    addMissile(listMissile);
//    addMissile(listMissile);

    apply_surface(0,0,surfBeam,screen,NULL);

    SDL_WM_SetCaption("ESC to quite | SPACE add missile | Q delete missile | ARROWS to move", NULL);

    int beam1y=0;
    int back1y=0;

    int beamHigh = surfBeam->h;

    // program main loop
    bool done = false;
    bool loose = false;

    Timer time;
    int iPastTimeBeam=0;
    int iPastTimeBack=0;
    int iPastTimeChar=0;
    time.start();

    Timer fps;
    while (!done)
    {
        printf("%d\n",Missile::iNewMissiles);

        fps.start();
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            myChar.handle_input(event);

            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keypresses
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    else if(event.key.keysym.sym == SDLK_SPACE)
                        addMissile(listMissile);
                    else if(event.key.keysym.sym == SDLK_q)
                        removeMissile(listMissile);
                    break;

            } // end switch
        } // end of message processing

        if(time.get_ticks()-iPastTimeChar>40)
        {
            iPastTimeChar=time.get_ticks();
            myChar.move();

            for(vector<Missile>::size_type i=0;i<listMissile.size();i++)
            {
                if(collision(myChar.getX(),myChar.getY(),myChar.getW(),myChar.getH(),
                   listMissile[i]->getX(),listMissile[i]->getY(),listMissile[i]->getW(),listMissile[i]->getH()))
                {
                    loose=true;
                }
            }

            //recheck s'il y a une collision entre les missiles
            if(time.do_action(0,1))
            {
                for(vector<Missile>::size_type i=0;i<listMissile.size();i++)
                {
                    for(vector<Missile>::size_type j=i+1;j<listMissile.size();j++)
                    {
                        while(collisionX(listMissile[i]->getX(),listMissile[i]->getW(),listMissile[j]->getX(),listMissile[j]->getW()))
                        {
                            //change le missile qui est le plus proche du bord de l'écran
                            //comme ça on ne voit pas le changement sur l'espace de jeu
                            if(listMissile[j]->getY()>listMissile[i]->getY())
                                listMissile[j]->newXPosition();
                            else
                                listMissile[i]->newXPosition();
                        }
                    }
                }
            }
            //bouge les missiles
            for(vector<Missile>::size_type i=0;i<listMissile.size();i++)
            {
                listMissile[i]->move();
            }
        }

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        //fonds
        apply_surface(0,back1y,surfBack1,screen,NULL);
        apply_surface(0,back1y+600,surfBack2,screen,NULL);

        //gauche
        //beam 1
        apply_surface(0,beam1y,surfBeam,screen,NULL);
        //beam2
        apply_surface(0,beam1y+beamHigh,surfBeam,screen,NULL);

        //droite
        //beam 1
        apply_surface(750,beam1y,surfBeam,screen,NULL);
        //beam2
        apply_surface(750,beam1y+beamHigh,surfBeam,screen,NULL);

        //show character
        myChar.show(screen);

        for(vector<Missile>::size_type i=0;i<listMissile.size();i++)
        {
            listMissile[i]->show(screen);
        }

        SDL_Flip(screen);

        if(time.get_ticks()-iPastTimeBeam>2)
        {
            iPastTimeBeam=time.get_ticks();
            //changement des positions
            if(beam1y+beamHigh<0)
            {
                beam1y=0;
            }
            else
            {
                beam1y--;
            }
        }
        if(time.get_ticks()-iPastTimeBack>100)
        {
            if(back1y<-800)
            {
                loose=true;
            }
            iPastTimeBack=time.get_ticks();
            back1y--;
        }
        //il y a eu une colision de fin de partie alors on relance le jeu
        if(loose)
        {
            for(vector<Missile>::size_type i=0;i<listMissile.capacity();i++)
            {
                removeMissile(listMissile);
            }
            myChar.reset();
            addMissile(listMissile);

            for(double i=0;i<10000000;i+=0.01)
                i+=0.1;
            loose=false;
        }
    }

    // free loaded bitmap
    SDL_FreeSurface(surfBeam);
    SDL_FreeSurface(surfBack1);
    SDL_FreeSurface(surfBack2);
    listMissile.clear();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

void addMissile(vector<Missile*> &_listMissile)
{
    Missile *newMissile = new Missile;
    _listMissile.push_back(newMissile);
}

void removeMissile(vector<Missile*> &_listMissile)
{
    if(_listMissile.size()>0)
    {
        delete _listMissile.back();
        _listMissile.pop_back();
    }
}
