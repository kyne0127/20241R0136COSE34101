#include <limits.h>

void print_gantt_chart_rr(Process *p, int len, Quantum q)
{
    int i, j;
    // Variables for loop
    int curr_time = 0;
    int time = 0;
    int flag = 1;
    int double_checker = 0;
    int prev_idle = 0;
    // Array to store remaining burst time for each process
    int *remain_burst_time = (int *)malloc(sizeof(int) * len);

    // Initialize processes
    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].available = TRUE;
        p[i].completed = FALSE;
    }

    printf("\t ");

    while (flag)
    {
        double_checker = 0;
        time = curr_time;
        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (remain_burst_time[i] > 0)
                {
                    if (remain_burst_time[i] < q)
                    {
                        printf(" ");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < remain_burst_time[i]; j++)
                            printf("--");
                    }

                    else
                    {
                        printf(" ");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < q; j++)
                            printf("--");
                    }

                    if (remain_burst_time[i] > q)
                    {
                        curr_time += q;
                        remain_burst_time[i] -= q;
                    }

                    else
                    {
                        curr_time += remain_burst_time[i];
                        remain_burst_time[i] = 0;
                        p[i].completed = TRUE;
                    }
                }
            }
            else {
                double_checker++;
            }
        }

        if (double_checker == len) {
            printf("xx");
            prev_idle = 1;
            // printf("{%d}", prev_idle);
            curr_time++;
        }

        // Check if all processes are completed
        flag = 0;
        for (i = 0; i < len; i++)
        {
            if(p[i].completed == FALSE) {
                flag = 1;
                break;
            }
        }
    }

    printf("\n\t ");

    curr_time = 0;
    time = 0;
    flag = 1;
    double_checker = 0;
    prev_idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].available = TRUE;
        p[i].completed = FALSE;
    }

    while (flag)
    {
        double_checker = 0;
        time = curr_time;
        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (remain_burst_time[i] > 0)
                {
                    if (remain_burst_time[i] < q)
                    {
                        printf("|");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        printf("%s", p[i].id);
                        for (j = 1; j < remain_burst_time[i]; j++)
                            printf("  ");
                    }

                    else
                    {
                        printf("|");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        printf("%s", p[i].id);
                        for (j = 1; j < q; j++)
                            printf("  ");
                    }

                    if (remain_burst_time[i] > q)
                    {
                        curr_time += q;
                        remain_burst_time[i] -= q;
                    }

                    else
                    {
                        curr_time += remain_burst_time[i];
                        remain_burst_time[i] = 0;
                        p[i].completed = TRUE;
                    }
                }
            }
            else {
                double_checker++;
            }
        }

        if (double_checker == len) {
            printf("  ");
            prev_idle = 1;
            // printf("{%d}", prev_idle);
            curr_time++;
        }

        // Check if all processes are completed
        flag = 0;
        for (i = 0; i < len; i++)
        {
            if(p[i].completed == FALSE) {
                flag = 1;
                break;
            }
        }
    }
    printf("|");

    printf("\n\t ");

    //하단바 출력

    curr_time = 0;
    time = 0;
    flag = 1;
    double_checker = 0;
    prev_idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].available = TRUE;
        p[i].completed = FALSE;
    }

    while (flag)
    {
        double_checker = 0;
        time = curr_time;
        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (remain_burst_time[i] > 0)
                {
                    if (remain_burst_time[i] < q)
                    {
                        printf(" ");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < remain_burst_time[i]; j++)
                            printf("--");
                    }

                    else
                    {
                        printf(" ");
                        if (prev_idle == 1) {
                            printf("\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < q; j++)
                            printf("--");
                    }

                    if (remain_burst_time[i] > q)
                    {
                        curr_time += q;
                        remain_burst_time[i] -= q;
                    }

                    else
                    {
                        curr_time += remain_burst_time[i];
                        remain_burst_time[i] = 0;
                        p[i].completed = TRUE;
                    }
                }
            }
            else {
                double_checker++;
            }
        }

        if (double_checker == len) {
            printf("xx");
            prev_idle = 1;
            // printf("{%d}", prev_idle);
            curr_time++;
        }

        // Check if all processes are completed
        flag = 0;
        for (i = 0; i < len; i++)
        {
            if(p[i].completed == FALSE) {
                flag = 1;
                break;
            }
        }
    }

    printf("\n\t");

    curr_time = 0;
    time = 0;
    flag = 1;
    double_checker = 0;
    prev_idle = 0;

    for (i = 0; i < len; i++)
    {
        remain_burst_time[i] = p[i].burst;
        p[i].available = TRUE;
        p[i].completed = FALSE;
    }

    printf("%d", curr_time);

    while (flag)
    {
        double_checker = 0;
        time = curr_time;
        for (i = 0; i < len; i++)
        {
            if (curr_time >= p[i].io_start_time && curr_time < p[i].io_start_time + p[i].io_duration)
            {
                p[i].available = FALSE;
            }
            else {
                p[i].available = TRUE;
            }

            if (p[i].completed == FALSE && p[i].arrive_time <= curr_time && p[i].available == TRUE)
            {
                if (remain_burst_time[i] > 0)
                {
                    if (remain_burst_time[i] < q)
                    {
                        printf("\b%2d", curr_time);
                        if (prev_idle == 1) {
                            printf("\b\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < remain_burst_time[i]; j++)
                            printf("  ");
                    }

                    else
                    {
                        printf("\b%2d", curr_time);
                        if (prev_idle == 1) {
                            printf("\b\b");
                            prev_idle = 0;
                        }
                        for (j = 0; j < q; j++)
                            printf("  ");
                    }

                    if (remain_burst_time[i] > q)
                    {
                        curr_time += q;
                        remain_burst_time[i] -= q;
                    }

                    else
                    {
                        curr_time += remain_burst_time[i];
                        remain_burst_time[i] = 0;
                        p[i].completed = TRUE;
                    }
                }
            }
            else {
                double_checker++;
            }
        }

        if (double_checker == len) {
            printf("   ");
            prev_idle = 1;
            curr_time++;
        }

        // Check if all processes are completed
        flag = 0;
        for (i = 0; i < len; i++)
        {
            if(p[i].completed == FALSE) {
                flag = 1;
                break;
            }
        }
    }

    printf("\b%2d", curr_time);

    printf("\n");

    free(remain_burst_time);
}
