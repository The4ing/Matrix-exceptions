#include "FunctionCalculator.h"
#include "Add.h"
#include "Sub.h"
#include "Comp.h"
#include "Identity.h"
#include "Transpose.h"
#include "Scalar.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


FunctionCalculator::FunctionCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_operations(createOperations()), m_istr(istr), m_ostr(ostr), m_maxOperations(0)
{
}


void FunctionCalculator::run()
{
    do {
        m_ostr << "Enter max number of operations (2-100): ";
        m_istr >> m_maxOperations;
        if (m_istr.fail() || m_maxOperations < 2 || m_maxOperations > 100) {
            m_ostr << "Invalid input. Please enter a number between 2 and 100.\n";
            m_istr.clear();
            m_istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);

    do {
        m_ostr << '\n';
        printOperations();
        m_ostr << "Enter command ('help' for the list of available commands): ";

        try {
            const auto action = readAction();
            runAction(action);
        }
        catch (const std::exception& e) {
            m_ostr << e.what();
            m_istr.clear();
            m_istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (m_running);
}




void FunctionCalculator::eval()
{
    try {
        if (auto index = readOperationIndex(); index)
        {
            const auto& operation = m_operations[*index];
            int inputCount = operation->inputCount();
            int size = 0;
            m_istr >> size;

            if (m_istr.fail()) throw InputFailure();

           
            if (size > MAX_MAT_SIZE || size <= 0) {
                throw MatrixSizeOutOfRange(); 
            }


            auto matrixVec = std::vector<Operation::T>();
            if (inputCount > 1)
                m_ostr << "\nPlease enter " << inputCount << " matrices:\n";

            for (int i = 0; i < inputCount; ++i)
            {
                SquareMatrix<int> input(size);
                m_ostr << "\nEnter a " << size << "x" << size << " matrix:\n";

                for (int row = 0; row < size; ++row)
                {
                    for (int col = 0; col < size; ++col)
                    {
                        int val;
                        m_istr >> val;
                        if (m_istr.fail()) throw InputFailure();

                        if (val < MIN_ALLOWED_VALUE || val > MAX_ALLOWED_VALUE) {
                            throw MatrixValueOutOfRange(); 
                        }

                        input(row, col) = val;
                    }
                }

                matrixVec.push_back(input);
            }


            m_ostr << "\n";
            operation->print(m_ostr, matrixVec);
            m_ostr << " = \n" << operation->compute(matrixVec);
        }
    }
    catch (const std::exception& e) {
        m_ostr << e.what();
    }
}



void FunctionCalculator::del()
{
    try {
        if (auto i = readOperationIndex(); i) {
            m_operations.erase(m_operations.begin() + *i);
        }
    }
    catch (const std::exception& e) {
        m_ostr << e.what();
        m_istr.clear();
        m_istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}




void FunctionCalculator::resize()
{
    m_ostr << "Enter new maximum number of functions (2-100): ";

    int newMax = 0;
    m_istr >> newMax;

    if (m_istr.fail() || newMax < 2 || newMax > 100)
    {
        m_ostr << "Invalid value. Must be between 2 and 100.\n";
        m_istr.clear();
        m_istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (newMax < static_cast<int>(m_operations.size()))
    {
        m_ostr << "Current number of functions (" << m_operations.size()
            << ") is greater than new maximum (" << newMax << ").\n";
        m_ostr << "Do you want to delete functions from the end to fit the new limit? (y/n): ";

        std::string choice;
        m_istr >> choice;

        if (choice != "y" && choice != "Y")
        {
            m_ostr << "Resize cancelled.\n";
            return;
        }

        while (static_cast<int>(m_operations.size()) > newMax)
        {
            m_operations.pop_back();
        }

        m_ostr << "Deleted extra functions. Now using " << m_operations.size()
            << "/" << newMax << " functions.\n";
    }

    m_maxOperations = newMax;
}



void FunctionCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}


void FunctionCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}


void FunctionCalculator::printOperations() const
{
    m_ostr << "List of available matrix operations:\n";
    for (decltype(m_operations.size()) i = 0; i < m_operations.size(); ++i)
    {
        m_ostr << i << ". ";
        m_operations[i]->print(m_ostr,true);
        m_ostr << '\n';
    }
    m_ostr << '\n';
}


std::optional<int> FunctionCalculator::readOperationIndex() const
{
    int i = 0;
    m_istr >> i;
    if (m_istr.fail()) {
        throw InputFailure();
    }

    if (i < 0 || i >= static_cast<int>(m_operations.size())) {
        throw InvalidOperation();
    }

    return i;
}



FunctionCalculator::Action FunctionCalculator::readAction() const
{
    std::string action;
    m_istr >> action;

    if (m_istr.fail()) {
        throw InputFailure();
    }

    const auto i = std::ranges::find(m_actions, action, &ActionDetails::command);
    if (i != m_actions.end()) {
        return i->action;
    }

    throw InvalidAction();
}
void FunctionCalculator::readFromFile()
{
    std::string filepath;
    m_istr >> filepath;

    if (m_istr.fail()) {
        throw InputFailure();
    }

    std::ifstream file(filepath);
    if (!file.is_open()) {
        m_ostr << "Failed to open file: " << filepath << '\n';
        return;
    }

  
    std::streambuf* prevInput = m_istr.rdbuf();
    std::streambuf* prevOutput = m_ostr.rdbuf();

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.empty()) continue;

        std::istringstream lineStream(line);
        std::ostringstream oss;

        
        m_istr.rdbuf(lineStream.rdbuf());
        m_ostr.rdbuf(oss.rdbuf());

        std::string command;
        lineStream >> command;

        const auto it = std::ranges::find(m_actions, command, &ActionDetails::command);
        if (it == m_actions.end()) {
            // החזרה לזרמים רגילים
            m_istr.rdbuf(prevInput);
            m_ostr.rdbuf(prevOutput);

            m_ostr << "Unknown command at line " << lineNumber << ": " << line << "\n";

           
            std::string choice;
            std::cout << "Continue reading the file? (y/n): ";
            std::cin >> choice;
            if (choice != "y" && choice != "Y") {
                std::cout << "Stopped reading from file.\n";
                return;
            }
            continue;
        }

        try {
            runAction(it->action);
        }
        catch (const std::exception& e) {
       
            m_istr.rdbuf(prevInput);
            m_ostr.rdbuf(prevOutput);

            m_ostr << "Error at line " << lineNumber << ": " << e.what();
            m_ostr << "Line content: " << line << '\n';

	    std::string choice;
            std::cout << "Continue reading the file? (y/n): ";
            std::cin >> choice;
            if (choice != "y" && choice != "Y") {
                std::cout << "Stopped reading from file.\n";
                return;
            }
            continue;
        }

    
        m_istr.rdbuf(prevInput);
        m_ostr.rdbuf(prevOutput);

        m_ostr << oss.str();
    }

    m_istr.rdbuf(prevInput);
    m_ostr.rdbuf(prevOutput);
}



void FunctionCalculator::runAction(Action action)
{
    switch (action)
    {
       
        case Action::Invalid:                                  break;

        case Action::Eval:         eval();                     break;
        case Action::Add:          binaryFunc<Add>();          break;
        case Action::Sub:          binaryFunc<Sub>();          break;
        case Action::Comp:         binaryFunc<Comp>();         break;
        case Action::Del:          del();                      break;
        case Action::Read:         readFromFile();             break;
        case Action::Resize:       resize();                   break;

        case Action::Help:         help();                     break;
        case Action::Exit:         exit();                     break;
        //case Action::Iden:       unaryFunc<Identity>();      break;
        //case Action::Tran:       unaryFunc<Transpose>();     break;
        case Action::Scal:         unaryWithIntFunc<Scalar>(); break;

        default:
            m_ostr << "Unknown enum entry used!\n";            break;
    }
}


FunctionCalculator::ActionMap FunctionCalculator::createActions() const
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num n - compute the result of function #num on an n×n matrix "
			"(that will be prompted)",
            Action::Eval
        },
        {
            "scal",
            "(ar) val - creates an operation that multiplies the "
			"given matrix by scalar val",
            Action::Scal
        },
        {
            "add",
            " num1 num2 - creates an operation that is the addition of the result of operation #num1 "
			"and the result of operation #num2",
            Action::Add
        },
         {
            "sub",
            " num1 num2 - creates an operation that is the subtraction of the result of operation #num1 "
			"and the result of operation #num2",
            Action::Sub
        },
        {
            "comp",
            "(osite) num1 num2 - creates an operation that is the composition of operation #num1 "
			"and operation #num2",
            Action::Comp
        },
        {
            "del",
            "(ete) num - delete operation #num from the operation list",
            Action::Del
        },
        {
            "read",
            " <file_path> - read and execute commands from file",
            Action::Read
        },
        {
           "resize",
           " <new_max> - change max number of allowed functions",
           Action::Resize
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        },
        

    };
}


FunctionCalculator::OperationList FunctionCalculator::createOperations() const
{
    return OperationList
    {
        std::make_shared<Identity>(),
        std::make_shared<Transpose>(),
    };
}
