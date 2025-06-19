// @file Token.cpp
#include <sstream>
#include <stdexcept>
#include "postfix.h"
#include "token.h"

using namespace std;

string opToString(Operator o) {
	string result="#";
	switch (o) {
		case Operator::ADD:		result = "+"; break;
		case Operator::SUBTRACT:	result = "-"; break;
		case Operator::MULTIPLY:	result = "*"; break;
		case Operator::DIVIDE:	result = "/"; break;
		case Operator::EXP:		result = "^"; break;
		case Operator::MODULO:   result = "%"; break;
		case Operator::LPAREN:	result = "("; break;
		case Operator::RPAREN:	result = ")"; break;
		default: break;
	}
	return result;
}

ostream& operator<<(std::ostream& os, const Token& t) {
	if (t.tag == Tag::OPERAND) {
		os << t.d << " ";
	}
	else {
		os << opToString(t.o) << " ";
	}
	return os;
}

bool last_token_valid = true;

Queue<Token> tokenize(string s) {
    cout << setw(10) << left << "TOKENIZE:";
    Queue<Token> q;
    last_token_valid = true; 

    for (size_t i = 0; i < s.length(); ++i) {
        if (isspace(s[i])) continue;

        if (isdigit(s[i]) || (s[i] == '.' && i + 1 < s.size() && isdigit(s[i + 1]))) {
            string num;
            while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) num += s[i++];
            --i;
            Token t; t.tag = Tag::OPERAND; t.d = stod(num);
            q.Push(t); cout << t.d << " ";
        }
        else if (isOperator(s[i])) {
            Token t(s[i]);
            q.Push(t); cout << opToString(t.o) << " ";
        }
        else {
            cout << "[Invalid token '" << s[i] << "'] ";
            last_token_valid = false;
        }
    }

    if (last_token_valid) {
        Token end('#');
        q.Push(end); cout << "# ";
    }

    cout << endl;
    return q;
}