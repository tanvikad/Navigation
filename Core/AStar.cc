#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>



#include "AStar.hh"

double  AStar::Node::infinity = std::numeric_limits<double>::infinity();


AStar::AStar(int width, int height, int depth, double prob, int startx, int starty, int startz, int endx, int endy,
             int endz, rotationalMotion_ motion, std::string data, double startTime, double velocity) :
        width_(width),
        height_(height),
        depth_(depth),
        prob_(prob),
        startx_(startx),
        starty_(starty),
        startz_(startz),
        endx_(endx),
        endy_(endy),
        endz_(endz),
        motion_(motion),
        grid_(nullptr),
        distance_(nullptr),
        startTime_(startTime),
        velocity_(velocity),
        resolveGrid_(3)

{
    makeGrid();
/*
    switch (motion)
    {
        case None:
            break;
        case rotationalMovement:
            addRotation(data);
            break;
        case sinTraversalPath:
            addSinTraversal(data);
            break;
        default:
            std::cout<<"Error, movement can only be None, rotationalMovement, sinTraversalPath";

    }
    addTime();

*/
}

AStar::AStar(int width, int height, int depth)
        : AStar(width, height, depth, 0.3, 0, 0, 0, width - 1, height - 1, depth - 1, sinTraversalPath, "", 0, 5)
{
}

void AStar::makeGrid()
{
    srand(time(0));
    Node *endNode = new Node(endx_, endy_, endz_, NULL);
    grid_ = new Node **[width_];
    for (int i = 0; i < width_; i++)
    {
        grid_[i] = new Node *[height_];
        for (int j = 0; j < height_; j++)
        {
            grid_[i][j] = new Node[depth_];
            for (int k = 0; k < depth_; k++)
            {

                double random = rand() % 100;
                bool isObstacle = (prob_ * 100) > random;
                if (i == startx_ && j == starty_ && k == startz_)
                {
                    isObstacle = false;
                }
                Node *node = new Node(i, j, k, endNode);
                node->setObstacle(isObstacle);
                grid_[i][j][k] = *node;

            }
        }
    }

    grid_[endx_][endy_][endz_] = *endNode;


}

