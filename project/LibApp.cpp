/*
  Module: LibApp
  Description: LibApp is the core module of the Seneca Library Application.
  It integrates all other modules and provides the main application logic,
  user interface, and user interaction workflows. It drives the application's
  main functionalities such as adding, removing, checking out, and returning publications.
  Author: Mohsen Sabet
*/

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"


using namespace std;
namespace sdds {
	bool LibApp::confirm(const char* message)
	{
		Menu confirmationMenu(message);
		confirmationMenu << "Yes";
		int response = ~confirmationMenu;
		return (response == 1);
	}

	LibApp::LibApp()
	{
		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit" 
				<< "Cancel and go back to the main menu";

		load();

	}

	LibApp::LibApp(const char filename[256]):
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_publicationMenu("Choose the type of publication:")
	{
		for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++) {
			PPA[i] = nullptr;
		}

		m_mainMenu 
			<< "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";
		
		m_exitMenu 
			<< "Save changes and exit" 
			<< "Cancel and go back to the main menu";

		strcpy(m_fileName, filename);
		

		m_publicationMenu 
			<< "Book" 
			<< "Publication";

		load();
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < NOLP; i++) {
			delete PPA[i];
		}
	}
	
	void LibApp::load()
	{
		cout << "Loading Data" << endl;

		ifstream file(m_fileName);
		char type{};

		for (int i = 0; file; i++) {
			file >> type;
			file.ignore();

			if (file) {
				if (type == 'P') {
					PPA[i] = new Publication;
				}
				else if (type == 'B') {
					PPA[i] = new Book;
				}
				else {
					cout << "no data" << endl;
				}
			}

			if (i < SDDS_LIBRARY_CAPACITY && PPA[i]){
				file >> *PPA[i];
				LLRN = PPA[i]->getRef();
				NOLP++;

			}

		}

	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;

		// Open file for writing (overwriting existing content)
		ofstream file(m_fileName);

		// Iterate through the library publications
		for (int i = 0; i < NOLP; i++) {
			// Save only non-deleted publications (reference number not 0)
			if (PPA[i]->getRef() != 0) {
				file << *PPA[i] << endl;
			}
		}
	}

	int LibApp::search(int option, char type) {
		// Initialize the PublicationSelector for user selection
		PublicationSelector PublicSelector("Select one of the following found matches:", 15);

		// Get user input for the publication title
		cin.ignore(1000, '\n');
		cout << "Publication Title: ";
		char userSelect[256];
		cin.getline(userSelect, 256);

		// Depending on the option, filter and insert the publications into the selector
		for (int i = 0; i < NOLP; i++) {
			// Common condition: matches title and type, and ref is not zero
			bool commonCondition = strstr(*PPA[i], userSelect) && PPA[i]->getRef() != 0 && type == PPA[i]->type();

			if (option == 1 && commonCondition) {
				// Search all publications
				PublicSelector << PPA[i];
			}
			else if (option == 2 && commonCondition && !PPA[i]->onLoan()) {
				// Search only available publications (not on loan)
				PublicSelector << PPA[i];
			}
			else if (option == 3 && commonCondition && PPA[i]->onLoan()) {
				// Search only checked-out publications
				PublicSelector << PPA[i];
			}
		}

		if (PublicSelector) {  // Check if the PublicationSelector has any matches
			PublicSelector.sort(); // Sort the found publications
			int ref = PublicSelector.run(); // Display the publications and get user's selection

			if (ref) {
				// print the publication here
				for (int i = 0; i < NOLP; i++) {
					if (ref == PPA[i]->getRef()) {
						cout << *PPA[i] << endl;
						break; // Exit the loop once the publication is found and printed
					}
				}
				// Return the reference number
				return ref;
			}
			else {
				// If the user aborted the selection
				cout << "Aborted!" << endl;
				return 0; // Indicate abort or no selection
			}
		}
		else {
			// No matching publications found
			cout << "No matches found!" << endl;
			return 0;  // Indicate no matches
		}
	}

	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		// Adjust the search method to search for "on loan" publications only
		int i = m_publicationMenu.run();
		char type = (i == 1) ? 'B' : 'P';
		int ref = search(3, type);

		if (ref != 0 && confirm("Return Publication?")) {
			Publication* pub = getPub(ref);
			if (pub) {
				Date date = getPub(ref)->checkoutDate();
				Date today;
				int daysLate = today - date;  // Placeholder for calculating days late.
				daysLate -= 15;
				if (daysLate > 0) {
					double penalty = 0.50 * daysLate;  // Calculate the penalty.
					cout << "Please pay $" << fixed << setprecision(2) << penalty
						<< " penalty for being " << daysLate << " days late!" << endl;
				}

				pub->set(0);
				cout << "Publication returned" << endl;
				m_changed = true;
			}
		}
	}

	Publication* LibApp::getPub(int libRef)
	{
		for (int i = 0; i < NOLP; i++)
		{
			if (libRef == PPA[i]->getRef()) {
				return PPA[i];
			}
		}

		return nullptr;
	}

	void LibApp::newPublication() {
		//  Check capacity
		if (NOLP == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			return;
		}
		//  Print message
		cout << "Adding new publication to the library" << endl;

		// Get publication type
		int choice = m_publicationMenu.run();

		Publication* pub = nullptr;

		if (choice == 1) {
			pub = new Book();
		
		}
		else if (choice == 2) {
			pub = new Publication();
		}
		else if (choice == 0)
		{
			cout << "Aborted!" << endl;
			return;
		}
		else {
			cin.setstate(ios::failbit);
		}
		// Read object from cin
		if (pub) {
			cin >> *pub;
		}

		// Check cin state
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Aborted!" << endl;
			delete pub;  // Free allocated memory
			return;
		}

		// Confirm with the user
		if (!confirm("Add this publication to the library?")) {
			cout << "Aborted!" << endl;
			delete pub;  // Free allocated memory
			return;
		}

		// If the publication is valid
		if (pub && *pub) {
			LLRN++;
			pub->setRef(LLRN);
			PPA[NOLP] = pub;
			NOLP++;
			m_changed = true;
			cout << "Publication added" << endl;
		}
		else {  // If the publication is not valid
			cout << "Failed to add publication!" << endl;
			delete pub;  // Free allocated memory
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		int i = m_publicationMenu.run();
		char type = (i == 1) ? 'B' : 'P';

		int ref = search(1, type);

		if (ref != 0) {
			if (confirm("Remove this publication from the library?")) {
				m_changed = true;
				getPub(ref)->setRef(0);
				cout << "Publication removed" << endl;
			}
		}

	}

	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;

		int i = m_publicationMenu.run();
		
		char type = (i == 1) ? 'B' : 'P';

		int ref = search(2, type);

		if (ref != 0) {
			if (confirm("Check out publication?")) {

				m_changed = true;

				int membershipNum;
				cout << "Enter Membership number: ";
				cin >> membershipNum;

				// Check for a 5-digit number
				while (membershipNum < 10000 || membershipNum > 99999) {
					cout << "Invalid membership number, try again: ";
					cin >> membershipNum;
					cin.clear();  // Clear any errors from input
					cin.ignore(10000, '\n');  // Skip to next newline
				}

				getPub(ref)->set(membershipNum);

				cout << "Publication checked out" << endl;

			}
		}
		return;
	}

	void LibApp::run() {
		bool exitFlag = false;

		while (!exitFlag) {
			int selection = ~m_mainMenu;

			if (selection == 1) {
				newPublication();
				cout << endl;
			}
			else if (selection == 2) {
				removePublication();
				cout << endl;
			}
			else if (selection == 3) {
				checkOutPub();
				cout << endl;
			}
			else if (selection == 4) {
				returnPub();
				cout << endl;
			}
			else if (selection == 0) {
				if (m_changed) {
					int exitSelection = ~m_exitMenu;
					if (exitSelection == 1) {
						save();
						exitFlag = true;
					}
					else if (exitSelection == 2) {
					}
					else if (exitSelection == 0) {
						if (confirm("This will discard all the changes are you sure?")) {
							exitFlag = true;
						}
					}
				}
				else {
					exitFlag = true;
				}
				cout << endl;
			}
		}

		cout << "-------------------------------------------\n";
		cout << "Thanks for using Seneca Library Application\n";
	}

}

