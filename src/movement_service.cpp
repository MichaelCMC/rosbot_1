// C++ includes
#include <string>

// ROS includes
#include "ros/ros.h"
#include "rosbot_1/movement.h"

// include motor control file
#include "movement_control.h"


class RosBot {
    private:
        ros::ServiceServer service_;

    public:
        RosBot(ros::NodeHandle& n) {
            // set up service to advertise to "Motion"
            service_ = n.advertiseService("Motion", &RosBot::callback,  this);
            // set up raspbery pi GPIO pins
            control::init();
        }

        // from request issue a movement command and print the command
        bool callback(rosbot_1::movement::Request &req, rosbot_1::movement::Response &res) {
            std::string command = req.message;

            if (command == "w") {
                ROS_INFO("Moving Forward");

                control::forward();
            } else if (command == "s") {
                ROS_INFO("Moving Backward");
    
                control::reverse();
            } else if (command == "a") {
                ROS_INFO("Moving Left");

                control::left();
            } else if (command == "d") {
                ROS_INFO("Moving Right");

                control::right();
            } else if (command == "x") {
                ROS_INFO("Stopping");
                
                control::stop();
            } else {
                ROS_INFO("Invalid Command");
            }
            
            return true;

        }
        ~RosBot() {

            // cleanup by setting GPIO pins to input
            control::cleanup();
        }
};

int main(int argc, char** argv) {
    // setup ros 
    ros::init(argc, argv, "rosbot_sub");
    ros::NodeHandle n;
    // set up RosBot class and spins
    RosBot bot = RosBot(n);
    ros::spin();
}
