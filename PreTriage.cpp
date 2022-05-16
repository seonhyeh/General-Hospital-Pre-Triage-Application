/* Citation and Sources...
Final Project Milestone 5
Module: PreTriage
Filename: PreTriage.cpp
Version 5.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/31  Start this project
2021/8/1  load function -> load number of file is different.
2021/8/1 indexOfFirstInLine -> cannot find first index
2021/8/1 PreTriage - warning ( due to constructor order)
2021/8/1 ~preTriage - error(memory) delete -> delete[];
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include <string>
#include "PreTriage.h"
#include "CovidPatient.h"
#include "utils.h"
#include "TriagePatient.h"

using namespace std;
namespace sdds
{
    // PreTriage is constructed using a Cstring for a file name that will be used as the data file for the module
    PreTriage::PreTriage(const char* dataFilename) :
        m_averCovidWait(15), m_averTriageWait(5),
        m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
        m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
    {
        // This name will be kept dynamically in the m_dataFilename member variable.
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        // import the Patient records from the data file
        load();
    }

    PreTriage::~PreTriage()
    {
        // The data file is opened for output
        ofstream out(m_dataFilename);
        // overwriting the content of the file if it already exists.
        if (out.is_open())
        {
            // The average COVID wait time and the average Triage wait time is written in the first line of the file
            out << m_averCovidWait << "," << m_averTriageWait << endl; //file
            cout << "Saving Average Wait Times," << endl;
            cout << "   COVID Test: " << m_averCovidWait << endl;
            cout << "   Triage: " << m_averTriageWait << endl;
            cout << "Saving m_lineup..." << endl;

            // All the patients are written into the file, comma-separated in individual lines.
            for (int i = 0; i < m_lineupSize; i++)
            {
                m_lineup[i]->fileIO(true);
                out << *m_lineup[i] << endl; //file
                // row#- comma separated patient information
                cout << (i + 1) << "- " << *m_lineup[i] << endl;
            }
            //the confirmation massage "done!" is printed on the screen at the end.
            cout << "done!" << endl;
        }
        // All the Patients pointed by the elements of the m_lineup array are deleted.
        for (int i = 0; i < m_lineupSize; i++)
        {
            delete m_lineup[i];
            m_lineup[i] = nullptr;
        }
        // data file name is deleted.
        if (m_dataFilename)
        {
            delete[] m_dataFilename;
            m_dataFilename = nullptr;
        }
    }

    // Receives a constant Patient Reference and returns the total estimated wait time for that type of Patient 
    // (COVID or Triage)
    const Time PreTriage::getWaitTime(const Patient& p)const
    {
        unsigned int cout = 0;
        int waitTime = 0;
        // Find the number of Patients matching the type of the Patient Reference in the lineup
        // one way to do this is to loop through the m_lineup array and count the patients matching the Patient Reference
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (m_lineup[i]->type() == p.type())
            {
                cout++;
            }
        }
        //Return the product of estimated wait time by the number of patients.
        waitTime = Time(p) * cout;

        return waitTime;
    }

    // Receives the reference of the admitting patient and adjusts the average wait time of 
    //that type of patient base on the admittance time of the patient.
    void PreTriage::setAverageWaitTime(const Patient& p)
    {
        int CT = Time(p).setToNow(); // Current Time
        int PTT = Time(p);// Patient's Ticket Time
        int PTN = p.number(); // Patient's Ticket Number

        // Modify and set the value of the average wait time (m_averCovidWait or m_averTriageWait) of the patient 
        // AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN
        if (p.type() == 'C')
        {
            m_averCovidWait = ((CT - PTT) + ((int)m_averCovidWait * (PTN - 1))) / PTN;
        }
        else if (p.type() == 'T')
        {
            m_averTriageWait = ((CT - PTT) + ((int)m_averTriageWait * (PTN - 1))) / PTN;
        }
    }

    void PreTriage::removePatientFromLineup(int index)
    {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }

    // Finds the index of the first patient in line which matches the type argument
    int PreTriage::indexOfFirstInLine(char type) const
    {
        int index = -1;
        int found = false;
        // Loop from the beginning of the m_lineup array of pointers and compare the patient with the type argument. 
        // If a match is found, return the index of the loop and terminate the function.
        for (int i = 0; i < m_lineupSize && !found; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                index = i;
                found = true;
            }
        }

        return index; // If no match is found return -1.
    }




    // Loads the average wait times and the patient records from the data file and stores them in the m_lineup array.
    void PreTriage::load()
    {
        char comma = '\0';
        char firstChar = '\0';
        int noOfPatient = 0;

        ifstream in(m_dataFilename);

        if (in.is_open())
        {
            // print "Loading data...", goto newline
            cout << "Loading data..." << endl;
            // read the covid average wait time from the data file && ignore the comma
            in >> m_averCovidWait >> comma;
            // read the triage average wait time from the data file
            in >> m_averTriageWait;
            // ignore the newline
            in.ignore(BUFFERSIZE, '\n');

            // loop from 0 to the maximum number of patients and stop if reading fails
            for (int i = 0; i < maxNoOfPatients && in; i++)
            {
                firstChar = 0;
                comma = 0;

                Patient* patient = nullptr; // have a patient-pointer
                // read the first character and ignore the comma
                in >> firstChar >> comma;
                //  if the character is 'C'
                if (firstChar == 'C')
                {
                    //  in the patient-pointer instantiate a Covid Patient
                    patient = new CovidPatient();
                }
                else if (firstChar == 'T')
                {
                    //   in the patient-pointer instantiate a Triage Patient
                    patient = new TriagePatient();
                }
                // If Instantiation happened
                if (patient != nullptr)
                {
                    // Set the patient to file IO
                    patient->fileIO(true);
                    // Read the patient from the file
                    patient->csvRead(in);
                    //   Set the Patient not to do file IO
                    patient->fileIO(false);
                    //  copy the patient pointer to the lineup array of pointers
                    m_lineup[i] = patient;
                    // increase the lineup size
                    m_lineupSize++;
                    noOfPatient++;
                }
            }
            // if there is still records left in the file, print the following warning:
            if (maxNoOfPatients == noOfPatient)
            {
                if (!in.eof())
                {
                    cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
                    cout << m_lineupSize << " Records imported..." << endl << endl;
                }
            }
            // if no records were read print "No data or bad data file!"
            if (m_lineupSize == 0 && in.eof())
            {
                cout << "No data or bad data file!" << endl << endl;
            }
            // otherwise, print "### Records imported..." (### is replaced with the number of records read)
            else if (m_lineupSize > 0 && in.eof())
            {
                cout << m_lineupSize << " Records imported..." << endl << endl;
            }
        }
    }



    // Registers a new patient
    void PreTriage::reg()
    {
        int selection = -1;
        // if lineup size has reached the maximum number of patient, it will print "Line up full!"
        if (m_lineupSize == maxNoOfPatients)
        {
            cout << "Line up full!" << endl;
        }
        else
        {
            // displays the m_pMenu and receives the selection
            m_pMenu >> selection;
            // if the selection is 1, in the next available lineup pointer instantiate a CovidPatient
            // if the selection is 2, in the next available lineup pointer instantiate a TriagePatient
            // if the selection is 0, terminate the function
            switch (selection)
            {
            case 1:
                m_lineup[m_lineupSize] = new CovidPatient();
                break;
            case 2:
                m_lineup[m_lineupSize] = new TriagePatient();
                break;
            case 0:
                break;
            default:
                break;
            }
            //set the patient's arrival time
            m_lineup[m_lineupSize]->setArrivalTime();
            cout << "Please enter patient information: " << endl;
            // (you might need to set the patient not to do File IO)
            m_lineup[m_lineupSize]->fileIO(false);
            // extract the patient from cin
            m_lineup[m_lineupSize]->read(cin);
            cout << endl;
            cout << "******************************************" << endl;
            // insert the patient into cout
            m_lineup[m_lineupSize]->write(cout);
            cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
            cout << "******************************************" << endl << endl;
            m_lineupSize++;
        }
    }

    //Calls the next patient in line to be admitted to the COVID test centre or Triage centre
    void PreTriage::admit()
    {
        int selection = -1;
        char type = '\0';
        // displays the m_pMenu and receives the selection to determine the type of the patient to admit.
        m_pMenu >> selection;
        //if selection is 1, the type is 'C'
        // if selection is 2, the type is 'T'
        // if selection is 0, terminate the function
        switch (selection)
        {
        case 1:
            type = 'C';
            break;
        case 2:
            type = 'T';
            break;
        case 0:
            break;
        default:
            break;
        }
        // find the index of the next patient in the line for the type (use member the member function)
        int index = indexOfFirstInLine(type);
        // if no patient is found, terminate the function
        if (index != -1)
        {
            cout << endl << "******************************************" << endl;
            m_lineup[index]->fileIO(false);
            cout << "Calling for ";
            // insert the patient into cout
            m_lineup[index]->write(cout);
            cout << "******************************************" << endl << endl;
            // set Average Wait Time for the patient
            setAverageWaitTime(*m_lineup[index]);
            // remove the patient from the lineup.
            removePatientFromLineup(index);
        }
    }



    void PreTriage::run(void)
    {
        int selection = -1;
        /*   if selection is 0, quit the function
           if selection is 1 call the reg function
           if selection is 2 call the admit function*/
        do
        {
            m_appMenu >> selection;
            switch (selection)
            {
            case 1:
                reg();
                break;
            case 2:
                admit();
                break;
            case 0:
                break;
            default:
                break;
            }

        } while (selection != 0);
    }
}