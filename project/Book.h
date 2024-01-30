/* Citation and Sources...
Final Project Milestone 5
Module: Book
Filename: Book.h
Version 1.0
Author	Mohsen Sabet
Student Number: 113205165
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include<iostream>
#include <cstring>
#include "Publication.h"
const size_t AUTHOR_NAME_LEGNTH = 256;

using namespace std;
namespace sdds {
	class Book : public Publication {
		char* m_author;
	public:
		Book();
		~Book();
		Book(const Book& source);
		Book& operator=(const Book& source);

		virtual char type()const;
		ostream& write(ostream& os)const;
		istream& read(istream& is);

		void set(int memberId);
		operator bool() const;
	};
}

#endif // !SDDS_BOOK_H__
