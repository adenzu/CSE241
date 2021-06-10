#include <iostream>
#include <fstream>
#include <string>


using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;
using std::string;



/**
 * Main function is at the bottom
 * 
 */



/*=====Helper Functions=====*/

/**
 * @brief Returns floor integer of log2 of given float number
 * 
 * @param x Floating number whose log2 is wanted
 * @return int
 * 
 * @details
 * C++ floats are IEEE754 floating point types, that are 32 bits consisting of one bit
 * for sign, 8 bits for exponent (of two), and rest being for raction
 * So to get log2 of a floating point, one can get this 8 bits, which this function does so
 * 
 * Won't work properly when a negative value is given, but there won't be such case in this assignment
 */
int log2Floor(float x){
    int y = * (int *) &x;   // Cast to integer while preserving bit order
    return (y >> 23) - 127; // Get rid of fraction part, subtract 127 since sign of exponent
                            // is reversed, return
}




/*=====VARIABLE=====*/

/**
 * @brief Bool variable class
 * 
 */
class Variable{
    public:
        // See function implementations below for further explanation

        Variable();                                     // Main constructor
        Variable(string _name, bool _value = false);    // Constructor with name and value of variable

        string GetName() {return name;}                 // Returns name of variable
        bool GetValue() {return value;}                 // Returns (bool) value of variable 

        void SetName(string newName);                   // Set variable name
        void SetValue(bool newValue);                   // Set variable value
        void Set(string newName, bool newValue);        // Set variable name and value
        void Set(Variable &other);                      // Set variable by another variable

        bool operator!();                                               // Returns not of value of variable
        Variable & operator=(Variable &other);                          // Sets value of variable to another variable's value
        Variable & operator=(bool other);                               // Sets value of variable to given value
        friend bool operator&&(bool other, Variable &var);              // And operation of variable with bool before it
        friend bool operator&&(Variable &var, bool other);              // And operation of variable with bool after it
        friend bool operator&&(Variable &var, Variable &other);         // And operation of variable with another variable
        friend bool operator==(bool other, Variable &var);              // Equal operation of variable with bool before it
        friend bool operator==(Variable &var, bool other);              // Equal operation of variable with bool after it
        friend bool operator==(Variable &var, Variable &other);         // Equal operation of variable wtih another variable
        friend bool operator||(bool other, Variable &var);              // Or operation of variable with bool before it
        friend bool operator||(Variable &var, bool other);              // Or operation of variable with bool after it
        friend bool operator||(Variable &var, Variable &other);         // Or operation of variable with another variable
        friend istream & operator>>(istream &in, Variable &var);        // Input operation 
        friend ostream & operator<<(ostream &out, const Variable &var); // Output operation
    private:
        string name;    // Variable name
        bool value;     // Variable value
};

/**
 * @brief Construct a new blank Variable object
 * 
 */
Variable::Variable() : name(), value()
{
    // blank
}

/**
 * @brief Construct a new Variable object
 * 
 * @param _name    
 * @param _value    
 */
Variable::Variable(string _name, bool _value) : name(_name), value(_value)
{
    // blank
}

/**
 * @brief Set variable's name to given string
 * 
 * @param newName 
 */
void Variable::SetName(string newName){
    name = newName;
}

/**
 * @brief Set variable's value to given value
 * 
 * @param newValue 
 */
void Variable::SetValue(bool newValue){
    value = newValue;
}

/**
 * @brief Set variable's name and value to given string and value respectively
 * 
 * @param newName 
 * @param newValue 
 */
void Variable::Set(string newName, bool newValue){
    name = newName;
    value = newValue;
}

/**
 * @brief Set variable's name and value to given variable's name and value respectively
 * 
 * @param other Given variable
 */
void Variable::Set(Variable &other){
    name = other.name;
    value = other.value;
}

/**
 * @brief Returns opposite of variable's value
 * 
 * @return bool
 */
bool Variable::operator!(){
    return !value;
}

/**
 * @brief Sets variable's value to given variable's value
 * 
 * @param other Given variable
 * @return Variable&
 */
Variable & Variable::operator=(Variable &other){
    value = other.value;
    return *this;
}

/**
 * @brief Sets variable's value to given value
 * 
 * @param other Given value
 * @return Variable& 
 */
Variable & Variable::operator=(bool other){
    value = other;
    return *this;
}

