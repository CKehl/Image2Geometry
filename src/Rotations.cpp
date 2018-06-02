/*
 * Rotations.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: christian
 */

#include "Rotations.h"

RotationsCV::RotationsCV() {
	// TODO Auto-generated constructor stub

}

RotationsCV::~RotationsCV() {
	// TODO Auto-generated destructor stub
}

//This is x-y-z
cv::Mat RotationsCV::MatrixFromEulerXYZ(cv::Mat euler)
{
	cv::Mat Rx = cv::Mat::eye(3,3,euler.type());
	cv::Mat Ry = cv::Mat::eye(3,3,euler.type());
	cv::Mat Rz = cv::Mat::eye(3,3,euler.type());

	Rx.at<double>(1,1) = cos(euler.at<double>(0,0));
	Rx.at<double>(1,2) = sin(euler.at<double>(0,0));
	Rx.at<double>(2,1) = -sin(euler.at<double>(0,0));
	Rx.at<double>(2,2) = cos(euler.at<double>(0,0));

	Ry.at<double>(0,0) = cos(euler.at<double>(1,0));
	Ry.at<double>(0,2) = -sin(euler.at<double>(1,0));
	Ry.at<double>(2,0) = sin(euler.at<double>(1,0));
	Ry.at<double>(2,2) = cos(euler.at<double>(1,0));

	Rz.at<double>(0,0) = cos(euler.at<double>(2,0));
	Rz.at<double>(0,1) = sin(euler.at<double>(2,0));
	Rz.at<double>(1,0) = -sin(euler.at<double>(2,0));
	Rz.at<double>(1,1) = cos(euler.at<double>(2,0));

	return Rz*Ry*Rx;
}

//This is z-x-z
cv::Mat RotationsCV::MatrixFromEuler(cv::Mat euler)
{
	cv::Mat Rx = cv::Mat::eye(3,3,euler.type());
	cv::Mat Ry = cv::Mat::eye(3,3,euler.type());
	cv::Mat Rz = cv::Mat::eye(3,3,euler.type());

	Rx.at<double>(0,0) = cos(euler.at<double>(0,0));
	Rx.at<double>(0,1) = sin(euler.at<double>(0,0));
	Rx.at<double>(1,0) = -sin(euler.at<double>(0,0));
	Rx.at<double>(1,1) = cos(euler.at<double>(0,0));

	Ry.at<double>(1,1) = cos(euler.at<double>(1,0));
	Ry.at<double>(1,2) = -sin(euler.at<double>(1,0));
	Ry.at<double>(2,1) = sin(euler.at<double>(1,0));
	Ry.at<double>(2,2) = cos(euler.at<double>(1,0));

	Rz.at<double>(0,0) = cos(euler.at<double>(2,0));
	Rz.at<double>(0,1) = sin(euler.at<double>(2,0));
	Rz.at<double>(1,0) = -sin(euler.at<double>(2,0));
	Rz.at<double>(1,1) = cos(euler.at<double>(2,0));

	return Rz*Ry*Rx;
}

cv::Mat RotationsCV::EulerFromMatrix(cv::Mat matrix)
{
	cv::Mat result = cv::Mat::zeros(3,1,matrix.type());

	if(matrix.at<double>(2,2)==0)
	{
		result.at<double>(0,0) = atan2(matrix.at<double>(0,0), matrix.at<double>(0,1));
		result.at<double>(1,0) = acos(matrix.at<double>(2,2));
		result.at<double>(2,0) = -atan2(matrix.at<double>(0,0), matrix.at<double>(1,0));
	}
	else
	{
		result.at<double>(0,0) = atan2(matrix.at<double>(2,0), matrix.at<double>(2,1));
		result.at<double>(1,0) = acos(matrix.at<double>(2,2));
		result.at<double>(2,0) = -atan2(matrix.at<double>(0,2), matrix.at<double>(1,2));
	}
	return result;
}

cv::Mat RotationsCV::MatrixFromRodiguez(cv::Mat rodriguez)
{
	cv::Mat result;
	double theta = cv::norm(rodriguez);
	cv::Mat r = rodriguez/theta;
	cv::Mat I = cv::Mat::eye(3,3,CV_64FC1);
	double e_cross_data[] = {0, -r.at<double>(2,0), r.at<double>(1,0),   r.at<double>(2,0), 0, -r.at<double>(0,0),   -r.at<double>(1,0), r.at<double>(0,0), 0};
	result = I * cos(theta) + (1-cos(theta))*r*r.t() + cv::Mat(3,3, CV_64FC1, e_cross_data) * sin(theta);
	return result;
}

