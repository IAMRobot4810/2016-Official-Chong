/*
 * ImageProcess.h
 *
 *  Created on: Feb 15, 2016
 *      Author: NinjaPC
 */

#ifndef SRC_IMAGEPROCESS_H_
#define SRC_IMAGEPROCESS_H_

#include "WPILib.h"

class ImageProcess {
public:
	ImageProcess();
	virtual ~ImageProcess();
public:
	struct ParticleReport {
		double PercentAreaToImageArea;
		double Area;
		double BoundingRectLeft;
		double BoundingRectTop;
		double BoundingRectRight;
		double BoundingRectBottom;
	};
	struct Scores {
		double Area;
		double Aspect;
	};
	double VIEW_ANGLE = 49.4;
	Image *frame;
	Image *binaryFrame;
	int imaqError;
	ParticleFilterCriteria2 criteria[1];
	ParticleFilterOptions2 filterOptions = {0,0,1,1};
	Scores scores;
	bool CompareParticleSizes(ParticleReport particle1, ParticleReport particle2);
	double ratioToScore(double ratio);
	double AreaScore(ParticleReport report);
	double AspectScore(ParticleReport report);
	double computeDistance (Image *image, ParticleReport report);

};

#endif /* SRC_IMAGEPROCESS_H_ */
