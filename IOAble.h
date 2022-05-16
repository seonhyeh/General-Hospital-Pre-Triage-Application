/* Citation and Sources...
Final Project Milestone 2
Module: IOAble
Filename: IOAble.h
Version 2.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/11  Start this project
2021/7/11  finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/


#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>
namespace sdds
{
    class IOAble
    {
    public:
        // 4 pure virtual functions
        virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
        virtual std::istream& csvRead(std::istream& istr) = 0;
        virtual std::ostream& write(std::ostream& ostr)const = 0;
        virtual std::istream& read(std::istream& istr) = 0;
        // virtual empty destructor
        virtual ~IOAble() {};
    };
    // Insertion and Extraction helper operator overloads.
    std::ostream& operator<<(std::ostream& ostr, const IOAble& io);
    std::istream& operator>>(std::istream& istr, IOAble& io);
}
#endif // !SDDS_IOABLE_H


