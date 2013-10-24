#include <stdlib.h>
#include <stdio.h>
#include <sdl/SDL.h>
#include <SDL_image.h>
#include <string>

#ifndef FONCT_MAIN_H
#define FONCT_MAIN_H

struct Clips
{
    int x,y,w,h;
};

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
SDL_Surface *load_image( std::string filename );
Uint32 get_pixel32( int x, int y, SDL_Surface *surface );
int MyRand(int a, int b);
int collision (int x1,int y1, int w1, int h1,
               int x2, int y2, int w2, int h2);
bool collisionX (int x1, int w1, int x2, int w2);
void SDL_Exit(std::string errorMessage);

#endif
