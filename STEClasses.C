#include "STEClasses.h"
#include "Value.h"
#include "ParserUtil.h"

void GlobalEntry::print(ostream& out, int indent) const
{
	// Add your code
         out<<"\n";
    printST(out, indent, '\0', '\0', true, 0, 0);

    out <<"\n";
    for(int i = 0; i < rules_.size(); i++)
    {
        rules_[i]->print(out, indent+STEP_INDENT);
        out<<"\n";
    }
}

void EventEntry::print(ostream& out, int indent) const
{
        out<<"event" << " "<<name();
        printST(out, indent, '(', ')', false, 0, 0);
        out<<";";

}


void VariableEntry::print(ostream& os, int indent) const
{
    os << (type()->fullName()) <<" "<< name();
    if (initVal_) {
        os << " = ";
        initVal()->print(os, indent);
    }
    if (varKind() != PARAM_VAR)
        os <<";";
}

void FunctionEntry::print(ostream& os, int indent) const
{
    os<<type()->retType_->name()<<" "<<name();
    int num_params = type()->argTypes() ? type()->argTypes()->size() : 0;
    if (num_params) {
        printST(os, indent, '(', ')', false, 0, num_params);
    } else {
        os << "()";
    }
    if (body_) {
        os << " {\n";
        printST(os, indent, '\0', '\0', true, num_params, 10000);

        body_->printWithoutBraces(os, indent);
        os << "}";
    }
    os<<";";
}

void ClassEntry::print(ostream& os, int indent) const
{
    os<<"class"<<" "<<name()<<";";
    printST(os, indent, '\0', '\0', true, 0, 0);
}
