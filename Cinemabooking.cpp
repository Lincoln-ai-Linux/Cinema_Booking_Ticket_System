#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream> //used for both reading from and writing to files.
#include <string>
#include "MyStack.h"
#include "PaymentHistory.h"
#include "Student(1).h"

using namespace std;

class StudentRegistration {
private:
    double seat_price = 20.00;
    string movieName;
    string movieTime;
    Student* head; // Pointer for the start of the linked list
    PaymentHistory paymentHistory;
    int ticketCount; // Moved here to a class member

public:
    // Constructor
    StudentRegistration() : head(nullptr), ticketCount(0) {}

    // Function prototypes
    void displayMenu();
    void movieTimings();
    void contactUs();
    void registerStudent();
    void editStudent();
    void deleteStudent();
    void deleteAllRegistrations();
    void searchStudent();
    void sortStudentsByName();
    void displayAllReceipts();
    void clearScreen() { system("CLS"); }
    void paymentProcess();
    void displayQRCode(Student* student);
    void displaySeatGrid(int seats[5][10]);

    void saveStudentsToFile();
    void loadStudentsFromFile();

    double getSeatPrice() const { return seat_price; }
    string reserveSeats(int seats[5][10]);
};

// Function to display the menu
void StudentRegistration::displayMenu() {
    cout << "\n\n\n\t\t\t\t\t\t***********************************************" << endl;
    cout << "\t\t\t\t\t\t||  Welcome to Cinema Ticket Booking System  ||" << endl;
    cout << "\t\t\t\t\t\t***********************************************" << endl;
    cout << "\n\t\t\t\t\t\t [1] Student Registration";
    cout << "\n\t\t\t\t\t\t [2] Contact Us";
    cout << "\n\t\t\t\t\t\t [3] Display Receipts";
    cout << "\n\t\t\t\t\t\t [4] Edit Student ";
    cout << "\n\t\t\t\t\t\t [5] Delete Student ";
    cout << "\n\t\t\t\t\t\t [6] Delete All Registrations ";
    cout << "\n\t\t\t\t\t\t [7] Search Student ";
    cout << "\n\t\t\t\t\t\t [8] Sort Students by Name ";
    cout << "\n\t\t\t\t\t\t [9] Exit \n\n";
    cout << "\t\t\t\t\t\t Enter Your Choice: ";
}

