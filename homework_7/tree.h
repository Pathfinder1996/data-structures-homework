#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <cctype>
#include <type_traits>
#include "stack.h"
#include "queue.h"
#include "token.h"

using namespace std;

// TreeNode
template <class T> class Tree; // forward

template <class T>
class TreeNode {
    friend class Tree<T>;
private:
    TreeNode<T>* LeftChild{ nullptr };
    T data;
    TreeNode<T>* RightChild{ nullptr };
};

// Tree
template <class T>
class Tree {
public:
    Tree() : root(nullptr) {}
    ~Tree() {}

    // BST interface
    bool IsEmpty() const { return root == nullptr; }
    void Insert(T);
    void Inorder() { Inorder(root);  cout << '\n'; }
    void Preorder() { Preorder(root); cout << '\n'; }
    void Postorder() { Postorder(root); cout << '\n'; }
    void Levelorder();

    // Expression tree
    void Infix(const string& expr); // print TOKENIZE and POSTFIX
    int Evaluate() const;

private:
    // traversal helpers
    void Inorder(TreeNode<T>*);
    void Preorder(TreeNode<T>*);
    void Postorder(TreeNode<T>*);

    // unified printing
    template <typename X>
    static void PrintTok(const X& v) {
        if constexpr (std::is_same_v<X, Token>) {
            if (v.type == Operand)
                cout << v.value << ' ';
            else
                cout << v.op << ' ';
        }
        else {
            cout << v << ' ';
        }
    }

    // expression tree helpers
    static TokenList Tokenize(const string&);
    static TokenList ToPostfix(const string&);
    void BuildByPostfix(const TokenList&);
    int Eval(TreeNode<T>*) const;

private:
    TreeNode<T>* root;
};

// BST Insert
template <class T>
void Tree<T>::Insert(T item)
{
    auto* n = new TreeNode<T>; n->data = item;
    if (!root) { 
        root = n; 
        return; 
    }

    TreeNode<T>* p = root;
    TreeNode<T>* parent = nullptr;
    while (p) {
        parent = p;
        p = (item < p->data) ? p->LeftChild : p->RightChild;
    }
    (item < parent->data ? parent->LeftChild : parent->RightChild) = n;
}

// Traversals
// Inorder
template <class T> void Tree<T>::Inorder(TreeNode<T>* r) {
    if (!r) {
        return;
    }

    Inorder(r->LeftChild); 
    PrintTok(r->data); 
    Inorder(r->RightChild);
}

// Preorder
template <class T> void Tree<T>::Preorder(TreeNode<T>* r) {
    if (!r) {
        return;
    }

    PrintTok(r->data); 
    Preorder(r->LeftChild); 
    Preorder(r->RightChild);
}

// Postorder
template <class T> void Tree<T>::Postorder(TreeNode<T>* r) {
    if (!r) {
        return;
    }

    Postorder(r->LeftChild); 
    Postorder(r->RightChild);
    PrintTok(r->data);
}

// Levelorder
template <class T> void Tree<T>::Levelorder() {
    if (!root) { cout << "(empty)\n"; return; }
    Queue<TreeNode<T>*> q; q.Push(root);
    while (!q.IsEmpty()) {
        TreeNode<T>* p = q.Pop(); PrintTok(p->data);
        if (p->LeftChild)  q.Push(p->LeftChild);
        if (p->RightChild) q.Push(p->RightChild);
    }
    cout << '\n';
}

// Tokenize
template <class T>
TokenList Tree<T>::Tokenize(const string& s)
{
    TokenList L; int num = 0, reading = 0;
    auto flush = [&] { if (reading) { L.push_back(Token(num)); num = 0; reading = 0; } };
    for (char c : s) {
        if (isdigit(c)) { num = num * 10 + (c - '0'); reading = 1; }
        else if (c == ' ') continue;
        else { flush(); L.push_back(Token(c)); }
    }
    flush(); L.push_back(Token('#'));
    return L;
}

// Infix to Postfix
template <class T>
TokenList Tree<T>::ToPostfix(const string& s)
{
    Stack<char> ops;
    TokenList out; int num = 0, reading = 0;
    auto flush = [&] { if (reading) { out.push_back(Token(num)); num = 0; reading = 0; } };
    auto prec = [](char op) { return (op == '+' || op == '-') ? 1 : 2; };

    for (char c : s) {
        if (isdigit(c)) { num = num * 10 + (c - '0'); reading = 1; }
        else if (c == ' ') continue;
        else if (c == '(') { flush(); ops.push(c); }
        else if (c == ')') {
            flush();
            while (!ops.empty() && ops.top() != '(') out.push_back(Token(ops.pop()));
            if (!ops.empty()) ops.pop();
        }
        else {
            flush();
            while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c))
                out.push_back(Token(ops.pop()));
            ops.push(c);
        }
    }
    flush(); while (!ops.empty()) out.push_back(Token(ops.pop()));
    out.push_back(Token('#'));

    return out;
}

//  Postfix
template <class T>
void Tree<T>::BuildByPostfix(const TokenList& post)
{
    Stack<TreeNode<Token>*> st;
    for (int i = 0; i < post.sz; ++i) {
        const Token& tk = post[i];
        if (tk.type == Operand) {
            auto* n = new TreeNode<Token>; n->data = tk; st.push(n);
        }
        else if (tk.op != '#') {
            auto* r = st.pop(), * l = st.pop();
            auto* n = new TreeNode<Token>; n->data = tk; n->LeftChild = l; n->RightChild = r;
            st.push(n);
        }
    }
    root = reinterpret_cast<TreeNode<T>*>(st.pop());
}

// Infix
template <class T>
void Tree<T>::Infix(const string& expr)
{
    if constexpr (is_same_v<T, Token>) {
        TokenList tk = Tokenize(expr);
        TokenList pfx = ToPostfix(expr);

        cout << left << setw(15) << "TOKENIZE:";
        for (int i = 0; i < tk.sz; ++i) {
            PrintTok(tk[i]);
        }
        cout << '\n';

        cout << left << setw(15) << "POSTFIX:";
        for (int i = 0; i < pfx.sz; ++i) {
            PrintTok(pfx[i]);
        }
        cout << "\n";

        BuildByPostfix(pfx);
    }
}

// Evaluate
template <class T> int Tree<T>::Evaluate() const { return Eval(root); }
template <class T>
int Tree<T>::Eval(TreeNode<T>* n) const
{
    if (!n) return 0;
    if constexpr (is_same_v<T, Token>) {
        if (n->data.type == Operand) {
            return n->data.value;
        }
        int L = Eval(n->LeftChild), R = Eval(n->RightChild);

        switch (n->data.op) {
        case '+': return L + R;
        case '-': return L - R;
        case '*': return L * R;
        case '/': return L / R;
        }
    }

    return 0;
}

#endif
