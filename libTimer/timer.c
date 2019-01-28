#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "timer.h"

#define NANOSECONDS 1000000000
#define MICROSECONDS_OFFSET 1000;
static struct timespec old_time;
static struct timespec cur_time;
static struct timespec result_time;
void lv_design_init_timer()
{

	if (clock_gettime(CLOCK_MONOTONIC, &cur_time) == -1) 
    {
      /* 에러 처리*/
      printf("Error\n");
      return 0;
    }
	old_time = cur_time;
}

void lv_design_update_time()
{
    old_time = cur_time;
}

uint64_t lv_design_get_time_diff()
{
	uint64_t time_interval = 0;
	if (clock_gettime(CLOCK_MONOTONIC, &cur_time) == -1) 
	{  
    	/* 에러 처리*/
		printf("Error\n");
   		return 0;
 	}
/*	printf("cur_time_sec = %lu\n",cur_time.tv_sec);
        printf("cur_time_nsec =%lu\n",cur_time.tv_nsec);
        printf("old_time_sec = %lu\n",old_time.tv_sec);
        printf("old_time_nsec = %lu\n",old_time.tv_nsec);*/
	if(cur_time.tv_nsec >= old_time.tv_nsec)
 	{
		result_time.tv_sec = cur_time.tv_sec - old_time.tv_sec;
		result_time.tv_nsec = cur_time.tv_nsec - old_time.tv_nsec;
 	}
 	else
 	{
		result_time.tv_sec = (cur_time.tv_sec - 1) - old_time.tv_sec;
		result_time.tv_nsec = (NANOSECONDS + cur_time.tv_nsec) - old_time.tv_nsec;
 	}
        
	time_interval = ((NANOSECONDS * result_time.tv_sec) + result_time.tv_nsec) / MICROSECONDS_OFFSET;
	return time_interval;
} 
