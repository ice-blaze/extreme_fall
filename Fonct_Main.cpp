#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Fonct_Main.h"

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip=NULL)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image a bien chargée
    if( loadedImage != NULL )
    {
        //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la surface a bien été optimisée
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //On retourne l'image optimisée
    return optimizedImage;
}

Uint32 get_pixel32( int x, int y, SDL_Surface *surface )
{
    //Convertie les pixels en 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Recupere le pixel demande
    return pixels[ ( y * surface->w ) + x ];
}

int MyRand(int a, int b){
    return rand()%(b-a) +a;
}

int collision (int x1,int y1, int w1, int h1,
               int x2, int y2, int w2, int h2)
{
    if(x1>x2+w2
       ||x1+w1<x2
       ||y1>y2+h2
       ||y1+h1<y2)
       {
           return false;
       }
       else
       {
           return true;
       }
}

bool collisionX (int x1, int w1, int x2, int w2)
{
    if(x1>x2+w2
       ||x2>x1+w1)
       {
           return false;
       }
       else
       {
           return true;
       }
}

void SDL_Exit(std::string errorMessage)
{
	printf(errorMessage.c_str());
	//SDL_Quit(); libéré la mémoire avant
}


