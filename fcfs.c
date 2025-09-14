#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int rt;     // Response Time
    int start_time;
} Process;

Process ps[100];   

int findmax(int a, int b) {
    return (a > b) ? a : b;
}

// Sort by AT, then by PID (tie-breaker)
int comparatorAT_PID(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->at < p2->at) return -1;
    else if (p1->at > p2->at) return 1;
    else {
        if (p1->pid < p2->pid) return -1;  // Lower PID first
        else if (p1->pid > p2->pid) return 1;
        else return 0;
    }
}

// Sort back by PID for displaying results in order
int comparatorPID(const void *a, const void *b) {
    return ((Process *)a)->pid - ((Process *)b)->pid;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int length_cycle, total_idle_time = 0;
    float cpu_utilization;

    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        if (ps[i].at < 0) {
            printf("Invalid arrival time. Must be >= 0.\n");
            return 1;
        }
        ps[i].pid = i; // assign PID in input order
    }

    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        if (ps[i].bt <= 0) {
            printf("Invalid burst time. Must be > 0.\n");
            return 1;
        }
    }

    // Sort by AT, then PID
    qsort(ps, n, sizeof(Process), comparatorAT_PID);

    // Scheduling
    for (int i = 0; i < n; i++) {
        ps[i].start_time = (i == 0) ? ps[i].at : findmax(ps[i].at, ps[i - 1].ct);
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].start_time - ps[i].at;

        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;

        if (i > 0) {
            total_idle_time += (ps[i].start_time - ps[i - 1].ct);
        }
    }

    length_cycle = ps[n - 1].ct - ps[0].start_time;

    // Resort by PID for display
    qsort(ps, n, sizeof(Process), comparatorPID);

    printf("\nProcess No.\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt,
               ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    printf("\nAverage Turnaround Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time = %.2f", sum_wt / n);
    printf("\nAverage Response Time = %.2f", sum_rt / n);
    printf("\nThroughput = %.2f processes/unit time", n / (float)length_cycle);
    printf("\nCPU Utilization = %.2f%%", cpu_utilization * 100);
    printf("\n");

    return 0;
}
