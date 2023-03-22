#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED

class ImpTimer{
public:
    ImpTimer();
    ~ImpTimer();
    void start();
    void stop();
    void paused();
    void unpaused();
    int get_ticks();
    bool isStarted();
    bool isPaused();
private:
    int start_tick;
    int paused_tick;

    bool is_paused;
    bool is_started;
};

#endif // IMPTIMER_H_INCLUDED
