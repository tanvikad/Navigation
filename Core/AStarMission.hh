

#ifndef NAVIGATION_ASTARMISSION_HH
#define NAVIGATION_ASTARMISSION_HH

#include <vector>
#include <iostream>
#include <map>
#include "AStar.cc"


class AStarMission
{
private:
    std::vector<std::vector<std::string>> goals_;
    double velocity_;
    std::vector<double> pose_;
    AStar* current_;
public:
    std::map<std::string, std::vector<double>> targets_;
    std::vector<std::vector<double>> path_;


    AStarMission(std::vector<std::vector<std::string>> goals, double velocity);

    void addGoals(std::vector<std::vector<std::string>> goals);

    void isSucessful(bool success, std::vector<double> pose);

    void recurse(std::vector<double> pose);

};

#endif //NAVIGATION_ASTARMISSION_HH