// Next variable functions are self explanatory

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

/**
 * @brief Boolean operation base class
 * 
 */
class Operation{
    public:
        // See function implementations below for further explanation
        
        Operation();                                            // Main constructor
        Operation(Variable **_variables, int _variableCount);   // Constructor with operation variables and number of them
        virtual ~Operation();                                   // Destructor

        void AddVariable(Variable *newVariable);                // Adds new variable to operation

        virtual bool Run();                                     // Runs the operation
    protected:
        void ResizeVariableArray(int newSize);                  // Resizes variable (pointer) array

        Variable **variables;                                   // Variable (pointer) array
        int variableCount;                                      // Number of variables
};

/**
 * @brief Construct a new blank Operation object
 * 
 */
Operation::Operation() : Operation(nullptr, 0)
{
    // blank
}

/**
 * @brief Construct a new Operation object
 * 
 * @param _variables Array of variable pointers
 * @param _variableCount Number of variables
 */
Operation::Operation(Variable **_variables, int _variableCount) 
         : variables(_variables), variableCount(_variableCount)
{
    // blank
}

/**
 * @brief Destroy the Operation object
 * 
 * @details 
 * Does not destroy variables, only destroys array elements that hold variables' adresses
 */
Operation::~Operation()
{
    delete [] variables;
    variables = nullptr;
}

/**
 * @brief Adds variable to operation
 * 
 * @param newVariable 
 */
void Operation::AddVariable(Variable *newVariable){
    ResizeVariableArray(variableCount + 1);     // Increase variable array size
    variables[variableCount - 1] = newVariable; // Put new variable's address 
}

/**
 * @brief Resizes variable (pointer) array
 * 
 * @param newSize 
 */
void Operation::ResizeVariableArray(int newSize){
    Variable **newVariablePointers = new Variable*[newSize]{};  // Allocate new variable pointer array

    // Copy existing variables' adresses to new pointer array
    if(newSize > variableCount)                     
        for(int i = 0; i < variableCount; ++i)      
            newVariablePointers[i] = variables[i];
    else                                            
        for(int i = 0; i < newSize; ++i)
            newVariablePointers[i] = variables[i];
    
    delete [] variables;                // Deallocate old pointer array
    variables = newVariablePointers;    // Update array
    variableCount = newSize;            // Update size
}

/**
 * @brief Runs the operation, returns true if operation completed successfully, false otherwise
 * 
 * @return bool
 * 
 * @details 
 * Operation base class is not intended to be run anywhere, or used.
 */
bool Operation::Run(){
    return true;
}



/*=====INPUT=====*/

/**
 * @brief Input operation class
 * 
 */
class INPUT : public Operation{
    public:
        // See function implementations below for further explanation

        INPUT(istream **_inputStream = nullptr, ifstream **_inputFileStream = nullptr); // Constructor

        virtual bool Run(); // Runs the operation
    private:
        istream **inputStream;      // Input stream
        ifstream **inputFileStream; // Input file stream
};

/**
 * @brief Construct a new INPUT object
 * 
 * @param _inputStream 
 * @param _inputFileStream 
 */
INPUT::INPUT(istream **_inputStream, ifstream **_inputFileStream) 
     : inputStream(_inputStream), inputFileStream(_inputFileStream)
{
    // blank
}

/**
 * @brief Reads input (file) stream and sets variables to read values, returns true if at least one value is read, false otherwise
 * 
 * @return bool 
 */
bool INPUT::Run(){
    bool successful = false;    // Is operation successful

    // Input stream is favored
    if(*inputStream != nullptr)
        for(int i = 0; i < variableCount; ++i){
            if(**inputStream >> *variables[i]) successful = true;
            else break;
        }

    else if(*inputFileStream != nullptr)
        for(int i = 0; i < variableCount; ++i){
            if(**inputFileStream >> *variables[i]) successful = true;
            else break;
        }
    
    return successful;
}



/*=====OUTPUT=====*/

/**
 * @brief Output operation class
 * 
 * @details 
 * Actually has no operation-level purpose since doesn't have to be run in given order in instructions file,
 * such as printing the variables or so, thus redundant
 */
class OUTPUT : public Operation{
    public:
        // See function implementations below for further explanation

        OUTPUT(ostream **_outputStream = nullptr, ofstream **_outputFileStream = nullptr);  // Constructor

