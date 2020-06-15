// C++ includes
#include <iostream>
#include <string>

// ROS includes
#include <ros/ros.h>
#include <rosbot_1/movement.h>
#include <sensor_msgs/Joy.h>

class DS4Input {
    private:
        ros::ServiceClient client_;
        ros::Subscriber sub_;
        rosbot_1::movement srv_;

        double linear_;
        double angular_;

    public:
        DS4Input(ros::NodeHandle& n) {
           // set up client to motion and subscriber to joy
           client_ = n.serviceClient<rosbot_1::movement>("Motion");
           sub_ = n.subscribe<sensor_msgs::Joy>("joy", 10, &DS4Input::joyCallback, this);
        }

        void joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
            // get the ds4 left stcik input
            linear_ = joy->axes[1];
            angular_ = joy->axes[0];
            
            // set the robot movement based on input
            if (linear_ == 1) {
                srv_.request.message = "w";
            } else if (linear_ == -1) {
                srv_.request.message = "s";
            } else if (angular_ == 1) {
                srv_.request.message = "a";
            } else if (angular_ == -1) {
                srv_.request.message = "d";
            } else {
                srv_.request.message = "x";
            }
            
            // call the service
            client_.call(srv_);
        
        }

};
        
int main(int argc, char** argv) {
    
    // set up ros
    ros::init(argc, argv, "rosbot_pub");
    ros::NodeHandle n;
    // set up DS4Input class and spins
    DS4Input rosbot = DS4Input(n);
    ros::spin();
}
    
