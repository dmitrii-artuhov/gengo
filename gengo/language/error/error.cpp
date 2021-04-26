#include "../../gengo.h"
#include "../error/error.h"
#include "../nodes/ast.h"


/*--- Error -------------------------*/

Error::Error(const std::string& error_name, std::string& details, Position &pos_start, Position &pos_end) :
error_name(error_name), details(details), pos_start(pos_start), pos_end(pos_end) {}

Error::Error(const std::string& error_name, std::string& details) :
	error_name(error_name), details(details) {}



std::string Error::As_string() {
	std::string res = "";
	
	{
		res += this->error_name + ":" + this->details;
		res += "\n";

		res += "File "
			+ this->pos_start.file_name + ", line "
			+ std::to_string((this->pos_start.line + 1))
			+ ":"
			+ std::to_string((this->pos_start.index + 1));
		res += "\n";
	}

	return res;
};
