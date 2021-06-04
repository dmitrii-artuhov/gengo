#include "../../../gengo.h"
#include "./functions.h"
#include "../types.h"
#include "../node/node.h"
#include "../float/float.h"
#include "../../tokens/token.h"



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

/*
Context* BaseFunction::GenerateNewContext(Context* parent = nullptr) {
	Context* new_context = new Context(this->func_name, parent);
	new_context->symbol_table = new SymbolTable();
	
	return new_context;		
}
*/

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
                    arg_type = p.second->type;
        NodeValue* arg_val = passed_args[i];
        value_t arg_type_t = (value_t)0;
    
        // choose proper type
        if (arg_type == TOKEN_INT) arg_type_t = INT_VALUE;
        else if (arg_type == TOKEN_FLOAT) arg_type_t = FLOAT_VALUE;

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
        new Context(this->context->name, this->context)
    );

    return new_func;
}

RunTimeResult* Function::Execute(Interpreter* interpreter, std::vector <NodeValue*>& args) {
    RunTimeResult* res = new RunTimeResult();

    res->Register(this->CheckArguments(args));

    if (res->error)
        return res;

    res->Register(this->PopulateArguments(args));

    if (res->error)
        return res;

    NodeValue* return_val = res->Register(interpreter->Visit(this->func_body, this->context));

    if (res->error)
        return res;

    // Cast to correct return type
    if (this->return_type->type == TOKEN_INT) {
        return_val = NodeValue::CastToType(return_val, INT_VALUE);
    }
    else if (this->return_type->type == TOKEN_FLOAT) {
        return_val = NodeValue::CastToType(return_val, FLOAT_VALUE);
    }

    return res->Success(return_val);
}
