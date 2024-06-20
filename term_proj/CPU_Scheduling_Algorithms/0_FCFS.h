#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include "./PrintFunction/PrintGanttChart_fcfs.h"

void fcfs_calculate(Process *p, int len)
{
    int i, j, curr_time = 0;
    int io_checker = 0;

    for (i = 0; i < len; i++)
    {
        io_checker = 0;
        for (j = curr_time; j <= curr_time + p[i].burst; j++) {
            if (j >= p[i].io_start_time && j < p[i].io_start_time + p[i].io_duration)
            {
                io_checker += 1;
            }
        }

        curr_time += io_checker;

        p[i].waiting_time = curr_time - p[i].arrive_time;
        p[i].completed = TRUE;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst;

        curr_time += p[i].burst;
        p[i].end_time = curr_time;
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

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    fcfs_calculate(p, len);

    for (i = 0; i < len; i++)
    {
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    printf("\n\tFCFS Scheduling Algorithm\n\n");

    fcfs_print_gantt_chart(p, len);
    
    printf("total time : %d", p[len-1].end_time);

    // 평균 대기시간, 턴어라운드 타임 출력
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);

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
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
