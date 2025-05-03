#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>
#include <iostream>



class Operation;


class FunctionCalculator
{
public:
    FunctionCalculator(std::istream& istr, std::ostream& ostr);
    void run();

private:
    void eval();
    void del();
    void readFromFile();
    void resize();
    void help();
    void exit();

    template <typename FuncType>
    void binaryFunc()
    {
        if (m_operations.size() >= m_maxOperations) {
            m_ostr << "Function limit reached. Cannot add more functions.\n";
            return;
        }

        if (auto f0 = readOperationIndex(), f1 = readOperationIndex(); f0 && f1)
        {
            m_operations.push_back(std::make_shared<FuncType>(m_operations[*f0], m_operations[*f1]));
        }
    }

    template <typename FuncType>
    void unaryFunc()
    {
        if (m_operations.size() >= m_maxOperations) {
            m_ostr << "Function limit reached. Cannot add more functions.\n";
            return;
        }

    	m_operations.push_back(std::make_shared<FuncType>());
	}
    template <typename FuncType>
    void unaryWithIntFunc()
    {
        if (m_operations.size() >= m_maxOperations) {
            m_ostr << "Function limit reached. Cannot add more functions.\n";
            return;
        }

        int i = 0;
        m_istr >> i;
        m_operations.push_back(std::make_shared<FuncType>(i));
    }
    void printOperations() const;

    enum class Action
    {
        Invalid,
        Eval,
        Iden,
        Tran,
        Scal,
        Sub,
        Add,
        Mul,
        Comp,
        Del,
        Resize,
        Read,
        Help,
        Exit,
    };

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
    };

    using ActionMap = std::vector<ActionDetails>;
    using OperationList = std::vector<std::shared_ptr<Operation>>;

    const ActionMap m_actions;
    OperationList m_operations;
    bool m_running = true;
    std::istream& m_istr;
    std::ostream& m_ostr;
    int m_maxOperations ;

    std::optional<int> readOperationIndex() const;
    Action readAction() const;

    void runAction(Action action);

    ActionMap createActions() const;
    OperationList createOperations() const ;
};
