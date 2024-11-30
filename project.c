#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "train.h"

int generateRandom60to70() { return (rand() % 11) + 60; }
int generateRandom1to10() { return (rand() % 10) + 1; }
int generateRandom5Digit() { return (rand() % 90000) + 10000; }
int generateRandom15to30() { return (rand() % 16) + 15; }
int generateRandom80to90() { return (rand() % 11) + 80; }
long long generateRandom10Digit() { return (long long)(rand() % 9000000000LL) + 1000000000LL; }

int main() {
    srand(time(0));
    int loop = 1;

    char previous_from[250] = "", previous_to[250] = "";
    int previous_day = 0, previous_month = 0, previous_year = 0;
    int Train_1 = 0, Train_2 = 0, Train_3 = 0, Train_4 = 0, Train_5 = 0;
    int Train_1_seats = 0, Train_2_seats = 0, Train_3_seats = 0, Train_4_seats = 0, Train_5_seats = 0;

    while (loop == 1) {
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

        while (1) {
            printf("Enter the date of journey (in format DD-MM-YYYY, until 01-02-2025): ");
            scanf("%d-%d-%d", &day, &month, &year);

            if (day > 31 || year < 2024 || month > 12) {
                printf("Invalid date. Please check and enter a valid journey date.\n");
            } else {
                break;
            }
        }

        // Check if the journey details are the same as the previous booking
        int repeated = (strcmp(from, previous_from) == 0 && strcmp(to, previous_to) == 0 && day == previous_day && month == previous_month && year == previous_year);

        if (!repeated) {
            Train_1 = generateRandom5Digit();
            Train_2 = generateRandom5Digit();
            Train_3 = generateRandom5Digit();
            Train_4 = generateRandom5Digit();
            Train_5 = generateRandom5Digit();

            Train_1_seats = generateRandom60to70();
            Train_2_seats = generateRandom60to70();
            Train_3_seats = generateRandom15to30();
            Train_4_seats = generateRandom80to90();
            Train_5_seats = generateRandom15to30();

            // Update previous journey details
            strcpy(previous_from, from);
            strcpy(previous_to, to);
            previous_day = day;
            previous_month = month;
            previous_year = year;
        }

        printf("Available Trains:\n");
        printf("\nTrain Number: %d (Express)\n", Train_1);
        printf("Available berths: %d\n", Train_1_seats);
        printf("\nTrain Number: %d (Express)\n", Train_2);
        printf("Available berths: %d\n", Train_2_seats);
        printf("\nTrain Number: %d (Express)\n", Train_3);
        printf("Waiting list (RAC): %d\n", Train_3_seats);
        printf("\nTrain Number: %d (Passenger)\n", Train_4);
        printf("Available berths: %d\n", Train_4_seats);
        printf("\nTrain Number: %d (Passenger)\n", Train_5);
        printf("Waiting list (RAC): %d\n", Train_5_seats);
        printf("--------------------------------------------------------------------\n");
        printf("The trains that are Express are AC and Passenger are Non-AC!\n");

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

        // Deduct seats for the selected train
        if (Train_Number == Train_1) {
            Train_1_seats -= Seats;
        } else if (Train_Number == Train_2) {
            Train_2_seats -= Seats;
        } else if (Train_Number == Train_3) {
            Train_3_seats -= Seats;
        } else if (Train_Number == Train_4) {
            Train_4_seats -= Seats;
        } else if (Train_Number == Train_5) {
            Train_5_seats -= Seats;
        }

        char names[4][250];
        char Seat_Preference[4];

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

        double fare = (Train_Number == Train_1 || Train_Number == Train_2) ? 950 : 650;
        double Total_Fare = fare * Seats * 1.18;
        printf("The fare (incl. GST) is %.2lf\n", Total_Fare);

        int confirm_code;
        while (1) {
            if (Train_Number == Train_1 || Train_Number == Train_2 || Train_Number == Train_3) {
                printf("Enter 1234567890 to confirm payment: ");
                scanf("%d", &confirm_code);
                if (confirm_code == 1234567890) {
                    break;
                }
            } else {
                printf("Enter 123456789 to confirm payment: ");
                scanf("%d", &confirm_code);
                if (confirm_code == 123456789) {
                    break;
                }
            }
            printf("Incorrect confirmation code. Please enter the correct code.\n");
        }

        long long PNR = generateRandom10Digit();

        createTicketFile(Train_Number, from, to, day, month, year, Seats, names, Seat_Preference, PNR);

        printf("Congratulations! Ticket has been booked.\n");

        printf("\nEnter 1 for booking another ticket");
        printf("\nEnter any other for exiting\n");
        scanf("%d", &loop);

        if (loop != 1) {
            printf("Exited\n");
        }
    }
    return 0;
}

