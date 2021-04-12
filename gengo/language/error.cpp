#include "../gengo.h"
#include "../headers/error.h"


/*--- Error -------------------------*/
Error::Error() :
error_name(""), details("") {};

Error::Error(const std::string& error_name, std::string& details) {
	this->error_name = error_name;
	this->details = details;
};

//Error::~Error() {
//	delete this;
//}

std::string Error::As_string() {
	std::string res = this->error_name + ":" + this->details;
	return res;
};

// setters
void Error::setErrorName(std::string& error_name) {
	this->error_name = error_name;
}

void Error::setErrorDetails(std::string& details) {
	this->details = details;
}

/*--- IllegalCharError -------------------------*/
IllegalCharError::IllegalCharError() :
	Error()
{};

IllegalCharError::IllegalCharError(std::string& details) :
	Error() {
	this->setErrorName(this->name);
	this->setErrorDetails(details);
};

//IllegalCharError::~IllegalCharError() {
//	delete this;
//}