#include "../../gengo.h"
#include "../error/error.h"
#include "../nodes/ast.h"


/*--- Error -------------------------*/

Error::Error(const std::string& error_name, std::string& details, Position &pos_start, Position &pos_end) :
error_name(error_name), details(details), pos_start(pos_start), pos_end(pos_end) {}

Error::Error(const std::string& error_name, std::string& details) :
	error_name(error_name), details(details) {}


Error::Error(const std::string& error_name, std::string& details, Context* ctx) :
	error_name(error_name), details(details), context(ctx) {}



std::string Error::As_string() {
	std::string res = "";

	if (this->error_name == ERROR_RUNTIME) {
		res += this->Traceback();
		res += this->error_name + ":" + this->details;
		res += "\n";
	}
	else {
		res += this->error_name + ":" + this->details;
		res += "\n";

		res += "At "
			+ this->pos_start.file_name + ", line "
			+ std::to_string((this->pos_start.line + 1))
			+ ":"
			+ std::to_string((this->pos_start.index + 1));
		res += "\n";
	}
	
	return res;
};


std::string Error::Traceback() {
	std::string res = "";

	Context* curr_ctx = this->context;

	while (curr_ctx) {
		res = std::string("At " + curr_ctx->name + "\n") + res;
		curr_ctx = curr_ctx->parent;
	}

	return std::string("Calls trace: \n") + res;
}