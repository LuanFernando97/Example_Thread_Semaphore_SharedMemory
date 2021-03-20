#ifndef DEF_POSIXSHMEM_H
#define DEF_POSIXSHMEM_H

#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

class PosixShMem
{
public:
    PosixShMem(const char *name, int size);
    virtual ~PosixShMem();

    virtual void *read();
    virtual void read(void *mem, int size);
    virtual void write(void *data, int size, unsigned long offset = 0);

    virtual void lockMemory();
    virtual void unlockMemory();

private:

    void *shm_pt;
    const char *shm_name;
    int shm_fd;

    sem_t *sem_pt;
    char sem_name[255];

};

#endif
