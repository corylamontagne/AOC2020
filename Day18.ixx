export module Day18;

import std.core;
import AOCUtil;

namespace Day18
{
    export typedef std::map<std::string, std::function<long long(long long, long long)>> OperatorMap;
    export typedef std::map<std::string, int> PrecedenceMap;

    void AddSpacing(std::string& exp, std::vector<std::tuple< std::string, bool> > vals)
    {
        for (auto [token, rightSide] : vals)
        {
            size_t pos = -1;
            int move = (rightSide) ? 1 : 2;
            while ((pos = exp.find(token, pos + move)) != std::string::npos && pos < exp.length())
            {
                exp.replace(pos, 1, (rightSide) ? (token + " ") : (" " + token));
            }
        }
    }

    bool isLeftParenthesis(const std::string& c) { return c == "("; }
    bool isRightParenthesis(const std::string& c) { return c == ")"; }

    long long RPN(std::queue<std::string> exp, const OperatorMap& operations)
    {
        long long result = 0;
        std::stack<long long> digit;

        while (!exp.empty())
        {
            if (AOC::isDigit(exp.front()) )
            { 
                digit.push( std::stoll(exp.front())); 
                exp.pop(); 
            }
            else
            {
                long long a = digit.top();
                digit.pop();
                long long b = digit.top();
                digit.pop();
                long long res = operations.find(exp.front())->second(a, b);
                exp.pop();
                digit.push(res);
            }
        }

        return digit.top();
    }

    export long long Calculate(std::string exp, const OperatorMap& operations, const PrecedenceMap& precMap)
    {
        AddSpacing(exp, { {"(", true}, {")", false} });
        std::vector<std::string> tokens = AOC::split(exp, ' ');

        std::queue<std::string> output;
        std::stack<std::string> operators;
        for (auto i : tokens)
        {
            if (AOC::isDigit(i)) { output.push(i); } //is digit
            else if (precMap.find(i) != precMap.end()) //is operator
            {
                while (!operators.empty() &&
                    !isLeftParenthesis(operators.top()) && 
                    (precMap.find(operators.top())->second >= precMap.find(i)->second))
                {
                    output.push(operators.top());
                    operators.pop();
                }

                operators.push(i);
            }
            else if (isLeftParenthesis(i))
            {
                operators.push(i);
            }
            else if (isRightParenthesis(i))
            {
                while (!isLeftParenthesis(operators.top()))
                {
                    output.push(operators.top());
                    operators.pop();
                }
                if (isLeftParenthesis(operators.top()))
                {
                    operators.pop();
                }
            }
        }
        while (!operators.empty())
        {
            output.push(operators.top());
            operators.pop();
        }

        return RPN(output, operations);
    }
}