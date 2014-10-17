/// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
//#include "std_msgs/String.h"
//  #include <std_msgs/Float64.h>
  #include <geometry_msgs/Twist.h>
// %EndTag(MSG_HEADER)%

//#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
float r=0.5;
float time_rev=10.0;
float v=0;
float w=0;

int main(int argc, char **argv)
{
 
// %Tag(INIT)%
  ros::init(argc, argv, "circle_cartesian_controller_node");//name of the node
// %EndTag(INIT)%

// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%
// %Tag(PUBLISHER)%
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("motor_controller/twist", 1000);//topic to publish



// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(10);
// %EndTag(LOOP_RATE)%

 /* **
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
// %Tag(ROS_OK)%
  int count = 0; //main iterations
  
  while (ros::ok())
  {
  
    v=2*3.1416*r/time_rev;
    w=v/r;	
 

    geometry_msgs::Twist msg;
    msg.linear.x=v;
    msg.angular.z=w;

// %Tag(ROSCONSOLE)%

    ROS_INFO("write: r=%.2f time=%.2f v=%.4f - w=%.4f",r,time_rev,v,w);//print in terminal
 //   ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%


// %Tag(PUBLISH)%
  //  chatter_pub.publish(msg);

 //   msg1.data=;
    chatter_pub.publish(msg);

// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%


// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%

    ++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%
