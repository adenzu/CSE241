#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>


const char * RANDOM_GEN_ARG = "-r"; // Argument for computer to generate secret number.
const char * USER_ENTER_ARG = "-u"; // Argument for computer to set secret number to given number.
const int MAX_ITERATION = 100;      // Iteration limit, once exceeded game will stop, user will be informed that they failed.

/* @brief   Handles all the input and output and game rules, basically main function of the game.
 * @param   secretNum   The number that user tries to find. 
 */
void PlayMastermind(long long secretNum);

/* @brief   Generates a random valid secret number for the game to user to find it.
 * @param   digitCount  Number of digits the generated secret number should have.
 * @return              Generated valid secret number.
 */
long long GenerateSecretNum(int digitCount);

/* @brief   Generates and returns a random integer between 0 and given number, 0 being included given number being excluded.
 * @param   upper   Upper limit of the newly generated random number.
 * @return          A random integer between 0 and upper.
 */
int RandomRange(int upper);

/* @brief   Generates and returns a random integer between given numbers, first given number being included second one being excluded.
 * @param   lower   Lower limit of the newly generated random number.
 * @param   upper   Upper limit of the newly generated random number.
 * @return          A random integer between lower and upper.
 */
int RandomRange(int lower, int upper);

/* @brief   Converts any non-negative number in char array form to integer. And returns the result.
 * @param   chArr   The char array that is only and only consisted of numerals.
 * @return          Integer equivalent of the given number (in char array form).
 */
int ConvertToInt(char * chArr);

/* @brief   Counts the number of digits there are in given number.
 * @param   number  The given number whose number digits will be counted.
 * @return          Number of digits of the number.
 */
int GetDigitCount(long long number);

/* @brief   Returns the digit number at given index of given number.
 * @param   number  The number whose digit number will be returned.
 * @param   index   Index of the wanted digit number. Being counted from rightmost digit and starting from 0.
 * @return          Digit number of the number at index.
 */
int GetDigit(long long number, int index);

/* @brief   Counts and returns number of same digits in given numbers, by place and value.
 * @param   number      The first given number to be checked.
 * @param   userGuess   The second given number to be checked.
 * @return              Number of same digits in given numbers.
 */
int GetExactDigits(long long number, long long userGuess);

/* @brief   Counts and returns number of digits that both given numbers have but in different places.
 * @param   number      The first given number to be checked.
 * @param   userGuess   The second given number to be checked.
 * @return              Number of same digits in different places in given numbers.
 */
int GetMisplacedDigits(long long number, long long userGuess);

/* @brief   Swaps two digits at given indexes in given number, then returns the result.
 *          Indexes are from rightmost and starting with 0.
 * @param   number      The number that the process will be done on.
 * @param   digitIndex1 The index of the first digit that will be swapped.
 * @param   digitIndex2 The index of the second digit that will be swapped.
 * @return              Resulting number after the swap. 
 */
long long SwapDigits(long long number, int digitIndex1, int digitIndex2);

/* @brief   Checks if given char is a number (0-9).
 * @param   ch  The char that will be checked. 
 * @return      True if char is number, false if otherwise.
 */
bool IsNumber(char ch);

/* @brief   Checks if given char array has a composition that resembles a positive number.
 * @param   chArr   The char array that will be checked.
 * @return          True if so, false otherwise.
 */
bool IsPosNumber(char * chArr);

/* @brief   Takes a number and calculates and returns its nth power.
 * @param   number  Base number.
 * @param   n       Power of the number.
 * @return          Result of nth power of val.
 */
long long PowInt(int number, int n);


