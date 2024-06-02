#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int process_id;
    int burst_time;
    int arrival_time;
    int priority;
} Process;

void generateRandomProcesses(Process p[], int n) {
    srand(time(NULL));  // Initialize random number generator seed

    int has_zero_arrival = 0;

    for (int i = 0; i < n; i++) {
        p[i].process_id = i;  // Process IDs start from 0
        p[i].burst_time = rand() % 10 + 1;  // Random burst time between 1 and 10
        p[i].arrival_time = rand() % 10;  // Random arrival time between 0 and 9
        if (p[i].arrival_time == 0) {
            has_zero_arrival = 1;
        }
        p[i].priority = rand() % 5 + 1;  // Random priority between 1 and 5
    }

    // Ensure at least one process has arrival time 0
    if (!has_zero_arrival) {
        p[0].arrival_time = 0;
    }
}

void printProcessesToFile(Process p[], int n, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d\n", n);  // Print number of processes

    for (int i = 0; i < n; i++) {
        fprintf(file, "P%d %d %d %d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].priority);
    }

    fprintf(file, "2\n");  // Additional constraint or information if needed

    fclose(file);
}

int main() {
    int n = 6;  // Number of processes
    Process p[n];

    generateRandomProcesses(p, n);
    printProcessesToFile(p, n, "process.txt");

    return 0;
}
