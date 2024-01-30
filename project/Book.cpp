/*
  Module: Book
  Description: This module contains utility functions and classes that
  are used across the Seneca Library Application. These utilities include
  common routines for input validation, formatting, and other helper functions
  essential for the operation of the application.
  Author: Mohsen Sabet
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
namespace sdds {

	Book::Book()
	{
		m_author = nullptr;
	}

	Book::~Book()
	{
		delete[] m_author;
	}

	Book::Book(const Book& source) :Publication(source)
	{
		if (source) {
			delete m_author;
			m_author = new char[strlen(source.m_author) + 1];
			strcpy(m_author, source.m_author);
		}
		else {
			m_author = nullptr;
		}

	}

	Book& Book::operator=(const Book& source)
	{
		Publication::operator=(source);
		if(this != &source){
			delete[] m_author;
			if (source.m_author != nullptr) {
				m_author = new char[strlen(source.m_author) + 1];
				strcpy(m_author, source.m_author);
			}
			else {
				m_author = nullptr;
			}
		}
		return *this;

	}

	char Book::type() const
	{
		return 'B';
	}

	ostream& Book::write(ostream& os) const
	{
		Publication::write(os);

		if (conIO(os)) {
			os << " ";

			if (strlen(m_author) > SDDS_AUTHOR_WIDTH)
			{
				os.write(m_author, SDDS_AUTHOR_WIDTH);
			}
			else 
			{
				os << left;
				os.width(SDDS_AUTHOR_WIDTH);
				os << m_author;
			}
			os << " |";
		}


		else {
			os << "\t" << m_author;
		}

		return os;
	}

	istream& Book::read(istream& is)
	{
		Publication::read(is);

		char temp_author[AUTHOR_NAME_LEGNTH];

		if (conIO(is)) {

			is.ignore(1000, '\n');
			cout << "Author: ";
			is.get(temp_author, AUTHOR_NAME_LEGNTH);
		}
		else {
			is.ignore(1000,'\t');
			is.get(temp_author, AUTHOR_NAME_LEGNTH);
		}
		if (!is.fail()) {
			m_author = new char[strlen(temp_author) + 1];
			strcpy(m_author, temp_author);
		}
		return is;

	}

	void Book::set(int memberId)
	{
		Publication::set(memberId);
		Publication::resetDate();
	}

	Book::operator bool() const
	{
		return m_author && m_author[0] != '\0' && Publication::operator bool();
	}
	 
}//end of namespace

