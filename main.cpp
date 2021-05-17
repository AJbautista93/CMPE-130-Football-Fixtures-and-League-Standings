#include "Standing.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

int main() {
	Standing S;
	std::cout << "Choose action: " << std::endl;
	std::cout << "Type 1 if you want to create new tournament. " << std::endl;
	std::cout << "Type 2 if you want to update new results. " << std::endl;
	int choice;
	std::cin >> choice;

	if (choice == 1) {
		S.loadTournament("Tournament.txt");
		S.createFixture("Fixture.txt");
	} else if (choice == 2) {
		S.loadFixture("Fixture.txt");
    S.quickSort(0, S.Records.size() - 1);
    S.createStanding("Standing.txt");
	}
	return 0;
}
