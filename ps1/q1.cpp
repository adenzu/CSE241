#include <iostream>

// Numbers between START_NUMBER and END_NUMBER will be checked, START_NUMBER included.
const int START_NUMBER = 3;
const int END_NUMBER   = 100;


int main(){

    bool isPrime;

    // Number check loop.
    for (int currNum = START_NUMBER; currNum < END_NUMBER; ++currNum){

        isPrime = true; // Set prime boolean to true as default.

        // Number divisor check loop. Checks if the current number divisable starting from 2 to half of the checked number.
        for (int currDivisor = 2; currDivisor <= currNum / 2; ++currDivisor){

            // If it's divisable set prime boolean to false and quit loop.
            if(!(currNum % currDivisor)){
                isPrime = false;
                break;
            }
        }

        // Inform the user if current number is prime.
        if(isPrime) std::cout << currNum << " is a prime number.\n";
        
    }
    
    return 0;   
}