#include "../../gengo.h"
#include "./position.h"


Position::Position(int index, int line, int col, std::string &file_name, std::string &file_text) :
	index(index),
	line(line),
	col(col),
	file_name(file_name),
	file_text(file_text)
{};



void Position::Advance(char current_char) {
	this->index += 1;
	this->col += 1;

	if (current_char == '\n') {
		this->line += 1;
		this->col = 0;
	}
};


Position Position::Copy() {
	return Position(index, line, col, file_name, file_text);
}