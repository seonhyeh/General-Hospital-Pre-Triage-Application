/* Citation and Sources...
Final Project Milestone 4
Module: CovidPatient
Filename: CovidPatient.cpp
Version 4.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/22  Start this project
2021/7/23 finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include "CovidPatient.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	// used to determine what is the ticket number of the next COVID test Patient
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient(nextCovidTicket)
	{
		nextCovidTicket++;
	}

	char CovidPatient::type()const
	{
		return 'C';
	}

	// csvRead virtual function override
	istream& CovidPatient::csvRead(istream& istr)
	{
		Patient::csvRead(istr);
		// number() function of the Patient class plus one
		nextCovidTicket = number() + 1;
		istr.ignore(BUFFERSIZE, '\n');

		return istr;
	}

	// write virtual function override
	ostream& CovidPatient::write(ostream& ostr)const
	{
		if (fileIO())
		{
			Patient::csvWrite(ostr);
		}
		else
		{
			ostr << "COVID TEST" << endl;
			Patient::write(ostr);
			ostr << endl;
		}

		return ostr;
	}

	// read virtual function override.
	istream& CovidPatient::read(istream& istr)
	{
		if (fileIO())
		{
			csvRead(istr);
		}
		else
		{
			Patient::read(istr);
		}

		return istr;
	}
}