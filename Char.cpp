#include "Char.h"
#include <iostream>

Character::Character(std::string filename)
{
    reset();

    snake=5;

    //surface
    myChar = load_image(filename);
    //width/height of the surface
    w=64;//myChar->w;
    h=64;//myChar->h;

    //annimation initialisation
    timeFrame.start();
    timeFramePast=0;
    //Clip the sprites
    clipsNormal[ 0 ].x = 0;
    clipsNormal[ 0 ].y = 0;
    clipsNormal[ 0 ].w = CHAR_WIDTH;
    clipsNormal[ 0 ].h = CHAR_HEIGHT;

    clipsNormal[ 1 ].x = CHAR_WIDTH;
    clipsNormal[ 1 ].y = 0;
    clipsNormal[ 1 ].w = CHAR_WIDTH;
    clipsNormal[ 1 ].h = CHAR_HEIGHT;

    clipsNormal[ 2 ].x = CHAR_WIDTH*2;
    clipsNormal[ 2 ].y = 0;
    clipsNormal[ 2 ].w = CHAR_WIDTH;
    clipsNormal[ 2 ].h = CHAR_HEIGHT;

    clipsNormal[ 3 ].x = CHAR_WIDTH*3;
    clipsNormal[ 3 ].y = 0;
    clipsNormal[ 3 ].w = CHAR_WIDTH;
    clipsNormal[ 3 ].h = CHAR_HEIGHT;

    clipsNormal[ 4 ].x = CHAR_WIDTH*4;
    clipsNormal[ 4 ].y = 0;
    clipsNormal[ 4 ].w = CHAR_WIDTH;
    clipsNormal[ 4 ].h = CHAR_HEIGHT;

    clipsNormal[ 5 ].x = CHAR_WIDTH*5;
    clipsNormal[ 5 ].y = 0;
    clipsNormal[ 5 ].w = CHAR_WIDTH;
    clipsNormal[ 5 ].h = CHAR_HEIGHT;

    //annimation descend
    clipsFall[ 0 ].x = 0;
    clipsFall[ 0 ].y = CHAR_HEIGHT;
    clipsFall[ 0 ].w = CHAR_WIDTH;
    clipsFall[ 0 ].h = CHAR_HEIGHT;

    clipsFall[ 1 ].x = CHAR_WIDTH;
    clipsFall[ 1 ].y = CHAR_HEIGHT;
    clipsFall[ 1 ].w = CHAR_WIDTH;
    clipsFall[ 1 ].h = CHAR_HEIGHT;

    clipsFall[ 2 ].x = CHAR_WIDTH*2;
    clipsFall[ 2 ].y = CHAR_HEIGHT;
    clipsFall[ 2 ].w = CHAR_WIDTH;
    clipsFall[ 2 ].h = CHAR_HEIGHT;

    clipsFall[ 3 ].x = CHAR_WIDTH*3;
    clipsFall[ 3 ].y = CHAR_HEIGHT;
    clipsFall[ 3 ].w = CHAR_WIDTH;
    clipsFall[ 3 ].h = CHAR_HEIGHT;

    clipsFall[ 4 ].x = CHAR_WIDTH*4;
    clipsFall[ 4 ].y = CHAR_HEIGHT;
    clipsFall[ 4 ].w = CHAR_WIDTH;
    clipsFall[ 4 ].h = CHAR_HEIGHT;

    clipsFall[ 5 ].x = CHAR_WIDTH*5;
    clipsFall[ 5 ].y = CHAR_HEIGHT;
    clipsFall[ 5 ].w = CHAR_WIDTH;
    clipsFall[ 5 ].h = CHAR_HEIGHT;

    frame = 0;
    status = CHAR_NORMAL;


}

void Character::handle_input(SDL_Event &event)
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {

            case SDLK_UP:

                upPress=true;
                break;

            case SDLK_DOWN:

                downPress=true;
                break;

            case SDLK_LEFT:

                leftPress=true;
                break;

            case SDLK_RIGHT:

                rightPress=true;
                break;

            default:
                break;
        }
    }
      //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                upPress=false;
                break;

            case SDLK_DOWN:
                downPress=false;
                break;

            case SDLK_LEFT:
                leftPress=false;
                break;

            case SDLK_RIGHT:
                rightPress=false;
                break;

            default:
                break;
        }
    }
}

void Character::move()
{
    if(upPress)
    {
        if(upVel<MAX_SPEED)
            upVel++;
    }
    else
    {
        if(upVel>0)
            upVel--;
    }

    if(downPress)
    {
        if(downVel<MAX_SPEED)
            downVel++;
    }
    else
    {
        if(downVel>0)
            downVel--;
    }

    if(leftPress)
    {
        if(leftVel<MAX_SPEED)
            leftVel++;
    }
    else
    {
        if(leftVel>0)
            leftVel--;
    }

    if(rightPress)
    {
        if(rightVel<MAX_SPEED)
            rightVel++;
    }
    else
    {
        if(rightVel>0)
            rightVel--;
    }

    //résistance vent
    if(y>0)
    {
        //gestion de l'accélération
        y-=2;

        if(x<=0)
            snake=-15;
        if(x+CHAR_WIDTH>=WIDTH_SCREEN)
            snake=15;

        if(snake>0)
        {
            snake--;
            x--;
            if(snake==1)
            {
                snake=-15;
            }
        }
        else if(snake<0)
        {
            snake++;
            x++;
            if(snake==-1)
            {
                snake=15;
            }
        }
    }
    else if(y<0)
    {
        y=0;
    }

    //Move the dot left or right
    xVel = rightVel-leftVel;
    x += xVel;

    //If the dot went too far to the left or right
    if(x<0)
        x=0;
    else if(x>WIDTH_SCREEN-CHAR_WIDTH)
        x=WIDTH_SCREEN-CHAR_WIDTH;

    //Move the dot up or down
    yVel = downVel-upVel;
    y += yVel;

    //If the dot went too far up or down
    if(y<0)
        y=0;
    else if(y>HEIGHT_SCREEN-CHAR_WIDTH)
        y=HEIGHT_SCREEN-CHAR_WIDTH;
}

void Character::show(SDL_Surface *screen)
{
    if(timeFrame.get_ticks()-timeFramePast>100)
    {
        timeFramePast=timeFrame.get_ticks();

        if( xVel<0)//vers la gauche
        {
            status=CHAR_NORMAL;
        }
        else if(xVel>0)//vers la droite
        {
            status=CHAR_NORMAL;
        }
        else if(yVel<0)//vers le haut
        {
            status=CHAR_NORMAL;
        }
        else if(yVel>0)//vers le bas
        {
            status=CHAR_FALL;
        }
        else if (yVel==0)
        {
            status=CHAR_NORMAL;
        }


        frame++;

        if( frame >= 6 )
            frame = 0;
    }

    //Show the dot
    if(status==CHAR_NORMAL)
        apply_surface( x, y, myChar, screen,&clipsNormal[frame]);
    else if (status==CHAR_FALL)
        apply_surface( x, y, myChar, screen,&clipsFall[frame]);
}

void Character::reset()
{
    //Initialize the offsets
    x = 0;
    y = 0;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;

    upPress=downPress=leftPress=rightPress=false;
    upVel=downVel=leftVel=rightVel=false;
}
