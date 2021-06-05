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
        new Context(this->context->name, this->context)
    );

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
        new Context(this->context->name, this->context)
    );

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

    return res->Success(NULL);
}


