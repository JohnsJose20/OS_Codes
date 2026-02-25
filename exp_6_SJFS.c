#include <stdio.h>

int main() {
    int n, i, j;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[n], waiting[n], process[n];
    float avgWaiting = 0;

  
    for(i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(burst[i] > burst[j]) {
               
                int temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

   

    for(i = 1; i < n; i++) {
        waiting[i] = 0;
        for(j = 0; j < i; j++) {
            waiting[i] += burst[j];
        }
    }

    
    for(i = 0; i < n; i++) {
        avgWaiting += waiting[i];
    }

    avgWaiting /= n;


    printf("\nProcess\tBurst Time\tWaiting Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", process[i], burst[i], waiting[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWaiting);

    return 0;
}
