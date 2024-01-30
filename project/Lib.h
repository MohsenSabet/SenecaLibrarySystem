/*
  Module: LibApp
  Description: LibApp is the core module of the Seneca Library Application.
  It integrates all other modules and provides the main application logic,
  user interface, and user interaction workflows. It drives the application's
  main functionalities such as adding, removing, checking out, and returning publications.
  Author: Mohsen Sabet
*/

#ifndef SDDS_LIB_H__
#define SDDS_LIB_H__

namespace sdds {

    const int SDDS_MAX_LOAN_DAYS = 15;
    // maximum number of day a publication can be borrowed with no penalty
    const int SDDS_TITLE_WIDTH = 30;
    // The width in which the title of a publication should be printed on the console
    const int SDDS_AUTHOR_WIDTH = 15;
    // The width in which the author name of a book should be printed on the console
    const int SDDS_SHELF_ID_LEN = 4;
    // The width in which the shelf id of a publication should be printed on the console
    const int SDDS_LIBRARY_CAPACITY = 333;
    // Maximum number of publications the library can hold.
}
#endif // !SDDS_LIB_H__