        virtual bool Run(); // Runs the operation
    private:
        ostream **outputStream;     // Output stream
        ofstream **outputFileStream;// Output file stream
};

/**
 * @brief Construct a new OUTPUT object
 * 
 * @param _outputStream 
 * @param _outputFileStream 
 */
OUTPUT::OUTPUT(ostream **_outputStream, ofstream **_outputFileStream) 
      : outputStream(_outputStream), outputFileStream(_outputFileStream)
{
    // blank
}

/**
 * @brief Doesn't do anything
 * 
 * @return true 
 */
bool OUTPUT::Run(){
    return true;
}



/*=====AND=====*/

/**
 * @brief And operation class
 * 
 */
class AND : public Operation{
    public:
        // See function implementations below for further explanation

        AND();  // Constructor

        virtual bool Run(); // Runs the operation
    private:
};

/**
 * @brief Construct a new AND object
 * 
 */
AND::AND()
{
    // blank
}

/**
 * @brief Evaluates boolean and operation among variables, returns true if operation completed successfully, false otherwise
 * 
 * @return bool
 */
bool AND::Run(){
    bool successful = variableCount > 1;

    if(successful){                     // At least two variables needed
        bool result = true;             // Result of boolean and operation

        // Result of operation will be stored in first variable, so
        // operation is done among other variables
        for(int i = 1; i < variableCount; ++i)
            result = result && *variables[i];
        
        *variables[0] = result; // Put result
    }

    return successful;
}



/*=====OR=====*/

/**
 * @brief Or operation class
 * 
 */
class OR : public Operation{
    public:
        // See function implementations below for further explanation
        
        OR();   // Constructor

        virtual bool Run(); // Runs the operation
    private:
};

/**
 * @brief Construct a new OR object
 * 
 */
OR::OR()
{
    // blank
}

/**
 * @brief Evaluates boolean or operation among variables, returns true if operation completed successfully, false otherwise
 * 
 * @return bool
 */
bool OR::Run(){
    bool successful = variableCount > 1;

    if(successful){                     // At least two variables needed
        bool result = false;            // Result of boolean or operation

        // Result of operation will be stored in first variable, so
        // operation is done among other variables
        for(int i = 1; i < variableCount; ++i)
            result = result || *variables[i];

        *variables[0] = result; // Put result
    }

    return successful;
}



/*=====NOT=====*/

/**
 * @brief Not operation class
 * 
 */
class NOT : public Operation{
    public:
        // See function implementations below for further explanation

        NOT();  // Constructor

        virtual bool Run(); // Runs the operation
    private:
};

/**
 * @brief Construct a new NOT object
 * 
 */
NOT::NOT()
{
    // blank
}

/**
 * @brief Evaluates boolean not operation among variables, returns true if operation completed successfully, false otherwise
 * 
 * @return bool
 */
bool NOT::Run(){
    bool successful = variableCount == 2;

    if(successful){    // Exactly two variables needed
        *variables[0] = !*variables[1];     
    }

    return successful;
}



/*=====FLIPFLOP=====*/

/**
 * @brief Flipflop operation class
 * 
 */
class FLIPFLOP : public Operation{
    public:
        // See function implementations below for further explanation

        FLIPFLOP(); // Constructor

        virtual bool Run(); // Runs the operation
    private:
        bool output;        // Output of flipflop
};

/**
 * @brief Construct a new FLIPFLOP object
 * 
 */
FLIPFLOP::FLIPFLOP() 
        : output(false)
{
    // blank
}

/**
 * @brief Changes output whenever true (1) input is given, returns true if operation is completed successfully, false otherwise
 * 
 * @return bool 
 */
bool FLIPFLOP::Run(){
    bool successful = variableCount == 2;

    if(successful){                         // Exactly 2 variables needed
        if(variables[1]->GetValue())        // If variable value is true (1)
            output = !output;               // Flip output value

        *variables[0] = output;             // Set first variable to output
    }

    return successful;
}



/*=====DECODER=====*/

/**
 * @brief Encoder operation class
 * 
 */
class DECODER : public Operation{
    public:
        // See function implementations below for further explanation

        DECODER();  // Constructor

        virtual bool Run(); // Runs the operation
    private:
};

/**
 * @brief Construct a new DECODER object
 * 
 */
DECODER::DECODER()
{
    // blank
}