// Function for student registration
void StudentRegistration::registerStudent() {
    clearScreen();
    cout << "\n\n\n\t\t\t\t\t\tWelcome to Student Registration\n";

    Student* newStudent = new Student();

    cout << "\t\t\t\t\t\tEnter your name: ";
    getline(cin >> ws, newStudent->name);

    // Handle mobile number input
    cout << "\t\t\t\t\t\tEnter your mobile number (10 digits): ";
    while (true) {
        getline(cin >> ws, newStudent->mobileNo);

        bool isValid = true;
        if (newStudent->mobileNo.length() != 10) {
            isValid = false;
        } else {
            for (char ch : newStudent->mobileNo) {
                if (!isdigit(ch)) {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            break;
        } else {
            cout << "\t\t\t\t\t\tInvalid mobile number! Please enter a valid 10-digit number: ";
        }
    }

    cout << "\t\t\t\t\t\tEnter your email ID: ";
    getline(cin >> ws, newStudent->emailid);

    cout << "\t\t\t\t\t\tEnter your 10-digit Student ID: ";
    while (true) {
        getline(cin >> ws, newStudent->studentID);

        bool isValidID = true;
        if (newStudent->studentID.length() != 10) {
            isValidID = false;
        } else {
            for (char ch : newStudent->studentID) {
                if (!isdigit(ch)) {
                    isValidID = false;
                    break;
                }
            }
        }

        if (isValidID) {
            break;
        } else {
            cout << "\t\t\t\t\t\tInvalid Student ID! Please enter a valid 10-digit number: ";
        }
    }

    newStudent->next = head;
    head = newStudent;

    // Now proceed with movie selection and seat reservation
    movieTimings();

    // Update the current student's information
    if (head){
        head->movieName = movieName;
        head->movieTime = movieTime;
        head->ticketCount = ticketCount;
    }

    clearScreen();
}

// Function to edit the student's details
void StudentRegistration::editStudent() {
    clearScreen();
    string studentID;
    cout << "\n\n\n\t\t\t\t\t\tEnter the Student ID to edit: ";
    cin >> studentID;

    Student* current = head;
    while (current != nullptr) {
        if (current->studentID == studentID) {
            cout << "\t\t\t\t\t\tEditing details for Student ID: " << current->studentID << endl;
            cout << "\t\t\t\t\t\tCurrent Name: " << current->name << endl;
            cout << "\t\t\t\t\t\tEnter new name: ";
            string tempName;
            getline(cin >> ws, tempName);
            if (!tempName.empty()) current->name = tempName;

            cout << "\t\t\t\t\t\tCurrent Mobile No: " << current->mobileNo << endl;
            cout << "\t\t\t\t\t\tEnter new mobile no: ";
            string tempMobile;
            getline(cin >> ws, tempMobile);
            if (!tempMobile.empty()) current->mobileNo = tempMobile;

            cout << "\t\t\t\t\t\tCurrent Email ID: " << current->emailid << endl;
            cout << "\t\t\t\t\t\tEnter new email ID: ";
            string tempEmail;
            getline(cin >> ws, tempEmail);
            if (!tempEmail.empty()) current->emailid = tempEmail;

            cout << "\n\t\t\t\t\t\tStudent details updated successfully!\n";
            return;
        }
        current = current->next;
    }
    cout << "\t\t\t\t\t\tStudent ID not found!\n";
}

// Function to delete student
void StudentRegistration::deleteStudent() {
    clearScreen();
    string studentID;
    cout << "\n\n\n\t\t\t\t\t\tEnter the Student ID to delete: ";
    cin >> studentID;

    Student* current = head;
    Student* prev = nullptr;

    while (current != nullptr) {
        if (current->studentID == studentID) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            cout << "\t\t\t\t\t\tStudent deleted successfully!\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "\t\t\t\t\t\tStudent ID not found!\n";
}

// Function for delete all the registrations
void StudentRegistration::deleteAllRegistrations() {
    while (head != nullptr) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "\n\n\n\t\t\t\t\t\tAll registrations have been deleted successfully!\n";
}

// Function for searching student by entering student ID
void StudentRegistration::searchStudent() {
    clearScreen();
    string studentID;
    cout << "\n\n\n\t\t\t\t\t\tEnter the Student ID to search: ";
    cin >> studentID;

    Student* current = head;
    while (current != nullptr) {
        if (current->studentID == studentID) {
            cout << "\n\t\t\t\t\t\tStudent found!\n";
            cout << "\t\t\t\t\t\tName: " << current->name << endl;
            cout << "\t\t\t\t\t\tMobile No: " << current->mobileNo << endl;
            cout << "\t\t\t\t\t\tEmail ID: " << current->emailid << endl;
            cout << "\t\t\t\t\t\tStudent ID: " << current->studentID << endl;
            cout << "\t\t\t\t\t\tMovie Name: " << current->movieName << endl;
            cout << "\t\t\t\t\t\tMovie Time: " << current->movieTime << endl;
            cout << "\t\t\t\t\t\tReserved Seats: " << current->reservedSeats << endl;
            return;
        }
        current = current->next;
    }
    cout << "\t\t\t\t\t\tStudent ID not found!\n";
}

// Bubble sort function for sorting student by name
void StudentRegistration::sortStudentsByName() {
    if (!head || !head->next) return;

    bool swapped;
    do {
        swapped = false;
        Student* current = head;
        Student* prev = nullptr;

        while (current->next) {
            if (current->name > current->next->name) {
                swapped = true;

                // Swap nodes
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }

                Student* temp = current->next->next;
                current->next->next = current;
                current->next = temp;

            } else {
                prev = current;
            }
            current = (prev) ? prev->next : head;
        }
    } while (swapped);
}

// Function to display all the receipts
void StudentRegistration::displayAllReceipts() {
    clearScreen();
    if (head == nullptr) {
        cout << "\n\n\n\t\t\t\t\t\tNo students registered yet.\n";
    } else {
        cout << "\n\n\n\t\t\t\t\t\t******************************************" << endl;
        cout << "\t\t\t\t\t\t||  All Registered Students' Receipts   ||" << endl;
        cout << "\t\t\t\t\t\t******************************************" << endl;

        Student* current = head;
        while (current != nullptr) {
            cout << "\t\t\t\t\t\tName: " << current->name << endl;
            cout << "\t\t\t\t\t\tMobile No: " << current->mobileNo << endl;
            cout << "\t\t\t\t\t\tEmail ID: " << current->emailid << endl;
            cout << "\t\t\t\t\t\tStudent ID: " << current->studentID << endl;
            cout << "\t\t\t\t\t\tMovie Name: " << current->movieName << endl;
            cout << "\t\t\t\t\t\tMovie Time: " << current->movieTime << endl;
            cout << "\t\t\t\t\t\tReserved Seats: " << current->reservedSeats << endl;
            cout << "\t\t\t\t\t\tNumber of Tickets: " << current->ticketCount << endl;
            cout << "\t\t\t\t\t\tTotal Amount: RM " << fixed << setprecision(2)
                 << (current->ticketCount * getSeatPrice()) << endl;
            cout << "\t\t\t\t\t\t----------------------------------------------------" << endl;
            current = current->next;
        }
    }
}

// Function to save the student information
void StudentRegistration::saveStudentsToFile() {
    ofstream file("students.txt");
    Student* current = head;
    while (current != nullptr) {
        file << current->name << "\n"
             << current->mobileNo << "\n"
             << current->emailid << "\n"
             << current->studentID << "\n"
             << current->movieName << "\n"
             << current->movieTime << "\n"
             << current->reservedSeats << "\n"
             << current->ticketCount << "\n";
        current = current->next;
    }
    file.close();
}

// Function to load the student information from the file
void StudentRegistration::loadStudentsFromFile() {
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        Student* newStudent = new Student();
        newStudent->name = line;
        getline(file, newStudent->mobileNo);
        getline(file, newStudent->emailid);
        getline(file, newStudent->studentID);
        getline(file, newStudent->movieName);
        getline(file, newStudent->movieTime);
        getline(file, newStudent->reservedSeats);
        getline(file, line);
        newStudent->ticketCount = stoi(line);

        newStudent->next = head;
        head = newStudent;
    }
    file.close();
}

// Function to display the movie name, and timings
void StudentRegistration::movieTimings() {
    clearScreen();
    int seats[5][10] = { 0 };
    int movie, timingChoice;

    cout << "\n\n\n\t\t\t\t\t\t Movies :";
    cout << "\n\t\t\t\t\t\t 1. Red One";
    cout << "\n\t\t\t\t\t\t\t  Language: English";
    cout << "\n\t\t\t\t\t\t\t  Subtitle: Malay/Chinese";
    cout << "\n\t\t\t\t\t\t\t  Classification: P12";
    cout << "\n\t\t\t\t\t\t\t  Genre: Action/Adventure";
    cout << "\n\t\t\t\t\t\t\t  Running Time: 2 Hours 4 Minutes";
    cout << "\n\t\t\t\t\t\t\t  Director: Jake Kasdan\n";

    cout << "\n\t\t\t\t\t\t 2. Venom: The Last Dance";
    cout << "\n\t\t\t\t\t\t\t  Language: English";
    cout << "\n\t\t\t\t\t\t\t  Subtitle: Malay/Chinese";
    cout << "\n\t\t\t\t\t\t\t  Classification: 13";
    cout << "\n\t\t\t\t\t\t\t  Genre: Action/Science Fiction";
    cout << "\n\t\t\t\t\t\t\t  Running Time: 1 Hours 49 Minutes";
    cout << "\n\t\t\t\t\t\t\t  Director: Kelly Marcel\n";

    cout << "\n\t\t\t\t\t\t 3. Cesium Fallout";
    cout << "\n\t\t\t\t\t\t\t  Language: Cantonese";
    cout << "\n\t\t\t\t\t\t\t  Subtitle: English/Chinese";
    cout << "\n\t\t\t\t\t\t\t  Classification: 13";
    cout << "\n\t\t\t\t\t\t\t  Genre: Action/Disaster/Drama ";
    cout << "\n\t\t\t\t\t\t\t  Running Time: 2 Hours 15 Minutes";
    cout << "\n\t\t\t\t\t\t\t  Director: Anthony Pun\n";

    cout << "\n\t\t\t\t\t\t 4. You Will Die In 6 Hours";
    cout << "\n\t\t\t\t\t\t\t  Language: Korean";
    cout << "\n\t\t\t\t\t\t\t  Subtitle: English/Malay/Chinese";
    cout << "\n\t\t\t\t\t\t\t  Classification: 16";
    cout << "\n\t\t\t\t\t\t\t  Genre: Mystery/Thriller ";
    cout << "\n\t\t\t\t\t\t\t  Running Time: 1 Hours 31 Minutes";
    cout << "\n\t\t\t\t\t\t\t  Director: Lee Yoon-Seok\n";

    cout << "\n\t\t\t\t\t\t 5. Panda Plan";
    cout << "\n\t\t\t\t\t\t\t  Language: Mandarin";
    cout << "\n\t\t\t\t\t\t\t  Subtitle: English/Chinese";
    cout << "\n\t\t\t\t\t\t\t  Classification: 13";
    cout << "\n\t\t\t\t\t\t\t  Genre: Action/Adventure/Comedy ";
    cout << "\n\t\t\t\t\t\t\t  Running Time: 1 Hours 39 Minutes";
    cout << "\n\t\t\t\t\t\t\t  Director: Zhang Luan\n";

    do {
        cout << "\n\t\t\t\t\t\tEnter Your Choice (1-5): ";
        cin >> movie;

        // Check if the input is valid
        if (cin.fail() || movie < 1 || movie > 5) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << "\t\t\t\t\t\tInvalid selection! Please select a valid number (1-5).\n";
        } else {
            break; // Valid input, exit the loop
        }

    } while (true); // Keep looping until we get a valid input.

    // Assign movie name based on selection
    switch (movie) {
        case 1: movieName = "Red One"; break;
        case 2: movieName = "Venom: The Last Dance"; break;
        case 3: movieName = "Cesium Fallout"; break;
        case 4: movieName = "You Will Die In 6 Hours"; break;
        case 5: movieName = "Panda Plan"; break;
        default:
            return; // This case won't occur, but just for safety.
    }

    // Time selection with validation
    do {
        cout << "\n\n\t\t\t\t\t\t Select the timings: ";
        cout << "\n\t\t\t\t\t\t 1. 0800";
        cout << "\n\t\t\t\t\t\t 2. 1300";
        cout << "\n\t\t\t\t\t\t 3. 1450";
        cout << "\n\t\t\t\t\t\t 4. 1800";
        cout << "\n\t\t\t\t\t\t 5. 2100";
        cout << "\n\t\t\t\t\t\t 6. 0100\n";

        cout << "\n\t\t\t\t\t\tPlease select the timings: ";
        cin >> timingChoice;

        // Check if the input is valid
        if (cin.fail() || timingChoice < 1 || timingChoice > 6) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << "\t\t\t\t\t\tInvalid timing selected! Please select a valid number (1-6).\n";
        } else {
            break; // Valid input, exit the loop
        }

    } while (true); // Keep looping until we get a valid input.

    // Set movieTime based on selection
    movieTime = (timingChoice == 1) ? "0800" :
                (timingChoice == 2) ? "1300" :
                (timingChoice == 3) ? "1450" :
                (timingChoice == 4) ? "1800" :
                (timingChoice == 5) ? "2100" : "0100";

    cout << "\n\t\t\t\t\t\tMovie you have selected: " << movieName << " at " << movieTime << ".\n";

    // Prompt for ticket count with input validation
    do {
        cout << "\n\t\t\t\t\t\t How many tickets do you want to reserve? (1-5): ";
        cin >> ticketCount;

        if (cin.fail() || ticketCount < 1 || ticketCount > 5) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "\n\t\t\t\t\t\tInvalid number of tickets! Please select between 1 and 5: ";
        } else {
            break; // Valid input, exit the loop
        }

    } while (true); // Keep looping until we get a valid input.

    // Ensure movieName and movieTime are assigned to the current student
    if (head) {
        head->movieName = movieName;
        head->movieTime = movieTime;
        head->ticketCount = ticketCount;
    }

    // Show seat grid and reserve seats
    displaySeatGrid(seats);
    string reservedSeats = reserveSeats(seats);  // Store the returned seat description

    // Store the reserved seats in the most recently added student
    if (head) {
        head->reservedSeats = reservedSeats;
    }
}

