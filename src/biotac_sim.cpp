//
// Created by behzad on 10/11/19.
//

#include "biotac_simulator/biotac_node.h"

BioTacSimulator::BioTacSimulator(ros::NodeHandle *nh, int id):
nh_(*nh), id_(id), pdc_(0), status_(0), is_started_(false)
{
    subscriber_ = nh_.subscribe("/simulation_status", 100, &BioTacSimulator::statusCallback, this);
    publisher_ = nh_.advertise<biotac_simulator::Biotac>("/sim/tactile", 100);
    // set up the reference spline
    for (auto p : pdc_ref_) { p += pdc_;}
//    pdc_spline_.set_points(t_ref_, pdc_ref_, false);
    pdc_spline_.set_points(t_ref_, pdc_ref_, true);
}

void BioTacSimulator::statusCallback(const std_msgs::Int16 &data)
{
    status_ = data.data;
}

void BioTacSimulator::publish()
{
    if (status_)
    {
        if (!is_started_) {
            t0_ = ros::Time::now();
            is_started_ = true;
            puts("BioTac has started.\n");
        } else {
            ros::Duration duration = ros::Time::now() - t0_;
            double dt = duration.toSec();
            pdc_ = pdc_spline_(dt);
        }
    }
    biotac_.pdc = pdc_;
    publisher_.publish(biotac_);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "biotacSimulator");
    ros::NodeHandle nh("~");
    BioTacSimulator biotac_simulator(&nh, 0);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        biotac_simulator.publish();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;

}