#include "postfix.h"
#include "stack.h"
#include <string>

// Global variable to store error messages
std::string g_errorMsg = "";

double Eval(Queue<Token>& postfix)
// Evaluate the postfix expression e. It is assumed that the last token (a token
// is either an operator, operand, or '#') in e is '#'. The function uses a stack
{
    // Clear any previous error message
    g_errorMsg = "";

    Stack<double> stack;  // Stack to hold operands during evaluation
    Token token;

    // Process each token in the postfix expression
    while (!postfix.IsEmpty()) {
        postfix.Delete(token);

        if (token.o == Operator::BOTTOM) {
            // End of expression reached
            break;
        }

        if (isOperand(token)) {
            // If operand, push onto stack
            stack.Push(token.d);
        }
        else {
            // Operator: pop operands, perform operation, push result
            double operand2, operand1, result;

            // For binary operators, need two operands
            if (stack.IsEmpty()) {
                g_errorMsg = "[Invalid Infix Expression]";
                return NAN;  // Not a number
            }
            stack.Delete(operand2);

            if (stack.IsEmpty()) {
                g_errorMsg = "[Invalid Infix Expression]";
                return NAN;
            }
            stack.Delete(operand1);

            // Perform the operation
            switch (token.o) {
            case Operator::ADD:
                result = operand1 + operand2;
                break;
            case Operator::SUBTRACT:
                result = operand1 - operand2;
                break;
            case Operator::MULTIPLY:
                result = operand1 * operand2;
                break;
            case Operator::DIVIDE:
                if (operand2 == 0) {
                    g_errorMsg = "[Division by Zero]";
                    return NAN;
                }
                result = operand1 / operand2;
                break;
            case Operator::MODULO:
                if (operand2 == 0) {
                    g_errorMsg = "[Modulo by Zero]";
                    return NAN;
                }
                result = fmod(operand1, operand2);
                break;
            case Operator::EXP:
                result = pow(operand1, operand2);
                break;
            default:
                g_errorMsg = "[Unknown Operator]";
                return NAN;
            }

            // Push result back onto stack
            stack.Push(result);
        }
    }

    // Final result should be the only item on the stack
    double finalResult;
    if (stack.IsEmpty()) {
        g_errorMsg = "[Empty Result]";
        return NAN;
    }

    stack.Top(finalResult);
    stack.Delete(finalResult);

    // Check if stack is now empty (should be for valid expression)
    if (!stack.IsEmpty()) {
        g_errorMsg = "[Extra operands in expression]";
        return NAN;
    }

    return finalResult;
}