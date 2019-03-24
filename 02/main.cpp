#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum Token_value : char {
	NUMBER, END, PLUS='+', MINUS='-', MUL='*', DIV='/'
};

enum Number_value : char {
	NUM0='0', NUM1='1', NUM2='2',
	NUM3='3', NUM4='4', NUM5='5',
	NUM6='6', NUM7='7', NUM8='8',
	NUM9='9'
};

Token_value curr_tok = PRINT;        // Хранит последний возврат функции get_token().
double number_value;                 // Хранит целый литерал или литерал с плавающей запятой.

double expr(std::istream*, bool);    // Обязательное объявление.

/****************************************************************************/

double error() {
	std::cout << "error" << endl;
	exit(0);
}

Token_value get_token(std::istream* input)
{
	char ch;
	do {    // Пропустить все пробельные символы кроме '\n'.
		if (!input->get(ch))
			return curr_tok = END; // Завершить работу калькулятора.
	} while (ch != '\0' && isspace(ch));
	switch (ch) {
		case 0: // При вводе символа конца файла, завершить работу калькулятора.
			return curr_tok = END;
		case MUL:
		case DIV:
		case PLUS:
		case MINUS:
		  return curr_tok = Token_value(ch); // Приведение к целому и возврат.
		case NUM0: case NUM1: case NUM2: case NUM3: case NUM4:
		case NUM5: case NUM6: case NUM7: case NUM8: case NUM9:
			input->putback(ch); // Положить назад в поток...
			*input >> number_value; // И считать всю лексему.
			return curr_tok = NUMBER;
		default:
			error();
	}
}

/* Каждая функция синтаксического анализа принимает аргумент типа bool
    * указывающий, должна ли функция вызывать get_token() для получения
	 * очередной лексемы. */

// prim() - обрабатывает первичные выражения.
double prim(std::istream* input, bool get)
{
	if (get)
		get_token(input);
	switch (curr_tok) {
		case NUMBER:
			double v = number_value;
			get_token(input);
			return v;
		case NAME:
			double& v = table[string_value];
			if (get_token(input) == ASSIGN)
				v = expr(input, true);
			return v;
		case MINUS:
			return -prim(input, true);
		default:
	  		error();
	}
}

// term() - умножение и деление.
double term(std::istream* input, bool get) {
	  double left = prim(input, get);

	    for ( ; ; ) {
			    switch (curr_tok) {
					      case MUL:
							          left *= prim(input, true);
									          break;
											        case DIV:
											          if (double d = prim(input, true)) {
														              left /= d;
																	              break;
																				          }
													          return error("Divide by 0");
															        default:
															            return left;
																		    }
				  }
}

// expr() - сложение и вычитание.
double expr(std::istream* input, bool get) {
	  double left = term(input, get);

	    for ( ; ; ) {
			    switch (curr_tok) {
					      case PLUS:
							          left += term(input, true);
									          break;
											        case MINUS:
											          left -= term(input, true);
													          break;
															        default:
															          return left;
																	      }
				  }
}

int main(int argc, char* argv[])
{
	std::istream* input = nullptr; // Указатель на поток.
	switch (argc) {
		case 1:
			input = &std::cin;
			break;
		case 2:
			input = new std::istringstream(argv[1]);
			break;
		default:
			error("Too many arguments");
			return 1;											  }
	while (*input) {
		get_token(input);
		if (curr_tok == END)
			break;
		// Снимает ответственность expr() за обработку пустых выражений.
		if (curr_tok == PRINT)
			continue;
		// expr() -> term() -> prim() -> expr() ...
		std::cout << expr(input, false) << std::endl;
	}
	if (input != &std::cin)
		delete input;
	return 0;
}
