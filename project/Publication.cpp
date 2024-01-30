/*
  Module: Publication
  Description: This module defines the Publication class, which serves
  as a base class for different types of publications in the library, such as
  books and periodicals. It encompasses common attributes and functionalities
  shared among various publication types.
  Author: Mohsen Sabet
*/

#define _CRT_SECURE_NO_WARNINGS

#include"Publication.h"

namespace sdds {
	Publication::Publication() : m_date() {
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
	}

	void Publication::set(int member_id)
	{
		if (member_id >= 10000 && member_id <= 99999) {
			m_membership = member_id;
		}
		else {
			m_membership = 0;
		}
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}
	void Publication::resetDate()
	{
		m_date = Date();
	}

	char Publication::type() const
	{
		return 'P';
	}

	bool Publication::onLoan() const
	{
		return m_membership != 0;
	}

	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title) const
	{
		return strstr(m_title, title) != nullptr;
	}

	Publication::operator const char* () const
	{
		return m_title;
	}

	int Publication::getRef() const
	{
		return m_libRef;
	}

	bool Publication::conIO(const ios& io) const
	{
		return ( & io == &cin || &io == &cout);
	}

	ostream& Publication::write(ostream& os) const
	{
		if (conIO(os)) {
			os << "| " << m_shelfId << " | ";
			if (strlen(m_title) > SDDS_TITLE_WIDTH) {

				os.write(m_title, SDDS_TITLE_WIDTH);
			}
			else {

				os << left;
				os.width(SDDS_TITLE_WIDTH);
				os.fill('.');
				os<< m_title;
			}
			
			os << " | ";
			if (m_membership == 0) {
				os.fill(' ');
				os.width(SDDS_SHELF_ID_LEN);
				os << " N/A ";
			}
			else {
				os.width(SDDS_SHELF_ID_LEN);
				os << m_membership;
			}
			os << " | " << m_date << " |";

		}
		else {
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t";
			os << m_title << "\t" << m_membership << "\t" << m_date;
		}
		return os;


	}

	istream& Publication::read(istream& istr) {
		
		// Clear all the attributes by freeing the memory and setting everything to their default values.
		if (m_title != nullptr) {
			delete[] m_title;
		}
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		m_date = Date();

		// Local variables to temporarily hold the data

		char temp_title[256];
		char temp_shelfId[SDDS_SHELF_ID_LEN + 1];
		int temp_membership = 0;
		int temp_libRef = -1;
		Date temp_date;

		if (conIO(istr)) {
			istr.ignore(1000, '\n');
			cout << "Shelf No: ";
			istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1);
			if (strlen(temp_shelfId) != SDDS_SHELF_ID_LEN) {
				istr.setstate(ios::failbit);
			}
			
			cout << "Title: ";
			istr.getline(temp_title, 256);
			
			cout << "Date: ";
			istr >> temp_date;
		}
		else {
			// File IO

			istr >> temp_libRef;
			istr.ignore();  // skip the tab
			istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(temp_title, 256, '\t');
			istr >> temp_membership;
			istr.ignore();  // skip the tab
			istr >> temp_date;
		}
		
		// If date is in an invalid state, set the istr to a fail state manually
		if (!temp_date) {
			istr.setstate(ios::failbit);
		}

		// If the input stream is in a valid state
		if (istr) {
			// Dynamically store the title into the title attribute
			m_title = new char[strlen(temp_title) + 1];
			strcpy(m_title, temp_title);

			// Copy the shelf id into the shelfId attribute
			strcpy(m_shelfId, temp_shelfId);

			// Set the membership, date, and libRef attributes
			set(temp_membership);
			m_date = temp_date;
			m_libRef = temp_libRef;
		}

		return istr;
	}


	Publication::operator bool() const
	{
		return m_title != nullptr && m_title[0] != '\0' && m_shelfId[0] != '\0';
	}

	Publication::Publication(const Publication& other)
	{
		m_membership = other.m_membership;
		m_libRef = other.m_libRef;
		m_date = other.m_date;
		m_title = new char[strlen(other.m_title) + 1];
		strcpy(m_title, other.m_title);
		strcpy(m_shelfId, other.m_shelfId);
	}

	Publication& Publication::operator=(const Publication& other)
	{
		if (this != &other) {
			delete[] m_title;
			m_title = nullptr;

			if (other.m_title != nullptr) {
				m_title = new char[strlen(other.m_title) + 1];
				strcpy(m_title, other.m_title);
			}

			strcpy(m_shelfId, other.m_shelfId);

			m_membership = other.m_membership;
			m_libRef = other.m_libRef;
			m_date = other.m_date;
		}
		return *this;
	}

	Publication::~Publication() {
		delete[] m_title;
	}


}