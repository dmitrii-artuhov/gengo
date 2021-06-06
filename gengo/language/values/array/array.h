#pragma once

#include "../../tokens/token.h"
#include "../../interpreter/runtime_result.h"
#include "../../context/context.h"

class NodeValue;




class Array {
private:
public:
	std::vector <NodeValue*> array_body;

	Array(std::vector <NodeValue*> &vec);
	bool InBounds(long long index, std::vector <NodeValue*>& arr);
	
	RunTimeResult* ReassingElementByIndex(std::vector <long long>& int_indexes, NodeValue* elem, Context* context);
	RunTimeResult* GetElementByIndex(std::vector <long long> &int_indexes, Context* context);
	
	
	std::string Represent();
};

