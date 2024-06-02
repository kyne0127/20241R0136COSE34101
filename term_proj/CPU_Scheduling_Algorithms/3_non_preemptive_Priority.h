#ifndef __NON__PREEMPTIVE__PRIORITY__SCHEDULING__
#define __NON__PREEMPTIVE__PRIORITY__SCHEDULING__

// Non-preemptive Priority Scheduling Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include <limits.h>

void npps_calculate(Process *p, int len)
{
    int i, j;
    int check;
    // 모든 process가 완료되었는지 확인할 변수 선언
    int min = -1;
    // 우선순위가 가장 높은 인덱스를 저장할 변수 선언
    int time = 0;
    // 현재 시간을 저장할 변수 선언 및 초기화

    // process의 초기 상태를 명확히 설정
    for (i = 0; i < len; i++) {
        p[i].completed = FALSE;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].response_time = 0;
        p[i].return_time = 0;
    }

    /* 모든 process가 완료될때 까지 반복 */
    while (TRUE)
    {
        min = -1;
        check = FALSE;

        /* process의 갯수만큼 반복 */
        for (i = 0; i < len; i++)
        {
            /* 현재 우선순위보다 높은 우선순위를 갖으며
               아직 실행되지 않았고 이미 도착한 process인 경우 */
            if ((p[i].priority < (min == -1 ? INT_MAX : p[min].priority))
                && (p[i].completed == FALSE)
                && (p[i].arrive_time <= time))
            {
                min = i;
                check = TRUE;
            }
        }

        /* 모든 process가 완료되었을 경우 */
        if (check == FALSE)
            break;

        /* 선택된 process 시간 계산 */
        p[min].response_time = time - p[min].arrive_time;
        p[min].return_time = time + p[min].burst;
        p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
        p[min].waiting_time = p[min].response_time;
        p[min].completed = TRUE;

        time += p[min].burst;
        // 실행된 process 시간 만큼 현재 시간 증가
    }
}

void npps_print_gantt_chart(Process *p, int len)
{
    int i, j;

    printf("\t ");

    /* 상단 바 출력 */
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t|");

    /* process ID 출력 */
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("%s", p[i].id);

        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("|");
    }

    printf("\n\t ");

    /* 하단 바 출력 */
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t");

    /* process 시간 출력 */
    printf("0");

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");

        if (p[i].return_time > 9)
            printf("\b");

        printf("%d", p[i].return_time);
    }

    printf("\n");
}

void NPPS(Process *p, int len)
{
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

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
        total_response_time += p[i].response_time;
    }

    quick_sort_by_return_time(p, len);
    // quick_sort_by_return_time 함수 호출로 반환 시간으로 정렬

    printf("\tNon-preemptive Priority Scheduling Algorithm\n\n");

    npps_print_gantt_chart(p, len);
    // npps_print_gantt_chart 함수 호출로 간트 차트 출력

    /* 평균 대기시간, 턴어라운드 타임, 응답 시간 출력 */
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

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
    fprintf(file, "Average Response Time: %.2f\n", (double)total_response_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif
