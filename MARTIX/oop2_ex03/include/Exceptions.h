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

class MatrixSizeOutOfRange : public std::exception {
public:
    MatrixSizeOutOfRange() = default;
    const char* what() const noexcept override {
        return "Matrix size is out of range (must be 1 to 5).\n";
    }
};

class MatrixValueOutOfRange : public std::exception {
public:
    MatrixValueOutOfRange() = default;
    const char* what() const noexcept override {
        return "Matrix value is out of range (-1024 to 1000).\n";
    }
};

