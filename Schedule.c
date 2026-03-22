#include <stdio.h>

int main() {
    int n, i, j, tq;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], priority[n];
    int wt_fcfs[n], wt_sjf[n], wt_pr[n], wt_rr[n];
    int tat[n], ct[n], rem_bt[n];
    float avg_fcfs = 0, avg_sjf = 0, avg_pr = 0, avg_rr = 0;

    // Input
    for(i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        rem_bt[i] = bt[i];
    }

    // ---------------- FCFS ----------------
    ct[0] = at[0] + bt[0];
    wt_fcfs[0] = 0;

    for(i = 1; i < n; i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];

        tat[i] = ct[i] - at[i];
        wt_fcfs[i] = tat[i] - bt[i];
    }

    for(i = 0; i < n; i++)
        avg_fcfs += wt_fcfs[i];
    avg_fcfs /= n;

    // ---------------- SJF ----------------
    int bt_sjf[n], wt_temp[n];
    for(i = 0; i < n; i++) {
        bt_sjf[i] = bt[i];
        wt_temp[i] = 0;
    }

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(bt_sjf[i] > bt_sjf[j]) {
                int temp = bt_sjf[i];
                bt_sjf[i] = bt_sjf[j];
                bt_sjf[j] = temp;
            }
        }
    }

    wt_temp[0] = 0;
    for(i = 1; i < n; i++)
        wt_temp[i] = wt_temp[i-1] + bt_sjf[i-1];

    for(i = 0; i < n; i++)
        avg_sjf += wt_temp[i];
    avg_sjf /= n;

    // ---------------- Priority ----------------
    int pr[n], bt_pr[n];
    for(i = 0; i < n; i++) {
        pr[i] = priority[i];
        bt_pr[i] = bt[i];
    }

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(pr[i] > pr[j]) {
                int temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt_pr[i]; bt_pr[i] = bt_pr[j]; bt_pr[j] = temp;
            }
        }
    }

    wt_pr[0] = 0;
    for(i = 1; i < n; i++)
        wt_pr[i] = wt_pr[i-1] + bt_pr[i-1];

    for(i = 0; i < n; i++)
        avg_pr += wt_pr[i];
    avg_pr /= n;

    // ---------------- Round Robin ----------------
    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &tq);

    int time = 0, remain;
    for(i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        wt_rr[i] = 0;
    }

    remain = n;
    while(remain > 0) {
        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt_rr[i] = time - bt[i];
                    rem_bt[i] = 0;
                    remain--;
                }
            }
        }
    }

    for(i = 0; i < n; i++)
        avg_rr += wt_rr[i];
    avg_rr /= n;

    // ---------------- Results ----------------
    printf("\nAverage Waiting Time:");
    printf("\nFCFS = %.2f", avg_fcfs);
    printf("\nSJF = %.2f", avg_sjf);
    printf("\nPriority = %.2f", avg_pr);
    printf("\nRound Robin = %.2f\n", avg_rr);

    // Minimum
    float min = avg_fcfs;
    char algo[20] = "FCFS";

    if(avg_sjf < min) { min = avg_sjf; sprintf(algo, "SJF"); }
    if(avg_pr < min) { min = avg_pr; sprintf(algo, "Priority"); }
    if(avg_rr < min) { min = avg_rr; sprintf(algo, "Round Robin"); }

    printf("\nAlgorithm with Minimum Average Waiting Time = %s\n", algo);

    return 0;
}
