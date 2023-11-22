#ifndef __Statistics_hpp__
#define __Statistics_hpp__

#include <string>
#include <vector>

class FileInit;

class StatisticsData {
public:
    StatisticsData(std::string name = "");
    void add(int level, int result);

private:
    friend class Statistics;
    std::string name;
    int all;
    int win;
    int lose;
    int draw;
};

class Statistics {
public:
    std::vector<std::vector<std::string>> getStatistics();
};

#endif