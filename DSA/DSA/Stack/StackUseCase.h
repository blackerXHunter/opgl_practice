#pragma once
#include "Stack.h"
#include "../Convert/Int_Str.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

template <typename T>
void PrintVector(dsa::Vector<T> &arr) {
	arr.travese([](T &v) {std::cout << v << " "; });
}

dsa::Stack<char> ScaleConvert(int val, int inputScale = 10) {
	static char digis[] = { '0', '1','2','3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9' ,'A' ,'B' ,'C' ,'D' ,'E' ,'F' };
	dsa::Stack<char> result;
	while (val) {
		result.Push(digis[val % inputScale]);
		val /= inputScale;
	}
	return result;
}


///表达式计算

bool isDigit(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	else {
		return false;
	}
}

int compute(int n1, char op, int n2) {
	switch (op) {
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '/':
		return n1 / n2;
	case '*':
		return n1 * n2;
	default:
		break;
	}
	return 0;
}



set<char> plus_minus = { '-', '+' };
set<char> mul_divide = { '/', '*' };
int compare_youxianji(char op1, char op2) {
	if (plus_minus.find(op1) != plus_minus.end()) {
		if (plus_minus.find(op2) != plus_minus.end()) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		if (plus_minus.find(op2) != plus_minus.end()) {
			return 1;
		}
		else {
			return 0;
		}
	}
}



dsa::Vector<string> expr_to_nibolan(const std::string &s) {
	int num = 0;
	dsa::Stack<std::string> nibolanStk, OpTmpStk;
	bool prevIsDigit = false;
	for (auto c : s) {
		if (c == ' ') {
			continue;
		}
		if (isDigit(c)) {
			num = num * 10 + (c - '0');
			prevIsDigit = true;
			if (s[s.size()-1] == c) {
				nibolanStk.Push(int_to_string(num));
			}
			continue;
		}
		else if (prevIsDigit) {
			nibolanStk.Push(int_to_string(num));
			prevIsDigit = false;
			num = 0;
		}

		if (c == '(') {
			OpTmpStk.Push(string() + c);
		}
		else if (c == ')') {
			while (OpTmpStk.top() != "(") {
				nibolanStk.Push(OpTmpStk.Pop());
			}
			OpTmpStk.Pop();
		}
		else {
			if (OpTmpStk.size() == 0) {
				OpTmpStk.Push(string() + c);
			}
			else {
				int compare_result = compare_youxianji(c, OpTmpStk.top()[0]);
				if (compare_result == 1) {
					OpTmpStk.Push(string() + c);
				}
				else {
					while (OpTmpStk.size() > 0 && 0 >= compare_youxianji(c, OpTmpStk.top()[0])) {
						nibolanStk.Push(OpTmpStk.Pop());
					}
					OpTmpStk.Push(string() + c);
				}
			}
		}
	}
	while (OpTmpStk.size() != 0) {
		nibolanStk.Push(OpTmpStk.Pop());
	}
	return nibolanStk;
}

int eval_nibolan(dsa::Vector<string> &expression) {
	dsa::Stack<int> stk;
	for (size_t i = 0; i < expression.size(); ++i) {
		if (isDigit(expression[i][0])) {
			stk.Push(string_to_int(expression[i]));
		}
		else {
			int n2 = stk.Pop(), n1 = stk.Pop();
			stk.Push(compute(n1, expression[i][0], n2));
		}
	}
	return stk.top();
}

int eval(const std::string &s) {
	if (s.empty()) {
		return 0;
	}
	return eval_nibolan(expr_to_nibolan(s));
}