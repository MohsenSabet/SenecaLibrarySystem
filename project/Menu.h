
/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Version 1.0
Author	Mohsen Sabet
Student Number: 113205165
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20;
    class Menu;
    class MenuItem {
    private:
        friend class Menu;
        char* m_content;
        MenuItem();
        MenuItem(const char* item);
        MenuItem(const MenuItem&) = delete;
        MenuItem& operator=(const MenuItem&) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char* () const;
        void display() const;
        bool isEmpty() const;
    };

    class Menu {
        char* m_menuTitle;
        MenuItem* m_menuItems[MAX_MENU_ITEMS]{};
        unsigned int m_itemCount;
    public:
        Menu();
        Menu(const char* title);
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;
        ~Menu();
        void display()const;
        unsigned int run()const;
        int operator~();
        Menu& operator<<(const char* menuitemConent);
        operator bool() const;
        operator unsigned int() const;
        operator int() const;
        const char* operator[](unsigned int index) const;
        friend ostream& operator<<(ostream& os, const Menu& menu);
    };
}
#endif //!SDDS_MENU_H__
