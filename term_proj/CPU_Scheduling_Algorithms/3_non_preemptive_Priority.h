#ifndef __NON__PREEMPTIVE__PRIORITY__SCHEDULING__
#define __NON__PREEMPTIVE__PRIORITY__SCHEDULING__

// Non-preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintFunction/PrintTable.h"
#include <limits.h>
#include "./PrintFunction/PrintGanttChart_nonpreemptive_priority.h"

void npps_calculate(Process *p, int len)
{
    int i, j;
    int curr_time = 0;
    int min;

    int io_checker = 0;
    int check;

    for (i = 0; i < len; i++) {
        p[i].completed = FALSE;
    }

    while (TRUE)
    {
        // printf("current time : %d\n", curr_time);
        min = -1;
        check = FALSE;

        for (i = 0; i < len; i++)
        {
            if ((p[i].priority < (min == -1 ? INT_MAX : p[min].priority))
                && (p[i].completed == FALSE)
                && (p[i].arrive_time <= curr_time))
            {
                if (min == -1 || p[j].burst < p[min].burst)
                {
                    min = i;
                    check = TRUE;
                    // printf("min is set to %d\n", min);
                }
            }
        }

        io_checker = 0;
        // I/O burst time을 처리
        for (j = curr_time; j <= curr_time + p[min].burst; j++) {
            if (j >= p[min].io_start_time && j < p[min].io_start_time + p[min].io_duration)
            {
                io_checker += 1;
            }
        }

        if (check == FALSE)
            break;

        curr_time += io_checker;

        p[min].waiting_time = curr_time - p[min].arrive_time;
        p[min].completed = TRUE;
        p[min].turnaround_time = p[min].waiting_time + p[min].burst;

        curr_time += p[min].burst;
        p[min].end_time = curr_time; // Set the end time
    }
}

void npps_print_gantt_chart(Process *p, int len)
{
	print_gantt_chart_nonpreemptive_priority(p, len);
}

void NPPS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    process_init(p, len);
    // process_init 함수 호출로 process 초기화

    merge_sort_by_arrive_time(p, 0, len);
    // merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

    npps_calculate(p, len);
    // npps_calculate 함수 호출로 시간 계산

    /* process의 갯수 만큼 반복 */
    for (i = 0; i < len; i++)
    {
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
    
    printf("\n");
    print_table(p, len);
    // print_table 함수 호출로 데이터 표 출력
    FILE *file = fopen("algorithm_comparison.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Algorithm: Non-preemptive Priority Scheduling\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
