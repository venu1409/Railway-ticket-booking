#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "irctc.c"

//inka ticket numbers set avaled code ni malli remodel cheyali


// Functions to generate random numbers within specific ranges
int generateRandom60to70() { return (rand() % 11) + 60; }
int generateRandom1to10() { return (rand() % 10) + 1; }
int generateRandom5Digit() { return (rand() % 90000) + 10000; }
int generateRandom15to30() { return (rand() % 16) + 15; }
int generateRandom80to90() { return (rand() % 11) + 80; }
long long generateRandom10Digit() { return (long long)(rand() % 9000000000LL) + 1000000000LL; }

int main() {
    srand(time(0));

    char from[250], to[250];
    int day, month, year;

    while (1) {
        printf("Enter boarding station: ");
        scanf("%s", from);

        printf("Enter destination station: ");
        scanf("%s", to);

        if (strcmp(from, to) == 0) {
            printf("Invalid input. Boarding and destination stations cannot be the same.\n");
        } else {
            break;
        }
    }

    time_t t = time(NULL); //chatgpt
    struct tm *tm_info = localtime(&t); //chatgpt

    char date[11];
    strftime(date, sizeof(date), "%d-%m-%Y", tm_info);
    printf("Today's date: %s\n", date);

    while (1) {
        printf("Enter the date of journey (in format DD-MM-YYYY, until 01-02-2025): ");
        scanf(" %d- %d- %d", &day, &month, &year);

         if (day > 31 || year < 2024 || month > 12){
            printf("Invalid date. Please check and enter a valid journey date.\n");
        } else {
            break;
        }
    }

    // Generating random train numbers
    int Train_1 = generateRandom5Digit();
    int Train_2 = generateRandom5Digit();
    int Train_3 = generateRandom5Digit();
    int Train_4 = generateRandom5Digit();
    int Train_5 = generateRandom5Digit();

    printf("Available Trains:\n");
    if (day == tm_info->tm_mday && month == tm_info->tm_mon + 1 && year == tm_info->tm_year + 1900)/*chatgpt*/ {
        printf("\nTrain Number: %d (Express)\n", Train_1);
        printf("Available berths: %d\n", generateRandom60to70());
        printf("\nTrain Number: %d (Passenger)\n", Train_4);
        printf("Available berths: %d\n", generateRandom80to90());
        printf("\nTrain Number: %d (Passenger)\n", Train_5);
        printf("Waiting list (RAC): %d\n", generateRandom15to30());
        printf("--------------------------------------------------------------------\n");
        printf("The trains that are Express are AC and Passenger are Non-AC!\n");
    } else {
        printf("\nTrain Number: %d (Express)\n", Train_1);
        printf("Available berths: %d\n", generateRandom60to70());
        printf("\nTrain Number: %d (Express)\n", Train_2);
        printf("Available berths: %d\n", generateRandom60to70());
        printf("\nTrain Number: %d (Express)\n", Train_3);
        printf("Waiting list (RAC): %d\n", generateRandom1to10());
        printf("\nTrain Number: %d (Passenger)\n", Train_4);
        printf("Available berths: %d\n", generateRandom80to90());
        printf("\nTrain Number: %d (Passenger)\n", Train_5);
        printf("Waiting list (RAC): %d\n", generateRandom15to30());
        printf("--------------------------------------------------------------------\n");
        printf("The trains that are Express are AC and Passenger are Non-AC!\n");
        printf("--------------------------------------------------------------------\n");
    }

    int Train_Number, Seats;
    while (1) {
        printf("\nEnter Train number: ");
        scanf("%d", &Train_Number);

        if (Train_Number == Train_1 || Train_Number == Train_2 || Train_Number == Train_3 || Train_Number == Train_4 || Train_Number == Train_5) {
            break;
        } else {
            printf("Invalid train number. Please enter a valid train number.\n");
        }
    }

    while (1) {
        printf("Enter number of seats (max 4): ");
        scanf("%d", &Seats);
        if (Seats >= 1 && Seats <= 4) {
            break;
        } else {
            printf("Invalid number of seats. Please enter a number between 1 and 4.\n");
        }
    }

    char names[4][250];
    char Seat_Preference[4];
    int seatNumber[4]; // Array to store seat numbers for each passenger
    int window_seat = 1, middle_seat = 2, aisle_seat = 3; // Starting seat numbers for each type

    for (int i = 0; i < Seats; i++) {
        int Age;
        char Gender;

        printf("\nEnter details for passenger %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", names[i]);

        while (1) {
            printf("Age: ");
            scanf("%d", &Age);
            if (Age >= 1 && Age <= 99) break;
            printf("Invalid age. Please enter a valid age.\n");
        }

        while (1) {
            printf("Gender (M/F): ");
            scanf(" %c", &Gender);
            if (Gender == 'M' || Gender == 'm' || Gender == 'F' || Gender == 'f') break;
            printf("Invalid gender. Please enter 'M' or 'F'.\n");
        }

        if (i == 0) {
            char Gmail_Address[250];
            printf("Email: ");
            scanf("%s", Gmail_Address);
        }

        printf("Enter Seat Preference (W for Window, M for Middle, A for Aisle): ");
        scanf(" %c", &Seat_Preference[i]);
    }

    double fare;//change chesa
    if (Train_Number == Train_1 || Train_Number == Train_2)
    {
        fare = 950;
    }
    else if (Train_Number == Train_4)
    {
        fare = 650;
    }
    else
    {
        fare = 0;
    }
    double Total_Fare = fare * Seats * 1.18;
    printf("The fare (incl. GST) is %.2lf\n", Total_Fare);

    int confirm_code;//change chesa
    while (1) {
        if (Train_Number == Train_1 || Train_Number == Train_2 || Train_Number == Train_3) {
            printf("Enter 1234567890 to confirm payment: ");
            scanf("%lld", &confirm_code);
            if (confirm_code == 1234567890) {
                break;
            }
        } else {
            printf("Enter 123456789 to confirm payment: ");
            scanf("%lld", &confirm_code);
            if (confirm_code == 123456789) {
                break;
            }
        }
        printf("Incorrect confirmation code. Please enter the correct code.\n");
    }

    long long PNR = generateRandom10Digit();

    createTicketFile(Train_Number, from, to, day, month, year, Seats, names, Seat_Preference, PNR);

    printf("Congratulations! Ticket has been booked.\n");

    return 0;
}
