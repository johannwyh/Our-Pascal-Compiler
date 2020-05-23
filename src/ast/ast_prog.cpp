#include "ast_prog.h"

ASTProgramHead::ASTProgramHead(std::string id) : id(id) {}
void ASTProgramHead::Print(GraphGenerator* g) {
    g->AddNode("program_head", this->line(), this->col());
    g->AddIdentifier(id);
    g->Pop();
}

ASTRoutineHead::ASTRoutineHead(ASTConstPart* const_part, ASTTypePart* type_part,
                               ASTVarPart* var_part,
                               ASTRoutinePart* routine_part)
    : const_part(const_part),
      type_part(type_part),
      var_part(var_part),
      routine_part(routine_part) {}

void ASTRoutineHead::Print(GraphGenerator* g) {
    g->AddNode("routine_head", this->line(), this->col());
    if (const_part != nullptr) const_part->Print(g);
    if (type_part != nullptr) type_part->Print(g);
    if (var_part != nullptr) var_part->Print(g);
    if (routine_part != nullptr) routine_part->Print(g);
    g->Pop();
}

ASTRoutineBody::ASTRoutineBody(ASTStmtList* compound_stmt)
    : compound_stmt(compound_stmt) {}
void ASTRoutineBody::Print(GraphGenerator* g) {
    g->AddNode("routine_body", this->line(), this->col());
    this->compound_stmt->Print(g);
    g->Pop();
}

ASTRoutine::ASTRoutine(ASTRoutineHead* routine_head,
                       ASTRoutineBody* routine_body)
    : routine_head(routine_head), routine_body(routine_body) {}
void ASTRoutine::Print(GraphGenerator* g) {
    g->AddNode("routine", this->line(), this->col());
    routine_head->Print(g);
    routine_body->Print(g);
    g->Pop();
}

ASTProgram::ASTProgram(ASTProgramHead* program_head, ASTRoutine* routine)
    : program_head(program_head), routine(routine) {}

void ASTProgram::Print(GraphGenerator* g) {
    g->AddNode("program", this->line(), this->col());
    program_head->Print(g);
    routine->Print(g);
    g->Pop();
}

ASTRoutinePart::ASTRoutinePart(ASTFuncProcBase* func_proc) {
    this->routine_list.clear();
    this->routine_list.push_back(func_proc);
}
void ASTRoutinePart::addFuncProcDecl(ASTFuncProcBase* func_proc) {
    this->routine_list.push_back(func_proc);
}
void ASTRoutinePart::Print(GraphGenerator* g) {
    g->AddNode("routine_part", this->line(), this->col());
    for (auto fp : this->routine_list) fp->Print(g);
    g->Pop();
}

ASTFunctionDecl::ASTFunctionDecl(ASTFunctionHead* function_head,
                                 ASTRoutine* routine)
    : function_head(function_head),
      routine(routine),
      ASTFuncProcBase(ASTFuncProcBase::FuncType::FUNCTION) {}
void ASTFunctionDecl::Print(GraphGenerator* g) {
    g->AddNode("function_decl", this->line(), this->col());
    if (function_head != nullptr) function_head->Print(g);
    if (routine != nullptr) routine->Print(g);
    g->Pop();
}

ASTFunctionHead::ASTFunctionHead(std::string func_name,
                                 ASTParaDeclList* parameters,
                                 ASTSimpleTypeDecl* simple_type_decl)
    : func_name(func_name),
      parameters(parameters),
      simple_type_decl(simple_type_decl) {}
void ASTFunctionHead::Print(GraphGenerator* g) {
    g->AddNode("function_head of " + this->func_name, this->line(),
               this->col());
    if (this->parameters != nullptr) this->parameters->Print(g);
    if (this->simple_type_decl != nullptr) this->simple_type_decl->Print(g);
    g->Pop();
}

ASTProcedureDecl::ASTProcedureDecl(ASTProcedureHead* procedure_head,
                                   ASTRoutine* routine)
    : procedure_head(procedure_head),
      routine(routine),
      ASTFuncProcBase(ASTFuncProcBase::FuncType::PROCEDURE) {}
void ASTProcedureDecl::Print(GraphGenerator* g) {
    g->AddNode("procedure_decl", this->line(), this->col());
    if (this->procedure_head != nullptr) this->procedure_head->Print(g);
    if (this->routine != nullptr) this->routine->Print(g);
    g->Pop();
}

ASTProcedureHead::ASTProcedureHead(std::string proc_name,
                                   ASTParaDeclList* parameters)
    : proc_name(proc_name), parameters(parameters) {}
void ASTProcedureHead::Print(GraphGenerator* g) {
    g->AddNode("procedure_head of " + this->proc_name, this->line(),
               this->col());
    if (this->parameters != nullptr) this->parameters->Print(g);
    g->Pop();
}

/*
ASTParameters::ASTParameters(ASTParaDeclList* para_dec_list)
    : para_dec_list(para_dec_list) {}
void ASTParameters::Print(GraphGenerator* g) {
    g->AddNode("parameters", this->line(), this->col());

    g->Pop();
}
*/

ASTParaDeclList::ASTParaDeclList(ASTParaTypeList* para_type_list) {
    this->para_decl_list.clear();
    this->para_decl_list.push_back(para_type_list);
}
void ASTParaDeclList::addParaTypeList(ASTParaTypeList* para_type_list) {
    this->para_decl_list.push_back(para_type_list);
}
void ASTParaDeclList::Print(GraphGenerator* g) {
    g->AddNode("para_decl_list", this->line(), this->col());
    for (auto type_list : para_decl_list) type_list->Print(g);
    g->Pop();
}

ASTParaTypeList::ASTParaTypeList(ASTParaList* para_list,
                                 ASTSimpleTypeDecl* simple_type_decl)
    : para_list(para_list), simple_type_decl(simple_type_decl) {}

void ASTParaTypeList::Print(GraphGenerator* g) {
    g->AddNode("para_type_list", this->line(), this->col());
    para_list->Print(g);
    simple_type_decl->Print(g);
    g->Pop();
}

ASTVarParaList::ASTVarParaList(ASTNameList* name_list)
    : name_list(name_list), ASTParaList(true) {}
void ASTVarParaList::Print(GraphGenerator* g) {
    g->AddNode("var_para_list", this->line(), this->col());
    name_list->Print(g);
    g->Pop();
}

ASTValParaList::ASTValParaList(ASTNameList* name_list)
    : name_list(name_list), ASTParaList(false) {}
void ASTValParaList::Print(GraphGenerator* g) {
    g->AddNode("val_para_list", this->line(), this->col());
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    name_list->Print(g);
    g->Pop();
}