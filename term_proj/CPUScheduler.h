#ifndef __CPU__SCHEDULING__ALGORITHMS__
#define __CPU__SCHEDULING__ALGORITHMS__

/* user_header_file_declaration */
#include "./CPU_Scheduling_Algorithms/0_FCFS.h"
#include "./CPU_Scheduling_Algorithms/1_non_preemptive_SJF.h"
#include "./CPU_Scheduling_Algorithms/2_preemptive_SJF.h"
#include "./CPU_Scheduling_Algorithms/3_non_preemptive_Priority.h"
#include "./CPU_Scheduling_Algorithms/4_preemptive_Priority.h"
#include "./CPU_Scheduling_Algorithms/5_RoundRobin.h"

void initialize_analysis_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error initializing file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}
// 파일 초기화 함수 선언

#endif