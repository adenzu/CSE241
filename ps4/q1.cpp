#include <iostream>



class HotDogStand{
    public:
        // initialized with zeros if arguments are not given
        HotDogStand(int _id = 0, unsigned int _soldCount = 0);

        void JustSold(); // Increases stand's sold hotdog count

        unsigned int GetSoldNumber() const;		// Returns number of hotdogs stand sold
        static unsigned int GetTotalSoldNumber();	// Returns total number of hotdogs sold
    private:
        int id;				
        unsigned int soldCount;             // unsigned since you can't sell negative many hotdogs
        static unsigned int totalSoldCount; // unsigned since you can't sell negative many hotdogs
};



int main(){

    // standC starts with 5 sold hotdogs, others are 0
    HotDogStand standA(1203, 0), standB(670, 0), standC(2021, 5);

    // Inform user about initial state of number of sold hotdogs
    std::cout << "Stand A sold " << standA.GetSoldNumber() << " hotdogs.\n"
              << "Stand B sold " << standB.GetSoldNumber() << " hotdogs.\n"
              << "Stand C sold " << standC.GetSoldNumber() << " hotdogs.\n" 
              << "In total " << HotDogStand::GetTotalSoldNumber() << " hotdogs were sold.\n\n";

    // For an arbitrary number of iteration
    for(int i = 0; i < 54; ++i){
        standA.JustSold();              // will sell 54 hotdogs
        if(!(i % 2)) standB.JustSold(); // will sell 27 hotdogs
        if(!(i % 3)) standC.JustSold(); // will sell 18 hotdogs
    }                                   // in total  99 new hotdogs were sold

    // Inform user about final state of number of sold hotdogs
    std::cout << "Stand A sold " << standA.GetSoldNumber() << " many hotdogs.\n"
              << "Stand B sold " << standB.GetSoldNumber() << " many hotdogs.\n"
              << "Stand C sold " << standC.GetSoldNumber() << " many hotdogs.\n"
              << "In total " << HotDogStand::GetTotalSoldNumber() << " hotdogs were sold.\n\n";

    return 0;
}


HotDogStand::HotDogStand(int _id, unsigned int _soldCount) : id(_id), soldCount(_soldCount) // set member variables
{
    totalSoldCount += soldCount;    // add member sold count to total sold count in case if it's other than zero
}

void HotDogStand::JustSold(){
    // increase both
    ++soldCount;        
    ++totalSoldCount;
}

unsigned int HotDogStand::GetSoldNumber() const{
    return soldCount;
}

unsigned int HotDogStand::GetTotalSoldNumber(){
    return totalSoldCount;
}

unsigned int HotDogStand::totalSoldCount = 0;
