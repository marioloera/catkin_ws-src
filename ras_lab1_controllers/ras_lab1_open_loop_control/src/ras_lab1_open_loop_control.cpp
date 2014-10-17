/// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
//#include "std_msgs/String.h"
//  #include <std_msgs/Float64.h>
  #include <ras_arduino_msgs/PWM.h>
// %EndTag(MSG_HEADER)%

//#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
 
// %Tag(INIT)%
  ros::init(argc, argv, "ras_lab1_open_loop_control_node");//name of the node
// %EndTag(INIT)%

// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%
// %Tag(PUBLISHER)%
//  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("distance_sensor_test_node/distance", 1000);
  //ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("kobuki/pwm", 1000);//topic to publish
  ros::Publisher chatter_pub = n.advertise<ras_arduino_msgs::PWM>("kobuki/pwm", 1000);//topic to publish
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
  
  int pwm1=0;
  int pwm2=0; 
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

   // std_msgs::Float64 msg1;//declare the mesage structure to publish


    pwm1=255;
    pwm2=255;	

    ras_arduino_msgs::PWM pwm_msg;
    pwm_msg.PWM1=pwm1;
    pwm_msg.PWM2=pwm2;

// %Tag(ROSCONSOLE)%

    ROS_INFO("Loop=%5d - pwm_msg.PWM1=%4d - pwm_msg.PWM2=%4d",count,pwm1,pwm_msg.PWM2);//print in terminal
 //   ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%


// %Tag(PUBLISH)%
  //  chatter_pub.publish(msg);

 //   msg1.data=distM;
    chatter_pub.publish(pwm_msg);

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
