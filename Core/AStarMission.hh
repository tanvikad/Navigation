//
// Created by tanvi on 6/13/2021.
//

#ifndef NAVIGATION2_ASTARMISSION_HH
#define NAVIGATION2_ASTARMISSION_HH


#include <vector>
#include <iostream>
#include <map>
#include "AStar.hh"


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

    std::vector<double> getPose(std::string poseString);
public:
    std::map<std::string, std::vector<double>> targets_;
    std::vector<std::vector<double>> path_;
    std::vector<std::vector<double>> obstacles_;


    AStarMission(std::vector<std::vector<std::string>> &goals, double velocity, int width, int height, int depth);
    AStarMission();
    void addGoals(std::vector<std::vector<std::string>> goals);

    void isSucessful(bool success, std::vector<double> pose);

    void recurse(std::vector<double> pose, double time);

};


#endif //NAVIGATION2_ASTARMISSION_HH
