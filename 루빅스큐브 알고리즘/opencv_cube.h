#include <iostream>

#ifndef __OPENCV_CUBE_H__
#define __OPENCV_CUBE_H__

using namespace std;

namespace help
{
	void help_cube();
}

/*	기존 프로토타입용 코드
class capture
{
private:
	int number;
	int menu;
	
public:
	int h,w,Red,Green,Blue,height,width,num;
	int avr_r,avr_g,avr_b;
	unsigned int time;
	int cube_data[6][9];
	void start();
	void check();
	void capture_n();
	void camera_auto();
	void camera_kb();
	void cube_color(int Red, int Green, int Blue, int num);
	void camera_on();
	void camera_cap();
};
*/

class cube_JK
{
private:

public:
	int cube_data[9];

	void camera_on();
	void camera_capture(int time);
	void color_print(int value,int num);
	void camera_off();

	void wait_key(int num);
};

#endif