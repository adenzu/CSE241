#include <iostream>



const int NUM_OF_MAX_DIGIT = 20; // Number of maximum digits will be stored and processed


/* @brief   Reads a large integer from user and stores it digit by digit in given array
 * @param   userInput   The integer array where read large integer will be stored
 */
void ReadLargeInt(int userInput[NUM_OF_MAX_DIGIT]);

/* @brief   Adds given two large integers and stores the result in other given array
 * @param   largeInt1   Array of first large integer to be added
 * @param   largeInt2   Array of second large integer to be added
 * @param   result      The array where result will be stored
 */
void AddLargeInts(const int largeInt1[NUM_OF_MAX_DIGIT], const int largeInt2[NUM_OF_MAX_DIGIT], int result[NUM_OF_MAX_DIGIT]);

/* @brief   Prints given array of a large integer
 * @param   largeInt    Array of a large integer
 */
void PrintLargeInt(const int largeInt[NUM_OF_MAX_DIGIT]);

/* @brief   Sets all elements of given array of large integer to zero (0)
 * @param   largeInt    The array of large integer that's elements will be set to zero
 */
void ResetLargeInt(int largeInt[NUM_OF_MAX_DIGIT]);



int main(){
    
    int largeInt1[NUM_OF_MAX_DIGIT];    // First read large integer 
    int largeInt2[NUM_OF_MAX_DIGIT];    // Second read large integer
    int result[NUM_OF_MAX_DIGIT];       // Result array to store calculation results

    int userInput;  // User input

    do{
        // Print menu
        std::cout << "1. Add two numbers\n"
                  << "0. Exit\n";

        // Get user input
        std::cin >> userInput;

        // If chooses to do addition
        if(userInput == 1){

            // Inform the user that there is limit to number of digits for integers
            std::cout << "Enter two integers with max " << NUM_OF_MAX_DIGIT << " digits:\n";
            
            // Reset integers to ready to new addition
            ResetLargeInt(largeInt1);
            ResetLargeInt(largeInt2);
            ResetLargeInt(result);

            // Get new integers
            ReadLargeInt(largeInt1);
            ReadLargeInt(largeInt2);

            // Add them
            AddLargeInts(largeInt1, largeInt2, result);
            
            // Print the result
            std::cout << "Result is:\n";
            PrintLargeInt(result);
            std::cout << std::endl;
        }
        // If enters any other number than one and zero, warn
        else if(userInput){
            std::cout << "Invalid input!\n";
        }
    }while(userInput);  // Go on as long as user enters 0

    return 0;
}


void ReadLargeInt(int userInput[NUM_OF_MAX_DIGIT]){
    
    char userInputString[NUM_OF_MAX_DIGIT]; // Where initial input is stored

    // Get integer by digits as characters
    std::cin >> userInputString;    

    // Until end of the input is reached
    for(int charIndex = 0; userInputString[charIndex]; ++charIndex){

        // Check if current character is non-numeric
        if(48 > userInputString[charIndex] || userInputString[charIndex] > 57){

            // Inform the user, reset given array and terminate the process
            std::cout << "Invalid input!\n";
            ResetLargeInt(userInput);
            break;
        }
        
        // Move digits of the integer one forth, to have a room to new one
        for(int digitIndex = charIndex; digitIndex; --digitIndex)
            userInput[digitIndex] = userInput[digitIndex - 1];
        
        // Store new digit
        userInput[0] = userInputString[charIndex] - '0';
    }
}

void AddLargeInts(const int largeInt1[NUM_OF_MAX_DIGIT], const int largeInt2[NUM_OF_MAX_DIGIT], int result[NUM_OF_MAX_DIGIT]){

    int carry = 0;      // Carry of the digit addition
    int digitSum = 0;   // Result of digit addition

    // For each digit
    for(int digitIndex = 0; digitIndex < NUM_OF_MAX_DIGIT; ++digitIndex){
        digitSum = largeInt1[digitIndex] + largeInt2[digitIndex];   // Sum the digits of given large integers
        result[digitIndex] = (digitSum + carry) % 10;               // Set the result digit
        carry = (digitSum + carry) / 10;                            // Set the carry
    }

    // If still have carry after the process, overflow occured
    if(carry)
        std::cout << "Integer overflow occured.\n"; // Inform the user
    
}

void PrintLargeInt(const int largeInt[NUM_OF_MAX_DIGIT]){

    bool encounteredPosNum = false; // If non-zero digit is encountered

    // Since digits are stored reverse, print process will be reverse
    for(int digitIndex = NUM_OF_MAX_DIGIT - 1; digitIndex + 1; --digitIndex){
        
        if(encounteredPosNum) std::cout << largeInt[digitIndex];    // If non-zero digit has encountered print current digit directly
        else if(largeInt[digitIndex]){                              // If non-zero digit hasn't encountered but current digit is one
            encounteredPosNum = true;           // Set that non-zero digit is encountered
            std::cout << largeInt[digitIndex];  // Print current digit
        }
        // Else if non-zero digit is yet to be seen and current digit is 0 likewise, then don't print
        // Ex:
        //      [3, 2, 0, 1, 0, 0, 0], the right-most zeros are not printed, printed integer: 1203
    }
}

void ResetLargeInt(int largeInt[NUM_OF_MAX_DIGIT]){
    // Set every element to 0 starting from index 0 until the last one
    for(int digitIndex = 0; digitIndex < NUM_OF_MAX_DIGIT; ++digitIndex)
        largeInt[digitIndex] = 0;
}