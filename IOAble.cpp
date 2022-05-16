/* Citation and Sources...
Final Project Milestone 2
Module: IOAble
Filename: IOAble.cpp
Version 2.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/11  Start this project
2021/7/11  error-missing include <iostream>
2021/7/11 finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds
{
    ostream& operator<<(ostream& ostr, const IOAble& io)
    {
        // insert the information of an IOAble object into ostream using the IOAble::write function.
        io.write(ostr);

        return ostr;
    }

    istream& operator>>(istream& istr, IOAble& io)
    {
        //  extract information from an istream into an IOAble object using the IOAble::read function.
        io.read(istr);

        return istr;
    }
}