/**
 * @brief Decodes given inputs and sets true (1) corresponding output, returns if operation completed successfully, false otherwise
 * 
 * @return bool
 * 
 * @details 
 * This assignment only needs decoder with 4 outputs and 2 inputs,
 * but I wrote the function more generalized so that decoder would work
 * for any number of inputs
 * 
 * Number of variables that are written after DECODER opcode is known,
 * and we also know for n many input 2^n many output is needed, thus we
 * can calculate number of inputs and separate inputs and outputs
 * 
 * n: number of input variables     x: number of total variables
 *  n + 2^n = x
 *  2^n = x - n
 *  n = log2(x - n) = log2(x * (1 - n/x)) = log2(x) + log2(1 - n/x)
 *  n >= 1  ->  x = n + 2^n >= 3  ->  n/x =< 1/3  ->  1 - n/x >= 2/3 > 1/2  ->  log2(1 - n/x) >= log2(2/3) > log2(1/2)  ->  log2(1 - n/x) > -1
 *  
 * knowing n is a whole number means log2(x) + log2(1 - n/x) is also a whole number and log2(1 - n/x) being greater than -1 (and lesser than 0)
 * means we can calculate n by getting floor of log2(x)
 */
bool DECODER::Run(){
    bool successful = false;

    int inputCount = log2Floor(variableCount);      // Number of input variables
    int outputCount = variableCount - inputCount;   // Number of output variables

    successful = (1 << inputCount) == outputCount;

    if(successful){  // If number of outputs is equal to two to the number of inputs 
        int outputIndex = 0;    // Corresponding output variable's index

        /**
         * @brief Evaluating index of output variable
         * 
         * @details 
         * The corresponding output is at index that is decimal equivalent to
         * given binary integer in form of inputs, so basically converts total input
         * to decimal
         */
        for(int i = outputCount; i < variableCount; ++i)
            outputIndex = (outputIndex << 1) | variables[i]->GetValue();

        // Assigning variable at correct index 
        *variables[outputIndex] = true;
    }

    return successful;
}



/*=====PROGRAM=====*/

/**
 * @brief Program class
 * 
 * @details 
 * Basically the interpreter class of this assignment's programming/circuit language,
 * that stores variables and operations and can be run many times
 */
class Program{
    public:
        // See function implementations below for further explanation

        Program();  // Main constructor
        
        // Constructor for each stream/file stream combination
        Program(ifstream &instructionFile, ifstream &_input, ofstream &_output);    
        Program(ifstream &instructionFile, istream &_input, ofstream &_output);
        Program(ifstream &instructionFile, ifstream &_input, ostream &_output);
        Program(ifstream &instructionFile, istream &_input, ostream &_output);
        ~Program(); // Destructor

        Variable * GetVariable(string name);            // Returns variable with given name

        void SetInstruction(ifstream &instructionFile); // Set operations (and variables) of program
        void SetInput(ifstream &_input);                // Set input stream
        void SetInput(istream &_input);                 // Set input (file) stream
        void SetOutput(ofstream &_output);              // Set output stream
        void SetOutput(ostream &_output);               // Set output (file) stream

        bool Run();                                     // Runs the program
    private:
        void ResizeOperationArray(int newSize); // Resizes operation (pointer) array
        void ResizeVariableArray(int newSize);  // Resizes variable (pointer) array
        void ResizeOutputArray(int newSize);    // Resizes output variable (pointer) array

        void Clean();               // Cleans every array
        void CleanOperationArray(); // Cleans operation array
        void CleanVariableArray();  // Cleans variable array
        void CleanOutputArray();    // Cleans output variable array

        istream *input;             // Input stream
        ifstream *inputFile;        // Input file stram
        ostream *output;            // Output stream     
        ofstream *outputFile;       // Output file stram

        Variable **variables;       // Variable pointer array
        Variable **outputVariables; // Output variable pointer array
        Operation **operations;     // Operation pointer array
        int variableCount;          // Number of variables
        int outputVariableCount;    // Number of output variables
        int operationCount;         // Number of operations
};

/**
 * @brief Construct a new blank Program object
 * 
 */
Program::Program() : input(nullptr), inputFile(nullptr), output(nullptr), outputFile(nullptr),
                     variables(nullptr), outputVariables(nullptr), operations(nullptr),
                     variableCount(0), outputVariableCount(0), operationCount(0)
{
    // blank
}

