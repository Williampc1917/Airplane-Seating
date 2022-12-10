#include <iostream>
#include <string>
using namespace std;

const int ROWS = 13;
const int SEATS = 6;

// Declare the seating plan as a 13 by 6 array of chars
char seatingPlan[ROWS][SEATS];

// Declare the arrays that store the passengers' names and seats
string passengers[80];
string seats[80];

// Declare the variable that stores the length of the arrays
int length = 0;

//Function prototypes
void initializeSeatingPlan();
void addReservation();
void cancelReservation();
void printPassengerNames();
void printSeatingPlan();
void printEndOfRunInformation();
bool validateSeat(string row, string seat);









int main() {
  // Initialize data
    
  initializeSeatingPlan();
    // Display menu and get user's choice
    int choice = 0;
    while (choice != 5)
    {
        cout << "1) Add a Reservation" << endl;
        cout << "2) Cancel a Reservation" << endl;
        cout << "3) Print Passenger Names and their Seats" << endl;
        cout << "4) Print the Seating Plan" << endl;
        cout << "5) Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform the selected action
        switch (choice)
        {
        case 1:
            addReservation();
            break;
        case 2:
            cancelReservation();
            break;
        case 3:
            printPassengerNames();
            break;
        case 4:
            printSeatingPlan();
            break;
        case 5:
            printEndOfRunInformation();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
  
}


void addReservation() {
    // Print the seating plan
    printSeatingPlan();

    // Ask the user for their name, ticket type, and desired seat
    string name, row, seat, ticketType;
  
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your ticket type (first class or economy class)('1' for first class or '2' for economy class): ";
    cin >> ticketType;
    cout << "Enter the row number of your desired seat: ";
    cin >> row;
    cout << "Enter the seat letter of your desired seat: ";
    cin >> seat;

    // Validate the desired seat
    // If the user picks first class, they are only allowed to sit in Rows 1 or 2
    if (ticketType == "1") {
        if (row != "1" && row != "2") {
            cout << "Invalid seat. First class passengers can only sit in Rows 1 or 2. Please try again." << endl;
            return;
        }
    }
    // If the user picks economy class, they are only allowed to sit in Rows 3-13
    else if (ticketType == "2") {
        if (stoi(row) < 3 || stoi(row) > 13) {
            cout << "Invalid seat. Economy class passengers can only sit in Rows 3-13. Please try again." << endl;
            return;
        }
    }
    // If the user enters an invalid ticket type, display an error message
    else {
        cout << "Invalid ticket type. Please try again." << endl;
        return;
    }

    // If the seat is available, add the reservation
    int rowNum = stoi(row);
    int seatNum = seat[0] - 'A'; // Convert the seat letter to a number
    if (seatingPlan[rowNum - 1][seatNum] == '*') {
        // Update the seating plan and the arrays that store the passengers names and seats
        seatingPlan[rowNum - 1][seatNum] = 'X';
        passengers[length] = name;
        seats[length] = row + seat;
        length++;
    } else {
        cout << "Seat is not available. Please try again." << endl;
    }
}
// Function that cancels a reservation
void cancelReservation() {
    // Ask the user for their name
    string name;
    cout << "Enter your name: ";
    cin >> name;

    // Check if the passenger is in the list
    bool found = false;
    int index;
    for (int i = 0; i < length; i++) {
        if (passengers[i] == name) {
            found = true;
            index = i;
            break;
        }
    }

    if (found) {
        // If the passenger is in the list, delete all the information related to the passenger
        // and update the seating plan
        string seat = seats[index];
        int rowNum = stoi(seat.substr(0, seat.length() - 1));
        int seatNum = seat[seat.length() - 1] - 'A';
        seatingPlan[rowNum - 1][seatNum] = '*';

        for (int i = index; i < length - 1; i++) {
            passengers[i] = passengers[i + 1];
            seats[i] = seats[i + 1];
        }
        length--;
    } else {
        // If the passenger is not in the list, print an error message
        cout << "Passenger not found. Please try again." << endl;
    }
}


// Function that prints the passengers' names and seats
void printPassengerNames() {
    if (length == 0) {
        // If there are no passengers, print "the plane is empty"
        cout << "The plane is empty" << endl;
    } else {
        // If there are passengers, print their names and seats
        cout << "Passenger Names and Seats" << endl;
        for (int i = 0; i < length; i++) {
            cout << passengers[i] << ": " << seats[i] << endl;
        }
    }
}


// Function that prints the end-of-run information
void printEndOfRunInformation() {
    // Print the final seating plan
    printSeatingPlan();

    // Print the list of passengers with their assigned seats in sorting order by name
    if (length == 0) {
        // If there are no passengers, print "the plane is empty"
        cout << "The plane is empty" << endl;
    } else {
        // If there are passengers, sort the passengers by name and print their names and seats
        for (int i = 0; i < length - 1; i++) {
            for (int j = i + 1; j < length; j++) {
                if (passengers[i] > passengers[j]) {
                    string temp = passengers[i];
                    passengers[i] = passengers[j];
                    passengers[j] = temp;

                    temp = seats[i];
                    seats[i] = seats[j];
                    seats[j] = temp;
                }
            }
        }

        cout << "Passenger Names and Seats" << endl;
        for (int i = 0; i < length; i++) {
            cout << passengers[i] << ": " << seats[i] << endl;
        }
    }
}


// Function that prints the seating plan
void printSeatingPlan() {
    // Print the column labels
    cout << "        A  B  C      D  E  F" << endl;

    // Print the rows of the seating plan
    for (int i = 0; i < 13; i++) {
        cout << "ROW " << (i + 1) << "   ";
        for (int j = 0; j < 6; j++) {
            cout << seatingPlan[i][j] << "  ";
            if (j == 2) {
                cout << "    ";
            }
        }
        cout << endl;
    }
}
void initializeSeatingPlan() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS; j++) {
            seatingPlan[i][j] = '*';
        }
    }
}