int main(int argc, char** argv){
    
    // If number of given arguments are not exactly 3, print error code 'E0' and proceed to terminate.
    if(argc != 3){
        std::cout << "E0\n";
    }
    else{

        // If user enters '-r' and given number is less than 10 and given number is a positive number.
        if(!strcmp(argv[1], RANDOM_GEN_ARG) && argv[2][1] == '\0' && IsPosNumber(argv[2])){

            srand(time(0)); // Set random seed.

            // Generated secret number for user to find.
            long long secretNumber = GenerateSecretNum(ConvertToInt(argv[2]));

            // Start the game.
            PlayMastermind(secretNumber);
        }
        /* Else if user enters '-u' and given number is positive and given number's digits are unique.
         *
         *      GetMisplacedDigits() function is used here to check if digits of the number are unique, because
         *      if any digit repeats, function will count it as if first of the appearences is found elsewhere in
         *      the number.
         *      
         *      Ex:
         *          2021    2021
         *          a       b c
         *
         *      a and b are at same index so it's not counted but a and c are both two (2) and at different indexes so counts that,
         *      thus it returns a positive number (2 in this case) and results in false (!2 -> false).
         */

        else if(!strcmp(argv[1], USER_ENTER_ARG) && IsPosNumber(argv[2]) && !GetMisplacedDigits(ConvertToInt(argv[2]), ConvertToInt(argv[2]))){
            // Start the game.
            PlayMastermind(ConvertToInt(argv[2]));
        }
        // If neither case happens there has to be an error so print 'E0' and proceed to terminate.
        else{
            std::cout << "E0\n";
        }
    }

    return 0;
}



void PlayMastermind(long long secretNum){

    // Input variable for the user's guesses.
    long long userGuess;

    // Number of digits of the secret number.
    int digitCount = GetDigitCount(secretNum);

    // Continue the game until the set limit.
    for(int i = 1; i < MAX_ITERATION; ++i){

        // Get user guess.
        std::cin >> userGuess;

        // If user doesn't enter a proper integer.
        if(std::cin.fail()){
            std::cout << "E2\n";    // Print the error message.
            return;                 // Terminate.
        }
        // Else if number of digits are not matched or user guess is not valid.
        else if(GetDigitCount(userGuess) != digitCount || GetMisplacedDigits(userGuess, userGuess)){
            std::cout << "E1\n";    // Print the error message.
            return;                 // Terminate.
        }
        // Else if user guesses the number correctly.
        else if(secretNum == userGuess){
            std::cout << "FOUND " << i << std::endl;    // Inform the user that they won.
            return;                                     // Terminate.
        }
        // If neither happens thus user guesses incorrect. 
        else
            std::cout << GetExactDigits(secretNum, userGuess) << " " << GetMisplacedDigits(secretNum, userGuess) << std::endl;  // Inform them.
    }

    // Prints when loop ends by the iteration count.
    std::cout << "FAILED\n";
}

long long GenerateSecretNum(int digitCount){

    // New generated secret number. Has every number as digit initially.
    long long newSecretNum = 1234567890;

    // Shuffles the secret number's digits by randomly selecting index for digits to be swapped.
    // Loop starts at index 1 to prevent digit 0 being randomly swapped with the leftmost place. 
    for(int i = 1; i < 10; ++i){

        // Swap the digit at index i with the digit at a random index between i-9.
        newSecretNum = SwapDigits(newSecretNum, i, RandomRange(i, 10));
    }

    // Lastly swap digit 0 with a random digit that is not at leftmost. 
    newSecretNum = SwapDigits(newSecretNum, 0, RandomRange(9));

    // Returns only the first digitCount many digits (starting from leftmost side).
    return newSecretNum / PowInt(10, 10 - digitCount);
}

int RandomRange(int upper){
    return RandomRange(0, upper);   // Using overloading.
}

int RandomRange(int lower, int upper){

    // Takes a random integer then takes mod to get it in range of the difference
    // then adds lower to get it in range of the limits.
    return rand() % (upper - lower) + lower;    
}

int ConvertToInt(char * chArr){

    // Result integer of the convertion.
    int result = 0;

    // Takes every char one by one and substracts 48 from it's ASCII value to get corresponding integer.
    // Multiplies the result integer by 10 each step to slide the digits to left.
    // 48 is substracted because char '0' has an ASCII value that is 48; thus '0' - 48 is 0.
    for(int i = 0; chArr[i] != '\0'; ++i) result = result * 10 + chArr[i] - 48;

    return result;
}

