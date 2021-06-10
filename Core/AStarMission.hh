

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
    int width_;
    int height_;
    int depth_;

    std::vector<int> getPose(std::string poseString);
public:
    std::map<std::string, std::vector<double>> targets_;
    std::vector<std::vector<double>> path_;
    std::vector<std::vector<int>> obstacles_;


    AStarMission(std::vector<std::vector<std::string>> goals, double velocity, int width, int height, int depth);

    void addGoals(std::vector<std::vector<std::string>> goals);

    void isSucessful(bool success, std::vector<double> pose);

    void recurse(std::vector<double> pose, double time);

};

#endif //NAVIGATION_ASTARMISSION_HH
