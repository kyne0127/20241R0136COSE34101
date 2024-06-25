#ifndef __ROUND__ROBIN__
#define __ROUND__ROBIN__

// Round Robin Scheduling

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include "./PrintFunction/PrintGanttChart_RR.h"

void rr_calculate_waiting_time(Process *p, int len, Quantum q, int *idle)
{
    int i;
    int curr_time = 0;
    int flag = 1;
    int double_checker = 0;

    int *remain_burst_time = (int *)malloc(sizeof(int) * len);

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].waiting_time = 0;
        p[i].available = TRUE;
    }

    while (flag)
    {
        double_checker = 0;
        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (remain_burst_time[i] > 0)
                {
                    if (remain_burst_time[i] > q)
                    {
                        curr_time += q;
                        remain_burst_time[i] -= q;
                    }

                    else
                    {
                        curr_time += remain_burst_time[i];
                        p[i].waiting_time += (curr_time - p[i].burst - p[i].arrive_time);
                        remain_burst_time[i] = 0;
                        p[i].completed = TRUE;
                    }
                }
            }
            else {
                double_checker++;
            }
        }

        if (double_checker == len) {
            idle++;
            // printf("{%d}", prev_idle);
            curr_time++;
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
    free(remain_burst_time);
}

void rr_calculate_turnaround_time(Process *p, int len)
{
    int i;

    for (i = 0; i < len; i++)
        p[i].turnaround_time = p[i].burst + p[i].waiting_time;
}

void rr_calculate_end_time(Process *p, int len)
{
    int i;

    for (i = 0; i < len; i++)
        p[i].end_time = p[i].turnaround_time + p[i].arrive_time;
}

void rr_print_gantt_chart(Process *p, int len, Quantum q)
{
    print_gantt_chart_rr(p, len, q);
}

void RR(Process *p, int len, Quantum quantum)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    double cpu_utilization = 0;

    int idle = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    rr_calculate_waiting_time(p, len, quantum, &idle);

    rr_calculate_turnaround_time(p, len);

    rr_calculate_end_time(p, len);

    for (i = 0; i < len; i++)
    {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    printf("\tRound Robin Scheduling Algorithm ( Quantum : %d )\n\n", quantum);

    rr_print_gantt_chart(p, len, quantum);

    quick_sort_by_end_time(p, len);

    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
    cpu_utilization = ((double)(p[len-1].end_time - idle) / (double)p[len-1].end_time) * 100.0;
    printf("\tCPU Utilization rate     : %-2.2lf%%\n", cpu_utilization);
    printf("\n");

    print_table(p, len);
    FILE *file = fopen("algorithm_comparison.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Algorithm: Round Robin\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "CPU Utilization rate: %.2f%%\n", cpu_utilization);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif

