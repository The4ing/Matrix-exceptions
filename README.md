
# Matrix Function Manager – Exercise 3

## Student Information:
**Name:** [Romi Sinizkey Or-ram Atar]  
**ID:** [322311457 ]  


---

## 1. General Description:
This program manages a dynamic list of matrix operations using object-oriented programming in C++.  
It enhances the previous assignment by adding **exception handling**, **robust input validation**, and **support for reading commands from a file**.

---

## 2. File List and Their Purpose:
- `main.cpp` – Entry point of the program; handles input flow and exception display.
- `Matrix.cpp / Matrix.h` – Implements matrix data structure and operations.
- `Operation.cpp / Operation.h` – Base class for all operations.
- `Options.cpp / Options.h` – Manages the list of created operations.
- `Eval.cpp`, `Scal.cpp`, `Add.cpp`, `Sub.cpp`, `Comp.cpp` – Implement specific operations.
- `Exceptions.h` – Contains custom exception classes.
- `Helpers.h/cpp` – Utility functions for parsing, validation, and formatting.
- `CommandReader.cpp / .h` – Manages reading commands either from the terminal or a file.

---

## 3. Main Data Structures:
- `Matrix` – 2D vector representing square matrices of max size 5×5.
- `std::vector<std::unique_ptr<Operation>>` – Stores created operations, allows dynamic allocation and polymorphism.
- `std::unordered_map`  – Maps command strings to handlers.

---

## 4. Algorithms:
- Matrix operations are computed with basic nested loops (no external libraries used).
- The program maintains command history and updates it dynamically on insert/delete.
- Input validation is handled via string parsing and exception-based control flow.

---

## 5. Design Overview:
- The system uses inheritance where `Operation` is the base class, and each concrete operation inherits from it.
- `Options` class holds and manages the list of current operations.
- Command parsing is done using `std::istringstream` to handle both terminal and file input line-by-line.
- `read` and `resize` are implemented as special command handlers.

---

## 6. Object Responsibilities & Interactions:
- `main()` delegates command handling to `CommandReader`.
- `CommandReader` decides the input source and directs commands to the operation handler.
- `Options` validates and manages function list capacity and updates.
- Each derived class from `Operation` performs its own evaluation logic.

---

## 7. Known Bugs:
- None known at submission time.

---

## 8. Additional Notes:
- **The `read` command is fully implemented and supports reading commands from a file.**  
  The program returns to terminal input after the file ends or an error occurs.
- Errors in commands (e.g., too many or too few arguments) are caught and reported per line.
- Maximum allowed matrix size is `5x5`, and values must be in range `[-1024, 1000]`.
- The initial maximum number of operations is requested at program start (between 2 and 100 inclusive).
- Exception classes are derived from `std::exception`, and handled at high-level control flow.
- Commands are processed one line at a time, each line is treated atomically.
- Supported commands: `eval`, `add`, `sub`, `scal`, `comp`, `resize`, `del`, `help`, `exit`, and `read`.

---

