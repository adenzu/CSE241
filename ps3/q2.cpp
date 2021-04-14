#include <iostream>


// Class consisting of numerator and denominator of a fraction 
class Fraction{
    public:
        /* @brief   Constructs member with given numerator and denominator numbers
         * @param   _numerator      Numerator
         * @param   _denominator    Denominator
         */
        Fraction(int _numerator, int _denominator);
        
        /* @brief   Change numerator of the fraction
         * @param   _numerator  Numerator
         */
        void SetNumerator(int _numerator);
        /* @brief   Change denominator of the fraction
         * @param   _denominator    Denominator
         */
        void SetDenominator(int _denominator);
        /* @brief   Change both the numerator and the denominator numbers of the fraction
         * @param   _numerator      Numerator
         * @param   _denominator    Denominator
         */
        void Set(int _numerator, int _denominator);

        /* @brief   Return floating point result of the fraction
         * @return  Floating point result of the freaction  
         */
        double GetDouble() const;
        // @brief   Prints reduced form of the fraction
        void PrintReduced();
    private:
        int numerator;      // Numerator of the fraction
        int denominator;    // Denominator of the fraction
        double result;      // Result of the fraction

        /* @brief   Finds and returns greatest common divisor of numerator and denominator of the fraction
         * @return  Greatest common divisor of numerator and denominator of the fraction
         */
        int GCD();
};



int main(){

    // Initialize a fraction
    Fraction a(35, 15);

    // Print reduced form and result
    std::cout << "Fraction "; a.PrintReduced(); std::cout << " is " << a.GetDouble() << std::endl;

    // Change numerator
    a.SetNumerator(1203);
    std::cout << "Fraction "; a.PrintReduced(); std::cout << " is " << a.GetDouble() << std::endl;  // Print reduced form and result
    
    // Change denominator
    a.SetDenominator(670);
    std::cout << "Fraction "; a.PrintReduced(); std::cout << " is " << a.GetDouble() << std::endl;  // Print reduced form and result
    
    return 0;
}



Fraction::Fraction(int _numerator, int _denominator){
    Set(_numerator, _denominator);  // Use Set func to set  
}

void Fraction::SetNumerator(int _numerator){
    Set(_numerator, denominator);  // Use Set func to set  
}

void Fraction::SetDenominator(int _denominator){
    Set(numerator, _denominator);  // Use Set func to set  
}

void Fraction::Set(int _numerator, int _denominator){
    numerator = _numerator;     
    denominator = _denominator;
    result = static_cast<double>(numerator) / denominator;  // Cast to double then do the division
                                                            // result is calculated only when variables are changed
                                                            // then stored thus it doesn't get calculated every
                                                            // time it needs to be got
}

double Fraction::GetDouble() const{
    return result;  // Return already calculated result
}

void Fraction::PrintReduced(){
    int gcd = GCD();    // gcd of numerator and denominator
    std::cout << numerator / gcd << "/" << denominator / gcd;  // Print reduced form   
}

int Fraction::GCD(){
    int numeratorC = numerator;     // copy of numerator
    int denominatorC = denominator; // copy of denominator

    // while none of them is zero
    while(numeratorC && denominatorC){
        if(numeratorC > denominatorC) numeratorC %= denominatorC;   // if numerator is greater than denominator
                                                                    // then set it to it's remainder of denominator
        else denominatorC %= numeratorC;    // vice versa
    }

    // one of them is zero always and the other is the greatest commond divisor
    // return the sum directly thus no check is needed which one is which
    return numeratorC + denominatorC;
}