//
// Created by behzad on 10/11/19.
//

#ifndef BIOTAC_SIMULATOR_BIOTAC_H
#define BIOTAC_SIMULATOR_BIOTAC_H

#include "ros/ros.h" // ROS Library
#include "std_msgs/Int16.h"
#include "biotac_simulator/Biotac.h"
#include "spline.h"

class BioTacSimulator
{
private:
    ros::NodeHandle nh_;
    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
    int id_;
    int pdc_;
    biotac_simulator::Biotac biotac_;
    int status_;
    bool is_started_;
    ros::Time t0_;
    std::vector<double> pdc_ref_= {0, 0, 100, 100};
    std::vector<double> t_ref_ = {0, 10, 20, 30};
    tk::spline pdc_spline_;
    void statusCallback(const std_msgs::Int16 &data);
public:
    BioTacSimulator(ros::NodeHandle *nh, int id);
    void publish();
    ~BioTacSimulator() {};
};


#endif //BIOTAC_SIMULATOR_BIOTAC_H
