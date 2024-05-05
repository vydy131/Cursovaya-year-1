#include <iostream>
#include <fstream>
#include <ctime>
#include "classes.h"

using namespace std;

User::User(string nm, string phn, string opr) {                            // Constructor for normal cases
    name = nm;
    phone = phn;
    oprtr = opr;
}

User::User(const User& orig) {                                             // Constructor for OPER-class
    name = orig.name;
    phone = orig.phone;
    oprtr = orig.oprtr;
}

User::User() {                                                             // Constructor for temporaries
    name = "default name";
    phone = "default phone number";
    oprtr = "default operator";
}

string User::getname() {
    return name;
}

string User::getphone() {
    return phone;
}

string User::getoprtr() {
    return oprtr;
}

void User::rewrite(string nm, string phn, string opr) {                     // Using only with temporaries
    name = nm;
    phone = phn;
    oprtr = opr;
}

User::~User() { }


float COMMISION = 0.1;

Oper::Oper(User us, float number) : User(us) {
    comis = COMMISION;
    income = number;
    clear_money = (1 - COMMISION) * income;
    oper_comis = income * COMMISION;

    time_t t = time(nullptr);
    struct tm lt;
    localtime_s(&lt, &t);
    char buf[100];
    strftime(buf, sizeof(buf), "%H:%M:%S %A, %d/%m/%Y", &lt);
    local_time = buf;
}

void Oper::print_info() {
    cout << "########################\n";
    cout << local_time << endl;
    cout << "User:\t\t\t\t" << this->getname() << endl;
    cout << "Phone number:\t\t\t" << this->getphone() << endl;
    cout << "Operator:\t\t\t" << this->getoprtr() << endl;
    cout << "Payment:\t\t\t" << income << endl;
    cout << "Commision\t\t\t" << oper_comis << endl;
    cout << "Balance:\t\t\t+" << clear_money << endl;
    cout << "########################\n";
}

void Oper::add_to_file(string file_name) {
    ofstream append(file_name, ios::app);
    if (!append.is_open()) {
        cout << "ERROR: can't open " << file_name << " for append\n";
        return;
    }

    append << "########################\n";
    append << local_time << endl;
    append << "User:\t\t\t\t" << this->getname() << endl;
    append << "Phone number:\t\t" << this->getphone() << endl;
    append << "Operator:\t\t\t" << this->getoprtr() << endl;
    append << "Payment:\t\t\t" << income << endl;
    append << "Commision\t\t\t" << oper_comis << endl;
    append << "Balance:\t\t\t+" << clear_money << endl;
    append << "########################\n";

    cout << "File has been updated successfully\n";
    append.close();
}