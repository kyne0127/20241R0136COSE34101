void print_gantt_chart_pps(Process *p, int len)
{
    int i;
    int total_burst_time = 0;
    int curr_time = 0, previous_time = 0;
    int k, pre_k = -1;
    int priority, num;
    int idle = 0;

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

    while (curr_time < total_burst_time)
    {
        priority = INT_MAX;

        for (i = 0; i < len; i++)
        {
            if ((p[i].completed == FALSE)
                && (p[i].arrive_time <= curr_time))
            {
                if (priority > p[i].priority)
                {
                    priority = p[i].priority;
                    k = i;
                }
            }
        }

        if (pre_k != k)
            printf(" ");

        printf("--");
        remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
            p[k].completed = TRUE;
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    printf("\n\t|");
    curr_time = 0;

    while (curr_time < total_burst_time)
    {
        priority = INT_MAX;

        for (i = 0; i < len; i++)
        {
            if ((p[i].completed == FALSE)
                && (p[i].arrive_time <= curr_time))
            {
                if (priority > p[i].priority)
                {
                    priority = p[i].priority;
                    k = i;
                }
            }
        }

        if (curr_time == 0)
        {
            count[k]++;
            printf("  ");
        }
        else
        {
            if (pre_k != k)
            {
                num = count[pre_k] + 1;
                count[pre_k] = 0;
                count[k]++;

                for (i= 0; i < num; i++)
                    printf("\b");

                printf("%2s", p[pre_k].id);

                for (i = 0; i < num - 2; i++)
                    printf(" ");

                printf("|  ");
            }
            else
            {
                count[k]++;
                printf("  ");

                if (curr_time == total_burst_time - 1)
                {
                    num = count[pre_k] + 1;
                    count[pre_k] = 0;
                    count[k]++;

                    for (i = 0; i < num; i++)
                        printf("\b");

                    printf("%2s", p[pre_k].id);

                    for (i = 0; i < num - 2; i++)
                        printf(" ");
                }
            }
        }

        pre_k = k;
        remain_burst_time[k]--;
        curr_time++;

        if (remain_burst_time[k] == 0)
            p[k].completed = TRUE;
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    printf("|\n\t");
    curr_time = 0;

    while (curr_time < total_burst_time)
    {
        priority = INT_MAX;

        for (i = 0; i < len; i++)
        {
            if ((p[i].completed == FALSE)
                && (p[i].arrive_time <= curr_time))
            {
                if (priority > p[i].priority)
                {
                    priority = p[i].priority;
                    k = i;
                }
            }
        }

        if (pre_k != k)
            printf(" ");

        printf("--");

        remain_burst_time[k]--;
        curr_time++;
        pre_k = k;

        if (remain_burst_time[k] == 0)
            p[k].completed = TRUE;
    }

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].completed = FALSE;
    }

    curr_time = 0;
    num = 0;
    printf("\n\t");

    while (curr_time <= total_burst_time)
    {
        if (total_burst_time != curr_time)
        {
            priority = INT_MAX;

            for (i = 0; i < len; i++)
            {
                if ((p[i].completed == FALSE)
                    && (p[i].arrive_time <= curr_time))
                {
                    if (priority > p[i].priority)
                    {
                        priority = p[i].priority;
                        k = i;
                    }
                }
            }

            if (pre_k != k)
            {
                for (i = 0; i < num && curr_time != 0; i++)
                    printf("  ");

                if (curr_time != 0)
                    printf(" ");

                printf("%-2d", curr_time);
                num = 0;

                previous_time = curr_time;
            }

            else
                num++;

            remain_burst_time[k]--;
            curr_time++;
            pre_k = k;

            if (remain_burst_time[k] == 0)
                p[k].completed = TRUE;
        }

        else
        {
            for (i = 0; i < curr_time - previous_time - 1; i++)
                printf("  ");
            printf(" ");

            printf("%-2d", curr_time);

            break;
        }
    }

    printf("\n");

    free(count);
    free(remain_burst_time);
}