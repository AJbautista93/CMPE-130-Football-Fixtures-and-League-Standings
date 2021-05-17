#ifndef STANDING_H_
#define STANDING_H_
#include "Team.h"
#include <vector>
#include <fstream>

class Standing {

public:
	Standing();
	void loadTournament(std::string filename);
  void createFixture(std::string filename);
  void loadFixture(std::string filename);
  void createStanding(std::string filename);
  void Analyze();
  int partition (int low, int high);
	void quickSort(int low, int high);
	virtual ~Standing();
  std::vector<std::string> Create;
  std::vector<Team> Records;
	std::vector<std::vector<int>> Results1;
  std::vector<std::vector<int>> Results2;
};

#endif /* STANDING_H_ */