int GetDigitCount(long long number){

    // Number of digits in number.
    int digitCount = 1;

    // Divide number by 10 each step until it hits to 0, add 1 to digitCount each step. 
    while(number /= 10) ++digitCount;

    return digitCount;
}

int GetDigit(long long number, int index){

    // Divide number by 10 index times to get the digit at given index to rightmost.
    while(index--) number /= 10;

    // Then return the digit by mod 10.
    return number % 10;
}

int GetExactDigits(long long number, long long userGuess){

    // Number of exact digits.
    int exactDigitNum = 0;
    
    // Go on as long as neither number is zero.
    while(number && userGuess){

        // Check if digits are the same, if so add 1 to exactDigitNum.
        if(number % 10 == userGuess % 10) ++exactDigitNum;
        
        // Get to next digit by dividing to 10.
        number /= 10;
        userGuess /= 10;
    }

    return exactDigitNum;
}

int GetMisplacedDigits(long long number, long long userGuess){

    // Number of misplaced digits.
    int misplacedDigitNum = 0; 

    // Copy of the guess of the user. To prevent original one from changing.
    long long userGuessCopy = userGuess;

    // Loop until number hits to 0. i is the current digit's index.
    for(int i = 0; number; ++i){
        
        // Loop until user guess copy hits to 0. j is the current digit's index.
        for(int j = 0; userGuessCopy; ++j){

            // Check if digits check out and indexes are different.
            if(number % 10 == userGuessCopy % 10 && i != j){
                ++misplacedDigitNum;    // Increase by 1.
                break;                  // Exit the loop since current digit is found.
            }

            // Get to next digit.
            userGuessCopy /= 10;
        }
 
        // Get to next digit.
        number /= 10;

        // Ready copy for the next loop.
        userGuessCopy = userGuess;
    }

    return misplacedDigitNum;
}

long long SwapDigits(long long number, int digitIndex1, int digitIndex2){

    int digit1 =  GetDigit(number, digitIndex1);    // First digit to be swapped.
    int digit2 =  GetDigit(number, digitIndex2);    // Second digit to be swapped.

    long long digitFactor1 = PowInt(10, digitIndex1);   // Factor that when it's multiplied with digit1 results at index digitIndex1.
    long long digitFactor2 = PowInt(10, digitIndex2);   // Factor that when it's multiplied with digit2 results at index digitIndex2.

    /* swapped = number - (digit1 * digitFactor1) - (digit2 * digitFactor2) + (digit1 * digitFactor2) + (digit2 * digitFactor1)
     * swapped = number + digit1 * (digitFactor2 - digitFactor1) + digit2 * (digitFactor1 - digitFactor2)
     * swapped = number + digit1 * (digitFactor2 - digitFactor1) - digit2 * (digitFactor2 - digitFactor1)
     * swapped = number + (digit1 - digit2) * (digitFactor2 - digitFactor1)
     * 
     * Ex:    1203 - 2 * 100 = 1003,    1003 - 3 * 1 = 1000,    1000 + 3 * 100 = 1300,    1300 + 2 * 1 = 1302
     */
    return number + (digit1 - digit2) * (digitFactor2 - digitFactor1);
}

bool IsNumber(char ch){

    // 47 is one less than ASCII value of '0' and 58 is one more than ASCII value of '9'.
    if(47 < ch && ch < 58) return true;
    return false;
}

bool IsPosNumber(char * chArr){

    // 0 is not a positive number neither a positive number starts with 0. If given is then return false.
    if(chArr[0] == '0') return false;
    else{

        // Until end of char array is reached.
        for(int i = 0; chArr[i] != '\0'; ++i){
            if(!IsNumber(chArr[i])) return false;   // Check if current character is a number, if not return false immediately.
        }
        return true;    // Returns true since no exceptions are found.
    }
}

long long PowInt(int number, int n){
    long long result = 1;           // Result of the calculation.
    while(n--) result *= number;    // Multiply result with given number n times.
    return result;
}
