#include <iostream>
#include <fstream>
#include <string>


using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using std::string;




/*=====Helper Functions=====*/

int log2Floor(float x){
    int y = * (int *) &x;
    return (y >> 23) - 127;
}




/*=====VARIABLE=====*/

class Variable{
    public:
        Variable();
        Variable(string _name, bool _value = false);

        string GetName() {return name;}
        bool GetValue() {return value;}

        void SetName(string newName);
        void SetValue(bool newValue);
        void Set(string newName, bool newValue);
        void Set(Variable &other);

        bool operator!();
        Variable & operator=(Variable &other);
        Variable & operator=(bool other);
        friend bool operator&&(bool other, Variable &var);
        friend bool operator&&(Variable &var, bool other);
        friend bool operator&&(Variable &var, Variable &other);
        friend bool operator==(bool other, Variable &var);
        friend bool operator==(Variable &var, bool other);
        friend bool operator==(Variable &var, Variable &other);
        friend bool operator||(bool other, Variable &var);
        friend bool operator||(Variable &var, bool other);
        friend bool operator||(Variable &var, Variable &other);
        friend istream & operator>>(istream &in, Variable &var);
        friend ostream & operator<<(ostream &out, const Variable &var);
    private:
        string name;
        bool value;
};

Variable::Variable() : name(), value()
{
    // blank
}

Variable::Variable(string _name, bool _value) : name(_name), value(_value)
{
    // blank
}

void Variable::SetName(string newName){
    name = newName;
}

void Variable::SetValue(bool newValue){
    value = newValue;
}

void Variable::Set(string newName, bool newValue){
    name = newName;
    value = newValue;
}

void Variable::Set(Variable &other){
    name = other.name;
    value = other.value;
}

bool Variable::operator!(){
    return !value;
}

Variable & Variable::operator=(Variable &other){
    value = other.value;
    return *this;
}

Variable & Variable::operator=(bool other){
    value = other;
    return *this;
}

bool operator&&(bool other, Variable &var){
    return other && var.value;
}

bool operator&&(Variable &var, bool other){
    return other && var.value;
}

bool operator&&(Variable &var, Variable &other){
    return other.value && var.value;
}

bool operator==(bool other, Variable &var){
    return other == var.value;
}

bool operator==(Variable &var, bool other){
    return other == var.value;
}

bool operator==(Variable &var, Variable &other){
    return other.value == var.value;
}

bool operator||(bool other, Variable &var){
    return other || var.value;
}

bool operator||(Variable &var, bool other){
    return other || var.value;
}

bool operator||(Variable &var, Variable &other){
    return other.value || var.value;
}

istream & operator>>(istream &in, Variable &var){
    in >> var.value;
    return in;
}

ostream & operator<<(ostream &out, const Variable &var){
    out << var.value;
    return out;
}



/*=====OPERATION=====*/

class Operation{
    public:
        Operation();
        Operation(Variable **_variables, int _variableCount);
        virtual ~Operation();

        void AddVariable(Variable *newVariable);

        virtual void Run();
    protected:
        void ResizeVariableArray(int newSize);

        Variable **variables;
        int variableCount;
};

Operation::Operation() : Operation(nullptr, 0)
{
    // blank
}

Operation::Operation(Variable **_variables, int _variableCount) 
         : variables(_variables), variableCount(_variableCount)
{
    // blank
}

Operation::~Operation()
{
    // blank
}

void Operation::AddVariable(Variable *newVariable){
    ResizeVariableArray(variableCount + 1);
    variables[variableCount - 1] = newVariable;
}

void Operation::ResizeVariableArray(int newSize){
    Variable **newVariablePointers = new Variable*[newSize]{};

    if(newSize > variableCount)
        for(int i = 0; i < variableCount; ++i)
            newVariablePointers[i] = variables[i];
    else
        for(int i = 0; i < newSize; ++i)
            newVariablePointers[i] = variables[i];
    
    delete [] variables;
    variables = newVariablePointers;
    variableCount = newSize;
}

void Operation::Run(){
    // blank
}



/*=====INPUT=====*/

class INPUT : public Operation{
    public:
        INPUT(istream **_inputStream = nullptr, ifstream **_inputFileStream = nullptr);

        virtual void Run();
    private:
        istream **inputStream;
        ifstream **inputFileStream;
};

INPUT::INPUT(istream **_inputStream, ifstream **_inputFileStream) 
     : inputStream(_inputStream), inputFileStream(_inputFileStream)
{
    // blank
}

