#ifndef __PREEMPTIVE__PRIORITY__SCHEDULING__
#define __PREEMPTIVE__PRIORITY__SCHEDULING__

// Preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include "./PrintGanttChart_preemptive_priority.h"
#include <limits.h>

void pps_calculate_time(Process *p, int len)
{
    int i;
    int priority;
    int curr_time = 0;
    int total_burst_time = 0;
    int k = -1;

    int *remain_burst_time = (int *)malloc(sizeof(int) * len);
    int *count = (int *)malloc(sizeof(int) * len);

    int flag = 1;

    for (i = 0; i < len; i++)
    {
        count[i] = 0;
        remain_burst_time[i] = p[i].burst;
        total_burst_time += p[i].burst;
        p[i].available == TRUE;
    }

    while (flag)
    {
        priority = INT_MAX;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
                // printf("current time : %d, I/O bursting : %s\n", curr_time, p[i].id);
            }
            else {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if ((p[i].completed == FALSE && p[i].available == TRUE)
                && (p[i].arrive_time <= curr_time)
                && (priority > p[i].priority))
            {
                priority = p[i].priority;
                k = i;
                // printf("current time : %d, highest priority process: %s\n", curr_time, p[i].id);
            }
        }

        if (k != -1 && count[k] == 0)
        {
            count[k]++;
        }

        if (k != -1) {
            remain_burst_time[k]--;
            curr_time++;

            if (remain_burst_time[k] == 0)
            {
                p[k].completed = TRUE;
                p[k].waiting_time = curr_time - p[k].burst - p[k].arrive_time;
                p[k].turnaround_time = p[k].waiting_time + p[k].burst;  // Turnaround time 계산
            }
        } else {
            curr_time++;
        }

        for (i = 0; i < len; i++)
        {
            if(p[i].completed == TRUE) {
                flag += 1;
            }
        }
        if ((flag-1)==len) {
            flag = 0; 
        }
        else {
            flag = 1;
        }
    }

    free(remain_burst_time);
    free(count);
}

void pps_print_gantt_chart(Process *p, int len)
{
    print_gantt_chart_pps(p,len);
}

void PPS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    pps_calculate_time(p, len);

    for (i = 0; i < len; i++)
    {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst;
        p[i].end_time = p[i].turnaround_time + p[i].arrive_time;

        if (p[i].turnaround_time < 0)  // Turnaround Time이 음수인지 확인
        {
            printf("Error: Turnaround Time for process %s is negative.\n", p[i].id);
            return;
        }

        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    printf("\tPreemptive Priority Scheduling Algorithm\n\n");

    pps_print_gantt_chart(p, len);

    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);

    print_table(p, len);

    FILE *file = fopen("algorithm_comparison.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Algorithm: Preemptive Priority\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
