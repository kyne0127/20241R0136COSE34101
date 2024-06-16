#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

// Shortest Job First Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include "./PrintGanttChart_nonpreemptive.h"

void sjf_calculate_time(Process *p, int len)
{
    int i, j;
    int curr_time = 0;
    int min;
    int completed_processes = 0;

    while (completed_processes < len)
    {
        min = -1;
        for (j = 0; j < len; j++)
        {
            if (p[j].completed == FALSE && p[j].arrive_time <= curr_time)
            {
                if (min == -1 || p[j].burst < p[min].burst)
                {
                    min = j;
                }
            }
        }

        if (min == -1)
        {
            curr_time++;
            continue;
        }

        // I/O burst time을 처리
        if (curr_time >= p[min].io_start_time && curr_time < p[min].io_start_time + p[min].io_duration)
        {
            curr_time += (p[min].io_start_time + p[min].io_duration - curr_time);
        }

        p[min].waiting_time = curr_time - p[min].arrive_time;
        p[min].completed = TRUE;
        curr_time += p[min].burst;
        p[min].turnaround_time = curr_time - p[min].arrive_time;
        p[min].end_time = curr_time; // Set the end time
        completed_processes++;
    }
}

void sjf_print_gantt_chart(Process *p, int len)
{
   print_gantt_chart_nonpreemptive(p, len);
}

void SJF(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    process_init(p, len);
    merge_sort_by_arrive_time(p, 0, len);

    sjf_calculate_time(p, len);

    for (i = 0; i < len; i++)
    {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    quick_sort_by_end_time(p, len);

    printf("\n\tSJF Scheduling Algorithms\n\n");

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
