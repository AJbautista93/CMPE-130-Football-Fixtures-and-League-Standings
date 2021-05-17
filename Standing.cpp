#include "Standing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 

Standing::Standing() {
}

void Standing::loadTournament(std::string filename) {
	std::ifstream MyReadFile;
  std::string Text;
	MyReadFile.open(filename, std::ios::in);
	if (MyReadFile.is_open()) {
		while (getline(MyReadFile, Text))
			{
				Create.push_back(Text);
			}
	} else {
		std::cout << "There is no tournament list." << std::endl;
	}
	MyReadFile.close();
}

void Standing::createFixture(std::string filename) {
  std::ofstream MyWriteFile;
  MyWriteFile.open(filename, std::ios::out);

  MyWriteFile << "Number of teams: " + std::to_string(Create.size()) << std::endl;
  MyWriteFile << "List of teams: " << std::endl;
  for (int i = 0; i < Create.size(); i++) {
    MyWriteFile << Create[i] << std::endl;
  }
  MyWriteFile << std::endl;

  int teams = Create.size();
  int totalRounds = (teams - 1)*2;
  int matchesPerRound = teams / 2;
  int halfRoundMark = (totalRounds/2);
  std::string rounds[totalRounds][matchesPerRound];
  std::string roundString;

  for (int round = 0; round < totalRounds; round++) {
    for (int match = 0; match < matchesPerRound; match++) {
      int home = (round + match) % (teams - 1);
      int away = (teams - 1 - match + round) % (teams - 1);

      if (match == 0) {
        away = teams - 1;
      }

      std::string HvA = Create[home] + " - " + Create[away];
      std::string AvH = Create[away] + " - " + Create[home];
      
      if (((round < halfRoundMark) && (match % 3 == 0)) || ((round >= halfRoundMark) && (match % 3 != 0))) {
        roundString = HvA;
      } else if (((round < halfRoundMark) && (match % 3 != 0)) || ((round >= halfRoundMark) && (match % 3 == 0))) {
        roundString = AvH;
      }
      rounds[round][match] = roundString;
    }
  }

    // Display the rounds    
  for (int i = 0; i < totalRounds; i++) {
    MyWriteFile << "Round " + std::to_string(i + 1) << std::endl;
    for (int j = 0; j < matchesPerRound; j++) {
      MyWriteFile << rounds[i][j] << std::endl;
    }
    MyWriteFile << std::endl;
  }
  MyWriteFile.close();
}

void Standing::Analyze() {
  for (int i = 0; i < Results1.size(); i++) {
    for (int j = i+1; j < Results1.size(); j++) {
      if (Results1[i][j] == -1) {
        continue;
      } else {
        Records[i].played++;
        Records[j].played++;
        Records[i].goalsfor += Results1[i][j];
        Records[i].goalsagainst += Results1[j][i];
        Records[j].goalsfor += Results1[j][i];
        Records[j].goalsagainst += Results1[i][j];
        
        if (Results1[i][j] > Results1[j][i]) {
          Records[i].wins++;
          Records[j].loses++;
          Records[i].points += 3;
        } else if (Results1[i][j] < Results1[j][i]) {
          Records[j].wins++;
          Records[i].loses++;
          Records[j].points += 3;
        } else {
          Records[i].draws++;
          Records[j].draws++;
          Records[i].points++;
          Records[j].points++;
        }
      }
    }
    Records[i].goaldiff = Records[i].goalsfor - Records[i].goalsagainst;
  }

  for (int i = 0; i < Results2.size(); i++) {
    for (int j = i+1; j < Results2.size(); j++) {
      if (Results2[i][j] == -1) {
        continue;
      } else {
        Records[i].played++;
        Records[j].played++;
        Records[i].goalsfor += Results2[i][j];
        Records[i].goalsagainst += Results2[j][i];
        Records[j].goalsfor += Results2[j][i];
        Records[j].goalsagainst += Results2[i][j];
        
        if (Results2[i][j] > Results2[j][i]) {
          Records[i].wins++;
          Records[j].loses++;
          Records[i].points += 3;
        } else if (Results2[i][j] < Results2[j][i]) {
          Records[j].wins++;
          Records[i].loses++;
          Records[j].points += 3;
        } else {
          Records[i].draws++;
          Records[j].draws++;
          Records[i].points++;
          Records[j].points++;
        }
      }
    }
    Records[i].goaldiff = Records[i].goalsfor - Records[i].goalsagainst;
  }
}

