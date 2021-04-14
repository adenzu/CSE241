#include <iostream>
#include <cstdlib>
#include <ctime>



// 10,000 duels will be played
const int NUM_OF_DUELS = 1e4;   // Number of duels will be played


/* @brief   Handles a whole duel, updates number of won duels of participants: Aaron, Bob, and Charlie
 * @param   aaronWinCount   Number of duels Aaron has won
 * @param   bobWinCoun      Number of duels Bob has won
 * @param   charlieWinCount Number of duels Charlie has won
 */
void PlayDuel(int &aaronWinCount, int &bobWinCount, int &charlieWinCount);

/* @brief   Handles Aaron's turn. Executes only if Aaron is alive, updates Charlie's or Bob's state if either one is shot by Aaron
 * @param   aaronAlive      Aaron's state of being alive
 * @param   bobAlive        Bob's state of being alive
 * @param   charlieAlive    Charlie's state of being alive
 */
void AaronShoot(bool aaronAlive, bool &bobAlive, bool &charlieAlive);

/* @brief   Handles Bob's turn. Executes only if Bob is alive, updates Charlie's or Aaron's state if either one is shot by Bob
 * @param   aaronAlive      Aaron's state of being alive
 * @param   bobAlive        Bob's state of being alive
 * @param   charlieAlive    Charlie's state of being alive
 */
void BobShoot(bool &aaronAlive, bool bobAlive, bool &charlieAlive);

/* @brief   Handles Charlie's turn. Executes only if Charlie is alive, updates Bob's or Aaron's state if either one is shot by Charlie
 * @param   aaronAlive      Aaron's state of being alive
 * @param   bobAlive        Bob's state of being alive
 * @param   charlieAlive    Charlie's state of being alive
 */
void CharlieShoot(bool &aaronAlive, bool &bobAlive, bool charlieAlive);


int main(){

    // Set random seed
    srand(time(0));

    // Each set to 0 since no duel is played yet
    int aaronWinCount = 0;      // Number of duels Aaron has won
    int bobWinCount = 0;        // Number of duels Bob has won
    int charlieWinCount = 0;    // Number of duels Charlie has won

    // Play NUM_OF_DUELS number of duels
    for(int roundNum = 0; roundNum < NUM_OF_DUELS; ++roundNum){
        PlayDuel(aaronWinCount, bobWinCount, charlieWinCount);  // Initiate duel
    }

    // Inform the user about the results
    std::cout << "Aaron won " << aaronWinCount << "/" << NUM_OF_DUELS << " duels or " << aaronWinCount / static_cast<double>(NUM_OF_DUELS) * 100 << "%\n"
              << "Bob won " << bobWinCount << "/" << NUM_OF_DUELS << " duels or " << bobWinCount / static_cast<double>(NUM_OF_DUELS) * 100 << "%\n"
              << "Charlie won " << charlieWinCount << "/" << NUM_OF_DUELS << " duels or " << charlieWinCount / static_cast<double>(NUM_OF_DUELS) * 100 << "%\n";


    return 0;
}


void PlayDuel(int &aaronWinCount, int &bobWinCount, int &charlieWinCount){

    // Each set to true since duel hasn't started yet
    bool aaronAlive = true;     // Aaron's state of being alive
    bool bobAlive = true;       // Bob's state of being alive
    bool charlieAlive = true;   // Charlie's state of being alive

    do{
        AaronShoot(aaronAlive, bobAlive, charlieAlive);     // Play Aaron's turn
        BobShoot(aaronAlive, bobAlive, charlieAlive);       // Play Bob's turn
        CharlieShoot(aaronAlive, bobAlive, charlieAlive);   // Play Charlie's turn
    }while( (aaronAlive && bobAlive) || (aaronAlive && charlieAlive) || (bobAlive && charlieAlive) );   // Go on as long as two of them are still alive

    // Increase number of won duels of the last man standing
    if(charlieAlive) ++charlieWinCount; 
    else if(bobAlive) ++bobWinCount; 
    else if(aaronAlive) ++aaronWinCount; 

}

void AaronShoot(bool aaronAlive, bool &bobAlive, bool &charlieAlive){

    // If Aaron is no longer with us, terminate the process
    if(!aaronAlive) return;

    // % 3 since Aaron has a 1/3 chance to shoot successfully 
    bool successfullShot = !(rand() % 3);   // Is shot successful

    if(successfullShot){
        if(charlieAlive) charlieAlive = false;  // Kill Charlie first if he's alive,
        else bobAlive = false;                  // kill Bob otherwise
        // Doesn't check if Bob is alive or not, for optimization purposes
    }
}

void BobShoot(bool &aaronAlive, bool bobAlive, bool &charlieAlive){
    
    // If Bob is no longer with us, terminate the process
    if(!bobAlive) return;

    // % 2 since Bob has a 1/2 chance to shoot successfully 
    bool successfullShot = !(rand() % 2);   // Is shot successful

    if(successfullShot){
        if(charlieAlive) charlieAlive = false;  // Kill Charlie first if he's alive,
        else aaronAlive = false;                // kill Aaron otherwise
        // Doesn't check if Aaron is alive or not, for optimization purposes
    }
}

void CharlieShoot(bool &aaronAlive, bool &bobAlive, bool charlieAlive){
    
    // If Charlie is no longer with us, terminate the process
    if(!charlieAlive) return;

    // Charlie never misses, no need to check if he missed

    if(bobAlive) bobAlive = false;  // Kill Bob if he's alive,
    else aaronAlive = false;        // kill Aaron otherwise
    // Doesn't check if Aaron is alive or not, for optimization purposes
}