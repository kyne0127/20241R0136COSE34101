#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include "./PrintFunction/PrintGanttChart_nonpreemptive_sjf.h"

void sjf_calculate_time(Process *p, int len)
{
    int i, j, curr_time = 0;
    int min;
    int completed_processes = 0;
    int io_checker;

    while (completed_processes < len)
    {
        min = -1;
        io_checker = 0;

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time)
            {
                if (min == -1 || p[i].burst < p[min].burst)
                {
                    min = i;
                }
            }
        }

        if (min == -1)
        {
            curr_time++;
            continue;
        }

        for (j = curr_time; j <= curr_time + p[min].burst; j++) {
            if (j >= p[min].io_start_time && j < p[min].io_start_time + p[min].io_duration)
            {
                io_checker += 1;
            }
        }

        curr_time += io_checker;

        p[min].waiting_time = curr_time - p[min].arrive_time;
        p[min].completed = TRUE;
        p[min].turnaround_time = p[min].waiting_time + p[min].burst;

        curr_time += p[min].burst;
        p[min].end_time = curr_time;
        completed_processes++;
    }
}

void sjf_print_gantt_chart(Process *p, int len)
{
    print_gantt_chart_nonpreemptive_sjf(p, len);
}

void SJF(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    double cpu_utilization = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    sjf_calculate_time(p, len);

    for (i = 0; i < len; i++)
    {
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    printf("\tNon-Preemptive SJF Scheduling Algorithm\n\n");

    quick_sort_by_end_time(p, len);

    sjf_print_gantt_chart(p, len);

    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);

    print_table(p, len);

    FILE *file = fopen("algorithm_comparison.txt", "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Algorithm: Non-Preemptive SJF\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
