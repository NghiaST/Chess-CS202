#include <StatisticsScreen/ProcessStatistics.hpp>
#include <DataControl/FileManager.hpp>
#include <StatisticsScreen/ProcessStatistics.hpp>

StatisticsData::StatisticsData(std::string name)
{
    this->name = name;
    all = 0;
    win = 0;
    lose = 0;
    draw = 0;
}

void StatisticsData::add(int variants, int level, int result)
{
    all++;
    if (result == 1) {
        win++;
    }
    else if (result == 0) {
        lose++;
    }
    else {
        draw++;
    }
}

std::vector<std::vector<std::string>> Statistics::getStatistics() {
    std::vector<std::vector<std::string>> statistics;
    int all, win, lose, draw;
    std::vector<StatisticsData> StatisticsList = FileManager::LoadStatistics();
    statistics.push_back({ "Mode", "Played", "Win", "Lose", "Draw" });
    for (int i = 0; i < StatisticsList.size(); i++) {
        all = StatisticsList[i].all;
        win = StatisticsList[i].win;
        lose = StatisticsList[i].lose;
        draw = StatisticsList[i].draw;
        statistics.push_back({ StatisticsList[i].name, std::to_string(all), std::to_string(win), std::to_string(lose), std::to_string(draw) });
    }
    return statistics;
}