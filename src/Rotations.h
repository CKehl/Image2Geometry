/*
 * Rotations.h
 *
 *  Created on: Jul 5, 2015
 *      Author: christian
 */

#ifndef ROTATIONS_H_
#define ROTATIONS_H_

#include "opencv_includes.h"

class RotationsCV {
	/*
	 * Euler angles represent here an extrinsic rotation
	 * (fixed coordinate system which does not turn after rotation application)
	 * for column-vector pre-multiplication (senseful)
	 * https://en.wikipedia.org/wiki/Euler_angles#Relationship_with_physical_motions
	 *
	 * Hence:
	 * R = Rz * Ry * Rx
	 * Hence: NO YAW-PITCH-ROLL
	 *
	 * all equations derived via:
	 * https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions#Conversion_formulae_between_formalisms
	 */
public:
	RotationsCV();
	virtual ~RotationsCV();

	static cv::Mat MatrixFromRodiguez(cv::Mat rodriguez);
	static cv::Mat MatrixFromEulerXYZ(cv::Mat euler);
	static cv::Mat MatrixFromEuler(cv::Mat euler);
	static cv::Mat MatrixFromQuaternion(cv::Mat quaternion);


	static cv::Mat QuaternionFromRodiguez(cv::Mat rodriguez);
	static cv::Mat QuaternionFromMatrix(cv::Mat matrix);
	static cv::Mat QuaternionFromEuler(cv::Mat euler);

	static cv::Mat RodriguezFromQuaternion(cv::Mat quaternion);

	static cv::Mat EulerFromMatrix(cv::Mat matrix);
	static cv::Mat EulerFromQuaternion(cv::Mat quaternion);
};

/*
class RotationsCV {
public:
	RotationsCV();
	virtual ~RotationsCV();

	static cv::Mat MatrixFromEuler(cv::Mat euler);
	static cv::Mat EulerFromMatrix(cv::Mat matrix);
};
*/

#endif /* ROTATIONS_H_ */
