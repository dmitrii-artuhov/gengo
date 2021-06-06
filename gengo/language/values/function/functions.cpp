#include "../../../gengo.h"
#include "./functions.h"
#include "../types.h"
#include "../node/node.h"
#include "../float/float.h"
#include "../int/int.h"
#include "../array/array.h"
#include "../../tokens/token.h"
#include "../string/string.h"


/*--- Base Function ------------------------------------------*/

BaseFunction::BaseFunction(
    std::string& func_name,
    std::vector <std::pair <std::string, Token*>> args,
    Token* return_type,
    Context* passed_ctx
): func_name(func_name),
   func_args(args),
   return_type(return_type),
   context(passed_ctx) {}


RunTimeResult* BaseFunction::CheckArguments(std::vector <NodeValue*> &passed_args) {
    RunTimeResult* res = new RunTimeResult();
    long long sz = passed_args.size();

    if (sz > this->func_args.size()) {
        return res->Failure({
            new Error(
                ERROR_RUNTIME,
                std::string("Too many arguments passed to '" + this->func_name + "'"),
                this->context
            )
        });
    }
    else if (sz < this->func_args.size()) {
        return res->Failure({
            new Error(
                ERROR_RUNTIME,
                std::string("Too few arguments passed to '" + this->func_name + "'"),
                this->context
            )
        });
    }
     
    return res->Success(NULL);
}

RunTimeResult* BaseFunction::PopulateArguments(std::vector <NodeValue*>& passed_args) {
    RunTimeResult* res = new RunTimeResult();

    int i = 0;
    for (std::pair <std::string, Token*> p : this->func_args) {
        std::string arg_name = p.first,
                    arg_type = p.second->value;
        NodeValue* arg_val = passed_args[i];
        value_t arg_type_t = (value_t)0;
    
        // choose proper type
        if (arg_type == TYPE_INT) arg_type_t = INT_VALUE;
        else if (arg_type == TYPE_FLOAT) arg_type_t = FLOAT_VALUE;

        arg_val = NodeValue::CastToType(arg_val, arg_type_t);

        this->context->symbol_table->Set(arg_name, arg_val);

        i++;
    }


    return res->Success(NULL);
}





/*--- Function ------------------------------------------*/

Function::Function(
    std::string& func_name,
    std::vector <std::pair<std::string, Token*>>& args,
    Token* return_type,
    ASTNode* func_body,
    Context* passed_ctx
) :
    BaseFunction(func_name, args, return_type, passed_ctx),
    func_body(func_body)
{}

Function* Function::Copy() {
    Function* new_func = new Function(
        this->func_name,
        this->func_args,
        this->return_type,
        this->func_body,
        new Context()
    );

    new_func->context->name = this->context->name;
    new_func->context->symbol_table = this->context->symbol_table;
    new_func->context->parent = this->context->parent;

    return new_func;
}

RunTimeResult* Function::Execute(Interpreter* interpreter, std::vector <NodeValue*>& args) {
    RunTimeResult* res = new RunTimeResult();

    res->Register(this->CheckArguments(args));

    if (res->ShouldReturn())
        return res;

    res->Register(this->PopulateArguments(args));

    if (res->ShouldReturn())
        return res;

    NodeValue* return_val = res->Register(interpreter->Visit(this->func_body, this->context));

    if (res->ShouldReturn())
        return res;

    // Cast to correct return type
    if (this->return_type->value == TYPE_INT) {
        return_val = NodeValue::CastToType(return_val, INT_VALUE);
    }
    else if (this->return_type->value == TYPE_FLOAT) {
        return_val = NodeValue::CastToType(return_val, FLOAT_VALUE);
    }

    return res->Success(return_val);
}



/*--- Built In Function -------------------------------------*/
BuiltInFunction::BuiltInFunction(
    std::string& func_name,
    std::vector <std::pair<std::string, Token*>>& args,
    Token* return_type,
    Context* passed_ctx
) :
    BaseFunction(func_name, args, return_type, passed_ctx)
{}

BuiltInFunction* BuiltInFunction::Copy() {
    BuiltInFunction* new_func = new BuiltInFunction(
        this->func_name,
        this->func_args,
        this->return_type,
        new Context()
    );

    new_func->context->name = this->context->name;
    new_func->context->symbol_table = this->context->symbol_table;
    new_func->context->parent = this->context->parent;


    return new_func;
}


