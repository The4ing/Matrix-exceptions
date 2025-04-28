#pragma once



/*This excpetion is thrown when an input coudln't be read*/
class InputFailure : public std::exception {
public:
    InputFailure() {};
    const char* what() const noexcept { return "Failed to read input, Make sure to enter numbers!\n"; }
};

/*This exception is thrown when a wrong number of arguemnts was entered*/
class InvalidArguemntCount : public std::exception {
public:
    InvalidArguemntCount() {};
    const char* what() const noexcept { return "Invalid arguments count\n"; }
};

/*This exception is thrown when an operation number wasn't in the operations list*/
class InvalidOperation : public std::exception {
public:
    InvalidOperation() {};
    const char* what() const noexcept {
        return "Operation not found in the list!!\n";
    }
};

/* This exception is thrown when a wrong action is entered*/
class InvalidAction : public std::exception {
public:
    InvalidAction() {};
    const char* what() const noexcept {
        return "Action not found!!\n";
    }
};