#ifndef THREADBASE_H
#define THREADBASE_H

#include <pthread.h>
#include <time.h>

class ThreadBase
{
private:
    pthread_t thread;
    struct timespec tim3, tim4;
    static void *start(void *param);

protected:
    int is_running;
    int is_alive;
    struct timespec tim1, tim2;

    ThreadBase();
    virtual ~ThreadBase();
    virtual int run() = 0;

public:
virtual void startActivity();
virtual void stopActivity();

};

#endif
