/// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
//#include "std_msgs/String.h"
//  #include <std_msgs/Float64.h>
#include <ras_arduino_msgs/ADConverter.h>  
#include <geometry_msgs/Twist.h>
#include <math.h>
// %EndTag(MSG_HEADER)%

//#include <sstream>

float vmax=.41;
float v=0;
float w=0;
int d1=0,d2=0;
float const ki_w=0.010;//ki=0.015
float const ki_v=0.10;
void ADC_Callback(const ras_arduino_msgs::ADConverter::ConstPtr& adc_msg)
{
  d1=adc_msg->ch1; 
  d2=adc_msg->ch2; 
  ROS_INFO("ch1=%3d ch2=%3d", d1,d2);
}



int main(int argc, char **argv)
{
 
// %Tag(INIT)%
  ros::init(argc, argv, "wall_following_controller_node");//name of the node
// %EndTag(INIT)%

// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%
// %Tag(PUBLISHER)%
//  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("1distance", 1000);
  //ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("kobuki/pwm", 1000);//topic to publish
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("motor_controller/twist", 1000);//topic to publish

  ros::Subscriber sub = n.subscribe("kobuki/adc", 1000, ADC_Callback);


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

//////////////////////////////////////////////////////////////////////////////////
    



//saturation 
  

//////////////////////////////////////////////////////////////////////////////

    geometry_msgs::Twist msg;
 
    v=(double)vmax/(1+ki_v*fabs(d1-d2));
    msg.linear.x=v;

    w=(double)-ki_w*(d1-d2);
    msg.angular.z=w;

// %Tag(ROSCONSOLE)%

    ROS_INFO("write: v=%.4f - w=%.4f",msg.linear.x,msg.angular.z);//print in terminal
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