void INPUT::Run(){

    if(*inputStream != nullptr)
        for(int i = 0; i < variableCount; ++i)
            **inputStream >> *variables[i];

    else if(*inputFileStream != nullptr)
        for(int i = 0; i < variableCount; ++i)
            **inputFileStream >> *variables[i];
}



/*=====OUTPUT=====*/

class OUTPUT : public Operation{
    public:
        OUTPUT(ostream **_outputStream = nullptr, ofstream **_outputFileStream = nullptr);

        virtual void Run();
    private:
        ostream **outputStream;
        ofstream **outputFileStream;
};

OUTPUT::OUTPUT(ostream **_outputStream, ofstream **_outputFileStream) 
      : outputStream(_outputStream), outputFileStream(_outputFileStream)
{
    // blank
}

void OUTPUT::Run(){
    // blank
}



/*=====AND=====*/

class AND : public Operation{
    public:
        AND();

        virtual void Run();
    private:
};

AND::AND()
{
    // blank
}

void AND::Run(){
    bool result = true;

    for(int i = 1; i < variableCount; ++i)
        result = result && *variables[i];
    
    *variables[0] = result;
}



/*=====OR=====*/

class OR : public Operation{
    public:
        OR();

        virtual void Run();
    private:
};

OR::OR()
{
    // blank
}

void OR::Run(){
    bool result = false;

    for(int i = 1; i < variableCount; ++i)
        result = result || *variables[i];
    
    *variables[0] = result;
}



/*=====NOT=====*/

class NOT : public Operation{
    public:
        NOT();

        virtual void Run();
    private:
};

NOT::NOT()
{
    // blank
}

void NOT::Run(){
    *variables[0] = !*variables[1];
}



/*=====FLIPFLOP=====*/

class FLIPFLOP : public Operation{
    public:
        FLIPFLOP();

        virtual void Run();
    private:
        bool output;
};

FLIPFLOP::FLIPFLOP() 
        : output(false)
{
    // blank
}

void FLIPFLOP::Run(){
    if(*variables[1] == true)
        output = !output;
    *variables[0] = output;
}



/*=====DECODER=====*/

class DECODER : public Operation{
    public:
        DECODER();

        virtual void Run();
    private:
};

DECODER::DECODER()
{
    // blank
}

void DECODER::Run(){
    int inputCount = log2Floor(variableCount);
    int outputIndex = 0;

    for(int i = variableCount - inputCount; i < variableCount; ++i)
        outputIndex = (outputIndex << 1) | (*variables[i] == true);

    *variables[outputIndex] = true;
}



/*=====PROGRAM=====*/

class Program{
    public:
        Program();
        Program(ifstream &instructionFile, ifstream &_input, ofstream &_output);
        Program(ifstream &instructionFile, istream &_input, ofstream &_output);
        Program(ifstream &instructionFile, ifstream &_input, ostream &_output);
        Program(ifstream &instructionFile, istream &_input, ostream &_output);
        ~Program();

        Variable * GetVariable(string name);

        void SetInstruction(ifstream &instructionFile);
        void SetInput(ifstream &_input);
        void SetInput(istream &_input);
        void SetOutput(ofstream &_output);
        void SetOutput(ostream &_output);

        void Run();
    private:
        void ResizeOperationArray(int newSize);
        void ResizeVariableArray(int newSize);
        void ResizeOutputArray(int newSize);

        istream *input;
        ifstream *inputFile;
        ostream *output;
        ofstream *outputFile;

        Variable **variables;
        Variable *inputVariables;
        Variable **outputVariables;
        Operation **operations;
        int variableCount;
        int inputVariableCount;
        int outputVariableCount;
        int operationCount;
};

Program::Program() : input(nullptr), inputFile(nullptr), output(nullptr), outputFile(nullptr),
                     variables(nullptr), inputVariables(nullptr), outputVariables(nullptr), operations(nullptr),
                     variableCount(0), inputVariableCount(0), outputVariableCount(0), operationCount(0)
{
    // blank
}

Program::Program(ifstream &instructionFile, ifstream &_input, ofstream &_output) 
                : input(nullptr), inputFile(&_input), output(nullptr), outputFile(&_output),
                  variables(nullptr), inputVariables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), inputVariableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

Program::Program(ifstream &instructionFile, istream &_input, ofstream &_output) 
                : input(&_input), inputFile(nullptr), output(nullptr), outputFile(&_output),
                  variables(nullptr), inputVariables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), inputVariableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

