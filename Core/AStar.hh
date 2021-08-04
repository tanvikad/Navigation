

#ifndef NAVIGATION_ASTAR_HH
#define NAVIGATION_ASTAR_HH
#include <limits>
#include <math.h>
#include <vector>

class AStar
{
public:
    std::vector<std::vector<double>> path_;
    enum rotationalMotion_ {rotationalMovement, sinTraversalPath, None};
    AStar(int width, int height, int depth, double prob, int startx, int starty, int startz, int endx, int endy, int endz, rotationalMotion_ motion, std::string data, double startTime, double velocity);
    AStar(int*** map, int width, int height, int depth, int startx, int starty, int startz, int endx, int endy, int endz, rotationalMotion_ motion, std::string data, double startTime, double velocity);
    AStar(std::vector<std::vector<double>> obstacles, int width, int height, int depth, int startx, int starty, int startz, int endx, int endy, int endz, rotationalMotion_ motion, std::string data, double startTime, double velocity);
    AStar(int width, int height, int depth);
    void updatePose(int startx, int starty, int startz);
    void solveGrid();
    void resolveGrid();
    void solveGridDFS();
    void printGrid() const;
    void addObstacles(std::vector<std::vector<double>> obstacle);



private:
    class Node;
    int width_;
    int height_;
    int depth_;
    double prob_;
    int startx_;
    int starty_;
    int startz_;
    int endx_;
    int endy_;
    int endz_;
    int resolveGrid_;
    double startTime_;
    rotationalMotion_ motion_;
    double velocity_;
    //struct pose{ double *position;};
    Node*** grid_;
    double*** distance_;

    void makeGridFromMap(int*** map);
    void makeGridFromObstacles(std::vector<std::vector<double>>);
    void makeGrid();


    void makeParent(Node *node, std::string value);
    void DFS(int x, int y, int z);
    void addRotation(std::string data);
    void addSinTraversal(std::string data, int amp, int freq, int period);
    void addTime(int velocity, int factor);



    class Node
    {

    public:
        static double infinity;
        bool isObstacle_ = false;
        int x_;
        int y_;
        int z_;
        double f_ = infinity;
        double  g_ = infinity;
        double  h_ = 0;
        std::string str_  = "0";
        std::string id_;
        Node* parent_ = NULL;
        rotationalMotion_ motion_;

        Node(int x, int y, int z, Node *end);
        Node();
        void setObstacle(bool isObstacle);
        friend bool operator< (const Node& a, const Node& b){return a.f_ > b.f_;}
        friend bool operator> (const Node& a, const Node& b) {return a.f_ <b.f_;}



        template<typename T>
        bool operator()(T *a, T *b) {
            return a->f_ < b->f_;
        }


    };
};


#endif //NAVIGATION_ASTAR_HH
