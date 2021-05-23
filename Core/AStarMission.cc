#include "AStarMission.hh"


/*
 * each vector in goals is of size three, with "goal", "linear movement", and "rotational movement"
 * ex: ["1 1 1 0 pi/2 pi", "goToLocation", "None"]
 * ex: ["buoy_fairy", "goToTarget", "SineTraversalMovement"]
 */
AStarMission::AStarMission(std::vector<std::vector<std::string>> goals, double velocity):
        goals_(goals),
        velocity_(velocity),
        current_(nullptr)
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

void AStarMission::recurse(std::vector<double> pose)
{
    //If an AStar object is created with the specific goal
    if(current_)
    {
        current_->updatePose(pose[0], pose[1], pose[2]);
        path_ = current_->path_;
    }else
    {
        //create a New Astar object
        current_ = nullptr;
    }
}


int main()
{

}