/**
 * @brief Construct a new Program object with instructions specified in given file
 * 
 * @param instructionFile 
 * @param _input 
 * @param _output 
 */
Program::Program(ifstream &instructionFile, ifstream &_input, ofstream &_output) 
                : input(nullptr), inputFile(&_input), output(nullptr), outputFile(&_output),
                  variables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

/**
 * @brief Construct a new Program object with instructions specified in given file
 * 
 * @param instructionFile 
 * @param _input 
 * @param _output 
 */
Program::Program(ifstream &instructionFile, istream &_input, ofstream &_output) 
                : input(&_input), inputFile(nullptr), output(nullptr), outputFile(&_output),
                  variables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

/**
 * @brief Construct a new Program object with instructions specified in given file
 * 
 * @param instructionFile 
 * @param _input 
 * @param _output 
 */
Program::Program(ifstream &instructionFile, ifstream &_input, ostream &_output) 
                : input(nullptr), inputFile(&_input), output(&_output), outputFile(nullptr),
                  variables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

/**
 * @brief Construct a new Program object with instructions specified in given file
 * 
 * @param instructionFile 
 * @param _input 
 * @param _output 
 */
Program::Program(ifstream &instructionFile, istream &_input, ostream &_output) 
                : input(&_input), inputFile(nullptr), output(&_output), outputFile(nullptr),
                  variables(nullptr), outputVariables(nullptr), operations(nullptr),
                  variableCount(0), outputVariableCount(0), operationCount(0)
{
    SetInstruction(instructionFile);
}

/**
 * @brief Destroy the Program object
 * 
 */
Program::~Program()
{
    Clean();
}

/**
 * @brief Returns pointer to the variable with given name
 * 
 * @param name 
 * @return Variable* 
 */
Variable * Program::GetVariable(string name){
    for(int i = 0; i < variableCount; ++i)
        if(variables[i]->GetName() == name)
            return variables[i];
    return nullptr;
}

/**
 * @brief Compile/set instructions in given file (stream)
 * 
 * @param instructionFile 
 */
void Program::SetInstruction(ifstream &instructionFile){
    Clean();    // Deallocate former operations and variables
    string readWord, lastOperationName{};

    // Until instruction file is fully read
    while(instructionFile >> readWord){

        // Check read word and add corresponding operation
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

        // If read word is not an opcode
        else{
            Variable *newVariable = GetVariable(readWord);  // Get variable with read word as name
            
            if(newVariable == nullptr){                     // If no such variable is found
                ResizeVariableArray(variableCount + 1);     // Increase variable array size
                newVariable = new Variable(readWord);       // Create new variable
                variables[variableCount - 1] = newVariable; // Add new variable
            }

            operations[operationCount - 1]->AddVariable(newVariable);   // Read variable is linked to operation that is written
                                                                        // before it, so add there too

            /**
             * @brief Special case for operation OUTPUT
             * 
             * @details 
             * OUTPUT operation does nothing but only indicates that variables should
             * be printed when program ends running, this cannot be achieved by using
             * its Run function, since it may come before end of the program and print
             * variables before the program ends, so that's handled here
             */
            if(lastOperationName == "OUTPUT"){          
                ResizeOutputArray(outputVariableCount + 1);             // Increase output variable array size
                outputVariables[outputVariableCount - 1] = newVariable; // Add new variable 
            }

            continue;   // Don't get outside of this block and reach to line 903
                        // otherwise variable name will be kept as operation name
                        // for next iterations
        }

        lastOperationName = readWord;   // Keep last read operation name to handle OUTPUT operation
    }
}

/**
 * @brief Set input of program
 * 
 * @param _input 
 */
void Program::SetInput(ifstream &_input){
    input = nullptr;
    inputFile = &_input;
}

/**
 * @brief Set input of program
 * 
 * @param _input 
 */
void Program::SetInput(istream &_input){
    inputFile = nullptr;
    input = &_input;
}

/**
 * @brief Set output of program
 * 
 * @param _input 
 */
void Program::SetOutput(ofstream &_output){
    output = nullptr;
    outputFile = &_output;
}

/**
 * @brief Set output of program
 * 
 * @param _input 
 */
void Program::SetOutput(ostream &_output){
    outputFile = nullptr;
    output = &_output;
}

/**
 * @brief Runs the program, returns true if program ran successfully, false otherwise
 * 
 * @return bool 
 */
