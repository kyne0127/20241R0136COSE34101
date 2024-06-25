#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include "./PrintFunction/PrintGanttChart_fcfs.h"

void fcfs_calculate(Process *p, int len, int *idle)
{
    int i, j, curr_time = 0;
    int earliest;
    int completed_processes = 0;

    int running_process = -1;
    int process_completeness = 0;
    int *remain_burst_time = (int *)malloc(sizeof(int) * len);

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].available = TRUE;
    }

    while (completed_processes < len)
    {
        earliest = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
                if (running_process == i) {
                    process_completeness = 0;
                }
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (process_completeness == 0 || running_process == -1) {
                    earliest = i;
                    process_completeness = 1;
                    running_process = i;
                    continue;
                }
            }
        }

        if (earliest == -1)
        {
            if(running_process == -1)
            {
                curr_time++;
                running_process = -1;
                process_completeness = 0;
                *idle += 1;
                continue;
            }
            else
            {
                earliest = running_process;
            }
        }

        remain_burst_time[earliest]--;
        curr_time++;

        if (remain_burst_time[earliest] == 0)
        {
            p[earliest].completed = TRUE;
            p[earliest].waiting_time = curr_time - p[earliest].burst - p[earliest].arrive_time;
            completed_processes++;
            process_completeness = 0;
            running_process = -1;
        }
    }
}

void fcfs_print_gantt_chart(Process *p, int len)
{
    print_gantt_chart_fcfs(p, len);
}

void FCFS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int curr_time = 0;
    double cpu_utilization = 0;

    int idle = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    fcfs_calculate(p, len, &idle);

    for (i = 0; i < len; i++)
    {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst;
        p[i].end_time = p[i]. turnaround_time + p[i].arrive_time;
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    printf("\n\tFCFS Scheduling Algorithm\n\n");

    fcfs_print_gantt_chart(p, len);
    
    // 평균 대기시간, 턴어라운드 타임 출력
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

    fprintf(file, "Algorithm: FCFS\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "CPU Utilization rate: %.2f%%\n", cpu_utilization);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
