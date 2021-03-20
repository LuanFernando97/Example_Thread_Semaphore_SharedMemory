#include <iostream>
#include <cstdlib>
#include "Containers/ReadMem/ReadMem.h"
#include "Containers/WriteMem/WriteMem.h"

using namespace std;

int main (int argc, char* argv[])
{
    ReadMem *read = new ReadMem();
    WriteMem *write = new WriteMem();
    int quit =-1;
    do
    {
        std::cin >> quit;
    } 
    while (quit != 0);
    delete read;
    delete write;

    return EXIT_SUCCESS;
}