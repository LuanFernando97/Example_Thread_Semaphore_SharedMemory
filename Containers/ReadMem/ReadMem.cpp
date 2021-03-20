#include "ReadMem.h"
#include "../test_struct.h"

#include <iostream>

ReadMem::ReadMem()
{
    this->data = new PosixShMem("SH_MEM",sizeof(TIMESTAMPED_TEST_DATA));
    this->startActivity();
}

ReadMem::~ReadMem()
{
    this->stopActivity();
    delete this->data;
}

void ReadMem::startActivity()
{
    ThreadBase::startActivity();
}

void ReadMem::stopActivity()
{
    ThreadBase::stopActivity();
    std::cout << "READ" << std::endl;
}

int ReadMem::run()
{
    this->is_running = 1;
    this->is_alive = 1;
    this->tim1.tv_sec = 0;
    this->tim1.tv_nsec = 100000000L;//10Hz

    TIMESTAMPED_TEST_DATA my_data;
    while(this->is_alive)
    {
        this->data->read(&my_data, sizeof(TIMESTAMPED_TEST_DATA));
        
        std::cout << "Cont: " << my_data.data.contador << "  TEMPO: " << my_data.time << std::endl;
        nanosleep(&this->tim1, &this->tim2);
    }
    this->is_running = 0;
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
