#include <iostream>
#include <vector>

// Prints elements of vector one after another with one space in between
void PrintVector(std::vector<int> v){
	for(int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
}


int main(){
	std::vector<int> suitors; // Initialize suitor vector

	// Get number of suitors
	unsigned int n;  
	std::cout << "Enter number of suitors: ";
	std::cin >> n;
	
	// Ready the vector
	for(unsigned int i = 0; i < n;)
		suitors.push_back(++i);

	// Print first state of the suitors
	PrintVector(suitors); std::cout << "\tinitial list of suitors, start counting from 1\n";

	// Start from 3rd suitor and increase index 2 each time, get mod of it by the vector size to get in bound if it's not
	// Go on until only one suitor is left
	for(unsigned int i = 2; 1 < suitors.size(); i = (i + 2) % suitors.size()){
		int eliminated = suitors[i]; // Store eliminated suitor number to print later
			
		suitors.erase(suitors.begin() + i); // Erase eliminated suitor

		// Print current status of suitors
		if(suitors.size() != 1){
			PrintVector(suitors); std::cout << "\tsuitor " << eliminated << " eliminated, continue counting from " << suitors[i%suitors.size()] << std::endl;
		}
		else{
			PrintVector(suitors); std::cout << "\tsuitor " << eliminated << " eliminated, " << suitors[0] << " is the lucky winner\n";
		}
	}
}
