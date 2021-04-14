#include <iostream>
#include <cstdlib>
#include <ctime>

// Game related constants.
const int WIN_SCORE = 100;
const int COMP_ROUND_SCORE_LIMIT = 20;
const int LOSE_ROLL = 1;

int rollDie();
int humanTurn(int humanTotalScore);
int computerTurn(int computerTotalScore);


int main(){

    // Set random seed.
    srand(time(0));

    int humanTotalScore = 0;
    int computerTotalScore = 0;

    bool gameOver = false;

    // Continue the game until it's set to be over.
    while(!gameOver){

        // player starts first.
        humanTotalScore += humanTurn(humanTotalScore);

        // Check if player won. If so congratulate and set game to be over.
        if(humanTotalScore >= WIN_SCORE){
            std::cout << "You won!\n";
            gameOver = true;
        }
        else{ // If player didn't win yet, play computer's turn.
            computerTotalScore += computerTurn(computerTotalScore);
            
            // Check if computer won. If so inform the player and set game to be over.
            if(computerTotalScore >= WIN_SCORE){
                std::cout << "Computer won!\n";
                gameOver = true;
            }
        }
    }
    
    return 0;
}


// Returns a random number between 1-6.
int rollDie(){
    return rand() % 6 + 1;
}


// Play player's turn.
// Returns gained score this turn.
int humanTurn(int humanTotalScore){

    int roundScore = 0;
    int roll = 0;

    // Set to be an arbitrary char to prevent any random chance for loop to not execute.
    char userInput = ' ';

    // Until player enters 'h' or wins continue the loop.
    while(userInput != 'h' && humanTotalScore + roundScore < WIN_SCORE){

        // Print different texts if player is yet to roll for the first time this round.
        if(!roll) std::cout << "It's your turn! Enter 'r' to roll the dice.\n";
        else      std::cout << "Enter 'r' to roll again or 'h' to hold.\n";

        std::cin >> userInput;

        // If player enters 'r' roll the dice and proceed depending on the outcome.
        if(userInput == 'r'){
            
            roll = rollDie();

            // If player rolls unlucky, inform the player they lost their turn and quit the loop. 
            if(roll == LOSE_ROLL){
                roundScore = 0; // Reset gained score.

                std::cout << "You lost your turn! Press 'c' to continue.\n";
                std::cin >> userInput;

                break;
            }
            else{ // If player rolls any other number add it to this turn's score and inform the player.
                roundScore += roll;

                std::cout << "Your score this round is: " << roundScore
                          << "\nIf you hold, your total score will be: " << humanTotalScore + roundScore << std::endl;
            }
        }
    }


    return roundScore;    
}


// Play the computer's turn.
// Returns computer's gained score.
int computerTurn(int computerTotalScore){

    int roundScore = 0;
    int roll = 0;

    char userInput;

    // Continue unless computer exceeds its round score limit or total score limit.
    while(roundScore < COMP_ROUND_SCORE_LIMIT && roundScore + computerTotalScore < WIN_SCORE){
        
        roll = rollDie();
        
        // If computer rolls unlucky, inform the player and quit the loop.
        if(roll == LOSE_ROLL){
            roundScore = 0; // Reset gained score.

            std::cout << "The computer loses its turn! Enter 'c' to continue.\n";
            std::cin >> userInput;

            break;
        }
        else{ // If any other number is rolled add it to turn's score and inform the player.
            roundScore += roll;

            std::cout << "The computer's score this round is: " << roundScore
                      << ".\nIf the computer holds, its total score will be: " << computerTotalScore + roundScore << std::endl; 
        }

    }

    // If computer holds, since didn't lose its turn it has some score gained, inform the user.
    if(roundScore){
        std::cout << "The computer holds. Enter 'c' to continue.\n";
        std::cin >> userInput;
    }

    return roundScore;
}