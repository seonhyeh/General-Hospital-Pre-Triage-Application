/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.cpp
Version 3.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/15  Start this project
2021/7/16 istream& Patient::csvRead(istream& istr) -fixed
2021/7/16 ostream& Patient::write(ostream& ostr)const - fixed (output length)
2021/7/17 done
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	const int nameMax = 25;

	Patient::Patient(int ticketNum, bool falg) : m_ticket(ticketNum)
	{
		m_name = nullptr;
		m_OHIPnum = 0;
		m_falg = falg;
	}

	bool Patient::fileIO()const
	{
		return m_falg;
	}

	void Patient::fileIO(bool set)
	{
		m_falg = set;
	}

	// Overload the operator== to compare the current object with an incoming single character 
	bool Patient::operator== (const char singleChar)const
	{
		return type() == singleChar;
	}

	// Overload the operator to compare the current object to another patient 
	bool Patient::operator== (const Patient& patient)const
	{
		return type() == patient.type();
	}

	// Sets the time of the ticket of the patient to the current time.
	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	// If the patient is casted to the Time type it should return the time of the ticket
	Patient::operator Time()const
	{
		return (Time)m_ticket;
	}

	// Create a query function called number that returns the number of the ticket.
	int Patient::number()const
	{
		return m_ticket.number();
	}

	ostream& Patient::csvWrite(ostream& ostr)const
	{
		ostr << type() << "," << m_name << "," << m_OHIPnum << ",";
		// it will call the csvWrite function of the member ticket object
		m_ticket.csvWrite(ostr);

		return ostr;
	}

	istream& Patient::csvRead(istream& istr)
	{
		char comma = '\0';

		//  the name pointer is deleted before the allocation to guarantee there is no memory leak
		if (m_name)
		{
			delete[] m_name;
			m_name = nullptr;
		}
		m_name = getcstr(nullptr, istr, ',');
		//  extract an integer from istream into the OHIP member variable && discard the delimeter
		istr >> m_OHIPnum >> comma;
		// extraction by calling the csvRead of the member ticket object
		m_ticket.csvRead(istr);

		return istr;

	}

	// Inserts the patient information into the ostream to be displayed on the console
	ostream& Patient::write(ostream& ostr)const
	{
		int i = 0;
		// insert the member [ticket object](#the-ticket into ostream
		m_ticket.write(ostr);
		// go to newline
		ostr << endl;
		// insert the name up to 25 character 
		if (m_name && strlen(m_name) > nameMax)
		{
			for (i = 0; i < nameMax; i++)
			{
				ostr << m_name[i];
			}
		}
		else // (ingnore the rest if more that 25 characters)
		{
			ostr << m_name;
		}
		// insert ", OHIP: " && insert the OHIP number number
		ostr << ", OHIP: " << m_OHIPnum;

		return ostr;
	}

	// Extracts the ticket information from the console using istream
	istream& Patient::read(istream& istr)
	{
		// the name pointer is deleted before the allocation to guarantee there is no memory leak
		if (m_name)
		{
			delete[] m_name;
			m_name = nullptr;
		}
		m_name = getcstr("Name: ", istr, '\n');
		// Extract the 9 digit OHIP number from istream; validate it and make sure it is 9 digits.
		// Invalid OHIP Number, [100000000 <= value <= 999999999]: 123123123
		m_OHIPnum = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");

		return istr;
	}

	Patient::~Patient()
	{
		delete[] m_name;
		m_name = nullptr;
	}
}