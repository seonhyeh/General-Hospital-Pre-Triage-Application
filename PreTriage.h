/* Citation and Sources...
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.h
Version 5.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/31  Start this project
2021/7/31 finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_PRETRIAGE_H
#define SDDS_PRETRIAGE_H
#include <iostream>
#include "Ticket.h"
#include "Patient.h"
#include "Menu.h"

namespace sdds
{
    // maximum number of patients in the lineup (Covid and Triage)
    const int maxNoOfPatients = 100;
    class PreTriage
    {
        // Time objects to hold the average wait time for COVID test and Triage per patient
        Time
            m_averCovidWait,
            m_averTriageWait;
        // An array of Patient pointers to hold COVID and Triage Patient lineups dynamically
        Patient* m_lineup[maxNoOfPatients]{};
        // A character pointer to hold the name of the data file dynamically
        char* m_dataFilename = nullptr;
        // Number of Patients in the lineup.
        int m_lineupSize = 0;
        Menu
            m_appMenu, // Menu object to hold the main menu.
            m_pMenu; // Menu object to hold the COVID/Triage patient selection.
        void reg();
        void admit();
        const Time getWaitTime(const Patient& p)const;
        void setAverageWaitTime(const Patient& p);
        void removePatientFromLineup(int index);
        int indexOfFirstInLine(char type) const;
        void load();
    public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run(void);
    };
}
#endif // !SDDS_PRETRIAGE_H
