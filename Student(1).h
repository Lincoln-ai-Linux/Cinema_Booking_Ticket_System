#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {
public:
    string name;          // Student's name
    string mobileNo;      // Student's mobile number
    string emailid;       // Student's email ID
    string studentID;     // Student's ID
    string movieName;     // Movie name
    string movieTime;     // Movie time
    string reservedSeats; // Reserved seats
    int ticketCount;      // Number of tickets
    Student* next;        // Pointer to the next student in the linked list

    // Constructor
    Student() : next(nullptr), ticketCount(0) {}
};

#endif // STUDENT_H
