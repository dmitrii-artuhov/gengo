#pragma once

class Position {
private:

public:
	int index, line, col;
	std::string file_name, file_text;

	Position(int index, int line, int col, std::string &file_name, std::string &file_text);
	Position();
	
	void Advance(char current_char = '\0');

	Position Copy();
};