#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__

// Shortest Job First Algorithmd

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

void sjf_calculate_time(Process *p, int len)
{
	int i, j;
	int curr_time = 0;
	// 현재 시간을 저장할 변수 선언 및 초기화
	int min = 0;
	// 최소 시간을 갖는 인덱스를 저장할 변수 선언 및 초기화

	/* 맨 처음에 실행되는 process 시간 계산 */
	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	
	curr_time = p[0].burst;
	// 현재 시간 완료된 process 시간 만큼 증가

	/* process의 갯수 -1 만큼 반복 */
	for(i = 1; i < len; i++)
	{
		/* process의 갯수 -1 만큼 반복 */
		for (j = 1; j < len; j++)
		{
			/* 이미 완료된 process일 경우 */
			if (p[j].completed == TRUE)
				continue;
				// 다음 루프로 이동

			/* 아직 완료되지 않은 process일 경우 */
			else
			{
				min = j;
				// min 변수 초기화
				break;
				// 반복문 탈출
			}
		}

		/* process의 갯수 -1 만큼 반복 */
		for (j = 1; j < len; j++)
		{
			/* 최소 작업 시간을 갖는 조건에 맞는 process 탐색, 도착한 process 중 CPU Busrt Time이 가장 낮은 프로세스 탐색 */
			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;
				// 최소 작업 process 갱신
			}
		}

		p[min].waiting_time = curr_time - p[min].arrive_time;
		// 실행할 process 대기 시간 계산
		p[min].completed = TRUE;
		// 실행 process 완료 상태 변경

		curr_time += p[min].burst;
		// 현재 시간 process의 실행 시간만큼 증가

		p[min].return_time = curr_time;
		// process 반환 시간 계산
		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;
		// process 턴어라운드 타임 계산
	}
}

void sjf_print_gantt_chart(Process *p, int len)
{
	int i, j;
	// 반복문에서 사용할 변수 선언

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

	printf("0");

	/* process 실행 시간 출력 */
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}

void SJF(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_response_time = 0;

	process_init(p, len);

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 함수 호출로 도착 시간을 기준으로 정렬

	sjf_calculate_time(p, len);

	/* process의 갯수 만큼 반복 */
	for (i = 0; i < len; i++)
	{
		p[i].return_time = p[i].turnaround_time + p[i].arrive_time;
		p[i].response_time = p[i].waiting_time;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("\tSJF Scheduling Algorithms\n\n");

	quick_sort_by_return_time(p, len);
	// quick_sort_by_return_time 함수 호출로 반환 시간으로 정렬

	sjf_print_gantt_chart(p, len);
	// sjf_print_gantt_chart 함수 호출로 간트 차트 출력

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

    fprintf(file, "Algorithm: Non-Preemptive SJF\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
	fprintf(file, "Average Response Time: %.2f\n", (double)total_response_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif