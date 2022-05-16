/* Citation and Sources...
Final Project Milestone 3
Module: Ticket
Filename: Ticket.cpp
Version 3.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/15  Start this project
2021/7/15  done
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include "Ticket.h"

using namespace std;
namespace sdds
{
	// Constructs a Ticket by setting the m_number member variable
	Ticket::Ticket(int number)
	{
		m_number = number;
	}

	// When Ticket is casted to Time it will return the m_time
	Ticket::operator Time()const
	{
		return m_time;
	}

	// A query returning the number of the ticket
	int Ticket::number()const
	{
		return m_number;
	}

	// Sets the Ticket time to the current time
	void Ticket::resetTime()
	{
		m_time.setToNow();
	}

	// Virtual function overrides

	// Inserts comma-separated ticket number and time into ostream.
	ostream& Ticket::csvWrite(ostream& ostr)const
	{
		return ostr << m_number << "," << m_time;
	}

	// Extracts the ticket number and time in a comma-separated format from istream
	istream& Ticket::csvRead(istream& istr)
	{
		char comma = '\0';
		return istr >> m_number >> comma >> m_time;
	}

	// Inserts a ticket into the ostream to be displayed on the console.
	ostream& Ticket::write(ostream& ostr)const
	{
		// Ticket No: 24, Issued at: 12:34
		return ostr << "Ticket No: " << m_number << ", Issued at: " << m_time;
	}

	istream& Ticket::read(istream& istr)
	{
		return csvRead(istr);
	}
}