// Function to display the seating grid
void StudentRegistration::displaySeatGrid(int seats[5][10]) {
    cout << "\n\n\n\t\t\t\t\t\tSeat Reservation Grid:\n";
    for (int i = 0; i < 5; i++) {
        cout << "\t\t\t\t\t\tRow " << (i + 1) << ": ";
        for (int j = 0; j < 10; j++) {
            if (seats[i][j] == 1) {
                cout << "[x] ";
            } else {
                cout << "[ ] ";
            }
        }
        cout << endl;
    }

    cout << "\n\t\t\t\t\t\tPress any key to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function for student to reserve the seats
string StudentRegistration::reserveSeats(int seats[5][10]) {
    int row, spot;
    string seatDescription;  //Used to store seat descriptions

    for (int i = 0; i < ticketCount; i++) {
        while (true) {
            cout << "\n\t\t\t\t\t\tSelect a row (1-5) and spot (1-10) for ticket " << (i + 1) << ": ";
            if (!(cin >> row) || !(cin >> spot)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\t\t\t\t\t\tInvalid input! Please enter numbers only.\n";
                continue;
            }

            if (row < 1 || row > 5 || spot < 1 || spot > 10) {
                cout << "\t\t\t\t\t\tInvalid selection! Please enter row (1-5) and spot (1-10)." << endl;
                continue;
            }

            row--;
            spot--;

            if (seats[row][spot] == 1) {
                cout << "\t\t\t\t\t\tSeat occupied! Please choose a different seat." << endl;
                continue;
            }

            seats[row][spot] = 1;

            // Add seat information to description string
            seatDescription += "Row " + to_string(row + 1) + " Seat " + to_string(spot + 1);
            if (i < ticketCount - 1) {
                seatDescription += ", ";
            }
            cout << "\t\t\t\t\t\tSeat (" << (row + 1) << ", " << (spot + 1) << ") reserved." << endl;
            break;
        }
    }

    // Save seat information to current student object
    if (head) {
        head->reservedSeats = seatDescription; // Save seat information
    }

    displaySeatGrid(seats);
    paymentProcess();
    return seatDescription;
}

// Function for the payment process
void StudentRegistration::paymentProcess() {
    clearScreen();
    double totalAmount = ticketCount * getSeatPrice();
    double cash;

    cout << "\n\n\n\t\t\t\t\t\t---------------------------------------------------------\n"
         << "\t\t\t\t\t\t|                       PAYMENT                         |\n"
         << "\t\t\t\t\t\t---------------------------------------------------------\n"
         << "\t\t\t\t\t\t" << left << setw(20) << "Number of tickets:" << " " << ticketCount << "\n"
         << "\t\t\t\t\t\t" << left << setw(20) << "Price of each ticket:" << " RM " << fixed << setprecision(2) << getSeatPrice() << endl
         << "\t\t\t\t\t\t---------------------------------------------------------\n"
         << "\t\t\t\t\t\t" << left << setw(20) << "Total Amount to PAY:" << " RM " << fixed << setprecision(2) << totalAmount << "\n"
         << "\t\t\t\t\t\t" << left << setw(20) << "Cash:" << " RM ";

    while (true) {
        cin >> cash;

        // Check if the input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the input buffer
            cout << "\t\t\t\t\t\tInvalid input! Please enter a numeric value for cash: RM ";
        } else if (cash < totalAmount) {
            cout << "\n\t\t\t\t\t\tSorry! Your cash is insufficient. Please enter a sufficient amount: RM ";
        } else {
            break; // Valid cash entered, exit the loop
        }
    }

    cout << fixed << setprecision(2) << "\n\t\t\t\t\t\tPayment successful! Your change is: RM " << cash - totalAmount << ", Thank you!\n";

    // Push the total amount and the reserved seat information onto the history stack
    if (head) {
        paymentHistory.push(totalAmount, head->reservedSeats, head->movieName, head->movieTime);
    }

    // Display receipt immediately after payment
    displayQRCode(head);

    cout << "\n\t\t\t\t\t\tPress any key to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    clearScreen();
}

