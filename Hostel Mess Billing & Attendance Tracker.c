#include <stdio.h>
#include <string.h>

#define DAYS 7       // Total days in a month (7 for simulation)
#define RATE 100      // Cost per day (Rupees 100)
#define MAX_STUDENTS 20

// Structure to store student details
struct Student {
    int id;
    char name[50];
    int attendance[DAYS];  // 1 = present, 0 = absent
    int totalDays;
    float billAmount;
    int billPaid;          // 1 = paid, 0 = unpaid
};

// Function declarations
void markAttendance(struct Student students[], int n);
void calculateBills(struct Student students[], int n);
void displaySummary(struct Student students[], int n);
void unpaidStudents(struct Student students[], int n);

int main() {
    struct Student students[MAX_STUDENTS];
    int n, choice;

    printf("Enter number of students: ");
    scanf("%d", &n);
    getchar(); // To clear newline from input buffer

    // Input student details
    for(int i = 0; i < n; i++) {
        students[i].totalDays = 0;
        students[i].billPaid = 0;
        printf("\nEnter details for student %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        getchar();

        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // remove newline

        // Initialize attendance to 0
        for(int d = 0; d < DAYS; d++)
            students[i].attendance[d] = 0;
    }

    // Menu-driven program
    do {
        printf("\n====== HOSTEL MESS MANAGEMENT SYSTEM ======\n");
        printf("1. Mark Attendance\n");
        printf("2. Calculate Bills\n");
        printf("3. Display Summary\n");
        printf("4. Show Students with Unpaid Bills\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                markAttendance(students, n);
                break;
            case 2:
                calculateBills(students, n);
                break;
            case 3:
                displaySummary(students, n);
                break;
            case 4:
                unpaidStudents(students, n);
                break;
            case 5:
                printf("\nExiting system. Thank you!\n");
                break;
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    } while(choice != 5);

    return 0;
}

// Function to mark attendance
void markAttendance(struct Student students[], int n) {
    int day;
    printf("\nEnter the day number (1-%d): ", DAYS);
    scanf("%d", &day);
    getchar();

    if(day < 1 || day > DAYS) {
        printf("Invalid day number.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        int present;
        printf("Is %s (ID: %d) present today? (1 = Yes, 0 = No): ", students[i].name, students[i].id);
        scanf("%d", &present);
        getchar();

        students[i].attendance[day - 1] = present;
    }

    printf("\nAttendance for Day %d recorded successfully!\n", day);
}

// Function to calculate bills
void calculateBills(struct Student students[], int n) {
    for(int i = 0; i < n; i++) {
        int presentDays = 0;

        for(int d = 0; d < DAYS; d++)
            if(students[i].attendance[d] == 1)
                presentDays++;

        students[i].totalDays = presentDays;
        float bill = presentDays * RATE;
        int absentDays = DAYS - presentDays;

        // Discount if absent for more than 5 days
        if(absentDays > 5) {
            float discount = bill * 0.10;
            bill -= discount;
            printf("\n%s (ID: %d) gets a discount of Rupees %.2f for %d days leave.\n",
                   students[i].name, students[i].id, discount, absentDays);
        }

        students[i].billAmount = bill;

        printf("\n%s (ID: %d): Total Days = %d, Bill = Rupees %.2f\n",
               students[i].name, students[i].id, presentDays, bill);

        printf("Has the student paid the bill? (1 = Yes, 0 = No): ");
        scanf("%d", &students[i].billPaid);
        getchar();
    }
    printf("\nBills calculated and payment status updated!\n");
}

// Function to display summary of all students
void displaySummary(struct Student students[], int n) {
    printf("\n====== MONTHLY SUMMARY ======\n");
    printf("ID\tName\t\tDays\tBill(Rupees)\tStatus\n");
    printf("-----------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%-12s\t%d\t%.2f\t%s\n",
               students[i].id,
               students[i].name,
               students[i].totalDays,
               students[i].billAmount,
               students[i].billPaid ? "Paid" : "Unpaid");
    }
}

// Function to display unpaid students
void unpaidStudents(struct Student students[], int n) {
    printf("\n====== UNPAID STUDENTS ======\n");
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(students[i].billPaid == 0) {
            printf("ID: %d | Name: %s | Due: Rupees %.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].billAmount);
            found = 1;
        }
    }
    if(!found)
        printf("All students have paid their bills!\n");
}