int Standing::partition (int low, int high) {
    Team pivot = Records[high];
    int i = (low - 1);
    Team temp;
    for (int j = low; j <= high - 1; j++)
    {
        if (Records[j].compare(pivot))
        {
            i++;
            temp = Records[j];
            Records[j] = Records[i];
            Records[i] = temp;
        }
    }
    temp = Records[i+1];
    Records[i+1] = Records[high];
    Records[high] = temp;
    return (i+1);
}

void Standing::quickSort(int low, int high) {
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void Standing::loadFixture(std::string filename) {
  std::ifstream MyReadFile;
  std::string Text;
  int teams;
  int k, a, b, c, d, e;
  std::vector<int> temp;
  std::string Team1, Team2;
  int Score1, Score2;
  Team S;
	MyReadFile.open(filename, std::ios::in);
  if (MyReadFile.is_open()) {
		getline(MyReadFile, Text);
    k = Text.find(": ", 0);
    teams = stoi(Text.substr(k+2));
    getline(MyReadFile, Text);

    Results1.resize(teams);
    for (int i = 0; i < Results1.size(); i++) {
      for (int j = 0; j < teams; j++)
        Results1[i].push_back(-1);
    }

    Results2.resize(teams);
    for (int i = 0; i < Results2.size(); i++) {
      for (int j = 0; j < teams; j++)
        Results2[i].push_back(-1);
    }

    for (int i = 0; i < teams; i++) {
      getline(MyReadFile, Text);
      S = Team(Text, i);
      Records.push_back(S);
    }
    getline(MyReadFile, Text);

    int totalRounds = (teams - 1)*2;
    int matchesPerRound = teams / 2;
    int halfRoundMark = (totalRounds/2);
    for (int i = 0; i < halfRoundMark; i++) {
      getline(MyReadFile, Text);
      for (int j = 0; j < matchesPerRound; j++) {
        getline(MyReadFile, Text);
        a = Text.find(" - ", 0);
				Team1 = Text.substr(0, a);
				b = Text.find(": ", a+3);
        if (b == std::string::npos) {
          continue;
        }
				Team2 = Text.substr(a+3, b-a-3);
				c = Text.find(" - ", b+2);
				Score1 = stoi(Text.substr(b+2, c-b-2));
				Score2 = stoi(Text.substr(c+3));

        for (int u = 0; u < teams; u++) {
          if (Records[u].name.compare(Team1) == 0) {
            d = Records[u].id;
          } else if (Records[u].name.compare(Team2) == 0) {
            e = Records[u].id;
          }
        }
        Results1[d][e] = Score1;
        Results1[e][d] = Score2;
      }
      getline(MyReadFile, Text);
    }

    for (int i = halfRoundMark; i < totalRounds; i++) {
      getline(MyReadFile, Text);
      for (int j = 0; j < matchesPerRound; j++) {
        getline(MyReadFile, Text);
        a = Text.find(" - ", 0);
				Team1 = Text.substr(0, a);
				b = Text.find(": ", a+3);
        if (b == std::string::npos) {
          continue;
        }
				Team2 = Text.substr(a+3, b-a-3);
				c = Text.find(" - ", b+2);
				Score1 = stoi(Text.substr(b+2, c-b-2));
				Score2 = stoi(Text.substr(c+3));

        for (int u = 0; u < teams; u++) {
          if (Records[u].name.compare(Team1) == 0) {
            d = Records[u].id;
          } else if (Records[u].name.compare(Team2) == 0) {
            e = Records[u].id;
          }
        }
        Results2[d][e] = Score1;
        Results2[e][d] = Score2;
      }
      getline(MyReadFile, Text);
    }
    Analyze();
	} else {
		std::cout << "There is no fixture available." << std::endl;
	}
  MyReadFile.close();
}

void Standing::createStanding(std::string filename) {
  std::ofstream MyWriteFile;
  MyWriteFile.open(filename, std::ios::out);

  MyWriteFile << std::left;
  MyWriteFile << "   " << std::setw(20) << "Name" << std::setw(4) << "P" << std::setw(4) << "W" << std::setw(4) << "D" << std::setw(4) << "L" << std::setw(4) << "GF" << std::setw(4) << "GA" << std::setw(4) << "GD" << std::setw(4) << "P" << std::endl;
  for (int i = 0; i < Records.size(); i++) {
    MyWriteFile << i + 1 << ". " << Records[i] << std::endl;
  }
}

Standing::~Standing() {
}
