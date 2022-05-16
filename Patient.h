/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.h
Version 3.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/15 Start this project
2021/7/15 done
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"

using namespace std;
namespace sdds
{
    class Patient :public IOAble
    {
        char* m_name;
        int m_OHIPnum;
        Ticket m_ticket;
        bool m_falg;
    public:
        // Constructorand destructor
         // If the file IO flag is not provided the default value "false" is passed 
         // also if the ticket number is not provided the default value zero (0) is passed.
        Patient(int ticketNum = 0, bool falg = false);
        ~Patient();
        // Copying and assignment : A patient cannot be copied or assigned to another patient;
        Patient(const Patient& patient) = delete;
        Patient& operator= (const Patient& patient) = delete;
        // Pure Virtual Function type()
        virtual char type()const = 0;
        bool fileIO()const;
        void fileIO(bool set);
        // operator== overloads
        bool operator== (const char singleChar)const; // character comparison
        bool operator== (const Patient& patient)const; // comparing to another patient
        void setArrivalTime();
        operator Time()const;
        int number()const;
        // pure virtual function overwrites
        std::ostream& csvWrite(std::ostream& ostr)const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };
}
#endif // !SDDS_PATIENT_H_


