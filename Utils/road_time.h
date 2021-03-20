#ifndef DEF_ROAD_TIME_H
#define DEF_ROAD_TIME_H

#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

typedef uint64_t road_time_t;

typedef uint32_t road_timerange_t;

typedef uint64_t road_time_diff_t;

typedef uint64_t road_timerange_diff_t;

static road_time_t road_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return(road_time_t)((road_time_t)(t.tv_sec)*1000000 + (road_time_t)(t.tv_usec));
}

#endif