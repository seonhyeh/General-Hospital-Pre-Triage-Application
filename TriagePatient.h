/* Citation and Sources...
Final Project Milestone 4
Module: TriagePatient
Filename: TriagePatient.h
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

#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H

#include <iostream>
#include "Patient.h"

namespace sdds
{
	class TriagePatient : public Patient
	{
		char* m_symptoms; //  list of the symptoms
	public:
		// Default Constructor
		TriagePatient();
		virtual char type()const;
		//  virtual function override
		ostream& csvWrite(ostream& ostr)const;
		istream& csvRead(istream& istr);
		ostream& write(ostream& ostr)const;
		istream& read(istream& istr);
		// Destructor
		~TriagePatient();
	};
}
#endif // !SDDS_TRIAGEPATIENT_H



