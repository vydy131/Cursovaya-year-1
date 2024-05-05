#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {                                                            // Base class for database of real users
private:
    string name;
    string phone;                                                       // Atribytes are permanent and 'read only' for any 'real' user,
    string oprtr;                                                       //  only temporary objects will use 'rewrite' method

public:
    User(string nm, string phn, string opr);                         
    User();                                                           
    User(const User& orig);                                           
    string getname();
    string getphone();
    string getoprtr();
    void rewrite(string nm, string phn, string opr);
    ~User();
};

class Oper : public User {                                                  // This class is legacy only because it includes all atr of User
private:
    float comis;                                                            // Contain the value of COMMISSION
    string local_time;                                                      // Current system time
    float income;                                                           // The money user insert
    float clear_money;                                                      // The money without commission
    float oper_comis;                                                       // Commission payment

public:
    Oper(User us, float number);
    void print_info();                                                      // Print info into console
    void add_to_file(string file_name = "operlog.txt");                     // Print info into file
};

#endif