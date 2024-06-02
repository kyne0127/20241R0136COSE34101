#include "CPUScheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 추가: 문자열 관련 함수 사용을 위한 헤더

int main()
{
    initialize_analysis_file("algorithm_comparison.txt");
    //알고리즘별 실행 결과 종합 파일 초기화

    int process_count = 0;

    int i = 0;

    int process_generator = system("./process_generator");
    //process_generator를 실행하여 프로세스 생성

    if (process_generator == -1) {
        perror("system");
        return 1;
    }


    Quantum quantum;
    // 시간 할당량
    Process *process;
    // 프로세스 구조체 배열을 동적 할당할 포인터 변수 선언

    /* 파일포인터 fp선언 및 process.txt를 읽기모드로 열기*/
    FILE *fp = fopen("process.txt", "r");

    if (fp == NULL)
    {
        printf("FILE OPEN ERROR!\n");
        return 0;
    }

    fscanf(fp, " %d", &process_count);

    /* process_count 만큼 프로세스 구조체 배열 동적 할당 */
    process = (Process *)malloc(sizeof(Process) * process_count);

    /* process의 갯수만큼 반복 */
    while (i < process_count)
    {
        fscanf(fp, "%s %d %d %d",
                process[i].id, &process[i].arrive_time, &process[i].burst, &process[i].priority);
        i++;
    }

    fscanf(fp, " %d", &quantum);

    /* FCFS 함수 호출로 First Come First Served 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    FCFS(process, process_count);
    puts("◣                                                                                                                             ◢\n");

    /* SJF 함수 호출로 Shortest Job First 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    SJF(process, process_count);
    puts("◣                                                                                                                             ◢\n");

    /* PSJF 함수 호출로 Preemptive Shortest Job Fisrt 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    PSJF(process, process_count);
    puts("◣                                                                                                                             ◢\n");

    /* NPPS 함수 호출로 Non-Preemptive Priority Scheduling 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    NPPS(process, process_count);
    puts("◣                                                                                                                             ◢\n");

    /* PPS 함수 호출로 Preemptive Priority Scheduling 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    PPS(process, process_count);
    puts("◣                                                                                                                             ◢\n");

    /* RR 함수 호출로 Round Robin 알고리즘 실행 */
    puts("◤                                                                                                                             ◥\n");
    RR(process, process_count, quantum);
    puts("◣                                                                                                                             ◢\n");

    fclose(fp);

    free(process);
    // 메모리 할당을 해준 프로세스 구조체 배열 할당 해제

    int analysis = system("./algorithms_analysis");
    // 알고리즘 결과 출력 및 분석

    if (analysis == -1) {
        perror("system");
        return 1;
    }

    getchar();

    return 0;
    // 메인 함수 종료
}
