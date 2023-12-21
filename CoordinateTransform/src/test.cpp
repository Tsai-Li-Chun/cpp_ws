#include <iostream>

#include "CoordinateTransformation.h"
#include "M5Manipulator.h"

using namespace std;

void ShowMatrix(const Matrix4d matrix) {
	printf("\
		%10.4lf , %10.4lf , %10.4lf , %10.4lf\n\
		%10.4lf , %10.4lf , %10.4lf , %10.4lf\n\
		%10.4lf , %10.4lf , %10.4lf , %10.4lf\n\
		%10.4lf , %10.4lf , %10.4lf , %10.4lf\n\n",
		matrix(0,0), matrix(0,1), matrix(0,2), matrix(0,3),
		matrix(1,0), matrix(1,1), matrix(1,2), matrix(1,3), 
		matrix(2,0), matrix(2,1), matrix(2,2), matrix(2,3), 
		matrix(3,0), matrix(3,1), matrix(3,2), matrix(3,3));
}

int main() {
	CoordinateTransformation coordinate_transformation;
	// CoordinateTransformation Integration Test
	/*******************************************************************************************************/
	// set eye-in-hand hand-eye calibration parameter
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	Matrix4d camera_robot_flange_to_camera = Matrix4d::Identity();
	camera_robot_flange_to_camera(0, 0) = 0.0322889;  camera_robot_flange_to_camera(0, 1) = -0.999467;    camera_robot_flange_to_camera(0, 2) =  0.00485068;	 camera_robot_flange_to_camera(0, 3) =  88.3186;
	camera_robot_flange_to_camera(1, 0) = 0.986447;  camera_robot_flange_to_camera(1, 1) =  0.0310864;   camera_robot_flange_to_camera(1, 2) = -0.161107;	 camera_robot_flange_to_camera(1, 3) = 267.454;
	camera_robot_flange_to_camera(2, 0) = 0.16087;  camera_robot_flange_to_camera(2, 1) =  0.00998691;  camera_robot_flange_to_camera(2, 2) =  0.986925;	 camera_robot_flange_to_camera(2, 3) =  85.1095;
	coordinate_transformation.SetCameraRobotFlangeToCameraTransMatrix(camera_robot_flange_to_camera);
	//std::cout << "(camera_robot) hand_eye_calibration_parameter :" << std::endl;
	//ShowMatrix(camera_robot_flange_to_camera);
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	// set two-robot root calibrated pose : camera_robot
	//------------------------------------------------------------------------------------------------//
	Pose camera_robot_root_to_flange_calibration;
	camera_robot_root_to_flange_calibration.SetData(228.235, 11.997, 1143.138, 179.997, -50.598, 3.009); // x,y,z,Rx,Ry,Rz
	//std::cout << "(camera_robot) root_to_flange :" << std::endl;
	//ShowMatrix(camera_robot_root_to_flange_calibration.GetData());
	//------------------------------------------------------------------------------------------------//

	// set calibrated (gripper) object information in camera frame
	//-----------------------------------------------------------------------------------------------------------------------------------------//
	Pose guide_robot_gripper_object_in_camera_frame_calibration;
	guide_robot_gripper_object_in_camera_frame_calibration.SetData(-225.805450, 29.109203, 970.318481, -0.069917, -0.292780, 0.836101, 0.458613); // x,y,z,qw,qx,qy,qz
	//std::cout << "calibrated_object_in_camera_frame :" << std::endl;
	//ShowMatrix(calibrated_object_in_camera_frame.GetData());
	//-----------------------------------------------------------------------------------------------------------------------------------------//


	// set gripper object information
	//----------------------------------------------------------------------------------------------------------//
	Matrix4d guide_robot_flange_to_gripper_object = Matrix4d::Identity();
	guide_robot_flange_to_gripper_object(2, 3) = 100.0;
	coordinate_transformation.SetGuideRobotFlangeToGripperObjectTransMatrix(guide_robot_flange_to_gripper_object);
	//----------------------------------------------------------------------------------------------------------//


	// set two-robot root calibrated pose : guid_robot
	//---------------------------------------------------------------------------------------------------//
	Pose guide_robot_root_to_flange_calib;
	guide_robot_root_to_flange_calib.SetData(703.321, 467.095, 350.559, -102.564, -37.113, -6.311);
	//std::cout << "(guide_robot) root_to_flange_calib :" << std::endl;
	//ShowMatrix(guide_robot_root_to_flange_calib.GetData());

	// calibrate two robot
	coordinate_transformation.CalibrateTwoRobotRoot(camera_robot_root_to_flange_calibration,
	                                                guide_robot_gripper_object_in_camera_frame_calibration,
	                                                guide_robot_root_to_flange_calib);
	//---------------------------------------------------------------------------------------------------//


	// get calibration info between two robot root
	//-----------------------------------------------------------------------------------------------------------------------//
	Matrix4d guide_robot_root_to_camera_robot_root = coordinate_transformation.GetGuideRobotRootToCameraRobotRootTransMatrix();
	//std::cout << "(guide_robot_) root to (camera_robot_) root :" << std::endl;
	//ShowMatrix(guide_robot_root_to_camera_robot_root);
	//-----------------------------------------------------------------------------------------------------------------------//


	//===================================================================================================================//
	// set (camera_robot) new pose
	Pose camera_robot_root_to_flange_new;
	camera_robot_root_to_flange_new.SetData(228.235, 11.997, 1143.138, 179.997, -50.598, 3.009); // x,y,z,Rx,Ry,Rz
	//std::cout << "new (camera_robot) root_to_flange :" << std::endl;
	//ShowMatrix(camera_robot_root_to_flange_new.GetData());

	// set new target object information in camera frame
	Pose targe_object_in_camera_frame_new;
	targe_object_in_camera_frame_new.SetData(-109.971405, 215.542267, 1037.727905, 0.667311, -0.094541, 0.534988, -0.509457); // x,y,z,qw,qx,qy,qz
	//std::cout << "new target_object_in_camera_frame :" << std::endl;
	//ShowMatrix(targe_object_in_camera_frame_new.GetData());

	double x, y, z, Rx, Ry, Rz;

	Pose camera_robot_root_to_target_object_new;
	coordinate_transformation.CalculateObjectInCameraRobotRoot(camera_robot_root_to_flange_new,
	                                                           targe_object_in_camera_frame_new,
	                                                           camera_robot_root_to_target_object_new);
	//std::cout << "(camera_robot) root_to_new_target_object :" << std::endl;
	//ShowMatrix(camera_robot_root_to_target_object_new.GetData());

	camera_robot_root_to_target_object_new.GetData(x, y, z, Rx, Ry, Rz);
	printf("(camera_robot) root_to_new_target_object pose : %lf , %lf , %lf , %lf , %lf , %lf\n\n\n", x, y, z, Rx, Ry, Rz);

	Pose guide_robot_root_to_target_object_new;
	coordinate_transformation.CalculateObjectInGuideRobotRoot(camera_robot_root_to_flange_new,
	                                                          targe_object_in_camera_frame_new,
	                                                          guide_robot_root_to_target_object_new);
	//std::cout << "(guide_robot) root_to_new_target_object :" << std::endl;
	//ShowMatrix(guide_robot_root_to_target_object_new.GetData());

	guide_robot_root_to_target_object_new.GetData(x, y, z, Rx, Ry, Rz);
	printf("(guide_robot) root_to_new_target_object pose : %lf , %lf , %lf , %lf , %lf , %lf\n\n", x, y, z, Rx, Ry, Rz);
	//===================================================================================================================//
	/*******************************************************************************************************/

	return 0;
}