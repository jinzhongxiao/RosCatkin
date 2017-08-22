#!/usr/bin/env python
import roslib
roslib.load_manifest('tf_test')
import rospy
import math
import tf
import geometry_msgs.msg
import turtlesim.srv
if __name__ == "__main__":
    rospy.init_node("test")
    listener = tf.TransformListener()


    rate = rospy.Rate(10.0)

    while not rospy.is_shutdown():
        try:
            now =rospy.Time.now()
            past =  now - rospy.Duration(5.0)
            listener.waitForTransform("/turtle2",
                                          "/turtle1", past, rospy.Duration(1.0))
                                          #"/world", rospy.Duration(1.0))
            (trans, rot) = listener.lookupTransform("/turtle2",
                                          "/turtle1", past)
                                        #  "/world")
            print "______________"
            print trans
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue

        rate.sleep()