Program::Program(ifstream &instructionFile, ifstream &_input, ostream &_output) 
                : input(nullptr), inputFile(&_input), output(&_output), outputFile(nullptr),
                  variables(nullptr), inputVariables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), inputVariableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

Program::Program(ifstream &instructionFile, istream &_input, ostream &_output) 
                : input(&_input), inputFile(nullptr), output(&_output), outputFile(nullptr),
                  variables(nullptr), inputVariables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), inputVariableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

Program::~Program()
{
    for(int i = 0; i < operationCount; ++i)
        delete operations[i];
    delete [] operations;

    for(int i = 0; i < variableCount; ++i)
        delete variables[i];
    delete [] variables;

    for(int i = 0; i < outputVariableCount; ++i)
        delete (outputVariables[i]);
    delete [] outputVariables;
}

Variable * Program::GetVariable(string name){
    for(int i = 0; i < variableCount; ++i)
        if(variables[i]->GetName() == name)
            return variables[i];
    return nullptr;
}

void Program::SetInstruction(ifstream &instructionFile){
    string readWord, lastOperationName{};

    while(instructionFile >> readWord){

        if(readWord == "INPUT"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new INPUT(&input, &inputFile);
        }
        else if(readWord == "OUTPUT"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new OUTPUT(&output, &outputFile);
        }
        else if(readWord == "AND"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new AND();
            
        }
        else if(readWord == "OR"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new OR();
            
        }
        else if(readWord == "NOT"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new NOT();
            
        }
        else if(readWord == "FLIPFLOP"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new FLIPFLOP();
            
        }
        else if(readWord == "DECODER"){
            ResizeOperationArray(operationCount + 1);
            operations[operationCount - 1] = new DECODER();
            
        }
        else{
            Variable *newVariable = GetVariable(readWord);
            
            if(newVariable == nullptr){
                ResizeVariableArray(variableCount + 1);
                newVariable = new Variable(readWord);
                variables[variableCount - 1] = newVariable;
            }

            operations[operationCount - 1]->AddVariable(newVariable);

            if(lastOperationName == "OUTPUT"){
                ResizeOutputArray(outputVariableCount + 1);
                outputVariables[outputVariableCount - 1] = newVariable;
            }

            continue;
        }

        lastOperationName = readWord;
    }
}

void Program::Run(){
    for(int i = 0; i < operationCount; ++i)
        operations[i]->Run();

    
    if(output != nullptr){
        for(int i = 0; i < outputVariableCount; ++i)
            *output << *outputVariables[i] << " ";
        *output << std::endl;
    }

    else if(outputFile != nullptr){
        for(int i = 0; i < outputVariableCount; ++i)
            *outputFile << *outputVariables[i] << " ";
        *outputFile << std::endl;
    }

    for(int i = 0; i < variableCount; ++i)
        variables[i]->SetValue(false);
}

void Program::ResizeOperationArray(int newSize){
    Operation **newOperations = new Operation*[newSize]{};

    if(newSize > operationCount)
        for(int i = 0; i < operationCount; ++i)
            newOperations[i] = operations[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newOperations[i] = operations[i];
        for(int i = newSize; i < operationCount; ++i)
            delete operations[i];
    }

    delete [] operations;
    operations = newOperations;
    operationCount = newSize;
}

void Program::ResizeVariableArray(int newSize){
    Variable **newVariables = new Variable*[newSize]{};

    if(newSize > variableCount)
        for(int i = 0; i < variableCount; ++i)
            newVariables[i] = variables[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newVariables[i] = variables[i];
        for(int i = newSize; i < variableCount; ++i)
            delete variables[i];
    }

    delete [] variables;
    variables = newVariables;
    variableCount = newSize;
}

void Program::ResizeOutputArray(int newSize){
    Variable **newOutputVariables = new Variable*[newSize]{};

    if(newSize > outputVariableCount)
        for(int i = 0; i < outputVariableCount; ++i)
            newOutputVariables[i] = outputVariables[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newOutputVariables[i] = outputVariables[i];
        for(int i = newSize; i < outputVariableCount; ++i)
            delete outputVariables[i];
    }

    delete [] outputVariables;
    outputVariables = newOutputVariables;
    outputVariableCount = newSize;
}




int main(){
    
    ifstream circuitFile("circuit.txt");
    ifstream inputFile("input.txt");

    Program myProgram(circuitFile, inputFile, std::cout);
    
    while(!inputFile.eof())
        myProgram.Run();
    
    return 0;
}