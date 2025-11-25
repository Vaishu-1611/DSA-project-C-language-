#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5   // Parking slots
#define MAXQ 10 // Waiting queue size

// -------------------- STACK (Parking Lot) --------------------
typedef struct {
    char car[20];
} Car;

Car parking[MAX];
int top = -1;

// -------------------- TEMPORARY STACK --------------------
Car tempStack[MAX];
int tempTop = -1;

// -------------------- QUEUE (Waiting Area) --------------------
Car queue[MAXQ];
int front = -1, rear = -1;

// -------------------- Stack Functions --------------------
int isParkingFull() {
    return (top == MAX - 1);
}

int isParkingEmpty() {
    return (top == -1);
}

void pushParking(Car c) {
    if (isParkingFull()) {
        printf("Parking is full. Can't add.\n");
        return;
    }
    parking[++top] = c;
}

Car popParking() {
    return parking[top--];
}

// -------------------- Temp Stack Functions --------------------
void pushTemp(Car c) {
    tempStack[++tempTop] = c;
}

Car popTemp() {
    return tempStack[tempTop--];
}

// -------------------- Queue Functions --------------------
int isQueueFull() {
    return (rear == MAXQ - 1);
}

int isQueueEmpty() {
    return (front == -1);
}

void enqueue(Car c) {
    if (isQueueFull()) {
        printf("Waiting queue is full!\n");
        return;
    }
    if (isQueueEmpty()) front = 0;
    queue[++rear] = c;
}

Car dequeue() {
    Car c = queue[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return c;
}

// -------------------- Parking Operations --------------------

void parkCar() {
    Car c;
    printf("Enter car number: ");
    scanf("%s", c.car);

    if (!isParkingFull()) {
        pushParking(c);
        printf("Car %s parked successfully at slot %d.\n", c.car, top + 1);
    } else {
        enqueue(c);
        printf("Parking full! Car %s added to waiting queue.\n", c.car);
    }
}

void removeCar() {
    if (isParkingEmpty()) {
        printf("Parking is empty!\n");
        return;
    }

    char carNum[20];
    printf("Enter car number to exit: ");
    scanf("%s", carNum);

    int found = 0;

    // Move cars until we find the target
    while (!isParkingEmpty()) {
        Car c = popParking();
        if (strcmp(c.car, carNum) == 0) {
            printf("Car %s removed successfully.\n", carNum);
            found = 1;
            break;
        } else {
            pushTemp(c); // move to temp stack
        }
    }

    // Restore cars from temp stack back to parking
    while (tempTop != -1) {
        pushParking(popTemp());
    }

    if (!found) {
        printf("Car not found in parking.\n");
        return;
    }

    // If waiting queue has cars, move one into parking
    if (!isQueueEmpty()) {
        Car nextCar = dequeue();
        pushParking(nextCar);
        printf("Car %s moved from waiting queue to parking.\n", nextCar.car);
    }
}

void displayStatus() {
    printf("\n--- PARKING LOT STATUS ---\n");

    if (isParkingEmpty()) {
        printf("Parking empty.\n");
    } else {
        printf("Cars in parking (bottom → top):\n");
        for (int i = 0; i <= top; i++) {
            printf("Slot %d → %s\n", i + 1, parking[i].car);
        }
    }

    printf("\n--- WAITING QUEUE ---\n");
    if (isQueueEmpty()) {
        printf("No cars in waiting queue.\n");
    } else {
        for (int i = front; i <= rear; i++) {
            printf("[%s] ", queue[i].car);
        }
        printf("\n");
    }
}

void searchCar() {
    char carNum[20];
    printf("Enter car number to search: ");
    scanf("%s", carNum);

    for (int i = 0; i <= top; i++) {
        if (strcmp(parking[i].car, carNum) == 0) {
            printf("Car %s is parked at slot %d.\n", carNum, i + 1);
            return;
        }
    }

    // search in queue
    for (int i = front; i <= rear; i++) {
        if (strcmp(queue[i].car, carNum) == 0) {
            printf("Car %s is in waiting queue at position %d.\n", carNum, i - front + 1);
            return;
        }
    }

    printf("Car not found.\n");
}

// -------------------- Main Menu --------------------
int main() {
    int choice;

    while (1) {
        printf("\n\n===== PARKING LOT SYSTEM =====\n");
        printf("1. Park Car\n");
        printf("2. Remove Car\n");
        printf("3. Display Status\n");
        printf("4. Search Car\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: displayStatus(); break;
            case 4: searchCar(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}