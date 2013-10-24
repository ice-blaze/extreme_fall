#include "Missile.hpp"

int Missile::iNewMissiles=0;

Missile::Missile()
{
    //Initialize the offsets
    newXPosition();
    y = HEIGHT_SCREEN+MISSILE_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    speed=10;
    yVel = -MyRand(speed-8,speed);

    w=MISSILE_WIDTH;
    h=MISSILE_HEIGHT;

    surfMissile = load_image("sprite/missile.png");

    //annimation initialisation
    timeFrame.start();
    timeFramePast=0;
    //Clip the sprites

    for (int i = 0;i<=MAX_FRAME;i++)
    {
    	clipsNormal[ i ].x = i*MISSILE_WIDTH;
        clipsNormal[ i ].y = 0;
        clipsNormal[ i ].w = MISSILE_WIDTH;
        clipsNormal[ i ].h = MISSILE_HEIGHT;
    }

    frame = 0;
    status = 0;
}

Missile::Missile(Missile const& copy)
{
    //Initialize the offsets
    newXPosition();
    y = HEIGHT_SCREEN+MISSILE_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    speed=10;
    yVel = -MyRand(speed-8,speed);

    w=MISSILE_WIDTH;
    h=MISSILE_HEIGHT;

    surfMissile = load_image("sprite/missile.png");

    //annimation initialisation
    timeFrame.start();
    timeFramePast=0;
    //Clip the sprites

    for (int i = 0;i<=MAX_FRAME;i++)
    {
    	clipsNormal[ i ].x = i*MISSILE_WIDTH;
        clipsNormal[ i ].y = 0;
        clipsNormal[ i ].w = MISSILE_WIDTH;
        clipsNormal[ i ].h = MISSILE_HEIGHT;
    }

    frame = 0;
    status = 0;
}

Missile::~Missile()
{
    SDL_FreeSurface(surfMissile);
}

void Missile::move()
{
    //Move the dot left or right
    x += xVel;

    //If the dot went too far to the left or right
    //if( ( x < 0 ) || ( x + MISSILE_WIDTH > SCREEN_WIDTH ) )
    {
        //move back
        x -= xVel;
    }

    //Move the dot up or down
    y += yVel;

    //If the dot went too far up or down
    if( ( y < 0-MISSILE_HEIGHT ) )
    {
        reset();
    }
}

void Missile::show(SDL_Surface *screen)
{
    if(timeFrame.do_action(0,125))//0 = frame
    {
        if(frame<MAX_FRAME)
            frame++;
        else
            frame=0;
    }

    if(status==0)
        apply_surface( x, y, surfMissile, screen,&clipsNormal[frame]);
}

void Missile::reset()
{
    if(timeFrame.do_action(1,10000))//1 = vitesse
    {
        speed+=2;
    }
    newXPosition();
    y = HEIGHT_SCREEN+MISSILE_HEIGHT;

    yVel = -MyRand(speed-8,speed);

    iNewMissiles++;
}

void Missile::newXPosition()
{
    x = MyRand(0,WIDTH_SCREEN-MISSILE_WIDTH);
}
