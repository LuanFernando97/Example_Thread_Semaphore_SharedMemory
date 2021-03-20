#include "WriteMem.h"
#include "../test_struct.h"

#include <iostream>

WriteMem::WriteMem()
{
    this->data = new PosixShMem("SH_MEM",sizeof(TIMESTAMPED_TEST_DATA));
    this->startActivity();
}

WriteMem::~WriteMem()
{
    this->stopActivity();
}

void WriteMem::startActivity()
{
    ThreadBase::startActivity();
}

void WriteMem::stopActivity()
{
    ThreadBase::stopActivity();
    std::cout << "WRITE" << std::endl;
}

int WriteMem::run()
{
    this->is_running = 1;
    this->is_alive = 1;
    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 100000000L;//10Hz

    TIMESTAMPED_TEST_DATA my_data;
    int my_cont = -1;
    while(this->is_alive)
    {
        my_data.data.contador = my_cont++;
        my_data.time = road_time();
        this->data->write(&my_data, sizeof(TIMESTAMPED_TEST_DATA));
        
        nanosleep(&this->tim1, &this->tim2);
    }
    this->is_running = 0;
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
