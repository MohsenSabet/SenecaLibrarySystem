## How to Run the Seneca Library Application

This section provides detailed instructions on how to compile and run the Seneca Library Application, a project involving multiple milestones that culminate in a comprehensive library management system.

### Prerequisites

- A C++ compiler (such as `g++`) capable of compiling C++11 standard code.
- The project's source files, including `.cpp` and `.h` files for Utils, Date, Streamable, Publication, Book, PublicationSelector, LibApp modules, and others as detailed in each milestone.

### Compiling the Project

1. **Clone the Repository**: Clone or download the repository to your local machine.
```
git clone https://github.com/yourusername/Seneca-Library-Application.git
```
2. **Navigate to the Project Directory**: Change to the directory containing the project files.
```
cd Seneca-Library-Application
```
3. **Compile the Source Code**: Compile the source files using the C++ compiler. Here's an example command to compile the project (adjust the source file names as necessary):

```
g++ -Wall -std=c++11 -g -o LibApp Utils.cpp Date.cpp Streamable.cpp Publication.cpp Book.cpp PublicationSelector.cpp LibApp.cpp LibAppMain.cpp
```

- `-Wall`: Enables all compiler's warning messages.
- `-std=c++11`: Compiles the code using the C++11 standard.
- `-g`: Includes debugging information in the executable.
- `-o LibApp`: Names the output executable `LibApp`.

### Running the Project

After compiling the project, execute the `LibApp` binary to start the application:

```
./LibApp
```


