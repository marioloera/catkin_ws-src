/// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
//#include "std_msgs/String.h"
#include <std_msgs/Float64.h>
// %EndTag(MSG_HEADER)%

//#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
 
// %Tag(INIT)%
  ros::init(argc, argv, "distance_sensor_calib_node");
// %EndTag(INIT)%

// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%
// %Tag(PUBLISHER)%
//  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("distance_sensor_test_node/distance", 1000);
  ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("distance_sensor_test_node/distance", 1000);
// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(50);
// %EndTag(LOOP_RATE)%

 /* **
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
// %Tag(ROS_OK)%
  int count = 0; //main iterations
  int numExp=4;//repeat the same distance, for noise reduction
  int i=1;//number of iterations in the same distance
  double incrementDistance=0.025; //incremente distance in meters 0.005 = 0.5 cm	
  double distM=0.10;//distance in miter, from 0.1 to 0.8
  while (ros::ok())
  {
// %EndTag(ROS_OK)%
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
// %Tag(FILL_MESSAGE)%

  //  std_msgs::String msg;
  //  std::stringstream ss;
  //   ss << "hello world " << count << " distM= "<<distM ;
  //    msg.data = ss.str();

    std_msgs::Float64 msg1;//declare the mesage structure to publish

// %EndTag(FILL_MESSAGE)%

// %Tag(ROSCONSOLE)%

    ROS_INFO("Loop=%5d - Experiment Number =%2d - Distance in Meters=%0.3f",count,i,distM);//print in terminal
 //   ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%


// %Tag(PUBLISH)%
  //  chatter_pub.publish(msg);

    msg1.data=distM;
    chatter_pub.publish(msg1);

// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%


// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
    if(i==numExp)
    {    
        if(distM<=0.80)
        {
                distM+=incrementDistance;
        }
 	else
	   break;
 
	i=0;
    }

    ++i;
    ++count;
  }


  return 0;
}
// %EndTag(FULLTEXT)%