// Function to display the QR code (benefits for the students)
void StudentRegistration::displayQRCode(Student* student) {
    cout << "\n\n\n\t\t\t\t\t\t***********************************************" << endl;
    cout << "\t\t\t\t\t\t||              Receipt                      ||" << endl;
    cout << "\t\t\t\t\t\t***********************************************" << endl;

    if (student) {  // Check whether the passed student pointer is valid
        cout << "\t\t\t\t\t\tName: " << student->name << "\n";
        cout << "\t\t\t\t\t\tMobile No: " << student->mobileNo << "\n";
        cout << "\t\t\t\t\t\tEmail ID: " << student->emailid << "\n";
        cout << "\t\t\t\t\t\tStudent ID: " << student->studentID << "\n";
        cout << "\t\t\t\t\t\tMovie Name: " << student->movieName << endl;
        cout << "\t\t\t\t\t\tMovie Time: " << student->movieTime << endl;
        cout << "\t\t\t\t\t\tReserved Seats: " << student->reservedSeats << endl; // Display reserved seats

        // Display a simple QR code representation (ASCII art)
        cout << "\n\t\t\t\t\t\t        ***************                  \n";
        cout << "\t\t\t\t\t\t        ***************                  \n";
        cout << "\t\t\t\t\t\t        ***************                  \n";
        cout << "\t\t\t\t\t\t        ***************                  \n";
        cout << "\t\t\t\t\t\t        ***************                  \n";
        cout << "\t\t\t\t\t\t        ***************                  \n";

        cout << "\n\t\t\t\t\t\tScan the QR code to claim the free Popcorn and Coca-cola at the counter!\n";
        cout << "\t\t\t\t\t\tPlease Enjoy Your Day\n";
        cout << "\n\t\t\t\t\t\tTickets purchased: " << student->ticketCount << "\n";
        cout << "\t\t\t\t\t\t---------------------------------------------------------\n";
        cout << "\t\t\t\t\t\tThank you for your purchase!\n";
    } else {
        cout << "\t\t\t\t\t\tNo student registered yet to display a receipt.\n";
    }
}

