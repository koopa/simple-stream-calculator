#include "sc.h"

//symbol_map table;  

//Token_stream ts{ std::cin };

Token_stream ts = { std::cin };
using symbol_map = std::map<std::string, double>;
static symbol_map table = {};
int no_of_errors = 0;

double error(const std::string& s)
{
	no_of_errors++;
	std::cerr << "error: " << s << std::endl;
	return 1;
}

std::ostream &operator<<(std::ostream &os, symbol_map &map) {
	for (const auto &[k, v] : map){
		os << k << ": " << v << std::endl;
	}
	return os;
}

double prim(bool get) //handle primaries
{
	if (get) ts.get(); //read next token
	switch (ts.current().kind) {
	case Kind::cmd: 
	{
		if (ts.current().string_value == std::string{ "ds" }) {
			std::cout << table << std::endl;
		}
		std::cout << std::endl;
		return 0;
	}
	case Kind::number: //floating - point constant
	{	double v = ts.current().number_value;
		ts.get();
		return v;
	}
	case Kind::name:
	{	double& v = table[ts.current().string_value]; //find the corresponding name
		if (ts.get().kind == Kind::assign)
			v = expr(true); //' = ' seen : assignment
		return v;
	}
	case Kind::minus: //unary minus
		return -prim(true);
	case Kind::lp:
	{	auto e = expr(true);
		std::cerr << "subexpr: " << e << std::endl;
		if (ts.current().kind != Kind::rp)
			return error("')' expected");
		ts.get(); // eat ')' 
		return e;
	}
	default:
		return error("primary expected");
	}
}

double term(bool get) //multiply and divide
{
	double left = prim(get);
	while (true) {
		switch (ts.current().kind) {
		case Kind::mul: left *= prim(true); break;
		case Kind::div: if (auto d = prim(true)) { left /= d; break; }
						return error("divide by 0");
		default:
			return left;
		}
	}
}


double expr(bool get) //add and subtract
{
	double left = term(get);
	while (true) {
		switch (ts.current().kind) {
		case Kind::plus: left += term(true); break;
		case Kind::minus: left -= term(true); break;
		default: return left;
		}
	}
}


void calculate() { 
	while (true) { 
		std::cout << "> ";
		ts.get();
		if (ts.current().kind == Kind::end) break;
		if (ts.current().kind == Kind::print) continue;
		std::cout << expr(false) << '\n'; 
	} 
}

int main() {
	//insert predefined names	
	table["pi"] = 3.1415926535897932385; 
	table["e"] = 2.7182818284590452354;
	calculate();
	return no_of_errors;
}
