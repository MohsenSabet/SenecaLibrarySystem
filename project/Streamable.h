/*
  Module: Streamable
  Description: The Streamable module is an interface that defines the
  structure for streaming operations (read and write) in the application.
  It provides a consistent interface for input and output operations
  across various classes that represent different entities in the library system.
  Author: Mohsen Sabet
*/


#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>

using namespace std;

namespace sdds {

	class Streamable {

	public:
		// Pure virtual functions
		virtual ostream& write(ostream& os) const = 0;
		virtual istream& read(istream& is) = 0;
		virtual bool conIO(const ios& iosObj) const = 0;
		virtual operator bool() const = 0;

		// Virtual destructor
		virtual ~Streamable() { };
	};
	ostream& operator<<(ostream& os, const Streamable& object);
	istream& operator>>(istream& is, Streamable& object);
}
#endif // !SDDS_STREAMABLE_H
