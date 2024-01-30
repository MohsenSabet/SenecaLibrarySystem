/*
  Module: LibApp
  Description: LibApp is the core module of the Seneca Library Application.
  It integrates all other modules and provides the main application logic,
  user interface, and user interaction workflows. It drives the application's
  main functionalities such as adding, removing, checking out, and returning publications.
  Author: Mohsen Sabet
*/

#ifndef SDDS_LIBAPP_H__
#define SDDS_LIBAPP_H__

#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
#include "Book.h"
#include "PublicationSelector.h"

namespace sdds {


	class LibApp {
		char m_fileName[256]={};                    // File name
		Publication* PPA[SDDS_LIBRARY_CAPACITY]; // Publication Pointers Array
		int NOLP =0;                          // Number Of Loaded Publications
		int LLRN;                              // Last Library Reference Number
		bool m_changed;
		 
		Menu m_mainMenu;
		Menu m_exitMenu;
		Menu m_publicationMenu;

		bool confirm(const char* message);
		void load();
		void save();
		int search(int,char);
		void returnPub();
		Publication *getPub(int libRef);
	public:
		LibApp();
		LibApp(const char filename[256]);
		~LibApp();
		void newPublication();
		void removePublication();
		void checkOutPub();
		void run();
	};

}

#endif // !SDDS_LIBAPP_H__
