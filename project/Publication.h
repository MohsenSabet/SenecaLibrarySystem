/*
  Module: Publication
  Description: This module defines the Publication class, which serves
  as a base class for different types of publications in the library, such as
  books and periodicals. It encompasses common attributes and functionalities
  shared among various publication types.
  Author: Mohsen Sabet
*/

#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"
using namespace std;
namespace sdds {
    
    class Publication : public Streamable {
        char* m_title{};
        char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};  // 4  + null terminator
        int m_membership = 0;
        int m_libRef = -1;
        Date m_date;

    public:
        //defult constructor 
        Publication();

        //destructor 
        ~Publication();

        // Sets the membership attribute to either zero or a five-digit integer.
        virtual void set(int member_id); 
        
        // Sets the **libRef** attribute value
        void setRef(int value);
        
        // Sets the date to the current date of the system.
        void resetDate();
       

        //Returns the character 'P' to identify this object as a "Publication object"
        virtual char type()const;
        
        //Returns true if the publication is checkout (membership is non-zero)
        bool onLoan()const;
        
        //Returns the date attribute
        Date checkoutDate()const;
        
        //Returns true if the argument title appears anywhere in the title of the 
        //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        bool operator==(const char* title)const;
        
        //Returns the title attribute
        operator const char* ()const;
       
        //Returns the libRef attirbute. 
        int getRef()const;
        
        //Returns true if the address of the io object 
        //is the same as the address of either the cin object or the cout object.
        bool conIO(const ios& io)const;

        /*
        If the os argument is a console IO object (use conIO()), print shelfId, title, membership and date attributes as the following 
        format (title is left-justified padded with dots)

        Otherwise:

        Print the type() and then libRef, shelfId, title, 
        membership and date attributes in a tab-separated format.
        No newline is printed afterwards either way.
        */
        ostream& write(ostream& os) const;

        istream& read(istream& istr);

        //Returns true if neither of the title or shelfId attributes is null or empty.
        //Otherwise, it will return false.
        operator bool() const;

        Publication(const Publication& other);  // copy constructor
        
        Publication& operator=(const Publication& other);  // copy assignment operator

    };


}
#endif // !SDDS_PUBLICATION_H__