// Function to contact us
void StudentRegistration::contactUs() {
    clearScreen();
    cout << "\n\n\n\t\t\t\t\t\t For any inquiries, please contact us at 0123456789 or visit our website.\n";
    cout << "\n\t\t\t\t\t\t Thank you for choosing our service!\n";
    cout << "\n\t\t\t\t\t\t\t Press any key to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearScreen();
}

// Main function
int main() {
    system("CLS");
    StudentRegistration sr;
    sr.loadStudentsFromFile();

    int choice;
    char ans;

    do {
        sr.displayMenu();
        while (true) {
            cin >> choice;

            // Check if the input is valid
            if (cin.fail() || choice < 1 || choice > 10) {
                cin.clear(); // clear error status
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                cout << "\t\t\t\t\t\tInvalid selection! Please input a number from 1 to 10: ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break; // The input is valid and exits the loop
            }
        }

        switch (choice) {
            case 1:sr.registerStudent();
                break;
            case 2:sr.contactUs();
                break;
            case 3:sr.displayAllReceipts();
                break;
            case 4:sr.editStudent();
                break;
            case 5:sr.deleteStudent();
                break;
            case 6:sr.deleteAllRegistrations();
                break;
            case 7:sr.searchStudent();
                break;
            case 8:sr.sortStudentsByName(); // Call function sorted by name
                break;
            case 9:sr.saveStudentsToFile();

                cout << "\n\n\n\t\t\t\t\t\tTHANK YOU AND VISIT AGAIN!\n\n\t\t\t\t\t\t";
                system("PAUSE");
                return 0;
            default:

                cout << "\t\t\t\t\t\tInvalid selection! Please input 1 to 10 only.\n";
                break;
        }

         // Prompt for choosing another option
        while (true) {
            cout << "\n\t\t\t\t\t\tDo you want to choose another option (y/n)? ";
            cin >> ans;

            // Check if the input is valid (y/n)
            if (ans == 'y' || ans == 'Y' || ans == 'n' || ans == 'N') {
                // If 'n', exit the program
                if (ans == 'n' || ans == 'N') {
                    sr.saveStudentsToFile();
                    cout << "\n\n\n\t\t\t\t\t\tTHANK YOU AND VISIT AGAIN!\n\n\t\t\t\t\t\t";
                    system("PAUSE");
                    return 0;
                }
                break; // Valid input, exit the loop

            } else {
                cout << "\t\t\t\t\t\tInvalid input! Please enter 'y' or 'n'.\n";
            }
        }

        sr.clearScreen();

    } while (true); // Continue the main loop
}
