#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

struct Result;
void clearFile();
int countStr();
void getResult(int*, Result&, std::vector<Result>);
void sortResult(int*, std::vector<Result>, int);
void rewriteResult(Result&, std::vector<Result>);
void writeResult(Result&, std::vector<Result>);
#endif
