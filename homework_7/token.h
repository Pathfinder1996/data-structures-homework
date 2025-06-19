#ifndef TOKEN_H_
#define TOKEN_H_

//  Token category
enum TokType { Operand, Operator };

//  Lightweight token
struct Token {
    TokType type; // Operand or Operator
    int value; // valid when type == Operand
    char op; // valid when type == Operator ('#' = sentinel)

    Token() : type(Operator), value(0), op('#') {}
    explicit Token(int v) : type(Operand), value(v), op(0) {} // ctor for operand
    explicit Token(char c) : type(Operator), value(0), op(c) {} // ctor for operator
};

struct TokenList {
    static constexpr int CAP = 256;
    Token data[CAP];
    int sz{ 0 };
    void push_back(const Token& t) { if (sz < CAP) data[sz++] = t; }
    Token& operator[](int i) { return data[i]; }
    const Token& operator[](int i) const { return data[i]; }
};

#endif
