// ticket.c
#include <stdio.h>
#include <string.h>

// Function to generate the ticket file
void createTicketFile(int Train_Number, const char *from, const char *to, int day, int month, int year, int seatCount, char names[][250], long long PNR) {
    FILE *file = fopen("ticket.txt", "w");
    if (file == NULL) {
        printf("Error creating ticket file!\n");
        return;
    }

    fprintf(file, "Ticket Booking Confirmation\n");
    fprintf(file, "---------------------------\n");
    fprintf(file, "Journey Details:\n");
    fprintf(file, "Train Number: %d\n", Train_Number);
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

