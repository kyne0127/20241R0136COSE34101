#ifndef __PROCESS__
#define __PROCESS__

// Process

#include <stdio.h>
#include <stdlib.h>

#define ID_LEN 20
#define TRUE 1
#define FALSE 0

/* 프로세스 구조체 */
typedef struct _process
{
    char id[ID_LEN];       // Process ID
    int arrive_time;       // Arrival Time
    int waiting_time;      // Waiting Time
    int return_time;       // Return Time
    int turnaround_time;   // TrunAround Time
    int response_time;     // Response Time
    int burst;             // CPU Burst Time
    int priority;          // Priority of Process
    int completed;         // Complete Checker
} Process; // Process 구조체 생성

typedef int Quantum; // 시간 할당량 Quantum 키워드 사용

/**
 * [process_init 프로세스 초기화 함수]
 * @param p   [프로세스 구조체 배열]
 * @param len [프로세스 갯수]
 */
void process_init(Process p[], int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        p[i].waiting_time = 0;   // Initialize Waiting time
        p[i].return_time = 0;    // Initialize Return time
        p[i].response_time = 0;  // Initialize Response time
        p[i].completed = FALSE;  // Initialize Completed Status
    }
}

#endif