#include "../../../gengo.h"
#include "./array.h"
#include "../types.h"
#include "../node/node.h"
#include "../int/int.h"
#include "../string/string.h"
#include "../../tokens/token.h"
#include "../../interpreter/runtime_result.h"
#include "../../context/context.h"




class NodeValue;

Array::Array(std::vector <NodeValue*>& vec): array_body(vec) {}

bool Array::InBounds(long long index, std::vector <NodeValue*> &arr) {
	if (index >= 0 && index < arr.size()) {
		return true;
	}
	return false;
}

std::string Array::Represent() {
	std::string res = "[";

	int i = 0;
	for (NodeValue* val : this->array_body) {
		res += val->Represent();
		if (i != this->array_body.size() - 1)
			res += ", ";
		
		i++;
	}
	res += "]";


	return res;
}




RunTimeResult* Array::GetElementByIndex(std::vector <long long>& int_indexes, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	std::vector <NodeValue*> &curr_layer = this->array_body;

	for (int i = 0; i < int_indexes.size(); i++) {
		long long index = int_indexes[i];

		if (i == int_indexes.size() - 1) {
			if (this->InBounds(index, curr_layer))
				return res->Success(curr_layer[index]);
			else
				return res->Failure(new Error(
					ERROR_RUNTIME,
					std::string("Index out of bounds"),
					context
				));
		}
		else {
			if (this->InBounds(index, curr_layer)) {
				if (curr_layer[index]->type != ARRAY_VALUE) {
					return res->Failure(new Error(
						ERROR_RUNTIME,
						std::string("Element is not iteratable at dimension " + std::to_string(i)),
						context
					));
				}
				else {
					Array* next_arr = reinterpret_cast<Array*> (curr_layer[index]->value);
					curr_layer = next_arr->array_body;
				}
			}
			else
				return res->Failure(new Error(
					ERROR_RUNTIME,
					std::string("Index out of bounds"),
					context
				));
		}
	}
}




RunTimeResult* Array::ReassingElementByIndex(std::vector <long long>& int_indexes, NodeValue* elem, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	std::vector <NodeValue*> &curr_layer = this->array_body;

	for (int i = 0; i < int_indexes.size(); i++) {
		long long index = int_indexes[i];

		if (i == int_indexes.size() - 1) {
			if (this->InBounds(index, curr_layer)) {
				curr_layer[index] = elem;
				return res->Success(curr_layer[index]);
			}
			else
				return res->Failure(new Error(
					ERROR_RUNTIME,
					std::string("Index out of bounds"),
					context
				));
		}
		else {
			if (this->InBounds(index, curr_layer)) {
				if (curr_layer[index]->type != ARRAY_VALUE) {
					return res->Failure(new Error(
						ERROR_RUNTIME,
						std::string("Element is not iteratable at dimension " + std::to_string(i)),
						context
					));
				}
				else {
					Array* next_arr = reinterpret_cast<Array*> (curr_layer[index]->value);
					curr_layer = next_arr->array_body;
				}
			}
			else
				return res->Failure(new Error(
					ERROR_RUNTIME,
					std::string("Index out of bounds"),
					context
				));
		}
	}
}

