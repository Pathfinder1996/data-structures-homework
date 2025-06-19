/*
Data Structures Homework 5
M11212913 Sheng-Yen Dai, 2025/05/03
*/

#include <cctype>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include "stack.h"
#include "postfix.h"
#include "queue.h"

#define debug 0
extern bool  last_token_valid;      // from token.cpp
double Eval(Queue<Token>&);
void   logo();

int main() {
    std::string infix;
    char cont;
    do {
        if (debug) logo();
        std::cout << std::left << std::setw(10) << "\nINFIX:    ";
        getline(std::cin >> std::ws, infix);
        if (!debug) std::cout << infix << '\n';

		// tokenize infix expression 
        Queue<Token> pfix = postfix(infix);
        double result = Eval(pfix);

		// print postfix expression
        std::cout << "Evaluate  " << infix;
		
        if (last_token_valid == false) {
            std::cout << " = -nan(ind)\n";
        }
        else {
            if (std::isnan(result))
                std::cout << " [Invalid Infix Expression]  = -nan(ind)\n";
            else if (std::isinf(result)) {
                std::cout << " = " << std::scientific << DBL_MAX << '\n';
                std::cout.unsetf(std::ios::scientific);
            }
            else
                std::cout << " = " << result << '\n';
        }

        std::cout << "Continue? (Y/N) [JJCHEN@NTUST] ";
        std::cin >> cont;
        std::cout << (char)std::toupper(cont) << '\n';

    } while (cont == 'Y' || cont == 'y');
    return 0;
}

void logo() {
    system("CLS");
    std::cout << "Demo program of a NTUST 2022 Calculator by J.-J. Chen\n";
    std::cout << "Enter the infix expression:\n";
}
