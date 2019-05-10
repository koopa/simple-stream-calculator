#pragma once
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include "Token.h"

class Token_stream {
public:
	Token_stream(std::istream& s) : ip{ &s }, owns{ false } { }
	Token_stream(std::istream* p) : ip{ p }, owns{ true } { }
	~Token_stream() { close(); }
	Token get(); //read and return next tken
	Token& current(); //most recently read token
	bool is_cmd();
	void set_input(std::istream& s) { close(); ip = &s; owns = false; } 
	void set_input(std::istream* p) { close(); ip =  p; owns = true; }
private: 
	void close() { if (owns) delete ip; }
	std::istream* ip; //pointer to an input stream
	bool owns; //does the Token_stream own the istream ?
	Token ct{ Kind::end }; // current token
};
