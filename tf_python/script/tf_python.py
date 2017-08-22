#!/usr/bin/env python

import rospy
import tf
import tf2_ros
import geometry_msgs.msg

br = tf2_ros.TransformBroadcaster()
def message_from_transform(T):
	msg = geometry_msgs.msg.Transform();
	q = tf.transformations.quaternion_from_matrix(T)
	translation = tf.transformations.translation_from_matrix(T)
	msg.translation.x = translation[0]
	msg.translation.y = translation[1]
	msg.translation.z = translation[2]

	msg.rotation.x = q[0]
	msg.rotation.y = q[1]
	msg.rotation.z = q[2]
	msg.rotation.w = q[3]

	return msg

def publish_transform():
	T1 = tf.transformations.concatenate_matrices(
		tf.transformations.translation_matrix((1,1,0)),
		# euler --> quaternion --> matrix
		tf.transformations.quaternion_matrix(
			tf.transformations.quaternion_from_euler(1,1,1))
	)


	T1_stamped = geometry_msgs.msg.TransformStamped()
	T1_stamped.header.stamp = rospy.Time.now()
	T1_stamped.header.frame_id = "world"
	T1_stamped.child_frame_id = "F1"
	T1_stamped.transform = message_from_transform(T1)
	br.sendTransform(T1_stamped)


	T2 = tf.transformations.concatenate_matrices(
		tf.transformations.translation_matrix((1,0,0)),
		tf.transformations.quaternion_matrix(
			tf.transformations.quaternion_about_axis(1.57,(1,0,0)))
		)

	T2_stamped = geometry_msgs.msg.TransformStamped()
	T2_stamped.header.stamp = rospy.Time.now()
	T2_stamped.header.frame_id = "F1"
	T2_stamped.child_frame_id = "F2"
	T2_stamped.transform = message_from_transform(T2)
	br.sendTransform(T2_stamped)


	T2_inverse = tf.transformations.inverse_matrix(T2)
	T3_stamped = geometry_msgs.msg.TransformStamped()
	T3_stamped.header.stamp = rospy.Time.now()
	T3_stamped.header.frame_id = "F2"
	T3_stamped.child_frame_id = "F3"
	T3_stamped.transform = message_from_transform(T2_inverse)
	br.sendTransform(T3_stamped)

	T1_inverse = tf.transformations.inverse_matrix(T1)
	T4_stamped = geometry_msgs.msg.TransformStamped()
	T4_stamped.header.stamp = rospy.Time.now()
	T4_stamped.header.frame_id = "F3"
	T4_stamped.child_frame_id = "F4"
	T4_stamped.transform = message_from_transform(T1_inverse)
	br.sendTransform(T4_stamped)
if __name__ == "__main__":
	rospy.init_node("tf_python")


	rospy.sleep(0.5)
	while not rospy.is_shutdown():
		publish_transform()
		rospy.sleep(0.5)



