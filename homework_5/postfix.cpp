#include "postfix.h"
#include "stack.h"

extern bool last_token_valid;

// in-stack precedence (isp)
int isp(char op) {
    switch (op) {
    case '(': return 8;  // lowest pop-priority
    case '^': return 1;  // left-assoc if isp==icp
    case '*': case '/': case '%': return 2;
    case '+': case '-':        return 3;
    case '#':      return 8;  // bottom marker
    default:       return 8;
    }
}
int isp(Token t) { return isp(opToString(t.o)[0]); }

// incoming precedence (icp)
int icp(char op) {
    switch (op) {
    case '(':      return 0;  // always push
    case '^':      return 1;  // equal to isp for left-assoc
    case '*': case '/': case '%': return 2;
    case '+': case '-':        return 3;
    case '#':      return 8;
    default:       return 8;
    }
}
int icp(Token t) { return icp(opToString(t.o)[0]); }

// check operand/operator
int isOperand(char c) { return isdigit(c) || c == '.'; }
int isOperand(Token t) { return t.tag == Tag::OPERAND; }
int isOperator(Token t) { return t.tag == Tag::OPERATOR; }
int isOperator(char c) {
    switch (c) {
    case '+': case '-': case '*': case '/':
    case '%': case '^': case '(': case ')': case '#':
        return 1;
    default:
        return 0;
    }
}

// convert infix string to postfix queue
Queue<Token> postfix(std::string expr) {
    Queue<Token> in = tokenize(expr);   // tokenizer prints TOKENIZE
    Queue<Token> out;
    if (!last_token_valid) return out;    // skip on invalid token

    std::cout << std::setw(10) << std::left << "POSTFIX:";
    Stack<Token> st;
    st.Push(Token('#'));
    Token x;

    while (!in.IsEmpty()) {
        in.Delete(x);
        if (isOperand(x)) {
            out.Push(x);
            std::cout << x.d << ' ';
        }
        else if (x.o == Operator::RPAREN) {
            Token y;
            while (st.Top(y) && y.o != Operator::LPAREN) {
                st.Delete(y);
                out.Push(y);
                std::cout << opToString(y.o) << ' ';
            }
            st.Delete(y); // pop '('
        }
        else if (x.o == Operator::BOTTOM) {
            Token y;
            while (st.Top(y) && y.o != Operator::BOTTOM) {
                st.Delete(y);
                out.Push(y);
                std::cout << opToString(y.o) << ' ';
            }
            out.Push(x);
            std::cout << "# ";
        }
        else {
            Token y;
            while (st.Top(y) && isp(y) <= icp(x)) {
                st.Delete(y);
                out.Push(y);
                std::cout << opToString(y.o) << ' ';
            }
            st.Push(x);
        }
    }
    std::cout << '\n';
    return out;
}
