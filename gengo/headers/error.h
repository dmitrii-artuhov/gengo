#pragma once

#include "./position.h"


class Error {
private:
	std::string
		error_name,
		details;

	Position *pos_start, *pos_end;

public:
	Error();
	//Error(std::string &error_name, std::string &details, Position* pos_start, Position* pos_end);


	// setters
	void setErrorName(std::string& error_name);
	void setErrorDetails(std::string &details);
	void setErrorPositions(Position* pos_start, Position* pos_end);
	
	std::string As_string();
};



class IllegalCharError : public Error {
public:
	std::string name = "Illegal Character";
	
	IllegalCharError();
	IllegalCharError(std::string &details, Position* pos_start, Position* pos_end);
};