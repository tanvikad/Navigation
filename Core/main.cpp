#include <iostream>
#include "AStar.hh"
#include "AStarMission.hh"
#include<vector>
#include<functional>

int main()
{
    //Tests the Mission Class by inputting a list of goals, obstacles and prints out a path
    std::vector<std::string> goal1 = {"0 1 7 0.5 0.6 0.7", "goToLocation", "None", ""};
    std::vector<std::string> goal2 = {"0 2 2 0.5 0.5 0.5", "SineTraversalMovement", "2 2 0"};

    /***
     * std::vector<double> degreesToRotate{std::stod(dataList[0]),std::stod(dataList[1]), std::stod(dataList[2])};
        double angularVelocity = std::stod(dataList[3]);
        double pauseDegree = std::stof(dataList[4]);
        double pauseTime = std::stof(dataList[5]);
     */
    std::vector<std::string> goal3 = {"0 4 3 0 0 0", "RotationalMovement", "5 5 0 1 2 2" };
    std::vector<std::vector<std::string>> goals;
    goals.push_back(goal1);
    goals.push_back(goal2);
    goals.push_back(goal3);
    AStarMission* mission = new AStarMission(goals, 5, 1, 10,10);

    std::vector<double> obstacle1 = {0, 5, 5, 0.1, 0.1, 0};
    std::vector<double> obstacle2 = {0, 1, 1, 0, 0, 0};
    std::vector<std::vector<double>> obstacles;
    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle2);

    mission->obstacles_ = obstacles;

    std::vector<double> currentPose = {0, 0, 0, 0, 0, 0};
    mission->recurse(currentPose, 0);
    mission->printPath();

    std::vector<double> obstacle3 = {0,0,2};
    obstacles.push_back(obstacle3);
    mission->obstacles_ = obstacles;
    mission->recurse(currentPose, 0.5);
    mission->printPath();

    mission->isSuccessful(true);
    currentPose[2] = 3;

    mission->recurse(currentPose, 1);
    mission->printPath();

    mission->isSuccessful(true);
    mission->recurse(currentPose, 10);
    mission->printPath();


    return 0;
}
