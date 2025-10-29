#include <stdio.h>
#include <string.h>

#define FLOORS 3
#define SLOTS 10

// Structure to store vehicle details
struct Vehicle {
    char number[20];
    char type[10];    // Bike, Car, Truck
    int entryTime;
    int exitTime;
    int isOccupied;   // 1 = slot filled, 0 = empty
};

// Function declarations
void initialize(struct Vehicle parking[FLOORS][SLOTS]);
void parkVehicle(struct Vehicle parking[FLOORS][SLOTS]);
void exitVehicle(struct Vehicle parking[FLOORS][SLOTS], int *totalRevenue);
void displayStatus(struct Vehicle parking[FLOORS][SLOTS]);
void endOfDayReport(struct Vehicle parking[FLOORS][SLOTS], int totalRevenue);

int main() {
    struct Vehicle parking[FLOORS][SLOTS];
    int choice, totalRevenue = 0;

    initialize(parking);

    do {
        printf("\n====== SMART VEHICLE PARKING SYSTEM ======\n");
        printf("1. Park Vehicle (Entry)\n");
        printf("2. Exit Vehicle\n");
        printf("3. Display Parking Status\n");
        printf("4. End of Day Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To clear newline from input buffer

        switch(choice) {
            case 1:
                parkVehicle(parking);
                break;
            case 2:
                exitVehicle(parking, &totalRevenue);
                break;
            case 3:
                displayStatus(parking);
                break;
            case 4:
                endOfDayReport(parking, totalRevenue);
                break;
            case 5:
                printf("\nThank you for using the Parking System!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}

// Initialize all parking slots as empty
void initialize(struct Vehicle parking[FLOORS][SLOTS]) {
    for(int i = 0; i < FLOORS; i++) {
        for(int j = 0; j < SLOTS; j++) {
            parking[i][j].isOccupied = 0;
        }
    }
}

// Function to park a vehicle
void parkVehicle(struct Vehicle parking[FLOORS][SLOTS]) {
    char number[20], type[10];
    int entry, parked = 0;

    printf("\nEnter Vehicle Number: ");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    printf("Enter Vehicle Type (bike/car/truck): ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = '\0';

    printf("Enter Entry Time (in hours, e.g., 10 for 10AM): ");
    scanf("%d", &entry);
    getchar();  // To clear newline from input buffer

    // Find first empty slot
    for(int i = 0; i < FLOORS && !parked; i++) {
        for(int j = 0; j < SLOTS && !parked; j++) {
            if(parking[i][j].isOccupied == 0) {
                strcpy(parking[i][j].number, number);
                strcpy(parking[i][j].type, type);
                parking[i][j].entryTime = entry;
                parking[i][j].isOccupied = 1;
                parked = 1;
                printf("\nVehicle parked at Floor %d, Slot %d\n", i + 1, j + 1);
            }
        }
    }

    if(!parked)
        printf("\nParking Full! No available slots.\n");
}

// Function to exit a vehicle and calculate charge
void exitVehicle(struct Vehicle parking[FLOORS][SLOTS], int *totalRevenue) {
    char number[20];
    int exitTime, duration, charge = 0, found = 0;

    printf("\nEnter Vehicle Number to Exit: ");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    for(int i = 0; i < FLOORS; i++) {
        for(int j = 0; j < SLOTS; j++) {
            if(parking[i][j].isOccupied == 1 && strcmp(parking[i][j].number, number) == 0) {
                found = 1;
                printf("Enter Exit Time (in hours): ");
                scanf("%d", &exitTime);
                getchar();  // To clear newline from input buffer

                duration = exitTime - parking[i][j].entryTime;
                if(duration <= 0)
                    duration = 1; // minimum 1 hour charge

                // Calculate charge based on vehicle type
                if(strcmp(parking[i][j].type, "bike") == 0)
                    charge = duration * 10; // 10 rupees per hour for bike
                else if(strcmp(parking[i][j].type, "car") == 0)
                    charge = duration * 20; // 20 rupees per hour for car
                else if(strcmp(parking[i][j].type, "truck") == 0)
                    charge = duration * 30; // 30 rupees per hour for truck
                else
                    charge = duration * 15; // default (15 rupees per hour if neither)

                printf("\nVehicle Found at Floor %d, Slot %d\n", i + 1, j + 1);
                printf("Parking Duration: %d hour(s)\n", duration);
                printf("Total Charge: Rupees %d\n", charge);

                *totalRevenue += charge;
                parking[i][j].isOccupied = 0; // Slot is now free
                break;
            }
        }
    }

    if(!found)
        printf("\nVehicle not found in the parking lot.\n");
}

// Display current parking status
void displayStatus(struct Vehicle parking[FLOORS][SLOTS]) {
    printf("\n------ Parking Status ------\n");
    for(int i = 0; i < FLOORS; i++) {
        printf("\nFloor %d: ", i + 1);
        for(int j = 0; j < SLOTS; j++) {
            if(parking[i][j].isOccupied)
                printf("[X] ");  // Occupied
            else
                printf("[ ] ");  // Empty
        }
        printf("\n");
    }
}

// Generate End of Day Report
void endOfDayReport(struct Vehicle parking[FLOORS][SLOTS], int totalRevenue) {
    int totalSlots = FLOORS * SLOTS;
    int usedSlots = 0;

    for(int i = 0; i < FLOORS; i++) {
        for(int j = 0; j < SLOTS; j++) {
            if(parking[i][j].isOccupied == 1)
                usedSlots++;
        }
    }

    float usagePercentage = ((float)usedSlots / totalSlots) * 100;

    printf("\n====== END OF DAY REPORT ======\n");
    printf("Total Parking Slots : %d\n", totalSlots);
    printf("Slots Occupied      : %d\n", usedSlots);
    printf("Usage Percentage    : %.2f%%\n", usagePercentage);
    printf("Total Revenue Earned: Rupees %d\n", totalRevenue);
    printf("=================================\n");
}
