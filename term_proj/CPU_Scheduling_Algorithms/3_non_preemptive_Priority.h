#ifndef __NON__PREEMPTIVE__PRIORITY__SCHEDULING__
#define __NON__PREEMPTIVE__PRIORITY__SCHEDULING__

// Non-preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include <limits.h>
#include "./PrintFunction/PrintGanttChart_npps.h"

void npps_calculate(Process *p, int len, int *idle)
{
    int i, j, curr_time = 0;
    int min;
    int completed_processes = 0;
    int highest_priority;

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
        highest_priority = INT_MAX;
        min = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration && p[i].arrive_time <= curr_time)
            {
                p[i].available = FALSE;
                if (running_process == i) {
                    process_completeness = 0;
                    running_process = -1;
                }
            }
            else {
                p[i].available = TRUE;
            }
        } 
        
        for (i = 0; i < len; i++)
        {
            if ((p[i].priority < (min == -1 ? INT_MAX : highest_priority))
                && (p[i].completed == FALSE)
                && (p[i].arrive_time <= curr_time) && p[i].available == TRUE)
            {
                if (process_completeness == 0 || running_process == -1) {
                    highest_priority = p[i].priority;
                    min = i;
                    process_completeness = 1;
                    running_process = i;
                }
            }
        }

        if (min == -1)
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
                min = running_process;
            }
        }

        remain_burst_time[min]--;
        curr_time++;

        if (remain_burst_time[min] == 0)
        {
            p[min].completed = TRUE;
            p[min].waiting_time = curr_time - p[min].burst - p[min].arrive_time;
            completed_processes++;
            process_completeness = 0;
            running_process = -1;
        }
    }
}

void npps_print_gantt_chart(Process *p, int len)
{
	print_gantt_chart_npps(p, len);
}

void NPPS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    double cpu_utilization = 0;

    int idle = 0;

    process_init(p, len);
    // process_init 함수 호출로 process 초기화

    merge_sort_by_arrive_time(p, 0, len);
    // merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

    npps_calculate(p, len, &idle);
    // npps_calculate 함수 호출로 시간 계산

    /* process의 갯수 만큼 반복 */
    for (i = 0; i < len; i++)
    {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst;
        p[i].end_time = p[i]. turnaround_time + p[i].arrive_time;
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
    }

    quick_sort_by_end_time(p, len);
    // quick_sort_by_end_time 함수 호출로 반환 시간으로 정렬

    printf("\tNon-preemptive Priority Scheduling Algorithm\n\n");

    npps_print_gantt_chart(p, len);
    // npps_print_gantt_chart 함수 호출로 간트 차트 출력

    /* 평균 대기시간, 턴어라운드 타임 출력 */
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

    fprintf(file, "Algorithm: Non-preemptive Priority Scheduling\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "CPU Utilization rate: %.2f%%\n", cpu_utilization);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
