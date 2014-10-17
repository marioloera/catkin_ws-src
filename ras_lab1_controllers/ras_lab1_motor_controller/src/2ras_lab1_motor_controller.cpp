/// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
//#include "std_msgs/String.h"
//  #include <std_msgs/Float64.h>
  #include <ras_arduino_msgs/PWM.h>
  #include <ras_arduino_msgs/Encoders.h>
  #include <geometry_msgs/Twist.h>
// %EndTag(MSG_HEADER)%

//#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
float v=0.0;
float w=0.0;
float wr,wl,wr_hat,wl_hat;
int const ticks=360;
int const freq=10;
float const base=0.23;
float const radius=0.0352;
float pwm_delta=0;
float ki_l=0.83*3;
float ki_r=0.80*3;
void inputReferenceCallback(const geometry_msgs::Twist::ConstPtr& reference_msg)
{
   v=reference_msg->linear.x;
   w=reference_msg->angular.z;
  
   wl=(double) (v/radius)-(base*w)/(2*radius); 
   wr=(double) (v/radius)+(base*w)/(2*radius); 

   ROS_INFO("hear: v=%.4f w=%.4f wl=%.4f wr=%.4f ",v,w,wl,wr);
}

int delta_encoder1=0;
int delta_encoder2=0;
void encodersCallback(const ras_arduino_msgs::Encoders::ConstPtr& encoder_msg)
{
   delta_encoder1=encoder_msg->delta_encoder1;
   delta_encoder2=encoder_msg->delta_encoder2;
   wl_hat=(double) 3.1416*2*freq*delta_encoder1/ticks;
   wr_hat=(double) 3.1416*2*freq*delta_encoder2/ticks;
   ROS_INFO("hear: del_enc1=%3d del_enc2=%3d wl_hat=%.4f wr_hat=%.4f", delta_encoder1,delta_encoder2,wl_hat,wr_hat);

}



int main(int argc, char **argv)
{
 
// %Tag(INIT)%
  ros::init(argc, argv, "ras_lab1_motor_controller_node");//name of the node
// %EndTag(INIT)%

// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%
// %Tag(PUBLISHER)%
//  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("1distance", 1000);
  //ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("kobuki/pwm", 1000);//topic to publish
  ros::Publisher chatter_pub = n.advertise<ras_arduino_msgs::PWM>("kobuki/pwm", 1000);//topic to publish


 ros::Subscriber sub = n.subscribe("motor_controller/twist", 1000, inputReferenceCallback);
 ros::Subscriber sub1 = n.subscribe("kobuki/encoders", 1000, encodersCallback);

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

//////////////////////////////////////////////////////////////////////////////////
    
    pwm_delta=(double) (wl-wl_hat)*ki_l;
    pwm1=(int) pwm1+pwm_delta;
    pwm_delta=(double) (wr-wr_hat)*ki_r;
    pwm2=(int) pwm2+pwm_delta;



//saturation 
    if(pwm1>255)
 	pwm1=255;

    if(pwm1<-255)
        pwm1=-255;

    if(pwm2>255)
        pwm2=255;

    if(pwm2<-255)
        pwm2=-255;



//////////////////////////////////////////////////////////////////////////////


    ras_arduino_msgs::PWM pwm_msg;
    pwm_msg.PWM1=pwm1;
    pwm_msg.PWM2=pwm2;

// %Tag(ROSCONSOLE)%

    ROS_INFO("write: loop=%5d - pwm1=%4d - pwm2=%4d",count,pwm1,pwm_msg.PWM2);//print in terminal
 //   ROS_INFO("%s", msg.data.c_str());
// %EndTag(ROSCONSOLE)%


// %Tag(PUBLISH)%
  //  chatter_pub.publish(msg);

 //   msg1.data=;
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
