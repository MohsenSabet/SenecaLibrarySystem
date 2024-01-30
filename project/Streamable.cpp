/*
  Module: Streamable
  Description: The Streamable module is an interface that defines the
  structure for streaming operations (read and write) in the application.
  It provides a consistent interface for input and output operations
  across various classes that represent different entities in the library system.
  Author: Mohsen Sabet
*/

#include "Streamable.h"

namespace sdds {
	ostream& operator<<(ostream& os, const Streamable& object)
	{
		if (object) {
		object.write(os);
		}
		return os;
	}

	istream& operator>>(istream& is, Streamable& object)
	{
		return object.read(is);
	}
}