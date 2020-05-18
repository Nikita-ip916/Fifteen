#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

struct result;
void clearFile();
int countStr();
void getResult(int*, result&, std::vector<result>);
void sortResult(std::vector<result>&, int);
void rewriteResult(result&, std::vector<result>);
void writeResult(result&, std::vector<result>);
#endif
