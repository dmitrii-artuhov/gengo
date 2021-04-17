#include "../gengo.h"
#include "../headers/error.h"


/*--- Error -------------------------*/
Error::Error() :
error_name(""), details("") {};

/*
Error::Error(std::string& error_name, std::string& details, Position* pos_start, Position* pos_end) :
	error_name(error_name),
	details(details),
	pos_start(pos_start),
	pos_end(pos_end)
{};
*/

std::string Error::As_string() {
	std::string res = "";
	
	{
		res += this->error_name + ":" + this->details;
		res += "\n";

		res += "File "
			+ this->pos_start->file_name + ", line "
			+ std::to_string((this->pos_start->line + 1))
			+ ":"
			+ std::to_string((this->pos_start->index + 1));
		res += "\n";
	}

	return res;
};

// setters
void Error::setErrorName(std::string& error_name) {
	this->error_name = error_name;
}

void Error::setErrorDetails(std::string& details) {
	this->details = details;
}

void Error::setErrorPositions(Position* pos_start, Position* pos_end) {
	this->pos_start = pos_start;
	this->pos_end = pos_end;
}

/*--- IllegalCharError -------------------------*/
IllegalCharError::IllegalCharError() :
	Error()
{};

IllegalCharError::IllegalCharError(std::string& details, Position* pos_start, Position* pos_end) :
	Error() {
	this->setErrorName(this->name);
	this->setErrorDetails(details);
	this->setErrorPositions(pos_start, pos_end);
};
