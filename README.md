# Data Structures in C

This project was created as a team assignment for the **C Programming course** at LUT University. The project was completed over multiple weeks with the goal of learning C programming fundamentals, testing practices, and collaborative teamwork.

**Note:** All code, comments, and documentation are written in Finnish as required by the course. The pdf files include the installation and operating instructions, quality report and final report of the project.

## Project Overview

This project implements three fundamental data structures in C:

1. **Linked List** - Single and doubly linked list implementation with sorting algorithms
2. **Binary Tree** - Binary search tree with traversal and manipulation functions
3. **Graph** - Graph data structure with node and edge management

Each data structure includes complete implementations, header files, comprehensive test suites, and sample data files for testing.

## Project Structure

```
Koodit/
├── main.c                          # Main program with interactive menu
├── linkitettyListaKirjasto.c/h    # Linked list implementation
├── binaariPuuKirjasto.c/h         # Binary tree implementation
├── graafiKirjasto.c/h             # Graph implementation
├── *Testit.c                      # Test suites for each data structure
├── Makefile                       # Build configuration
└── testidata/                     # Test data files
```

## Building and Running

Navigate to the `Koodit` directory and use the Makefile:

```bash
cd Koodit
make              # Compile the main program
./projekti        # Run the program
make test1        # Run linked list tests
make test2        # Run binary tree tests
make test3        # Run graph tests
make clean        # Clean build artifacts
```

## Learning Objectives

Through this project, the team gained hands-on experience with:
- C programming language fundamentals
- Memory management and pointers
- Data structure implementation
- Algorithm design and efficiency
- Unit testing and debugging
- Version control and team collaboration
- Makefile-based build systems

---

