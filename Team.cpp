#include "Team.h"

Team::Team() {
	id = 0;
	name = "";
  played = 0;
  wins = 0;
  draws = 0;
  loses = 0;
  goalsfor = 0;
  goalsagainst = 0;
  goaldiff = 0;
  points = 0;
}

Team::Team(const Team& S) {
	this->name = S.name;
  this->id = S.id;
  this->played = S.played;
  this->wins = S.wins;
  this->draws = S.draws;
  this->loses = S.loses;
  this->goalsfor = S.goalsfor;
  this->goalsagainst = S.goalsagainst;
  this->goaldiff = S.goaldiff;
  this->points = S.points;
}

Team::Team(std::string name, int id) {
  this->id = id;
  this->name = name;
  played = 0;
  wins = 0;
  draws = 0;
  loses = 0;
  goalsfor = 0;
  goalsagainst = 0;
  goaldiff = 0;
  points = 0;
}

std::ostream& operator<< (std::ostream& os, const Team& S) {
  os << std::left;
	os << std::setw(20) << S.name << std::setw(4) << S.played << std::setw(4) << S.wins << std::setw(4) << S.draws << std::setw(4) << S.loses << std::setw(4) << S.goalsfor << std::setw(4) << S.goalsagainst << std::setw(4) << S.goaldiff << std::setw(4) << S.points;
	return os;
}

void Team::operator=(const Team& S) {
	this->name = S.name;
  this->id = S.id;
  this->played = S.played;
  this->wins = S.wins;
  this->draws = S.draws;
  this->loses = S.loses;
  this->goalsfor = S.goalsfor;
  this->goalsagainst = S.goalsagainst;
  this->goaldiff = S.goaldiff;
  this->points = S.points;
}

bool Team::compare(Team S) {
	if (this->points > S.points) {
		return true;
  } else if (this->points == S.points) {
    if (this->goaldiff > S.goaldiff) {
      return true;
    } else if (this->goaldiff == S.goaldiff) {
      if (this->goalsfor > S.goalsfor) {
      return true;
      }
    }
  }
	return false;
}

Team::~Team() {
}
