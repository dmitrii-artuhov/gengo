#pragma once



class Error {
private:
	std::string
		error_name,
		details;
public:
	Error();
	Error(const std::string &error_name, std::string &details);
	//~Error();

	// setters
	void setErrorName(std::string& error_name);
	void setErrorDetails(std::string &details);
	
	std::string As_string();
};



class IllegalCharError : public Error {
public:
	std::string name = "Illegal Character";
	
	IllegalCharError();
	IllegalCharError(std::string &details);
	//~IllegalCharError();
};