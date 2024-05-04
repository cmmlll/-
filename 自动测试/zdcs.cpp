
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

// 函数原型
bool isOperator(char c);
double applyOperation(double a, double b, char op);
double evaluateExpression(const string& expr);
double evaluatePostfix(const string& postfix);

int main() {
    ifstream fin("expressions.txt"); // 假设表达式存储在名为expressions.txt的文件中
    ofstream fout("results.txt");

    string expression;
    while (getline(fin, expression)) {
        double result = evaluateExpression(expression);
        fout << expression << " = " << result << endl;
    }

    fin.close();
    fout.close();

    cout << "计算完成，请查看results.txt文件获取结果。" << endl;

    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double applyOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0.0; // 错误的运算符
    }
}

double evaluateExpression(const string& expr) {
    stack<double> operands;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (isOperator(token[0])) {
            double b = operands.top();
            operands.pop();
            double a = operands.top();
            operands.pop();
            double result = applyOperation(a, b, token[0]);
            operands.push(result);
        }
        else {
            double operand;
            stringstream(token) >> operand;
            operands.push(operand);
        }
    }

    return operands.top();
}
