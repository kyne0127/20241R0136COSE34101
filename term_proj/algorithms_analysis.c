#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALGORITHMS 10
#define LINE_LENGTH 256

typedef struct {
    char name[50];
    double avg_waiting_time;
    double avg_turnaround_time;
    double cpu_utilization;
} AlgorithmResult;

void analyze_results(const char *filename);
void print_all_results(AlgorithmResult results[], int count);

int main() {
    analyze_results("algorithm_comparison.txt");
    return 0;
}

void analyze_results(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    AlgorithmResult results[MAX_ALGORITHMS];
    int count = 0;
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file) && count < MAX_ALGORITHMS) {
        if (strncmp(line, "Algorithm:", 10) == 0) {
            strncpy(results[count].name, line + 11, strlen(line) - 12); // Remove "Algorithm: "
            results[count].name[strlen(line) - 12] = '\0'; // Null-terminate the string

            if (fgets(line, sizeof(line), file)) {
                sscanf(line, "Average Waiting Time: %lf", &results[count].avg_waiting_time);
            }

            if (fgets(line, sizeof(line), file)) {
                sscanf(line, "Average Turnaround Time: %lf", &results[count].avg_turnaround_time);
            }

            if (fgets(line, sizeof(line), file)) {
                sscanf(line, "CPU Utilization rate: %lf", &results[count].cpu_utilization);
            }

            // Skip the separator line
            fgets(line, sizeof(line), file);

            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("No results found in the file.\n");
        return;
    }

    int best_waiting_index = 0;
    int best_turnaround_index = 0;
    int best_cpu_utilization_index = 0;

    for (int i = 1; i < count; i++) {
        if (results[i].avg_waiting_time < results[best_waiting_index].avg_waiting_time) {
            best_waiting_index = i;
        }
        if (results[i].avg_turnaround_time < results[best_turnaround_index].avg_turnaround_time) {
            best_turnaround_index = i;
        }
        if (results[i].cpu_utilization > results[best_cpu_utilization_index].cpu_utilization) {
            best_cpu_utilization_index = i;
        }
    }

    // Print all results
    print_all_results(results, count);

    printf("Best Algorithm by Average Waiting Time:\n");
    printf("Algorithm: %s\n", results[best_waiting_index].name);
    printf("Average Waiting Time: %.2f\n", results[best_waiting_index].avg_waiting_time);
    printf("--------------------------\n");

    printf("Best Algorithm by Average Turnaround Time:\n");
    printf("Algorithm: %s\n", results[best_turnaround_index].name);
    printf("Average Turnaround Time: %.2f\n", results[best_turnaround_index].avg_turnaround_time);
    printf("--------------------------\n");

    printf("Best Algorithm by CPU Utilization Rate:\n");
    printf("Algorithm: %s\n", results[best_cpu_utilization_index].name);
    printf("CPU Utilization Rate: %.2f%%\n", results[best_cpu_utilization_index].cpu_utilization);
    printf("--------------------------\n");
}

void print_all_results(AlgorithmResult results[], int count) {
    printf("\nAll Algorithm Results:\n");
    printf("+-------------------------------------+-----------------------+---------------------------+------------------------+\n");
    printf("|            Algorithm                | Average Waiting Time  | Average Turnaround Time   | CPU Utilization Rate   |\n");
    printf("+-------------------------------------+-----------------------+---------------------------+------------------------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-35s | %21.2f | %25.2f | %21.2f%% |\n",
               results[i].name, results[i].avg_waiting_time, results[i].avg_turnaround_time, results[i].cpu_utilization);
        printf("+-------------------------------------+-----------------------+---------------------------+------------------------+\n");
    }
}