RunTimeResult* BuiltInFunction::Execute(std::vector <NodeValue*>& args) {
    RunTimeResult* res = new RunTimeResult();

    res->Register(this->CheckArguments(args));

    if (res->ShouldReturn())
        return res;

    res->Register(this->PopulateArguments(args));

    if (res->ShouldReturn())
        return res;

    if (this->func_name == BUILT_IN_FUNCTION_PRINT) {
        NodeValue* return_val = res->Register(
            this->Print()
        );


        if (res->ShouldReturn())
            return res;

        return res->Success(return_val);
    }
    else if (this->func_name == BUILT_IN_FUNCTION_LENGTH) {
        NodeValue* return_val = res->Register(
            this->Length()
        );

        if (res->ShouldReturn())
            return res;

        return res->Success(return_val);
    }
    else if (this->func_name == BUILT_IN_FUNCTION_SIZE) {
        NodeValue* return_val = res->Register(
            this->Size()
        );

        if (res->ShouldReturn())
            return res;

        return res->Success(return_val);
    }
    else if (this->func_name == BUILT_IN_FUNCTION_PUSH) {
        NodeValue* return_val = res->Register(
            this->Push()
        );

        if (res->ShouldReturn())
            return res;

        return res->Success(return_val);
    }
    else if (this->func_name == BUILT_IN_FUNCTION_POP) {
        NodeValue* return_val = res->Register(
            this->Pop()
        );

        if (res->ShouldReturn())
            return res;

        return res->Success(return_val);
    }
    else {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("No built-in function with the name '" + this->func_name + "' was defined"),
            this->context
        ));
    }
}


/*--- Built-in functions ----------------*/
RunTimeResult* BuiltInFunction::Print() {
    RunTimeResult* res = new RunTimeResult();

    NodeValue* val = this->context->symbol_table->Get("value");

    if (!val) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No argument found for '" + BUILT_IN_FUNCTION_PRINT + "' function"),
            this->context
        ));
    }

    std::cout << val->Represent() << std::endl;

    return res->Success(val);
}


RunTimeResult* BuiltInFunction::Length() {
    RunTimeResult* res = new RunTimeResult();

    NodeValue* val = this->context->symbol_table->Get("value");

    if (!val) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No argument found for '" + BUILT_IN_FUNCTION_LENGTH + "' function"),
            this->context
        ));
    }

    if (val->type != STRING_VALUE) {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Invalid argument type provided. Expected 'string'."),
            this->context
        ));
    }

    String* str_val = reinterpret_cast<String*> (val->value);
    NodeValue* res_val = new NodeValue((long long)str_val->value.size());

    return res->Success(res_val);
}


RunTimeResult* BuiltInFunction::Size() {
    RunTimeResult* res = new RunTimeResult();

    NodeValue* val = this->context->symbol_table->Get("value");

    if (!val) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No argument found for '" + BUILT_IN_FUNCTION_SIZE + "' function"),
            this->context
        ));
    }

    if (val->type != ARRAY_VALUE) {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Invalid argument type provided. Expected 'array'."),
            this->context
        ));
    }

    Array* arr_val = reinterpret_cast<Array*> (val->value);
    NodeValue* res_val = new NodeValue((long long)arr_val->array_body.size());

    return res->Success(res_val);
}


RunTimeResult* BuiltInFunction::Push() {
    RunTimeResult* res = new RunTimeResult();

    NodeValue* arr = this->context->symbol_table->Get("array");
    NodeValue* elem = this->context->symbol_table->Get("element");

    if (!arr) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No first argument found for '" + BUILT_IN_FUNCTION_PUSH + "' function"),
            this->context
        ));
    }

    if (arr->type != ARRAY_VALUE) {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Invalid first argument type provided. Expected 'array'."),
            this->context
        ));
    }

    if (!elem) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No second argument found for '" + BUILT_IN_FUNCTION_PUSH + "' function"),
            this->context
        ));
    }

    Array* arr_val = reinterpret_cast<Array*> (arr->value);
    arr_val->array_body.push_back(elem);

    return res->Success(elem);
}



RunTimeResult* BuiltInFunction::Pop() {
    RunTimeResult* res = new RunTimeResult();

    NodeValue* arr = this->context->symbol_table->Get("array");
    NodeValue* ind = this->context->symbol_table->Get("index");

    if (!arr) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No first argument found for '" + BUILT_IN_FUNCTION_POP + "' function"),
            this->context
        ));
    }

    if (arr->type != ARRAY_VALUE) {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Invalid first argument type provided. Expected 'array'."),
            this->context
        ));
    }

    if (!ind) {
        return res->Failure(new Error(
            ERROR_INTERNAL,
            std::string("No second argument found for '" + BUILT_IN_FUNCTION_POP + "' function"),
            this->context
        ));
    }

    if (ind->type != INT_VALUE) {
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Invalid first argument type provided. Expected 'int'."),
            this->context
        ));
    }

    IntNumber* index = reinterpret_cast<IntNumber*> (ind->value);

    Array* arr_val = reinterpret_cast<Array*> (arr->value);

    if (!arr_val->InBounds(index->value, arr_val->array_body))
        return res->Failure(new Error(
            ERROR_RUNTIME,
            std::string("Index out of bounds"),
            this->context
        ));

    NodeValue* del_val = arr_val->array_body[index->value];
    arr_val->array_body.erase(arr_val->array_body.begin() + index->value);

    return res->Success(del_val);
}


