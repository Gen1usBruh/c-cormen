#include "Calc.h"

void Parser::replaceInPlace(std::string/*&*/ subject, std::string_view search,
    std::string_view replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}
std::string Parser::removeSpaces(std::string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
void Parser::computeSubString(std::string/*&*/ piece, char arithmOper) {
    while (piece.find(arithmOper) != std::string::npos) {
        int foundOper = piece.find(arithmOper);
        int foundOperPrev = piece.find_last_of("+-/*:^", foundOper - 1);
        int foundOperNext = piece.find_first_of("+-/*:^", foundOper + 1);
        if (foundOperNext == std::string::npos) {
            foundOperNext = foundOper + 2;
        }
        std::string beforeOp = piece.substr(foundOperPrev + 1, foundOper - foundOperPrev - 1);
        std::string afterOp = piece.substr(foundOper + 1, foundOperNext - foundOper - 1);
        std::string parsedSum = std::to_string(operatorFunction[arithmOper](std::stod(beforeOp), std::stod(afterOp)));
        std::string toBeReplaced = beforeOp + arithmOper + afterOp;
        replaceInPlace(piece, toBeReplaced, parsedSum);
    }
}

void Parser::parseString() {
    std::vector<std::pair<char, int>> vecPosOfBraces;
    for (unsigned i = 0; i < input.length(); i++) {
        if (input[i] == vecOfOps[LeftBrace]) {
            std::pair<char, int> tmPairLeft(vecOfOps[LeftBrace], i);
            vecPosOfBraces.push_back(tmPairLeft);
        }
        if (input[i] == vecOfOps[RightBrace]) {
            std::pair<char, int> tmPairRight(vecOfOps[RightBrace], i);
            vecPosOfBraces.push_back(tmPairRight);
        }
    }
    //{0, 1, 5, 9, 13, 16, 20, 24};
    std::vector<std::string> vecOfStringPieces;
    for (unsigned i = 0; i < vecPosOfBraces.size() - 1; i++) {
        if (vecPosOfBraces[i].first == vecOfOps[LeftBrace]
            && vecPosOfBraces[i + 1].first == vecOfOps[RightBrace]
            && vecPosOfBraces[i].second < vecPosOfBraces[i + 1].second)
        {
            std::string subInput = input.substr(vecPosOfBraces[i].second + 1, vecPosOfBraces[i + 1].second - vecPosOfBraces[i].second - 1);
            vecOfStringPieces.push_back(subInput);
        }
    }
}
double Parser::parseWithoutBraces() {

    removeSpaces(input);

    for (auto i = vecOfOps.end() - 3; i >= vecOfOps.begin(); i--) {
        if (input.find(*i) != std::string::npos) {
            computeSubString(input, *i);
        }
    }

    return std::stod(input);
}

int main() {
	std::string input;             //{"2.6 + 5  -  4 + 1.2+7.5"}
	std::getline(std::cin, input); //{"3 + 5 * 4-6.2/2.1+5.7+2^3-10:2"}
	Parser parseObj(input);
	std::cout << parseObj.parseWithoutBraces();

	return 0;
}