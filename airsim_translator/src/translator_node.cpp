#include <airsim_car_ros_pkgs/CarCmd.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>
#include <ros/ros.h>
 
airsim_car_ros_pkgs::CarCmd *cmd_ = 0;

void brakeCallback(const std_msgs::Float64::ConstPtr& msg){
    cmd_->brake = msg->data;
}

void gearCallback(const std_msgs::String::ConstPtr& msg){
    //gear = msg.data;
}

void handbrakeCallback(const std_msgs::Bool::ConstPtr& msg){
    cmd_->handbrake = msg->data;
}
void steeringCallback(const std_msgs::Float64::ConstPtr& msg){
    cmd_->steering = (-1.0)*msg->data;
}
void throttleCallback(const std_msgs::Float64::ConstPtr& msg){
    cmd_->throttle = msg->data;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "translator");

    ros::NodeHandle nh_;

    cmd_ = new airsim_car_ros_pkgs::CarCmd;

    ros::Publisher pub_ = nh_.advertise<airsim_car_ros_pkgs::CarCmd>("/airsim_node/PhysXCar/car_cmd_body_frame", 10);

    ros::Subscriber brake_sub_ = nh_.subscribe("/brake_command", 10, brakeCallback);
    ros::Subscriber gear_sub_ = nh_.subscribe("/gear_command", 10, gearCallback);
    ros::Subscriber handbrake_sub_ = nh_.subscribe("/handbrake_command", 10, handbrakeCallback);
    ros::Subscriber steering_sub_ = nh_.subscribe("/steering_command", 10, steeringCallback);
    ros::Subscriber throttle_sub_ = nh_.subscribe("/throttle_command", 10, throttleCallback);

    //ros::Rate loop_rate(10);

    while (ros::ok()) {
  	  pub_.publish(*cmd_);
  	  ros::spinOnce();     
        //loop_rate.sleep(); //Dorme tempo suficiente para manter a frequencia definida no rate();
    }
    return 0;
}
