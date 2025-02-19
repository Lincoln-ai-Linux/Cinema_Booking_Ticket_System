#ifndef PAYMENTHISTORY_H
#define PAYMENTHISTORY_H

#include "MyStack.h"
#include <string>

using namespace std;

class PaymentHistory {
private:
    // Define a structure to store payment records
    struct PaymentRecord {
        double amount;          // Amount paid
        string reservedSeats;   // Reserved seats
        string movieName;       // Movie name
        string movieTime;       // Movie time
    };

    MyStack<PaymentRecord> history; // Use custom stack to store payment records

public:
    // Push a payment record onto the stack
    void push(double amount, const string& seats, const string& movie, const string& time) {
        history.push({amount, seats, movie, time});
    }

    // Pop a payment record from the stack
    bool pop(double& amount, string& seats, string& movie, string& time) {
        if (history.isEmpty()) return false; // If stack is empty, return false
        PaymentRecord record = history.top(); // Get the top record
        amount = record.amount;
        seats = record.reservedSeats;
        movie = record.movieName;
        time = record.movieTime;
        history.pop(); // Remove the top record
        return true;
    }

    // Overloaded pop function to only get amount and seats
    bool pop(double& amount, string& seats) {
        string movie, time;
        return pop(amount, seats, movie, time);
    }

    // Display the payment history
    void displayHistory() {
        MyStack<PaymentRecord> temp = history; // Copy the stack to traverse
        cout << "\nPayment History:\n";
        while (!temp.isEmpty()) {
            PaymentRecord record = temp.top();
            cout << "Paid Amount: RM " << record.amount
                 << ", Reserved Seats: " << record.reservedSeats
                 << ", Movie: " << record.movieName
                 << ", Time: " << record.movieTime << endl;
            temp.pop();
        }
    }
};

#endif // PAYMENTHISTORY_H
