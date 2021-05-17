#ifndef TEAM_H_
#define TEAM_H_
#include <iostream>
#include <iomanip>

class Team {
	friend std::ostream& operator<< (std::ostream& os, const Team& S);
public:
	Team();
	Team(const Team& S);
	Team(std::string name, int id);
	void operator=(const Team& S);
	bool compare(Team S);
	virtual ~Team();
  std::string name;
  int id;
  int played;
  int wins;
  int draws;
  int loses;
  int goalsfor;
  int goalsagainst;
  int goaldiff;
  int points;
};

#endif
