#include "PosixShMem.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <cstdio>

PosixShMem::PosixShMem(const char *name, int size)
{
    this->shm_name = name;
    strcpy(this->sem_name, "Semaphore_");
    strcat(this->sem_name, name);

    this->shm_pt = 0;
    this->sem_pt = 0;

    if((this->shm_fd = shm_open(this->shm_name, O_RDWR, 0666)) == -1)
    {
        if((this->shm_fd = shm_open(this->shm_name, O_CREAT|O_RDWR, 0666)) == -1)
        {
            perror("IPC error: shm_open");
            exit(1);
        }
        if(ftruncate(this->shm_fd, size) == -1)
        {
            perror("IPC error: ftryncate");
            exit(1);
        }
    }
    this->shm_pt = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, this->shm_fd, 0);
    if(this->shm_pt == MAP_FAILED)
    {
        perror("IPC error: mmap");
        exit(1);
    }

    if((this->sem_pt = sem_open(this->sem_name, O_RDWR, 0)) == SEM_FAILED)
    {
        if((this->sem_pt = sem_open(this->sem_name, O_CREAT|O_RDWR, 0666, 1)) == SEM_FAILED)
        {
            perror("IPC error: sem_open");
            exit(1);
        }
    }
}

PosixShMem::~PosixShMem()
{
    if(shm_unlink(this->shm_name) == -1)
    {
        perror("IPC error: shm_unlink");
    }
    if(this->sem_pt)
    {
        if(sem_close(this->sem_pt) == -1)
        {
            perror("IPC error: sem_close");
        }
    }
}

void *PosixShMem::read()
{
    return this->shm_pt;
}

void PosixShMem::read(void *mem, int size)
{
    this->lockMemory();
    memcpy(mem, this->shm_pt, size);
    this->unlockMemory();
}

void PosixShMem::write(void *data, int size, unsigned long offset)
{
    this->lockMemory();
    uint32_t *dest = (uint32_t*) this->shm_pt + offset;
    memcpy(dest, data, size);
    this->unlockMemory();
}

void PosixShMem::lockMemory()
{
    if(sem_wait(this->sem_pt) == -1)
    {
        perror("IPC error: sem_wait");
    }
}


void PosixShMem::unlockMemory()
{
    if(sem_post(this->sem_pt) == -1)
    {
        perror("IPC error: sem_post");
    }
}
