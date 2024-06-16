#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

// Gantt Chart 출력 함수
void fcfs_print_gantt_chart(Process *p, int len)
{
    int i, j, curr_time = 0;

    printf("\t ");

    // 상단 바 출력
    for (i = 0; i < len; i++)
    {
        // Idle time을 처리
        if (curr_time < p[i].arrive_time)
        {
            for (j = curr_time; j < p[i].arrive_time; j++)
                printf("xx");
            curr_time = p[i].arrive_time;
        }

        // I/O burst time을 처리
        if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
        {
            for (j = curr_time; j < p[i].io_start_time + p[i].io_duration; j++)
                printf("xx");
            curr_time += (p[i].io_start_time + p[i].io_duration - curr_time);
        }

        // 실제 작업 시간 출력
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        curr_time += p[i].burst;
        printf(" ");
    }

    printf("\n\t|");

    // process 이름 출력
    curr_time = 0;
    for (i = 0; i < len; i++)
    {
        // Idle time을 처리
        if (curr_time < p[i].arrive_time)
        {
            for (j = curr_time; j < p[i].arrive_time; j++)
                printf("  ");
            curr_time = p[i].arrive_time;
        }

        // I/O burst time을 처리
        if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
        {
            for (j = curr_time; j < p[i].io_start_time + p[i].io_duration; j++)
                printf("  ");
            curr_time = p[i].io_start_time + p[i].io_duration;
        }

        // 실제 작업 시간 출력
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("%s", p[i].id);

        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        curr_time += p[i].burst;
        printf("|");
    }

    printf("\n\t ");

    // 하단 바 출력
    curr_time = 0;
    for (i = 0; i < len; i++)
    {
        // Idle time을 처리
        if (curr_time < p[i].arrive_time)
        {
            for (j = curr_time; j < p[i].arrive_time; j++)
                printf("xx");
            curr_time = p[i].arrive_time;
        }

        // I/O burst time을 처리
        if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
        {
            for (j = curr_time; j < p[i].io_start_time + p[i].io_duration; j++)
                printf("xx");
            curr_time += (p[i].io_start_time + p[i].io_duration - curr_time);
        }

        // 실제 작업 시간 출력
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        curr_time += p[i].burst;
        printf(" ");
    }

    printf("\n\t");

    // process 시간 출력
    curr_time = 0;
    printf("0");
    for (i = 0; i < len; i++)
    {
        // Idle time을 처리
        if (curr_time < p[i].arrive_time)
        {
            for (j = curr_time; j < p[i].arrive_time; j++)
                printf("  ");
            curr_time = p[i].arrive_time;
        }

        // I/O burst time을 처리
        if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
        {
            for (j = curr_time; j < p[i].io_start_time + p[i].io_duration; j++)
                printf("  ");
            curr_time = p[i].io_start_time + p[i].io_duration;
        }

        // 실제 작업 시간 출력
        for (j = 0; j < p[i].burst; j++)
            printf("  ");

        if (curr_time + p[i].burst > 9)
            printf("\b");

        curr_time += p[i].burst;
        printf("%d", curr_time);
    }

    printf("\n");
}


void FCFS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    double cpu_utilization = 0;
    int curr_time = 0;

    process_init(p, len);

    merge_sort_by_arrive_time(p, 0, len);

    // 맨 처음 들어온 process 실행
    if (p[0].arrive_time > 0)
    {
        curr_time = p[0].arrive_time;
    }

    // 다음 프로레스 부터 순차적으로 계산
    for (i = 0; i < len; i++)
    {
        if (curr_time < p[i].arrive_time)
        {
            curr_time = p[i].arrive_time;
        }

        // I/O burst time을 처리
        if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
        {
            curr_time += (p[i].io_start_time + p[i].io_duration - curr_time);
            // printf("process: %s current time: %d\n", p[i].id, curr_time);
        }

        p[i].waiting_time = curr_time - p[i].arrive_time;

        p[i].turnaround_time = p[i].waiting_time + p[i].burst;

        p[i].end_time = p[i].turnaround_time + p[i].arrive_time;

        // 실행된 process만큼 증가
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        curr_time += p[i].burst;
    }

    printf("\n\tFCFS Scheduling Algorithm\n\n");

    fcfs_print_gantt_chart(p, len, idle);

    // 평균 대기시간, 턴어라운드 타임 출력
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);

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
