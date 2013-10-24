#ifndef CLASSE_TIMER_H
#define CLASSE_TIMER_H
//Le Timer
class Timer
{
    private:
    //Le temps quand le timer est lanc�
    int startTicks;

    //Derni�re action
    int lastActionTick[10];

    //Le temps enregistr� quand le Timer a �t� mis en pause
    int pausedTicks;

    //Le status du Timer
    bool paused;
    bool started;

    public:
    //Initialise les variables
    Timer();

    //Les diff�rentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();

    //recup�re le nombre de millisecondes depuis que le timer a �t� lanc�
    //ou r�cup�re le nombre de millisecondes depuis que le timer a �t� mis en pause
    int get_ticks();
    int getLastActionTick(int track){return lastActionTick[track];}

    //
    bool do_action(int track, int diff);

    //Fonctions de v�rification du status du timer
    bool is_started();
    bool is_paused();
};
#endif
