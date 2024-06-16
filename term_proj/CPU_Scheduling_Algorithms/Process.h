#ifndef __PROCESS__
#define __PROCESS__

// Process

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include stdbool.h to use bool type

#define ID_LEN 20
#define TRUE 1
#define FALSE 0

/* 프로세스 구조체 */
typedef struct _process
{
    char id[ID_LEN];       // Process ID
    int arrive_time;       // Arrival Time
    int waiting_time;      // Waiting Time
    int turnaround_time;   // TurnAround Time
    int burst;             // CPU Burst Time
    int priority;          // Priority of Process
    int completed;         // Complete Checker
    int io_start_time;     // I/O Start Time
    int io_duration;       // I/O Duration
    int end_time;          // Actual End Time
    bool available;        // Availability checker
} Process; // Process 구조체 생성

typedef int Quantum; // 시간 할당량 Quantum 키워드 사용

void process_init(Process p[], int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        p[i].waiting_time = 0;   // Initialize Waiting time
        p[i].completed = FALSE;  // Initialize Completed Status
        p[i].end_time = 0;       // Initialize End Time
        p[i].available = TRUE;   // Initialize Availability
    }
}

#endif
