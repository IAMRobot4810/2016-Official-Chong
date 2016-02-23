/*
 * ImageProcess.h
 *
 *  Created on: Feb 15, 2016
 *      Author: NinjaPC
 */

#include "WPILib.h"

#ifndef SRC_IMAGEPROCESS_H_
#define SRC_IMAGEPROCESS_H_

class ImageProcess {
private:

public:
	ImageProcess();
	virtual ~ImageProcess();

	struct ParticleReport_ {
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
	static bool CompareParticleSizes(ParticleReport_ particle1, ParticleReport_ particle2);
	double ratioToScore(double ratio);
	double AreaScore(ParticleReport_ report);
	double AspectScore(ParticleReport_ report);
	double computeDistance (Image *image, ParticleReport_ report);
	Range RING_HUE_RANGE = {101, 64};
	Range RING_SAT_RANGE = {88, 255};
	Range RING_VAL_RANGE = {134, 255};
	double AREA_MINIMUM = 0.5;
	double LONG_RATIO = 2.22;
	double SHORT_RATIO = 1.4;
	double SCORE_MIN = 75.0;

};

#endif /* SRC_IMAGEPROCESS_H_ */