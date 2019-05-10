#include "Token_stream.h"
#include "sc.h"

Token Token_stream::get() {
	char ch;
//	char ch = ip->get();
//	std::cout << "next: " << ch << '\n';
//	if (!ch) return ct = { Kind::end };

	do {
		if (!ip->get(ch)) return ct = { Kind::end };
	} while (ch != '\n' && isspace(ch));

	switch (ch) {		
	case 0:
		return ct = { Kind::end }; //assign and return
	case '\n':
	case ';': //end of expression; print
		return ct = { Kind::print };
	case '*': case '/': case '+': case '-': case '(': case ')': case '=': 
		return ct = { static_cast<Kind>(ch) };
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': 
		ip->putback(ch); // put the first digit (or .) back into the input stream
		*ip >> ct.number_value; // read number into ct 
		ct.kind=Kind::number; 
		return ct; 
	case '!':
		while (ip->get(ch) && isalnum(ch)) {
			ct.string_value += ch;
		}
		ip->putback(ch);
		if (is_cmd()) {
			ct.kind = Kind::cmd;
			return ct;
		}
		error("unknown cmd");
		return ct = { Kind::print };
	default: //name, name=, or error 
		if (isalpha(ch)) { 
			ct.string_value = ch;
			while (ip->get(ch) && isalnum(ch)) {
				ct.string_value += ch;
			}
			ip->putback(ch);
			ct.kind=Kind::name; 
			return ct;
		}
		error("bad token"); 
		return ct = { Kind::print };
	}
}
std::set<std::string> cmds = {
	"ds"
};
bool Token_stream::is_cmd() {
	return cmds.find(ct.string_value) != cmds.end();
}

Token& Token_stream::current() {
	return ct;
}
