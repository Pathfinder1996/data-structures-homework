/* Binary Tree Traversal - Preorder, Inorder, Postorder */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string> 
#include "tree.h" // design the tree class by yourself
#include "queue.h"

using namespace std;
void init();
Tree<char> bt;
Tree<Token> bt2;
string infix, input;

int main() {
    init();

    cout << "Part I: Basic Tree Travrsal\n";
    for (char ch : input) bt.Insert(ch);

    cout << left << setw(15) << "\nOriginal Input Chars:" << input << '\n';
    cout << left << setw(15) << "Preorder:";   bt.Preorder();
    cout << left << setw(15) << "Inorder:";    bt.Inorder();
    cout << left << setw(15) << "Postorder:";  bt.Postorder();
    cout << left << setw(15) << "Levelorder:"; bt.Levelorder();

    cout << "\nPartII:BT Infix expression :\n";
    bt2.Infix(infix);

    cout << left << setw(15) << "\nInorder: ";    bt2.Inorder();
    cout << left << setw(15) << "Preorder: ";     bt2.Preorder();
    cout << left << setw(15) << "Postorder: ";    bt2.Postorder();
    cout << left << setw(15) << "Levelorder: ";   bt2.Levelorder();

    cout << "\nThe infix expression " << infix
        << "is evaluated to " << bt2.Evaluate() << endl;

    return 0;
}

void init() {  // read the infix from the file infix.txt
    ifstream inFile("input.txt", ios::in); // input file
    if (!inFile) { cerr << "Cannot open input file" << endl; exit(1); }
    inFile >> debug;	inFile.clear();  inFile.ignore(100, '\n');
    inFile >> input;    inFile.clear();  inFile.ignore(100, '\n');
    inFile >> infix;	inFile.clear();  inFile.ignore(100, '\n');
};
