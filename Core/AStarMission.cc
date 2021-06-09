#include "AStarMission.hh"


/*
 * each vector in goals is of size three, with "goal", "linear movement", and "rotational movement"
 * ex: ["1 1 1 0 pi/2 pi", "goToLocation", "None"]
 * ex: ["buoy_fairy", "goToTarget", "SineTraversalMovement"]
 */
AStarMission::AStarMission(std::vector<std::vector<std::string>> goals, double velocity, int width, int height, int depth):
        goals_(goals),
        velocity_(velocity),
        current_(nullptr),
        width_(width),
        height_(height),
        depth_(depth)
{

}

void AStarMission::addGoals(std::vector<std::vector<std::string>> goals)
{
    goals_.insert(std::end(goals_), std::begin(goals), std::end(goals));
}

void AStarMission::isSucessful(bool success, std::vector<double> pose)
{
    if(success)
    {
        goals_.erase(goals_.begin(), goals_.begin()+1);
        current_ = nullptr;
    }
    pose_ = pose;
}

void AStarMission::recurse(std::vector<double> pose, double time)
{
    //If an AStar object is created with the specific goal
    if(current_)
    {
        current_->updatePose(pose[0], pose[1], pose[2]);
        path_ = current_->path_;
    }else
    {
        std::vector<double> goal;
        current_ = new AStar(obstacles_, width_, height_, depth_, pose[0], pose[1], pose[2], goal[0], goal[1], goal[2], AStar::rotationalMotion_::None, "", time, velocity_);
        current_->solveGrid();
        path_ = current_->path_;
    }
}


int main()
{

}