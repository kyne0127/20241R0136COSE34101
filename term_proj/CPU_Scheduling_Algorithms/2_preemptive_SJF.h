#ifndef __SHORTEST__REMAINING__TIME
#define __SHORTEST__REMAINING__TIME

// Preemptive Shortest Job First Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include "./PrintGanttChart_preemptive_sjf.h"
#include <limits.h>

void psjf_calculate_time(Process *p, int len)
{
    int i;
    int curr_time = 0;
    int total_burst_time = 0;
    int shortest_remain_time;
    int k = 0;

    int *remain_burst_time = (int *)malloc(sizeof(int) * len);
    int *count = (int *)malloc(sizeof(int) * len);

    int flag = 1;
    int idle = 0;

    for (i = 0; i < len; i++)
    {
        count[i] = 0;
        remain_burst_time[i] = p[i].burst;
        total_burst_time += p[i].burst;
        p[i].available = TRUE;
    }

    while (flag)
    {
        shortest_remain_time = INT_MAX;
        k = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
            {
                shortest_remain_time = remain_burst_time[i];
                k = i;
                idle += 1;
            }
        }

        if (k == -1)
        {
            if (idle == 0) {
                // printf("Currently CPU is in Idle State. curr_time : %d\n", curr_time);
            }
            curr_time++;
            continue;
        }
        else {
            if (idle == 0) {
                // printf("Currently CPU is in Idle State. curr_time : %d\n", curr_time);
            }
        }
        idle = 0; // Reset idle when a process is selected

        if (count[k] == 0)
        {
            count[k]++;
        }

        remain_burst_time[k]--;
        curr_time++;

        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
            p[k].waiting_time = curr_time - p[k].burst - p[k].arrive_time;
        }

        // Check if all processes are completed
        flag = 0;
        for (i = 0; i < len; i++)
        {
            if(p[i].completed == FALSE) {
                flag = 1;
                break;
            }
        }
    }

    free(count);
    free(remain_burst_time);
}


void psjf_print_gantt_chart(Process *p, int len) {
    print_gantt_chart_psjf(p, len);
}

void PSJF(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);
    psjf_calculate_time(p, len);

    for (i = 0; i < len; i++)
    {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst;
        p[i].end_time = p[i].turnaround_time + p[i].arrive_time;
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    printf("\tPreemptive Shortest Job First Algorithm\n\n");

    psjf_print_gantt_chart(p, len);

    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n\n", (double)total_turnaround_time / (double)len);

    print_table(p, len);
    FILE *file = fopen("algorithm_comparison.txt", "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Algorithm: Preemptive SJF\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
