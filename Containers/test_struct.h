#ifndef TEST_STRUCT
#define TEST_STRUCT

#include "../Utils/road_time.h"

typedef struct
{
    uint64_t contador;
}TEST_DATA;


typedef struct
{
    road_time_t time;
    TEST_DATA data;
}TIMESTAMPED_TEST_DATA;

#endif
