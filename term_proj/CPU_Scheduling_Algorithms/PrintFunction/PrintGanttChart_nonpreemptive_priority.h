void print_gantt_chart_nonpreemptive_priority(Process *p, int len)
{
    printf("\t ");
    
    int i, j, curr_time = 0;

    for (i = 0; i < len; i++)
    {
        for (j = curr_time; j < p[i].end_time; j++)
        {
            printf("--");
            if (j >= p[i].io_start_time && j < p[i].io_start_time + p[i].io_duration)
            {
                printf("\b\bxx");
                curr_time++;
            }
        }
        curr_time += p[i].burst;
        printf(" ");
    }

    printf("\n\t|");

    curr_time = 0;

    for (i = 0; i < len; i++)
    {
        for (j = curr_time; j < p[i].end_time; j++)
        {
                for (j = curr_time; j < p[i].end_time; j++)
                {
                    if (j >= p[i].io_start_time && j < p[i].io_start_time + p[i].io_duration)
                    {
                        printf("  ");
                        curr_time++;
                    }
                    else
                    {
                        if (j == curr_time)
                        {
                            printf("%2s", p[i].id);
                        }
                        else
                        {
                            printf("  ");
                        }
                    }
            }
            curr_time += p[i].burst;
            printf("|");
        }
    }

    printf("\n\t ");

    curr_time = 0;

    for (i = 0; i < len; i++)
    {
        for (j = curr_time; j < p[i].end_time; j++)
        {
            printf("--");
            if (j >= p[i].io_start_time && j < p[i].io_start_time + p[i].io_duration)
            {
                printf("\b\bxx");
                curr_time++;
            }
        }
        curr_time += p[i].burst;
        printf(" ");
    }

    printf("\n\t");
    printf("0");

    curr_time = 0;
    int prev = 0;

    for (i = 0; i < len; i++)
    {
        for (j = curr_time; j < p[i].end_time; j++)
        {
            printf("  ");
        }
        curr_time = p[prev].end_time;
        prev += 1;
        printf("\b%2d", p[i].end_time);
    }
    printf("\n");
}