#ifndef __SHORTEST__REMAINING__TIME
#define __SHORTEST__REMAINING__TIME

// Preemptive Shortest Job First Algorithm

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"
#include <limits.h>

void psjf_calculate_time(Process *p, int len)
{
	int i;
	int current_time = 0;
	int total_burst_time = 0;
	int shortest_remain_time;
	// 현재 남아 있는 실행 시간이 가장 짧은 process의 남은 실행 시간을 저장할 변수
	int k = 0;
	// 현재 실행중인 process 번호를 저장할 변수 선언 및 초기화

	/* 각 process 별 남은 실행 시간을 저장할 배열 동적 할당 */
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);
	/* 응답 시간을 확인하는데 사용할 배열 동적 할당 */
	int *count = (int *)malloc(sizeof(int) * len);

	/* process의 갯수만큼 반복 */
	for (i = 0; i < len; i++)
	{
		count[i] = 0;
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
	}

	/* 현재 시간이 총 실행 시간이 되기 전까지 반복 */
	while (current_time < total_burst_time)
	{
		shortest_remain_time = INT_MAX;
		// 최소작업 인덱스를 INT_MAX로 초기화

		/* current time이 가장 마지막에 들어온 process의 arrival time 보다 작을 경우 */
		if (current_time <= p[len - 1].arrive_time)
		{
			/* process의 갯수만큼 반복 */
			for (i = 0; i < len; i++)
			{
				/* 완료되지 않았으며 arrival time이 current time보다 작거나 같으며
				   현재 최소작업 시간보다 남은 실행시간이 작을 경우 */
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time)
							&& (shortest_remain_time > remain_burst_time[i]))
				{
					shortest_remain_time = remain_burst_time[i];
					// 최소 작업 시간 갱신
					k = i;
					// 최소 작업 process 인덱스 갱신
				}
			}
		}

		/* 더 이상 새로운 process가 들어오지 않는 경우 */
		else
		{
			/* process의 갯수만큼 반복 */
			for (i = 0; i < len; i++)
			{
				/* 완료되지 않았으며 현재 최소작업 시간보다
				   남은 실행시간이 작을 경우 */
				if ((p[i].completed == FALSE)
						&& (shortest_remain_time > remain_burst_time[i]))
				{
					shortest_remain_time = remain_burst_time[i];
					// 최소 작업 시간 갱신
					k = i;
					// 최소 작업 process 인덱스 갱신
				}
			}
		}

		/* 선택된 process가 처음 시작될 경우 */
		if (count[k] == 0)
		{
			count[k]++;
			// 초기 실행이 아님을 표시
			p[k].response_time = current_time;
			// 실행중인 process의 응답시간 저장
		}

		remain_burst_time[k]--;
		// 실행된 process의 남은 시간 감소
		current_time++;
		// 현재 시간 증가

		/* process의 남은 실행 시간이 0이될 경우 */
		if (remain_burst_time[k] == 0)
		{
			p[k].completed = TRUE;
			// 완료 상태로 변경
			p[k].waiting_time = current_time - p[k].burst - p[k].arrive_time;
			// 대기 시간 계산
			p[k].return_time = current_time;
			// 반환 시간 계산
		}
	}

	/* 동적 할당한 배열의 메모리 할당 해제 */
	free(count);
	free(remain_burst_time);
}

