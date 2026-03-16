#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty;        
int buffer_size;  
int x = 0;    

void displayStatus() {
    printf("\n\n[STATUS] Mutex: %d | Full: %d | Empty: %d", mutex, full, empty);
    printf("\n-------------------------------------------");
}

void producer() {
    
    if (mutex == 1 && empty != 0) {
        --mutex;  
        --empty;  
        x++;      
        printf("\nProducer produces item %d", x);
        
        ++full;   
        ++mutex;  
        displayStatus();
    } else {
        printf("\nBuffer is FULL! Producer must wait.");
    }
}

void consumer() {
    
    if (mutex == 1 && full != 0) {
        --mutex;  
        --full;   
        printf("\nConsumer consumes item %d", x);
        x--;      
        
        ++empty;  
        ++mutex;  
        displayStatus();
    } else {
        printf("\nBuffer is EMPTY! Consumer must wait.");
    }
}

int main() {
    int choice;

   
    printf("Enter the size of the buffer: ");
    scanf("%d", &buffer_size);
    
    
    empty = buffer_size; 

    printf("\n1. Producer\n2. Consumer\n3. Exit");
    displayStatus();

    while (1) {
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("\nInvalid choice! Please select 1, 2, or 3.");
        }
    }
    return 0;
}
