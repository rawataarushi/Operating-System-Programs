#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;        // arrival time
    int bt;        // burst time
    int priority;  // smaller = higher priority
    int rt;        // remaining time
    int ct;        // completion time
    int tat;       // turnaround time
    int wt;        // waiting time
};
int main() {
    int n, i, time = 0, completed = 0;
    float avg_tat = 0, avg_wt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter Priority for P%d (smaller = higher): ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt; // initially remaining time = burst time
    }
    printf("\nGantt Chart: ");
    while (completed < n) {
        int idx = -1;
        int minPriority = 9999;
        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                }
                else if (p[i].priority == minPriority && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            printf("| P%d ", p[idx].pid);
            p[idx].rt--; 
            time++;
            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                avg_tat += p[idx].tat;
                avg_wt += p[idx].wt;
            }
        } else {
            printf("| idle ");
            time++;
        }
    }
    printf("|\n");
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t\t%d\t%d\t%d",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\n\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    return 0;
}
