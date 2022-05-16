/* Citation and Sources...
Final Project Milestone 4
Module: CovidPatient
Filename: CovidPatient.h
Version 4.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/22  Start this project
2021/7/22 finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/


#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_

#include <iostream>
#include "Patient.h"

using namespace std;
namespace sdds
{
	class CovidPatient : public Patient
	{
	public:
		// default constructor
		CovidPatient();
		virtual char type()const;
		ostream& write(ostream& ostr)const;
		istream& read(istream& istr);
		istream& csvRead(istream& istr);
	};
}
#endif // !SDDS_COVIDPATIENT_H_



