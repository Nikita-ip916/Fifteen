#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

struct Result;
void clearFile();
int countStr();
int checkName(Result&);
void getResult(int*, Result&, std::vector<Result>&);
void sortResult(int*, std::vector<Result>&, int);
void writeResult(Result&, std::vector<Result>&);
void readResult(Result&, std::vector<Result>&);
#endif
