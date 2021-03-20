#ifndef READMEM_H
#define READMEM_H

#include "../../Utils/PosixShMem/PosixShMem.h"
#include "../../Utils/ThreadBase/ThreadBase.h"

class ReadMem: public ThreadBase
{
public:
    ReadMem();
    ~ReadMem();

private:

    PosixShMem *data;
    void startActivity() override;
    void stopActivity() override;
    int run() override;
    
};

#endif
