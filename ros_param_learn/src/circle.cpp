#include <ros/ros.h>
#include <iostream>
#include <string>
#include <geometry_msgs/Twist.h>
/*******

rosparam与param的不同在于，rosparam可以导入.yaml格式的文件内容设置参数，在需要设置大量参数时，rosparam更加实用。yaml的语法十分简单，几乎就是 参数名：参数值 的形式


*****/
int main(int argc, char ** argv){
	ros::init(argc, argv, "circle");
	ros::NodeHandle nh;
	ros::NodeHandle n("~");
	std::string str1,str2;


	geometry_msgs::Twist T;
	if(!nh.getParam("speed", T.linear.x)){            //获取全局参数
		ROS_ERROR("Get Speed Error");
		return 0;
	}

	int index = 3;
	nh.param("speed", index, index);       //nh.param<std::string>("default_param", default_param, "default_value");  
	                                    //该函数获取参数服务器上的speed， 有则给index赋值， 如果没有则用
											//函数中定义的变量index给自身赋值



	nh.setParam("string_param","str1");  //这句通过代码来向参数服务器添加全局参数
	n.setParam("string_param","str2");   //私有参数通过设置句柄为私有来实现，和上面不同，一个全局，一个私有

	  
	nh.getParam("string_param", str1);    //获取全局参数
	n.getParam("string_param", str2);     // 获取私有参数



	T.angular.z = T.linear.x / 2.0;

	ros::Publisher twist_pb = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);

	ros::Rate rate(1);
	while(ros::ok()){
		twist_pb.publish(T);
		ros::spinOnce();
		ROS_INFO("the index is ");
		std::cout<<index<<"     str :"<<str1<<","<<str2<<std::endl;
		rate.sleep();
	}
	return 0;
}