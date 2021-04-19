#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string_view>
//#include <sstream>
//#include <typeinfo>
//#include <optional>

class Parser
{
private:
    std::string input;
    std::vector<const char> vecOfOps = { '+', '-', '*', '/', ':', '^', '(', ')' };
    std::unordered_map<const char, std::function<double(double, double)>> operatorFunction= {
        {'+', [](double a, double b) {return a + b;}},
        {'-', [](double a, double b) {return a - b;}},
        {'*', [](double a, double b) {return a * b;}},
        {'/', [](double a, double b) {return a / b;}},
        {':', [](double a, double b) {return a / b; }},
        {'^', [](double a, double b) {return pow(a, b);}}
    };
    void replaceInPlace(std::string/*&*/ subject, std::string_view search,
        std::string_view replace);
    std::string removeSpaces(std::string str);
    void computeSubString(std::string/*&*/ piece, char arithmOper);
public:
    Parser(std::string userInput)
        :input(userInput)
    {}
    virtual ~Parser() = default;
    enum Token
    {
        Plus,
        Minus,
        Multiply,
        Divide,
        Divide_overload,
        Exponent,
        LeftBrace,
        RightBrace
    };
    void parseString();
    double parseWithoutBraces();
};