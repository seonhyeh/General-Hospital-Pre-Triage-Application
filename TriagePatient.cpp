/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.cpp
Version 4.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/22  Start this project
2021/7/23  finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include "TriagePatient.h"
#include "utils.h"

namespace sdds
{
	//  used to determine what is the ticket number of the next triage Patient
	int nextTriageTicket = 1;

	TriagePatient::TriagePatient() :Patient(nextTriageTicket)
	{
		m_symptoms = nullptr;
		nextTriageTicket++;
	}

	char TriagePatient::type()const
	{
		return 'T';
	}

	ostream& TriagePatient::csvWrite(ostream& ostr)const
	{
		Patient::csvWrite(ostr);
		ostr << ',' << m_symptoms;

		return ostr;
	}

	istream& TriagePatient::csvRead(istream& istr)
	{
		char comma = '\0';

		if (m_symptoms)
		{
			delete[] m_symptoms;
			m_symptoms = nullptr;
		}
		Patient::csvRead(istr);
		// Ignores a character (comma)
		istr >> comma;
		m_symptoms = getcstr(nullptr, istr, '\n');
		nextTriageTicket = number() + 1;

		return istr;
	}

	ostream& TriagePatient::write(ostream& ostr)const
	{
		if (fileIO())
		{
			csvWrite(ostr);
		}
		else
		{
			ostr << "TRIAGE" << endl;
			Patient::write(ostr);
			ostr << endl;
			ostr << "Symptoms: " << m_symptoms << endl;
		}

		return ostr;
	}

	istream& TriagePatient::read(istream& istr)
	{
		if (fileIO())
		{
			csvRead(istr);
		}
		else
		{
			if (m_symptoms)
			{
				delete m_symptoms;
				m_symptoms = nullptr;
			}
			Patient::read(istr);
			m_symptoms = getcstr("Symptoms: ", istr, '\n');
		}

		return istr;
	}

	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
		m_symptoms = nullptr;
	}
}