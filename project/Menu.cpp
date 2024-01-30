/* Citation and Sources...
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	Mohsen Sabet
Student Number: 113205165
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"


namespace sdds {
    MenuItem::MenuItem() : m_content(nullptr) {}

    MenuItem::MenuItem(const char* item) : m_content(nullptr) {
        if (item) {
            m_content = new char[strlen(item) + 1];
            strcpy(m_content, item);
        }
    }

    MenuItem::~MenuItem() {
        delete[] m_content;
    }

    bool MenuItem::isEmpty() const {
        return m_content == nullptr;
    }

    MenuItem::operator bool() const {
        return !isEmpty();
    }

    MenuItem::operator const char* () const {
        return m_content;
    }

    void MenuItem::display() const {
        if (!isEmpty()) {
            cout << m_content;
        }
    }

    Menu::Menu() : m_menuTitle(nullptr), m_itemCount(0) {}

    Menu::Menu(const char* title) : m_menuTitle(nullptr), m_itemCount(0) {
        if (title) {
            m_menuTitle = new char[strlen(title) + 1];
            strcpy(m_menuTitle, title);
        }
    }

    Menu::~Menu() {
        delete[] m_menuTitle;
        for (unsigned int i = 0; i < m_itemCount; ++i) {
            delete m_menuItems[i];
        }
    }

    void Menu::display() const {
        if (m_menuTitle && m_menuTitle[0] != '\0') {
            cout << m_menuTitle << "\n";
        }
        for (unsigned int i = 0; i < m_itemCount; ++i) {
            cout << " " << i + 1 << "- " << m_menuItems[i]->m_content << endl;
        }
        cout << " 0- Exit\n> ";
    }

    unsigned int Menu::run()const {
        unsigned int selection;
        display();
        int flag = 1;

        while (flag) {
            cin >> selection;
            if (cin.fail() || selection > m_itemCount) {
                cin.clear();
                cin.ignore(99999, '\n');
                cout << "Invalid Selection, try again: ";
            }
            else {
                flag = 0;
            }
        }
        return selection;
    }

    int Menu::operator~() {
        return run();
    }

    Menu& Menu::operator<<(const char* menuitemConent) {
        if (m_itemCount < MAX_MENU_ITEMS) {
            m_menuItems[m_itemCount] = new MenuItem(menuitemConent);
            m_itemCount++;
        }

        return *this;
    }

    Menu::operator bool() const {
        return m_itemCount > 0;
    }

    Menu::operator unsigned int() const {
        return m_itemCount;
    }

    Menu::operator int() const {
        return m_itemCount;
    }

    const char* Menu::operator[](unsigned int index) const {
        return *m_menuItems[index % m_itemCount];
    }

    ostream& operator<<(ostream& os, const Menu& menu) {
        if (menu.m_menuTitle && menu.m_menuTitle[0] != '\0') {
            os << menu.m_menuTitle;
        }
        return os;
    }
}
