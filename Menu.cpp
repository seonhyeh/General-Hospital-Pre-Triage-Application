/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 2.0
Name: Seonhye Hyeon
ID: 125635193
Email: shyeon@myseneca.ca
Revision History
-----------------------------------------------------------
Date      Reason
2021/7/10  Start this project
2021/7/11  finished
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Menu.h"
#include "utils.h"
using namespace std;
namespace sdds
{
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		if (MenuContent && NoOfSelections > 0)
		{
			// Dynamically allocates memory to hold the content pointed by m_text
			m_text = new char[strlen(MenuContent) + 1];
			strcpy(m_text, MenuContent);
			// keeps the number of Selections in m_noOfSel
			m_noOfSel = NoOfSelections;
		}
		else
		{
			m_text = nullptr;
			m_noOfSel = 0;
		}
	}

	// Deallocates the dynamically allocated memory
	Menu::~Menu()
	{
		if (m_text)
		{
			delete[] m_text;
			m_text = nullptr;
		}
	}

	// Copy and assignment
	Menu::Menu(const Menu& menu)
	{
		m_noOfSel = menu.m_noOfSel;
		if (menu.m_text)
		{
			m_text = new char[strlen(menu.m_text) + 1];
			strcpy(m_text, menu.m_text);
		}
		else
		{
			m_text = nullptr;
		}
	}

	void Menu::display()const
	{
		cout << m_text << endl;
		cout << "0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection)
	{
		//  first calls the display function
		display();
		//  selection as an integer value using the getInt() function
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");

		return Selection;
	}
}