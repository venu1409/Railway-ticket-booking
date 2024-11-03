#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number between 60 and 70
int generateRandom60to70() {
    return (rand() % 11) + 60;
}

// Function to generate a random number between 1 and 10
int generateRandom1to10() {
    return (rand() % 10) + 1;
}

// Function to generate a random 5-digit number
int generateRandom5Digit() {
    return (rand() % 90000) + 10000;
}

// Function to generate a random number between 15 and 30
int generateRandom15to30() {
    return (rand() % 16) + 15;
}

// Function to generate a random number between 80 and 90
int generateRandom80to90() {
    return (rand() % 11) + 80;
}

// Function to generate a random 10-digit PNR
long long generateRandom10Digit() {
    return (long long)(rand() % 9000000000LL) + 1000000000LL;
}

// Function to create the ticket file
void createTicketFile(const char *from, const char *to, int day, int month, int year, int seatCount, char names[][250], long long PNR) {
    FILE *file = fopen("ticket.txt", "w");
    if (file == NULL) {
        printf("Error creating ticket file!\n");
        exit(1);
    }

    fprintf(file, "Ticket Booking Confirmation\n");
    fprintf(file, "---------------------------\n");
    fprintf(file, "Journey Details:\n");
    fprintf(file, "From: %s\n", from);
    fprintf(file, "To: %s\n", to);
    fprintf(file, "Date of Journey: %02d-%02d-%04d\n", day, month, year);
    fprintf(file, "PNR Number: %lld\n\n", PNR);
    fprintf(file, "\nPassenger Details:\n");

    for (int i = 0; i < seatCount; i++) {
        fprintf(file, "Passenger %d: %s\n", i + 1, names[i]);
    }

    fprintf(file, "---------------------------\n");
    fprintf(file, "Thank you for booking with us!");

    fclose(file);
    printf("\nTicket details have been saved to ticket.txt\n");
}

int main() {
    char from[250], to[250];
    int day, month, year;

    printf("Enter boarding station: ");
    scanf("%s", from);

    printf("Enter destination station: ");
    scanf("%s", to);

    // Ensure boarding and destination stations are different
    if (strcmp(from, to) == 0) {
        printf("Boarding and destination stations cannot be the same.\n");
        return 1;
    }

    // Get today's date
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Format and print the current date
    char date[11];
    strftime(date, sizeof(date), "%d-%m-%Y", tm_info);
    printf("Today's date: %s\n", date);

    // Input journey date
    printf("Enter the date of journey (in format DD-MM-YYYY): ");
    if (scanf("%02d-%02d-%04d", &day, &month, &year) != 3 || day < 1 || day > 31 || month < 1 || month > 12 || year < 2024) {
        printf("Invalid date. Please check and enter a valid journey date.\n");
        return 1;
    }

    // Seed random generator
    srand(time(0));

    // Generate random train numbers
    int Train_1 = generateRandom5Digit();
    int Train_2 = generateRandom5Digit();
    int Train_3 = generateRandom5Digit();
    int Train_4 = generateRandom5Digit();
    int Train_5 = generateRandom5Digit();

    // Display trains based on whether the journey is today
    if (day == tm_info->tm_mday && month == tm_info->tm_mon + 1 && year == tm_info->tm_year + 1900) {
        printf("There are limited trains running today.\n");
        printf("\nTrain Number: %d (Express)\n", Train_1);
        printf("Available berths: %d\n", generateRandom60to70());
        printf("\nTrain Number: %d (Passenger)\n", Train_4);
        printf("Available berths: %d\n", generateRandom80to90());
        printf("\nTrain Number: %d (Passenger)\n", Train_5);
        printf("Waiting list (RAC): %d\n", generateRandom15to30());
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
    }

    // Select train and seats
    int Train_Number, Seats;
    printf("\nEnter Train number: ");
    scanf("%d", &Train_Number);

    if (Train_Number != Train_1 && Train_Number != Train_2 && Train_Number != Train_3 && Train_Number != Train_4 && Train_Number != Train_5) {
        printf("Invalid train number.\n");
        return 1;
    }

    printf("Enter number of seats (max 4): ");
    scanf("%d", &Seats);
    if (Seats < 1 || Seats > 4) {
        printf("Invalid number of seats. Maximum allowed is 4.\n");
        return 1;
    }

    // Collect passenger details
    char names[4][250];
    for (int i = 0; i < Seats; i++) {
        printf("\nEnter details for passenger %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", names[i]);
        printf("Age: ");
        int Age;
        scanf("%d", &Age);
        if (Age < 1 || Age > 99) {
            printf("Invalid age.\n");
            return 1;
        }

        printf("Gender (M/F): ");
        char Gender;
        scanf(" %c", &Gender);
        if (Gender != 'M' && Gender != 'F') {
            printf("Invalid gender.\n");
            return 1;
        }

        if (i == 0) {
            char Gmail_Address[250];
            printf("Email: ");
            scanf("%s", Gmail_Address);
        }
    }

    // Calculate fare based on train type
    double fare = (Train_Number == Train_1 || Train_Number == Train_2) ? 950 : 650;
    double Total_Fare = fare * Seats * 1.18;  // Including GST
    printf("The fare (incl. GST) is %.2lf\n", Total_Fare);

    // Confirm payment
    int confirm_code;
    if (fare != 0) {
        printf("Enter 1234567890 to confirm payment: ");
        scanf("%d", &confirm_code);
        if (confirm_code != 1234567890) {
            printf("Incorrect confirmation code.\n");
            return 1;
        }
    }

    // Generate PNR and save ticket details
    long long PNR = generateRandom10Digit();
    printf("\nYOUR PNR NUMBER: %lld\n", PNR);
    createTicketFile(from, to, day, month, year, Seats, names, PNR);

    printf("Congratulations! Ticket has been booked.\n");
    return 0;
}
