#include <iostream>
#include "AStar.hh"
#include "AStarMission.hh"
#include<vector>
#include<functional>
#include <unordered_set>



int main()
{
   // 1937331036


    std::unordered_set<std::string> set_;
    set_.insert("hello");
    set_.insert("bye");
    set_.insert("hello");
    for (auto it = set_.begin(); it != set_.end(); it++)
        std::cout<<*it<<std::endl;

    AStar* pStar = new AStar(1,15,15);
    pStar->solveGrid();
    pStar->solveGridDFS();
    pStar->printGrid();
    pStar->updatePose(0,3,2);
    pStar->printGrid();
    pStar->updatePose(0,9,2);
    pStar->printGrid();
    pStar->updatePose(0,13,3);
    pStar->printGrid();
    pStar->updatePose(0,5,10);
    pStar->printGrid();
    std::vector<std::vector<double>> path = pStar->path_;
    for(int i = 0; i < path.size(); i++)
    {
        std::cout<<path[i][0]<<' '<<path[i][1]<<' '<<path[i][2]<<std::endl;
    }
    int map1[1][3][3] = {{{0,1,1},{0,0,0},{0,0,0}}};



    std::vector<std::vector<double>> obstacle;
    std::vector<double> pose1 {0,1,0.4};
    obstacle.push_back(pose1);

    AStar* createMap = new AStar(obstacle, 1, 3, 3, 0, 0, 0, 0, 2, 2, AStar::rotationalMotion_::None, "", 0, 5);
    std::cout<<"hello"<<std::endl;

    createMap->printGrid();
    createMap->solveGrid();
    createMap->printGrid();

    std::vector<std::string> goal1 = {"0 1 7 0.5 0.6 0.7"};
    std::vector<std::string> goal2 = {"0 2 2 0.5 0.5 0.5"};
    std::vector<std::vector<std::string>> goals;
    goals.push_back(goal1);
    goals.push_back(goal2);
    AStarMission* mission = new AStarMission();

    std::vector<double> obstacle1 = {0, 5, 5, 0.1, 0.1, 0};
    std::vector<double> obstacle2 = {0, 1, 1, 0, 0, 0};
    std::vector<std::vector<double>> obstacles;
    obstacles.push_back(obstacle1);
    obstacles.push_back(obstacle2);

    mission->obstacles_ = obstacles;

    std::vector<double> currentPose = {0, 0, 0, 0, 0, 0};
    mission->recurse(currentPose, 0);


    return 0;
}