void AStar::printGrid() const
{
    for (int i = 0; i < width_; i++)
    {
        for (int j = 0; j < height_; j++)
        {
            for (int k = 0; k < depth_; k++)
            {
                std::cout << grid_[i][j][k].str_ << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;

    }

}

void AStar::solveGrid()
{
    std::priority_queue<Node> q;
    grid_[startx_][starty_][startz_].g_ = 0;
    grid_[startx_][starty_][startz_].f_ = grid_[startx_][starty_][startz_].g_ + grid_[startx_][starty_][startz_].h_;
    q.push(grid_[startx_][starty_][startz_]);

    std::unordered_set<std::string> closed;
    std::unordered_set<std::string> open;
    while (!q.empty())
    {

        Node *now = &grid_[q.top().x_][q.top().y_][q.top().z_];
        q.pop();
        closed.insert(now->id_);
        now->str_ = "2";
        if (now->x_ == endx_ && now->y_ == endy_ && now->z_ == endz_)
        {
            break;
        }
        int dy[26] = {1, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, 0, -1, -1, -1, 0};
        int dx[26] = {-1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, 0, -1, 0, 1, -1, 1, -1, 0, 1, 0};
        int dz[26] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        for (int i = 0; i < 26; i++)
        {
            if (0 <= now->x_ + dx[i] && now->x_ + dx[i] < width_ && 0 <= now->y_ + dy[i] && now->y_ + dy[i] < height_ &&
                0 <= now->z_ + dz[i] && now->z_ + dz[i] < depth_)
            {
                Node *side = &grid_[now->x_ + dx[i]][now->y_ + dy[i]][now->z_ + dz[i]];
                if (side->str_ == "3")
                {
                    side->parent_ = &grid_[now->x_][now->y_][now->z_];
                    makeParent(&grid_[endx_][endy_][endz_], "4");
                    return;
                }
                if (side->isObstacle_) continue;
                if (closed.find(side->id_) != closed.end()) continue;
                double distance = pow((pow((dx[i]), 2) + pow((dy[i]), 2) + pow((dz[i]), 2)), 0.5);
                if (now->g_ + distance < side->g_ || open.find(side->id_) == open.end())
                {
                    side->g_ = now->g_ + distance;
                    side->f_ = side->g_ + side->h_;
                    side->parent_ = &grid_[now->x_][now->y_][now->z_];
                    if (open.find(side->id_) == open.end())
                    {
                        open.insert(side->id_);
                        q.push(*side);
                    }
                }
            }
        }
    }
    path_.clear();
    makeParent(&grid_[endx_][endy_][endz_], "3");
    std::cout<<"A* distance "<<grid_[endx_][endy_][endz_].f_<<std::endl;
    std::reverse(path_.begin(),path_.end());

}

void AStar::makeParent(AStar::Node *node, std::string value)
{
    grid_[node->x_][node->y_][node->z_].str_ = value;
    std::vector<double> current;
    current.push_back(node->x_);
    current.push_back(node->y_);
    current.push_back(node->z_);
    current.push_back(0);
    current.push_back(0);
    current.push_back(0);

    path_.push_back(current);
    if (node->parent_ == NULL) return;
    makeParent(node->parent_, value);
}

void AStar::solveGridDFS()
{
    distance_ = new double **[width_];
    for (int i = 0; i < width_; i++)
    {
        distance_[i] = new double *[height_];
        for (int j = 0; j < height_; j++)
        {
            distance_[i][j] = new double[depth_];
            for (int k = 0; k < depth_; k++)
            {
                distance_[i][j][k] = Node::infinity;

            }
        }
    }
    distance_[endx_][endy_][endz_] = 0;
    DFS(endx_, endy_, endz_);
    std::cout<<"Actual Distance "<<distance_[startx_][starty_][startz_]<<std::endl;
}

void AStar::DFS(int x, int y, int z)
{
    int dy[26] = {1, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, 0, -1, -1, -1, 0};
    int dx[26] = {-1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, 0, -1, 0, 1, -1, 1, -1, 0, 1, 0};
    int dz[26] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    for (int i = 0; i < 26; i++)
    {
        if (0 <= x + dx[i] && x + dx[i] < width_ && 0 <= y + dy[i] && y + dy[i] < height_ && 0 <= z + dz[i] &&
            z + dz[i] < depth_)
        {
            Node *side = &grid_[x + dx[i]][y + dy[i]][z + dz[i]];
            if (side->isObstacle_) continue;
            float d = pow((pow((dx[i]), 2) + pow((dy[i]), 2) + pow((dz[i]), 2)), 0.5);
            if (distance_[side->x_][side->y_][side->z_] > distance_[x][y][z] + d)
            {
                distance_[side->x_][side->y_][side->z_] = distance_[x][y][z] + d;
                DFS(side->x_, side->y_, side->z_);
            }


        }
    }
}

void AStar::addRotation(std::string data)
{
    return;
}

void AStar::addSinTraversal(std::string data)
{
    return;
}

void AStar::addTime()
{
    return;
}

void AStar::updatePose(int startx, int starty, int startz)
{
    std::cout << "Entered update pose" << std::endl;
    if(startx >= width_ || starty >= height_ || startz >= depth_)
    {
        std::cout<<"Index Out Of Bounds"<<std::endl;
        return;
    }
    if (grid_[startx][starty][startz].isObstacle_)
    {
        std::cout << "Updated pose is an obstacle" << std::endl;
        return;
    }
    startx_ = startx;
    starty_ = starty;
    startz_ = startz;
    std::cout << grid_[startx][starty][startz].id_ << std::endl;
    std::cout << "Updating pose" << std::endl;

    resolveGrid_ += 2;
    resolveGrid();
}

void AStar::resolveGrid()
{
    std::priority_queue<Node> q;
    grid_[startx_][starty_][startz_].g_ = 0;
    grid_[startx_][starty_][startz_].f_ = grid_[startx_][starty_][startz_].g_ + grid_[startx_][starty_][startz_].h_;
    grid_[startx_][starty_][startz_].parent_ = NULL;
    q.push(grid_[startx_][starty_][startz_]);

    std::unordered_set<std::string> closed;
    std::unordered_set<std::string> open;
    while (!q.empty())
    {
        Node *now = &grid_[q.top().x_][q.top().y_][q.top().z_];
        q.pop();
        closed.insert(now->id_);
        if (now->str_ >= "3" && std::stoi(now->str_) % 2 == 1)
        {
            break;
        }
        now->str_ = std::to_string(resolveGrid_-1);
        int dy[26] = {1, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, 0, -1, -1, -1, 0};
        int dx[26] = {-1, 0, 1, -1, 1, -1, 0, 1, -1, 0, 1, -1, 1, -1, 0, 1, 0, -1, 0, 1, -1, 1, -1, 0, 1, 0};
        int dz[26] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        for (int i = 0; i < 26; i++)
        {
            if (0 <= now->x_ + dx[i] && now->x_ + dx[i] < width_ && 0 <= now->y_ + dy[i] && now->y_ + dy[i] < height_ &&
                0 <= now->z_ + dz[i] && now->z_ + dz[i] < depth_)
            {
                Node *side = &grid_[now->x_ + dx[i]][now->y_ + dy[i]][now->z_ + dz[i]];
                /*if(side->str_ == "3")
                {
                    side->parent_ = &grid_[now->x_][now->y_][now->z_];
                    makeParent(&grid_[endx_][endy_][endz_], "4");
                    return;
                }*/
                if (side->isObstacle_) continue;
                if (closed.find(side->id_) != closed.end()) continue;
                double distance = pow((pow((dx[i]), 2) + pow((dy[i]), 2) + pow((dz[i]), 2)), 0.5);
                if (now->g_ + distance < side->g_ || open.find(side->id_) == open.end())
                {
                    side->g_ = now->g_ + distance;
                    side->f_ = side->g_ + side->h_;
                    side->parent_ = &grid_[now->x_][now->y_][now->z_];
                    if (open.find(side->id_) == open.end())
                    {
                        open.insert(side->id_);
                        q.push(*side);
                    }
                }
            }
        }
    }
    path_.clear();
    makeParent(&grid_[endx_][endy_][endz_],  std::to_string(resolveGrid_));
    std::reverse(path_.begin(),path_.end());
}

AStar::Node::Node(int x, int y, int z, AStar::Node *end)
{
    x_ = x;
    y_ = y;
    z_ = z;
    if (end != NULL)
    {
        h_ = pow((pow((end->x_ - x_), 2) + pow((end->y_ - y_), 2) + pow((end->z_ - z_), 2)), 0.5);
    }
    id_ = std::to_string(x_) + ' ' + std::to_string(y_) + ' ' + std::to_string(z_);
}

void AStar::Node::setObstacle(bool isObstacle)
{
    isObstacle_ = isObstacle;
    if (isObstacle_)
    {
        str_ = "1";
    } else
    {
        str_ = "0";
    }
}

AStar::Node::Node()
{
    Node(0, 0, 0, NULL);
}



