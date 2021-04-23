// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int priority(char ch) {
switch (ch) {
case '(':
return 0;
case ')':
return 1;
case '+':
return 2;
case '-':
return 2;
case '*':
return 3;
case '/':
return 3;
default:
return -1;
}
}
std::string infx2pstfx(std::string inf) {
std::string pstfx;
int i = 0;
char ch = inf[i];
char top = 0;
TStack <char> stackChar;
while (ch) {
int prior;
prior = priority(ch);
if (prior > -1) {
if ((prior == 0 || prior > priority(top) ||
stackChar.isEmpty()) && ch != ')') {
if (stackChar.isEmpty())
top = ch;
stackChar.push(ch);
} else if (ch == ')') {
while (stackChar.get() != '(') {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
}
stackChar.pop();
if (stackChar.isEmpty())
top = 0;
} else {
while (!stackChar.isEmpty() &&
priority(stackChar.get()) >= prior) {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
pstfx.push_back(stackChar.get());//не воруй
pstfx.push_back(' ');//мой код
stackChar.pop();//пиши свой!
}
if (stackChar.isEmpty())
top = ch;
stackChar.push(ch);
}
} else {
pstfx.push_back(ch);
pstfx.push_back(' ');
}
ch = inf[++i];
}
while (!stackChar.isEmpty()) {
pstfx.push_back(stackChar.get());
pstfx.push_back(' ');
stackChar.pop();
}
pstfx.erase(pstfx.end() - 1, pstfx.end());
return pstfx;
}
int calculating(char operate, int number1, int number2) {
switch (operate) {
case '+':
return number1 + number2;
break;
case '-':
return number1 - number2;
break;
case '*':
return number1 * number2;
break;
case '/':
return number1 / number2;
break;
}
}

int eval(std::string pst) {
TStack <int> stackInt;
int i = 0, result = 0;
char ch = pst[i];
while (ch) {
if (ch >= '0' && ch <= '9') {
int insertInt = 0;
int dec = 1;
while (ch != ' ') {
insertInt += (ch - 48) * dec;
dec *= 10;
ch = pst[++i];
}
stackInt.push(insertInt);
} else {
char operate = ch;
i++;
int number2 = stackInt.get();
stackInt.pop();
int number1 = stackInt.get();
stackInt.pop();
int result = calculating(operate, number1, number2);
stackInt.push(result);
}
if (i < pst.size())
ch = pst[++i];
else
ch = 0;
}
result = stackInt.get();
stackInt.pop();
return result;
}
