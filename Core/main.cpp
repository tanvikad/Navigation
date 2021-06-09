#include <iostream>
#include "AStar.hh"
#include "AStar.cc"
#include<queue>
#include<vector>
#include<functional>
#include <unordered_set>
#include <typeinfo>

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



    std::vector<std::vector<int>> obstacle;
    std::vector<int> pose {0,0,1};
    obstacle.push_back(pose);

    AStar* createMap = new AStar(obstacle, 1, 3, 3, 0, 0, 0, 0, 2, 2, AStar::rotationalMotion_::None, "", 0, 5);
    std::cout<<"hello"<<std::endl;

    createMap->printGrid();
    createMap->solveGrid();
    createMap->printGrid();


    return 0;
}
