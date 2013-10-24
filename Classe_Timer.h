#ifndef CLASSE_TIMER_H
#define CLASSE_TIMER_H
//Le Timer
class Timer
{
    private:
    //Le temps quand le timer est lancé
    int startTicks;

    //Dernière action
    int lastActionTick[10];

    //Le temps enregistré quand le Timer a été mis en pause
    int pausedTicks;

    //Le status du Timer
    bool paused;
    bool started;

    public:
    //Initialise les variables
    Timer();

    //Les différentes actions du timer
    void start();
    void stop();
    void pause();
    void unpause();

    //recupére le nombre de millisecondes depuis que le timer a été lancé
    //ou récupére le nombre de millisecondes depuis que le timer a été mis en pause
    int get_ticks();
    int getLastActionTick(int track){return lastActionTick[track];}

    //
    bool do_action(int track, int diff);

    //Fonctions de vérification du status du timer
    bool is_started();
    bool is_paused();
};
#endif
