#include <iostream>
#include <string.h>

using namespace std;

#define ERROR -1
#define CORRECT 1
#define MAXSTACKSIZE 100

typedef struct SqStack {
    char base[MAXSTACKSIZE];
    char* top;
}SqStack;
SqStack MBStack;


//初始化栈
int InitStack(SqStack& s) {
    if (s.base == NULL)
        return ERROR;
    s.top = s.base;
    return CORRECT;
}



//将数据进栈
int Push(SqStack& s, char e) {
    if ((s.top - s.base) >= MAXSTACKSIZE)
        return ERROR;
    s.top++;
    *s.top = e;
    return CORRECT;
}


//将数据出栈
int Pop(SqStack& s, char& e) {
    if (s.top <= s.base)
        return ERROR;
    e = *s.top;
    s.top--;
    return CORRECT;
}


//判断栈是否为空
int StackEmpty(SqStack& s) {
    if (s.top <=s.base)
        return ERROR;
    return CORRECT;

}


//括号匹配
int MatchBracket(SqStack& s, char* BracketString) {
    int i;
    char C, sC;
    InitStack(s);
    for (i = 0; i < strlen(BracketString); i++) {  //先遍历整个传入的数据
        C = BracketString[i];
        if ((C == '(') || (C == '[') || (C == '{')) {
            //先从左到右遍历，找出算数当中出现的左括号并且将左括号其压入栈当中
            Push(s, C);
        }
        else {
            if ((C == ')') || (C == ']') || (C == '}'))
            {
                //在这里表示没有任何左括号存在，即左括号少于右括号，返回-2
                if (StackEmpty(s) == ERROR) return -2;
                //这个时候的意思就是栈当中存在左括号，这时候已经遍历到一个"]","}",")"等三个右
                //括号，然后我们想一下，当我们的算数的括号的匹配的时候，
                //那么当抽到一个右括号的时候，肯定是有一个位于栈顶的左括号存在的，然后这时候将
                //栈顶的元素取出来，进行匹配，如果两个都为一个搭配的左右括号，那么这个时候就是
                //相互匹配的

                Pop(s, sC);  //将栈顶的左括号取出

                //下面这三个判断指的是遍历的算数符号和从栈顶取出的括号进行比对，如果不成功，那
                //么返回-1，表示左右括号匹配次序不对
                if ((C == ')') && (sC != '(')) return -1;
                if ((C == ']') && (sC != '[')) return -1;
                if ((C == '}') && (sC != '{')) return -1;
            }
        }
    }
    //这个表示栈当中的元素不空，那么就是存在没有匹配完的左括号，也就是左括号比右括号多
    if (StackEmpty(s) != ERROR) return -3;
    //这个时候表示左右括号匹配完全正确，然后栈的元素全部匹配取出完了
    if (StackEmpty(s) == ERROR) return 0;
}


void printResult(SqStack& s, char* BracketString) {
    int result = MatchBracket(s, BracketString);
    if (result == 0) {
        cout << "匹配完全成功" << endl;
    }
    else if (result == -1) {
        cout << "左右括号匹配次序不正确" << endl;
    }
    else if (result == -2) {
        cout << "右括号多于左括号" << endl;
    }
    else {
        cout << "左括号多于右括号" << endl;
    }
}


int main() {
    int i, SampleNum;
    char BracketString[MAXSTACKSIZE];
    cin >> SampleNum;
    for (i = 0; i < SampleNum; i++) {
        cin >> BracketString;
        printResult(MBStack, BracketString);
    }
    return 0;
}
