#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty;        
int buffer_size;  
int buffer[100]; 
int in = 0;      
int out = 0;     


void viewBuffer() {
    if (full == 0) {
        printf("\n>>> Current Buffer: [ EMPTY ]");
       
    } else {
        printf("\n>>> Current Buffer: [ ");
        for (int i = 0; i < full; i++) {
            int index = (out + i) % buffer_size;
            printf("%d ", buffer[index]);
        }
        printf("]");
    }
    printf("\n-------------------------------------------");
}

void displayStatus() {
    printf("\n[STATUS] Mutex: %d | Full: %d | Empty: %d", mutex, full, empty);
    
    viewBuffer();
}

void producer() {
    int val;
    
    
    if (mutex == 1 && empty != 0) {
        printf("\nEnter the value to produce: ");
        scanf("%d", &val);

        --empty; 
        --mutex; 

        buffer[in] = val; 
        printf("\nProducer produced: %d at slot %d", val, in);
        in = (in + 1) % buffer_size; 

        ++mutex; 
        ++full;  
        displayStatus();
    } else {
        printf("\nBuffer is FULL, Cannot produce, Producer needs to wait.");
    }
}

void consumer() {
    
    if (mutex == 1 && full != 0) {
        --full;  
        --mutex; 

        int consumed_val = buffer[out]; 
        printf("\nConsumer consumed: %d from slot %d", consumed_val, out);
        out = (out + 1) % buffer_size; 

        ++mutex; 
        ++empty; 
        displayStatus();
    } else {
        printf("\nBuffer is EMPTY, Nothing to consume, Consumer need to wait.");
    }
}

int main() {
    int choice;

    printf("Enter the size of the buffer: ");
    scanf("%d", &buffer_size);
    empty = buffer_size; 

    printf("\n--- MENU ---");
    printf("\n1. Producer (Add Value)");
    printf("\n2. Consumer (Remove Value)");
    printf("\n3. Exit");

    while (1) {
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: exit(0);
            default: printf("\nInvalid choice!");
        }
    }
    return 0;
}
