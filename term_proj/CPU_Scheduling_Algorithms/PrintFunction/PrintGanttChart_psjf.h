#include <limits.h>

void print_gantt_chart_psjf(Process *p, int len)
{
	int i;
    int curr_time = 0;
    int k = -1, pre_k = -1;
    int shortest_remain_time;

    int *remain_burst_time = (int *)malloc(sizeof(int) * len);
	int *count = (int *)malloc(sizeof(int) * len);

    int flag = 1;
	int idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
        p[i].available = TRUE;
    }

    printf("\t ");

    while (flag)
    {
        shortest_remain_time = INT_MAX;
        k = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else
            {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
            {
                shortest_remain_time = remain_burst_time[i];
                k = i;
				idle += 1;
            }
        }

        if (k == -1)
        {
            if (idle == 0) {
                printf("xx");
            }
            curr_time++;
            continue;
        }

        if (pre_k != k && pre_k != -1)
        {
            printf(" ");
        }
		idle = 0;

        printf("--");
        remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
        }

        flag = 0;
        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE)
            {
                flag = 1;
                break;
            }
        }
    }
	// PID 출력
	curr_time = 0;
	pre_k = -1;
	printf("\n\t|");

	flag = 1;
	idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
        p[i].available = TRUE;
		count[i] = 0;
    }

	while (flag)
    {
        shortest_remain_time = INT_MAX;
        k = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else
            {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
            {
                shortest_remain_time = remain_burst_time[i];
                k = i;
				idle += 1;
            }
        }

		if (k == -1)
        {
            if (idle == 0) {
                printf("  ");
            }
            curr_time++;
            continue;
        }

        if (pre_k != k && pre_k != -1)
        {
            printf("|");
        }

		if (pre_k != k)
		{
			count[pre_k] = 0;
			// 이전 process 카운트 초기화
			count[k]++;
			printf("%2s", p[k].id);
		}
		else {
			count[k]++;

			printf("  ");
		}

		idle = 0;

		remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

		//종료 조건
        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
        }

        flag = 0;
        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE)
            {
                flag = 1;
                break;
            }
        }
    }
	printf("|");
	printf("\n\t ");

	// 하단바 출력
	curr_time = 0;
	pre_k = -1;
	flag = 1;
	idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
        p[i].available = TRUE;
    }

    while (flag)
    {
        shortest_remain_time = INT_MAX;
        k = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else
            {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
            {
                shortest_remain_time = remain_burst_time[i];
                k = i;
				idle += 1;
            }
        }

        if (k == -1)
        {
            if (idle == 0) {
                printf("xx");
            }
            curr_time++;
            continue;
        }

        if (pre_k != k && pre_k != -1)
        {
            printf(" ");
        }
		idle = 0;

        printf("--");
        remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
        }

        flag = 0;
        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE)
            {
                flag = 1;
                break;
            }
        }
    }
	printf("\n\t");

	//시간 출력
	curr_time = 0;
	pre_k = -1;
	flag = 1;
	idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
        p[i].available = TRUE;
		count[i] = 0;
    }

    printf("%d", curr_time);

	while (flag)
    {
        shortest_remain_time = INT_MAX;
        k = -1;

        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else
            {
                p[i].available = TRUE;
            }
        }

        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && remain_burst_time[i] < shortest_remain_time && p[i].available == TRUE)
            {
                shortest_remain_time = remain_burst_time[i];
                k = i;
            }
            idle += 1;
        }

		if (k == -1)
        {
            if (idle > 0) {
                printf("  ");
            }
            curr_time++;
            continue;
        }

        if (pre_k != k && pre_k != -1)
        {
            printf("\b%2d", curr_time);
        }

		if (pre_k != k)
		{
			count[pre_k] = 0;
			// 이전 process 카운트 초기화
			count[k]++;
			printf("  ");
		}
		else {
			count[k]++;

			printf("  ");
		}

		idle = 0;

		remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

		//종료 조건
        if (remain_burst_time[k] == 0)
        {
            p[k].completed = TRUE;
        }

        flag = 0;
        for (i = 0; i < len; i++)
        {
            if (p[i].completed == FALSE)
            {
                flag = 1;
                break;
            }
        }
    }
	printf("\b%2d", curr_time);
	printf("\n");

    free(remain_burst_time);
}