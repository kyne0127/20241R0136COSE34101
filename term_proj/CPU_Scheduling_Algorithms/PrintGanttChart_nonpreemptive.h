void print_gantt_chart_nonpreemptive(Process *p, int len)
{
    int i, j, curr_time = 0;

    printf("\t ");

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

    curr_time = 0;
    printf("0");
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