void psjf_print_gantt_chart(Process *p, int len)
{
	int i;
	int total_burst_time = 0;
	int current_time = 0, previous_time;
	// previous_time : 이전 process가 실행된 시간을 저장할 변수 추가 선언
	int k, pre_k = 0;
	// pre_k : 이전 process 번호를 저장할 변수 추가 선언
	int shortest_remain_time, gap;
	// gap : 새로 실행된 process 사이 거리를 저장할 변수 선언

	int *count = (int *)malloc(sizeof(int) * len);
	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		total_burst_time += p[i].burst;
		p[i].completed = FALSE;
		count[i] = 0;
	}

	printf("\t ");

	/* 동일 알고리즘을 실행하며 상단 바 출력 */
	while (current_time < total_burst_time)
	{
		shortest_remain_time = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time))
				{
					if (shortest_remain_time > remain_burst_time[i])
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}
		}

		else
		{
			for (i = 0; i < len; i++)
			{
				if (p[i].completed == FALSE)
				{
					if (shortest_remain_time > remain_burst_time[i])
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}
		}

		/* 이전에 실행된 process와 다른 process일 경우 */
		if (pre_k != k)
			printf(" ");
			// 공백 출력

		printf("--");
		remain_burst_time[k]--;
		current_time++;
		pre_k = k;
		// 이전 process 저장

		if (remain_burst_time[k] == 0)
			p[k].completed = TRUE;
	}

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	printf("\n\t|");

	/* 동일 알고리즘을 실행하며 process 아이디 출력
	   이전 process와 비교하며 \b 사용하여 간격 조절 */
	while (current_time <= total_burst_time)
	{
		/* 현재 시간이 총 실행시간과 다를 경우 */
		if (current_time != total_burst_time)
		{
			shortest_remain_time = INT_MAX;

			if (current_time <= p[len - 1].arrive_time)
			{
				for (i = 0; i < len; i++)
				{
					if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time)
							&& (shortest_remain_time > remain_burst_time[i]))
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}

			else
			{
				for (i = 0; i < len; i++)
				{
					if ((p[i].completed == FALSE)
						&& (shortest_remain_time > remain_burst_time[i]))
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}

			if (current_time == 0)
			{
				count[k]++;
				printf("  ");
			}

			else
			{
				/* 이전 process와 다른 process일 경우 */
				if (pre_k != k)
				{
					gap = count[pre_k] + 1;
					// 두 process 시간 차이 저장
					count[pre_k] = 0;
					// 이전 process 카운트 초기화
					count[k]++;
					// 현재 process 카운트 증가

					/* 두 process 차이만큼 \b 출력 */
					for (i = 0; i < gap; i++)
						printf("\b");

					/* 이전 process ID 출력 */
					printf("%2s", p[pre_k].id);

					/* 간격을 맞추어 공백 출력 */
					for (i = 0; i < gap - 2; i++)
						printf(" ");

					printf("|  ");
				}

				/* 같은 process일 경우 */
				else
				{
					count[k]++;
					// 현재 process 카운트 증가

					printf("  ");
					// 공백 출력
				}
			}

			pre_k = k;
			remain_burst_time[k]--;
			current_time++;

			if (remain_burst_time[k] == 0)
				p[k].completed = TRUE;
		}

		/* 현재 실행시간이 총 실행시간과 같을 경우 */
		else
		{
			/* 이전 실행 시간 만큼 \b 출력 */
			for (i = 0; i < count[pre_k] + 1; i++)
				printf("\b");

			/* 현재 process ID 출력 */
			printf("%2s", p[k].id);

			/* 간격을 맞추어 공백 출력 */
			for (i = 0; i < count[pre_k] - 1; i++)
				printf(" ");

			break;
			// 반복문 탈출
		}
	}

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	printf("|\n\t");

	/* 동일 알고리즘을 사용하여 하단 바 출력 */
	while (current_time < total_burst_time)
	{
		shortest_remain_time = INT_MAX;

		if (current_time <= p[len - 1].arrive_time)
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
					&& (p[i].arrive_time <= current_time)
						&& (shortest_remain_time > remain_burst_time[i]))
				{
					shortest_remain_time = remain_burst_time[i];
					k = i;
				}
			}
		}

		else
		{
			for (i = 0; i < len; i++)
			{
				if ((p[i].completed == FALSE)
					&& (shortest_remain_time > remain_burst_time[i]))
				{
					shortest_remain_time = remain_burst_time[i];
					k = i;
				}
			}
		}

		if (pre_k != k)
			printf(" ");

		printf("--");

		remain_burst_time[k]--;
		current_time++;
		pre_k = k;

		if (remain_burst_time[k] == 0)
			p[k].completed = TRUE;
	}

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
		p[i].completed = FALSE;
	}

	current_time = 0;
	printf("\n\t");

	/* process ID 출력과 같은 방법으로 실행하며 시간 출력 */
	while (current_time <= total_burst_time)
	{
		if (total_burst_time != current_time)
		{
			shortest_remain_time = INT_MAX;

			if (current_time <= p[len - 1].arrive_time)
			{
				for (i = 0; i < len; i++)
				{
					if ((p[i].completed == FALSE)
						&& (p[i].arrive_time <= current_time)
							&& (shortest_remain_time > remain_burst_time[i]))
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}

			else
			{
				for (i = 0; i < len; i++)
				{
					if ((p[i].completed == FALSE)
						&& (shortest_remain_time > remain_burst_time[i]))
					{
						shortest_remain_time = remain_burst_time[i];
						k = i;
					}
				}
			}


			if (pre_k != k)
			{
				for (i = 0; i < gap && current_time != 0; i++)
					printf("  ");

				if (current_time != 0)
					printf(" ");

				printf("%-2d", current_time);
				gap = 0;

				previous_time = current_time;
			}

			else
				gap++;

			remain_burst_time[k]--;
			current_time++;
			pre_k = k;

			if (remain_burst_time[k] == 0)
				p[k].completed = TRUE;
		}

		else
		{
			for (i = 0; i < current_time - previous_time - 1; i++)
				printf("  ");
			printf(" ");

			printf("%-2d", current_time);

			break;
		}
	}

	printf("\n");

	/* 동적 할당한 배열 메모리 할당 해제 */
	free(count);
	free(remain_burst_time);
}

void PSJF(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_response_time = 0;

	process_init(p, len);

	merge_sort_by_arrive_time(p, 0, len);
	// process들을 arrival time에 따라 오름차순으로 정렬

	psjf_calculate_time(p, len);
	// psjf_calculate_time 함수 호출로 process 시간 계산

	/* process의 갯수 만큼 반복 */
	for (i = 0; i < len; i++)
	{
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("\tPreemptive Shortest Job First Algorithm\n\n");

	psjf_print_gantt_chart(p, len);
	// psjf_print_gantt_chart 함수 호출로 간트 차트 출력

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

    fprintf(file, "Algorithm: Preemptive SJF\n");
    fprintf(file, "Average Waiting Time: %.2f\n", (double)total_waiting_time / (double)len);
    fprintf(file, "Average Turnaround Time: %.2f\n", (double)total_turnaround_time / (double)len);
	fprintf(file, "Average Response Time: %.2f\n", (double)total_response_time / (double)len);
    fprintf(file, "--------------------------\n");

    fclose(file);
}

#endif