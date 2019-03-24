#include <string>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
stringstream ss;

void error()
{
    cout << "error" << endl;
    exit(0);
}

enum Token_value {
	NAME,		NUMBER,		END,
	PLUS='+',	MINUS='-',	MUL='*',	DIV='/'
};

Token_value curr_tok;
double number_value;
string string_value;

Token_value get_token()
{
	char ch;
	do {	// skip whitespace
		if(!ss.get(ch)) return curr_tok = END;
	} while (isspace(ch));
	switch (ch) {
	case '*':
	case '/':
	case '+':
	case '-':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		ss.putback(ch);
		ss >> number_value;
		return curr_tok = NUMBER;
	default:			// error
		error();
		return curr_tok = END;
	}
}

double expr(bool);	// cannot do without

double prim(bool get)		// handle primaries
{
	if (get) get_token();
	switch (curr_tok) {
		case NUMBER:		// floating-point constant
		{
			double v = number_value;
			get_token();
			return v;
		}
		case MINUS:		// unary minus
			return -prim(true);
		default:
			error();
			return 1;
	}
}

double term(bool get)		// multiply and divide
{
	double left = prim(get);
	for (;;)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			error();
		default:
			return left;
		}
}

double expr(bool get)		// add and subtract
{
	double left = term(get);
	for (;;)
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		error();
	string str = argv[1];
	ss.str(str);
	while (ss) {
		get_token();
		if (curr_tok == END) break;
		cout << expr(false) << endl;
	}
	return 0;	
}
