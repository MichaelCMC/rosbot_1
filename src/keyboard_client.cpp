// C++ includes
#include <iostream>
#include <string>

// ROS includes
#include "ros/ros.h"
#include "rosbot_1/movement.h"

class UserInput {
    private:
        ros::ServiceClient client_;
        rosbot_1::movement srv_;

    public:
        UserInput(ros::NodeHandle& n) {
           // set up the client that will request through "Motion" service
           client_ = n.serviceClient<rosbot_1::movement>("Motion");
        }

        void clientCall() {
            ros::Rate loop_rate(10);
            
            // loops until ros is shutdown
            while (ros::ok()) {
                std::string input;

                // take in user input
                std::cout << "Desired Robot Movement (w, a, s, d, or x to stop): ";
                std::cin >> input;

                // set user input as request message
                srv_.request.message  = input;

                // call using the updated servie message
                client_.call(srv_);

                loop_rate.sleep();
            }
        }
};
        
int main(int argc, char** argv) {
    
    // set up ros
    ros::init(argc, argv, "rosbot_pub");
    ros::NodeHandle n;
    // set up UserInput class and starts it
    UserInput rosbot = UserInput(n);
    rosbot.clientCall();
}
    
