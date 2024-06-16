#include <limits.h>

void print_gantt_chart_psjf(Process *p, int len)
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

// {
//     int i;
//     int total_burst_time = 0;
//     int curr_time = 0, previous_time;
//     int k, pre_k = 0;
//     int shortest_remain_time, gap;


//     int *remain_burst_time = (int *)malloc(sizeof(int) * len);
//     int *count = (int *)malloc(sizeof(int) * len);

//     int flag = 1;
//     int idle = 0;

//     for (i = 0; i < len; i++)
//     {
//         remain_burst_time[i] = p[i].burst;
//         total_burst_time += p[i].burst;
//         p[i].completed = FALSE;
//         p[i].available == TRUE;
//         count[i] = 0;
//     }

//     printf("\t ");

//     while (flag)
//     {
//         shortest_remain_time = INT_MAX;
//         k = -1;

//         for (i = 0; i < len; i++)
//         {
//             if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
//             {
//                 p[i].available = FALSE;
//             }
//             else {
//                 p[i].available = TRUE;
//             }
//         }

//         for (i = 0; i < len; i++)
//         {
//             if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
//             {
//                 shortest_remain_time = remain_burst_time[i];
//                 k = i;
//                 idle += 1;
//             }
//         }

//         if (pre_k != k)
//         {
//             printf(" ");
//         }

//         idle = 0;

//         if (idle == 0) {
//             printf("xx");
//         }
//         else {
//             printf("--");
//         }
//         remain_burst_time[k]--;
//         curr_time++;
//         pre_k = k;

//         if (remain_burst_time[k] == 0)
//         {
//             p[k].completed = TRUE;
//         }

//         for (i = 0; i < len; i++)
//         {
//             if(p[i].completed == TRUE) {
//                 flag += 1;
//             }
//         }
//         if ((flag-1)==len) {
//             flag = 0; 
//         }
//         else {
//             flag = 1;
//         }
//     }

//     // print PID

//     printf("\n\t ");

//     pre_k = 0;
//     curr_time = 0;
//     previous_time = 0;

//     flag = 1;
//     idle = 0;

//    for (i = 0; i < len; i++)
//     {
//         remain_burst_time[i] = p[i].burst;
//         p[i].completed = FALSE;
//         p[i].available == TRUE;
//     }

//     while (flag)
//     {
//         shortest_remain_time = INT_MAX;
//         k = -1;

//         for (i = 0; i < len; i++)
//         {
//             if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
//             {
//                 p[i].available = FALSE;
//             }
//             else {
//                 p[i].available = TRUE;
//             }
//         }

//         for (i = 0; i < len; i++)
//         {
//             if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
//             {
//                 shortest_remain_time = remain_burst_time[i];
//                 k = i;
//                 idle += 1;
//             }
//         }

//         if (curr_time == 0)
//         {
//             count[k]++;
//             printf("  ");
//         }

//         else
//         {
//             if (pre_k != k){
//                 gap = count[pre_k] + 1;
//                 count[pre_k] = 0;
//                 count[k]++;

//                 for (i=0; i<gap; i++)
//                     printf("\b");

//                 printf("%2s", p[pre_k].id);

//                 for (i=0; i<gap; i++)
//                     printf(" ");

//                 printf("|  ");
//             }
//             else
// 				{
// 					count[k]++;
// 					// 현재 process 카운트 증가

// 					printf("  ");
// 					// 공백 출력
// 				}
//         }

//         pre_k = k;
//         remain_burst_time[k]--;
//         curr_time++;
        
//         // while 문 종료조건
//         for (i = 0; i < len; i++)
//         {
//             if(p[i].completed == TRUE) {
//                 flag += 1;
//             }
//         }
//         if ((flag-1)==len) {
//             flag = 0; 
//         }
//         else {
//             flag = 1;
//         }
//     }
    

//     // print bottom

//     printf("\n\t ");

//     pre_k = 0;
//     curr_time = 0;
//     previous_time = 0;

//     flag = 1;
//     idle = 0;

//    for (i = 0; i < len; i++)
//     {
//         remain_burst_time[i] = p[i].burst;
//         p[i].completed = FALSE;
//         p[i].available == TRUE;
//     }

//     while (flag)
//     {
//         shortest_remain_time = INT_MAX;
//         k = -1;

//         for (i = 0; i < len; i++)
//         {
//             if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
//             {
//                 p[i].available = FALSE;
//             }
//             else {
//                 p[i].available = TRUE;
//             }
//         }

//         for (i = 0; i < len; i++)
//         {
//             if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
//             {
//                 shortest_remain_time = remain_burst_time[i];
//                 k = i;
//                 idle += 1;
//             }
//         }

//         if (k == -1)
//         {
//             if (idle == 0) {
//                 printf("xx");
//             }
//             else {
//                 printf(" ");
//             }
//             curr_time++;
//             continue;
//         }

//         if (pre_k != k && pre_k != -1)
//         {
//             if (idle == 0) {
//                 printf("xx");
//             }
//             else {
//                 printf(" ");
//             }
//         }

//         idle = 0;

//         printf("--");
//         remain_burst_time[k]--;
//         curr_time++;
//         pre_k = k;

//         if (remain_burst_time[k] == 0)
//         {
//             p[k].completed = TRUE;
//         }

//         for (i = 0; i < len; i++)
//         {
//             if(p[i].completed == TRUE) {
//                 flag += 1;
//             }
//         }
//         if ((flag-1)==len) {
//             flag = 0; 
//         }
//         else {
//             flag = 1;
//         }
//     }

//     //print end_time

    

//     printf("\n");

//     free(count);

//     free(remain_burst_time);
// }