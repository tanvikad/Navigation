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

    int*** map= new int **[1];
    for(int i = 0; i < 1; i++)
    {
        map[i] = new int*[3];
        for(int j = 0; j < 3; j++)
        {
            map[i][j] = new int[3];
            for(int k = 0; k < 3; k++)
            {
                map[i][j][k] = map1[i][j][k];
            }
        }
    }
    AStar* createMap = new AStar(map, 1, 3, 3, 0, 0, 0, 0, 2, 2, AStar::rotationalMotion_::None, "", 0, 5);
    std::cout<<"hello"<<std::endl;

    createMap->printGrid();


    return 0;
}
