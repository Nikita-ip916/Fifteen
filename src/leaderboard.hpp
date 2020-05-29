#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

struct Result;
void clearFile();
int countStr();
bool checkName(Result&);
void getResult(int*, Result&);
void sortResult(int*, std::vector<Result>&, int);
void writeResult(Result&, std::vector<Result>&);
void readResult(Result&, std::vector<Result>&);
void fixFile(Result&, std::vector<Result>&);
#endif
