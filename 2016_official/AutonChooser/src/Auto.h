#ifndef AUTO_H
#define AUTO_H

#include "WPILib.h"

class Auto{
private:

	bool targetAcquired;
	enum AutonPos{LEFT, RIGHT, NONE};
	enum AutonMode{TERRAIN, ARM, NONE_};
	AutonMode mode;
	AutonPos pos;
public:
	Auto();
	Auto(int mode, int pos);
	~Auto();

};



#endif /* SRC_AUTO_H_ */