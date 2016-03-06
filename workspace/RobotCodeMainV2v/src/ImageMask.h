#ifndef IMAGE_H
#define IMAGE_H

#include "WPILib.h"
#include "NIVision.h"

class ImageMask{
private:
	Image* image;
	Image* binaryImage;
	int error;

	Range RING_HUE_RANGE = {120, 100};
	Range RING_SAT_RANGE = {242, 255};
	Range RING_VAL_RANGE = {242, 255};
public:
	ImageMask();
	ImageMask(Image* img, Image* binImg, int imaqError);

	bool maskImage();
	Image* getbinImage();
	void setImage(Image* img);
	int getError();
};


#endif
