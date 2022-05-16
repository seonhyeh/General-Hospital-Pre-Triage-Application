/* Citation and Sources...
Final Project Milestone 1
Module: Time
Filename: Time.cpp
Version 1.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/2  Start this project
2021/7/4  std::ostream& Time::write(std::ostream& ostr) const - output mins '0' is missing
2021/7/4  std::istream& Time::read(std::istream& istr)
- error: conditional jump or move depends on uninitialised value(s).
2021/7/4 Time Time::operator-(const Time& D)const -  made a code one line
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{
	const int TODAYMIN = 1440; // 24 * 60

	// sets the Time to the current time using sdds::getTime()
	Time& Time::setToNow()
	{
		m_min = getTime();

		return *this;
	}

	//Constructs the Time by setting the number of minutes held in the object or set the time to zero by default.
	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	// Writes the time into a stream in HH:MM format padding the spaces with zero if the numbers are single digit
	std::ostream& Time::write(std::ostream& ostr) const
	{
		int hours = m_min / 60;
		int mins = m_min % 60;

		// HH:MM format
		ostr.fill('0');
		ostr.width(2);
		ostr << hours << ':';
		ostr.fill('0');
		ostr.width(2);
		ostr << mins;
		return ostr;
	}

	// Reads the time from a stream in H:M format
	std::istream& Time::read(std::istream& istr)
	{
		int hours = 0;
		int mins = 0;
		char colon;

		istr >> hours >> colon >> mins;
		if (istr)
		{
			// istr >> hours >> colon >> mins;
			if (hours < 0 || colon != ':' || mins < 0)
			{
				istr.setstate(ios::failbit);
			}
			m_min = hours * 60 + mins;
		}
		else
		{
			istr.setstate(ios::failbit);
		}

		return istr;
	}

	// Time basic arithmetic operations
	// Calculates the time difference between the current time and the incoming argument Time D
	Time& Time::operator-= (const Time& D)
	{
		int d = D.m_min % TODAYMIN;
		m_min += TODAYMIN;
		m_min -= d;
		m_min %= TODAYMIN;

		return *this;
	}

	Time Time::operator-(const Time& D)const
	{
		Time time;
		int d = D.m_min % TODAYMIN;

		/*time.m_min = m_min + TODAYMIN;
		time.m_min = m_min - d;*/
		time.m_min = (m_min + TODAYMIN - d) % TODAYMIN;

		//  returns a Time object
		return time;
	}

	// Add the minute value of the right operand to the value of the left operand
	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;

		//  returns the reference of the left operand.
		return *this;
	}

	Time Time::operator+(const Time& D)const
	{
		Time time;

		time.m_min = m_min + D.m_min;

		return time;
	}

	// Sets the minute value of the left operand to the value of the right operand
	Time& Time::operator=(unsigned int val)
	{
		m_min = val;

		return *this;
	}

	// Multiplies the minutes' value of the left operand by the value of the right operand
	Time& Time::operator *= (unsigned int val)
	{
		m_min *= val;

		return *this;
	}

	Time Time::operator *(unsigned int val)const
	{
		Time time;

		time.m_min = m_min * val;

		return time;
	}

	// Divides the minutes' value of the left operand by the value of the right operand 
	Time& Time::operator /= (unsigned int val)
	{
		m_min /= val;

		return *this;
	}

	Time Time::operator /(unsigned int val)const
	{
		Time time;

		time.m_min = m_min / val;

		return time;
	}

	// When the time is cast to an integer, it will return the number of minutes as an integer.
	Time::operator int()const
	{
		return (int)m_min; // casting
	}

	// When the time is cast to an unsigned integer, it will return the number of minutes.
	Time::operator unsigned int()const
	{
		return m_min; //m_min default value is unsigned int 
	}

	// Overload the insertion operator to be able to insert a Time object into an ostream object
	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		return D.write(ostr);
	}

	// Overload the extraction operator to be able to extract data from an istream object into the Time object
	std::istream& operator>>(std::istream& istr, Time& D)
	{
		return D.read(istr);
	}
}