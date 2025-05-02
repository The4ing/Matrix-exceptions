#pragma once
#include <exception>
#include <stdexcept>

/* This exception is thrown when an input couldn't be read */
class InputFailure : public std::exception {
public:
    InputFailure() = default;
    const char* what() const noexcept override {
        return "Failed to read input, Make sure to enter numbers!\n";
    }
};

/* This exception is thrown when a wrong number of arguments was entered */
class InvalidArgumentCount : public std::exception {
public:
    InvalidArgumentCount() = default;
    const char* what() const noexcept override {
        return "Invalid arguments count\n";
    }
};

/* This exception is thrown when an operation number wasn't in the operations list */
class InvalidOperation : public std::exception {
public:
    InvalidOperation() = default;
    const char* what() const noexcept override {
        return "Operation not found in the list!!\n";
    }
};

/* This exception is thrown when a wrong action is entered */
class InvalidAction : public std::exception {
public:
    InvalidAction() = default;
    const char* what() const noexcept override {
        return "Action not found!!\n";
    }
};

/* This exception is thrown for invalid matrix input */
class InvalidMatrixInput : public std::exception {
public:
    InvalidMatrixInput() = default;
    const char* what() const noexcept override {
        return "Invalid matrix input! Please enter only numbers in matrix format.\n";
    }
};
