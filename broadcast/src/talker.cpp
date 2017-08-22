
#include "ros/ros.h"

#include "std_msgs/String.h"
#include "broadcast/RecObject.h"
#include "broadcast/ObjectsStamped.h"
#include <sstream>
using namespace std;
/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<broadcast::ObjectsStamped>("/we_vision/UnknownObj", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    string name = "unknown";

    std_msgs::Header* header = new std_msgs::Header;
  //Option: world laser_link map odom....
    header->frame_id = "/base_link";
    header->stamp = ros::Time::now();
    geometry_msgs::Pose p;//(2,2,2,2,2,2);

    p.position.x = 0.83179;
    p.position.y = -0.017;
    p.position.z = 0.831;

    p.orientation.w = 0.0;
    p.orientation.x = 0.0;
    p.orientation.y = 0.0;
    p.orientation.z = 0.0;

    broadcast::RecObject rect;
    rect.name = name; rect.color= "voilet"; rect.shape= "";
    rect.pose = p;

    rect.length = 0.0743365287781;
    rect.width = 0.0742703378201;
    rect.height = 0.0866529345512;

    broadcast::ObjectsStamped obs;
    obs.header = *header;
    obs.objects.resize(1);
    obs.objects[0] = rect;

    chatter_pub.publish(obs);

    ros::spinOnce();

    loop_rate.sleep();

    ++count;
  }


  return 0;
}
