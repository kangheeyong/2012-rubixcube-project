#include <stdio.h>
#include <iostream>
#include <stdlib.h>

//#include <WinDef.h>

#ifndef __OPENCV_CUBE_H__
#define __OPENCV_CUBE_H__

class opencv
{
private:
	
public:
	int cube_data[9];
	void camera_on();
	void camera_off();
	void image_set();
	void camera_capture(int time);
};

#endif