bool Program::Run(){
    bool successful = true; // Is program run completed successfully

    // Run each operation
    for(int i = 0; i < operationCount && successful; ++i)
        successful = successful && operations[i]->Run();

    // If any operation failed terminate the program
    if(!successful) return successful;

    // Output stream is favored
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

    // Reset variables for the next run
    for(int i = 0; i < variableCount; ++i)
        variables[i]->SetValue(false);
    
    return successful;
}

/**
 * @brief Resizes operation array
 * 
 * @param newSize 
 */
void Program::ResizeOperationArray(int newSize){
    Operation **newOperations = new Operation*[newSize]{};  // Allocate new operation pointer array

    // Copy former operation addresses
    if(newSize > operationCount)
        for(int i = 0; i < operationCount; ++i)
            newOperations[i] = operations[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newOperations[i] = operations[i];
        
        // If new size is lesser than before deallocate leftover operations
        for(int i = newSize; i < operationCount; ++i){
            delete operations[i];
            operations[i] = nullptr;
        }
    }

    delete [] operations;       // Deallocate old pointer array
    operations = newOperations; // Update array
    operationCount = newSize;   // Update size
}

void Program::ResizeVariableArray(int newSize){
    Variable **newVariables = new Variable*[newSize]{}; // Allocate new variable pointer array

    // Copy former variable addresses
    if(newSize > variableCount)
        for(int i = 0; i < variableCount; ++i)
            newVariables[i] = variables[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newVariables[i] = variables[i];

        // If new size is lesser than before deallocate leftover variables
        for(int i = newSize; i < variableCount; ++i){
            delete variables[i];
            variables[i] = nullptr;
        }
    }

    delete [] variables;        // Deallocate old variable array
    variables = newVariables;   // Update array
    variableCount = newSize;    // Update size
}

void Program::ResizeOutputArray(int newSize){
    Variable **newOutputVariables = new Variable*[newSize]{};   // Allocate new output variable pointer array

    // Copy former output variable addresses
    if(newSize > outputVariableCount)
        for(int i = 0; i < outputVariableCount; ++i)
            newOutputVariables[i] = outputVariables[i];
    else{
        for(int i = 0; i < newSize; ++i)
            newOutputVariables[i] = outputVariables[i];

        // If new size is lesser than before deallocate leftover output variables
        for(int i = newSize; i < outputVariableCount; ++i){
            delete outputVariables[i];
            outputVariables[i] = nullptr;
        }
    }

    delete [] outputVariables;              // Deallocate old output variable array
    outputVariables = newOutputVariables;   // Update array
    outputVariableCount = newSize;          // Update size
}

/**
 * @brief Cleans program operations and variables
 * 
 */
void Program::Clean(){
    CleanOperationArray();      // Clean operations
    CleanVariableArray();       // Clean variables
    
    // Clean only the output variable pointer array since it had the addresses 
    // of the same variables that were also in variable pointer array
    delete [] outputVariables;
    outputVariables = nullptr;
    outputVariableCount = 0;
}

/**
 * @brief Clean operation array
 * 
 */
void Program::CleanOperationArray(){
    for(int i = 0; i < operationCount; ++i){
        delete operations[i];
        operations[i] = nullptr;
    }
    delete [] operations;
    operations = nullptr;
    operationCount = 0;
}

/**
 * @brief Clean variable array
 * 
 */
void Program::CleanVariableArray(){
    for(int i = 0; i < variableCount; ++i){
        delete variables[i];
        variables[i] = nullptr;
    }
    delete [] variables;
    variables = nullptr;
    variableCount = 0;
}

/**
 * @brief Clean output variable array
 * 
 */
void Program::CleanOutputArray(){
    for(int i = 0; i < outputVariableCount; ++i){
        delete outputVariables[i];
        outputVariables[i] = nullptr;
    }
    delete [] outputVariables;
    outputVariables = nullptr;
    outputVariableCount = 0;
}



int main(){
    
    ifstream circuitFile("circuit.txt");    // Instructions file
    ifstream inputFile("input.txt");        // Input file

    // Initialize program
    Program myProgram(circuitFile, inputFile, std::cout);
    
    // Until all input values are evaluated through program
    while(!inputFile.eof())
        myProgram.Run();    // Run program
    
    // Close files
    circuitFile.close();
    inputFile.close();

    return 0;
}