cv::Mat RotationsCV::QuaternionFromRodiguez(cv::Mat rodriguez)
{

	double theta = cv::norm(rodriguez);
	cv::Mat r = rodriguez/theta;
	double qi = r.at<double>(0,0) * sin(theta/2);
	double qj = r.at<double>(1,0) * sin(theta/2);
	double qk = r.at<double>(2,0) * sin(theta/2);
	double qr = cos(theta/2);
	double out_data[] = {qr, qi, qj, qk};
	cv::Mat result = cv::Mat(4,1,CV_64FC1,out_data);
	return result;
}

cv::Mat RotationsCV::QuaternionFromMatrix(cv::Mat matrix)
{
	double qr = 0.5 * sqrt(1+matrix.at<double>(0,0)+matrix.at<double>(1,1)+matrix.at<double>(2,2));
	double qi = (1/(4*qr))*(matrix.at<double>(2,1)-matrix.at<double>(1,2));
	double qj = (1/(4*qr))*(matrix.at<double>(0,2)-matrix.at<double>(2,0));
	double qk = (1/(4*qr))*(matrix.at<double>(1,0)-matrix.at<double>(0,1));
	double out_data[] = {qr, qi, qj, qk};
	cv::Mat result = cv::Mat(4,1,CV_64FC1,out_data);
	return result;
}

cv::Mat RotationsCV::RodriguezFromQuaternion(cv::Mat quaternion)
{
	double q_len = cv::norm(quaternion);
	cv::Mat r = quaternion/q_len;
	double theta = 2*acos(quaternion.at<double>(0,0));
	r = r*theta;
	return r;
}

cv::Mat RotationsCV::MatrixFromQuaternion(cv::Mat quaternion)
{
	double qr=quaternion.at<double>(0,0), qi=quaternion.at<double>(1,0), qj=quaternion.at<double>(2,0), qk=quaternion.at<double>(3,0);
	double qhat_data[] = {qr, qi, qj, qk};
	cv::Mat qhat = cv::Mat(3,1,CV_64FC1,qhat_data);
	cv::Mat I = cv::Mat::eye(3,3,CV_64FC1);
	cv::Mat sigma = cv::Mat::zeros(3,3,CV_64FC1);
	sigma.at<double>(0,1) = -qk; sigma.at<double>(0,2) = qj;
	sigma.at<double>(1,0) = qk; sigma.at<double>(1,2) = -qi;
	sigma.at<double>(2,0) = -qj; sigma.at<double>(2,1) = qi;
	cv::Mat result = (qr*qr-(qhat.dot(qhat)))*I + 2*(qhat * qhat.t()) - 2*qr*sigma;
	return result;
}

cv::Mat RotationsCV::QuaternionFromEuler(cv::Mat euler)
{
	double phi = euler.at<double>(0,0), theta = euler.at<double>(1,0), psi = euler.at<double>(2,0);
	//double qi = sin(phi/2)*cos(theta/2)*cos(psi/2) - cos(phi/2)*sin(theta/2)*sin(psi/2);
	//double qj = sin(phi/2)*cos(theta/2)*cos(psi/2) - cos(phi/2)*sin(theta/2)*sin(psi/2);
	//double qk = cos(phi/2)*sin(theta/2)*cos(psi/2) + sin(phi/2)*cos(theta/2)*sin(psi/2);
	//double qr = cos(phi/2)*cos(theta/2)*cos(psi/2) + sin(phi/2)*sin(theta/2)*sin(psi/2);
	double qi = cos((phi-psi)/2.)*sin(theta/2.);
	double qj = sin((phi-psi)/2.)*sin(theta/2.);
	double qk = sin((phi+psi)/2.)*cos(theta/2.);
	double qr = cos((phi+psi)/2.)*cos(theta/2.);
	double out_data[] = {qr, qi, qj, qk};
	cv::Mat result = cv::Mat(4,1,CV_64FC1,out_data);
	return result;
}

// Roll-Pitch-Yaw order
cv::Mat EulerFromQuaternion(cv::Mat quaternion)
{
	double qr=quaternion.at<double>(0,0), qi=quaternion.at<double>(1,0), qj=quaternion.at<double>(2,0), qk=quaternion.at<double>(3,0);
	double roll = std::atan2((qi*qk+qj*qr), -(qj*qk-qi*qr));
	double pitch = std::acos(-(qi*qi)-(qj*qj)+(qk*qk)+(qr*qr));
	double yaw = std::atan2((qi*qk-qj*qr), (qj*qk+qi*qr));
	double out_data[] = {roll,yaw, pitch};
	cv::Mat result = cv::Mat(3,1,CV_64FC1,out_data);
	return result;
}

