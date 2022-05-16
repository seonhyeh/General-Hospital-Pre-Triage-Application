/* Citation and Sources...
Final Project Milestone 1
Module: utils
Filename: utils.cpp
Version 1.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/2  start this project
2021/7/4  finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
    bool debug = false;  // made global in utils.h
    //const int BUFFERSIZE = 1000;

    int getTime()
    {
        int mins = -1;
        if (debug)
        {
            Time t(0);
            cout << "Enter current time: ";
            do
            {
                cin.clear();
                cin >> t;   // needs extraction operator overloaded for Time
                if (!cin)
                {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else
                {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else
        {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }


    int getInt(const char* prompt)
    {
        bool flag = false;
        int val = 0;

        if (prompt)
        {
            cout << prompt;
        }
        do
        {
            flag = false;
            cin >> val;
            if (cin.fail()) // if user input is not a number 
            {
                cout << "Bad integer value, try again: ";
                cin.clear(); // initialize the flags
                cin.ignore(BUFFERSIZE, '\n'); // makes empty buffer
                flag = true;
            }
            else
            {
                // If after a valid integer value any character other than a New Line is entered
                if (cin.get() != '\n')
                {
                    cout << "Enter only an integer, try again: ";
                    cin.clear();
                    cin.ignore(BUFFERSIZE, '\n');
                    flag = true;
                }
            }
        } while (flag);

        return val;
    }

    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
    {
        int val = 0;

        if (prompt)
        {
            cout << prompt;
        }
        do
        {
            val = getInt();
            // The range of the valid entry is checked after a valid integer is received.
            if (val < min || val > max)
            {
                // the errorMessage is displayed only if the errorMessage is not null.
                if (errorMessage)
                {
                    cout << errorMessage;
                }
                // the range of valid entry is displayed in the following format only if the showRangeAtError argument is trues
                if (showRangeAtError)
                {
                    cout << "[" << min << " <= value <= " << max << "]: ";
                }
            }
        } while (val < min || val > max);

        return val;
    }

    //Optional Challenge
    char* getcstr(const char* prompt, std::istream& istr, char delimiter)
    {
        char input[BUFFERSIZE];
        char* str;

        if (prompt)
        {
            cout << prompt;
        }
        // Receives an unknown size string from the istream object
        istr.getline(input, BUFFERSIZE, delimiter);
        // allocates a dynamic Cstring to the size of the string 
        str = new char[strlen(input) + 1];
        // copies the value of the string into it
        strcpy(str, input);

        // return the dynamically allocated memory
        return str;
    }

}