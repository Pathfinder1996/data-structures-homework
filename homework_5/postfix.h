#ifndef POSTFIX_H
#define POSTFIX_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <cmath>
#include "queue.h"
#include "token.h"
using namespace std;
   
Queue<Token> postfix(string e);
int isOperand(char input);
int isOperator(char input);
int isOperand(Token x);
int isOperator(Token x);
int isp(char input);
int isp(Token input);
int icp(char input);
int icp(Token input);

#endif

