/*
 * ros_caffe_test.cpp
 *
 *  Created on: Aug 31, 2015
 *      Author: Tzutalin
 */

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "Classifier.h"
#include <dirent.h>  
using namespace std;
const std::string RECEIVE_IMG_TOPIC_NAME = "camera/rgb/image_raw";
const std::string PUBLISH_RET_TOPIC_NAME = "/caffe_ret";

Classifier* classifier;
std::string model_path;
std::string weights_path;
std::string mean_file;
std::string label_file;
std::string image_path;

ros::Publisher gPublisher;

void publishRet(const std::vector<Prediction>& predictions);

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        //cv::imwrite("rgb.png", cv_ptr->image);
		cv::Mat img = cv_ptr->image;
		std::vector<Prediction> predictions = classifier->Classify(img);
		publishRet(predictions);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

// TODO: Define a msg or create a service
// Try to receive : $rostopic echo /caffe_ret
void publishRet(const std::vector<Prediction>& predictions)  {
    std_msgs::String msg;
    std::stringstream ss;
    for (size_t i = 0; i < predictions.size(); ++i) {
        Prediction p = predictions[i];
        ss << "[" << p.second << " - " << p.first << "]" << std::endl;
    }
    msg.data = ss.str();
    gPublisher.publish(msg);
}
string filePath = "/home/roger/WorkSpace/caffe/have-fun-with-machine-learning/data/untrained-samples";  

int main(int argc, char **argv) {
    struct dirent *ptr;      
    DIR *dir;
    ros::init(argc, argv, "ros_caffe_test");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    // To receive an image from the topic, PUBLISH_RET_TOPIC_NAME
    image_transport::Subscriber sub = it.subscribe(RECEIVE_IMG_TOPIC_NAME, 1, imageCallback);
	gPublisher = nh.advertise<std_msgs::String>(PUBLISH_RET_TOPIC_NAME, 100);
    const std::string ROOT_SAMPLE = ros::package::getPath("ros_caffe");
    model_path = "/home/roger/Downloads/20170820-114817-f935_epoch_30.0/deploy.prototxt";
    weights_path = "/home/roger/Downloads/20170820-114817-f935_epoch_30.0/snapshot_iter_30.caffemodel";
    mean_file = "/home/roger/Downloads/20170820-114817-f935_epoch_30.0/mean.binaryproto";
    label_file = "/home/roger/Downloads/20170820-114817-f935_epoch_30.0/labels.txt";
    image_path = "/home/roger/WorkSpace/caffe/have-fun-with-machine-learning/data/untrained-samples/seahorse3.jpg";

    classifier = new Classifier(model_path, weights_path, mean_file, label_file);


    dir=opendir(filePath.c_str());  

    vector<string> files;  
    cout << "文件列表: "<< endl;  
    while((ptr=readdir(dir))!=NULL)  
    {  
   
        //跳过'.'和'..'两个目录  
        if(ptr->d_name[0] == '.')  
            continue;  
        int i = 1;
        while(1){
            if(ptr->d_name[i] == '.')break;
            i++;
        }  
        //cout << ptr->d_name[i+1];
        if(ptr->d_name[i+1] == 'j')
            files.push_back(ptr->d_name);  
    }  

    for (int i = 0; i < files.size(); ++i)  
    {  
        //Test data/cat.jpg
        std::cout << files[i] <<std::endl;
        cv::Mat img = cv::imread("/home/roger/WorkSpace/caffe/have-fun-with-machine-learning/data/untrained-samples/"+files[i], -1);
     
        // Test data/cat.jpg
        // cv::Mat img = cv::imread(image_path, -1);
        std::vector<Prediction> predictions = classifier->Classify(img,2);
        /* Print the top N predictions. */
        std::cout << "Test default image under /data/cat.jpg" << std::endl;
        for (size_t i = 0; i < predictions.size(); ++i) {
            Prediction p = predictions[i];
            std::cout << std::fixed << std::setprecision(4) << p.second << " - \"" << p.first << "\"" << std::endl;
        }
    	publishRet(predictions);

        ros::spinOnce();
    }
    delete classifier;
    ros::shutdown();
    return 0;
}
