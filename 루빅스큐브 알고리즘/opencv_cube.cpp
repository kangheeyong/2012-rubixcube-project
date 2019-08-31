
#include "opencv_cube.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
//#include "BlobLabeling.h"
IplImage *image,*image_h,*image_s,*image_v;
uchar *data,*data_h,*data_s,*data_v;

CvCapture *capture;

int cube_ave[21][9];

void delay()
{
	for(int time = 0 ; time < 10000 ; time++ );
}

/* 프로토타입용 코드
void capture::start()
{
	number = 6;
	cout<<"카메라를 받기위한 프로그램 입니다."<<endl;
	cout<<"원하시는 메뉴를 선택해 주세요."<<endl;
	cout<<"1. 키보드 입력 없이 바로 카메라 영상 받기"<<endl;
	cout<<"2. 키보드 'a'입력시 카메라 영상 받기"<<endl;
	menu = getch();

	capture::check();
}

void capture::check()
{
	cout<<"체크 확인용 함수 입니다."<<endl;
	cout<<"계속 진행하시려면 아무키나 누르세요. "<<endl;

	switch(menu)
	{
		case 49:
			capture::camera_auto();
			break;
		case 50:
			capture::capture_n();
			break;
	}
}

void capture::capture_n()
{
	while( number!=0 )
	{
		cout<<number<<"번째 사진 입니다. "<<endl;
		system("cls");
		capture::camera_kb();
		number--;
	}
}

void capture::cube_color(int Red, int Green, int Blue, int num)
{
	if( ( Red-Blue ) > 50 )
	{
		if( ( Red-Green ) < 50 )	{	printf("yellow\n");	cube_data[number][num] = 1;	}
		else if( Green > 70 )	{	printf("orange\n");	cube_data[number][num] = 0;	}
		else	{	printf("red\n");	cube_data[number][num] = 2;	}
	}
	else if( ( Blue-Red ) > 50 )	{	printf("blue\n");	cube_data[number][num] = 5;	}
	else if( ( Green-Red ) > 30 )	{	printf("green\n");	cube_data[number][num] = 4;	}
	else	{	printf("white\n");	cube_data[number][num] = 3;	}
}

void capture::camera_auto()
{
	int h,w,Red,Green,Blue,height,width,num;
	int avr_r,avr_g,avr_b;
	unsigned int time;
    IplImage* image;
	uchar* data;

	image = cvCreateImage(cvSize(640,480),8,3);

    CvCapture* capture = cvCaptureFromCAM(0);

    cvNamedWindow( "T9-camera", 0 );

    cvResizeWindow( "T9-camera", 640, 480 );
	
	data = (uchar *)image->imageData;

	time = 0;
	num = 0;

    while(1)
	{
        cvGrabFrame( capture );
        image = cvRetrieveFrame( capture );

		data = (uchar *)image->imageData;
		avr_r = 0; avr_g = 0; avr_b = 0;
		for(int x=0;x<3;x++)
		{
			for(int y=0;y<3;y++)
			{
				num = x*3+y;
				printf("%d = ( %3d, %3d, %3d )",num,data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3]);
				
				Red = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2];
				Green = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1];
				Blue = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3];
				capture::cube_color(Red,Green,Blue,num);

				avr_r = avr_r + Red;
				avr_g = avr_g + Green;
				avr_b = avr_b + Blue;
			}
		}
		printf("\n\n%3d, %3d, %3d \n\n",avr_r/9,avr_g/9,avr_b/9);
		cout<<number<<endl;
		cout<<time<<endl;

		for(int x = 0;x<3;x++)
		{
			for( int y=0;y<3;y++)
			{
				CvPoint pt1 = cvPoint(160+x*136,80+y*136);
				CvPoint pt2 = cvPoint(240+x*136,160+y*136);

				CvScalar color = cvScalar(0,0,255);
				cvDrawRect(image,pt1,pt2,color);
			}
		}

        cvShowImage( "T9-camera", image );
  
        if( time == 30 )	//================================================== 큐브 데이터 받는 부분 입니다. cube_data[9]에 데이터 저장
		{
			cvSaveImage("line.jpg",image);
			time = 0;
			number--;
			if( number == 0 )	break;
		}

		cvWaitKey(10);

		time++;
		system("cls");
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "T9-camera" );

	cvWaitKey();
}

void capture::camera_kb()
{
	int h,w,Red,Green,Blue,height,width,num,root;
	int avr_r,avr_g,avr_b;
    IplImage* image;
	uchar* data;

	image = cvCreateImage(cvSize(640,480),8,3);

    CvCapture* capture = cvCaptureFromCAM(2);

    cvNamedWindow( "T9-camera", 0 );

    cvResizeWindow( "T9-camera", 640, 480 );
	
	data = (uchar *)image->imageData;

	num = 0;

    while(1)
	{
        cvGrabFrame( capture );
        image = cvRetrieveFrame( capture );

		data = (uchar *)image->imageData;
		avr_r = 0; avr_g = 0; avr_b = 0;
		for(int x=0;x<3;x++)
		{
			for(int y=0;y<3;y++)
			{
				num = x*3+y;
				printf("%d = ( %3d, %3d, %3d )",num,data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3]);
				Red = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2];
				Green = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1];
				Blue = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3];
				capture::cube_color(Red,Green,Blue,num);

				avr_r = avr_r + Red;
				avr_g = avr_g + Green;
				avr_b = avr_b + Blue;
			}
		}
		printf("\n\n%3d, %3d, %3d",avr_r/9,avr_g/9,avr_b/9);

		for(int x = 0;x<3;x++)
		{
			for( int y=0;y<3;y++)
			{
				CvPoint pt1 = cvPoint(160+x*136,80+y*136);
				CvPoint pt2 = cvPoint(240+x*136,160+y*136);

				CvScalar color = cvScalar(0,0,255);
				cvDrawRect(image,pt1,pt2,color);
			}
		}

        cvShowImage( "T9-camera", image );
  
        if( cvWaitKey(10) == 97 )
		{
			cvSaveImage("line.jpg",image);
			break;
		}
		system("cls");
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "T9-camera" );

	cvWaitKey();
}

void capture::camera_on()
{
    IplImage* image;
	uchar* data;

    CvCapture* capture = cvCaptureFromCAM(0);
	
}

void capture::camera_cap()
{
	IplImage* image;
	uchar* data;

	image = cvCreateImage(cvSize(640,480),8,3);
	data = (uchar *)image->imageData;

    cvNamedWindow( "T9-camera", 0 );

    cvResizeWindow( "T9-camera", 640, 480 );

	CvCapture* capture = cvCaptureFromCAM(0);

	cvGrabFrame( capture );
    image = cvRetrieveFrame( capture );

	for(int x=0;x<3;x++)
	{
		for(int y=0;y<3;y++)
		{
			num = x*3+y;
			//printf("%d = ( %3d, %3d, %3d )",num,data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1],data[(120 + 136*x)*(640*3) + (200 + 136*y)*3]);
				
			Red = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+2];
			Green = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3+1];
			Blue = data[(120 + 136*x)*(640*3) + (200 + 136*y)*3];
			capture::cube_color(Red,Green,Blue,num);

		}
	}
}

*/


void cube_JK::camera_on()
{
	capture = cvCaptureFromCAM(2);				// 카메라 전원 켜기
}

void cube_JK::camera_capture(int time)
{
	int round = 0;

	image = cvCreateImage(cvSize(640,480),8,3);				// 카메라 확면 받을 변수 선언
	image_h = cvCreateImage(cvSize(640,480),8,1);			// HSV 값 받을 변수 선언
	image_s = cvCreateImage(cvSize(640,480),8,1);			// HSV 값 받을 변수 선언
	image_v = cvCreateImage(cvSize(640,480),8,1);

	cvNamedWindow("CAM1_RGB",1);								// 카메라 영상 띄울 윈도우 창 생성

	while(round != time)
	{
		cout<<round<<endl;

		cvGrabFrame(capture);								// 카메라에서 영상 가져오기
		image = cvRetrieveFrame(capture);					// 가져온 영상 image 변수에 저장

//		cvSubS(image,CV_RGB(30,30,30),image);

		for(int x = 0;x<3;x++)								// 9개의 사각형 레이블링 입히기
		{
			for( int y=0;y<3;y++)
			{
				CvPoint pt1 = cvPoint(160+x*136,80+y*136);
				CvPoint pt2 = cvPoint(240+x*136,160+y*136);

				CvScalar color = cvScalar(0,0,255);
				cvDrawRect(image,pt1,pt2,color);
			}
		}
		
		cvShowImage("CAM1_RGB",image);						// image를 정해진 윈도우 창에 출력

		data = (uchar *)image->imageData;					// image에 저장된 이미지의 데이터화

		cvCvtColor(image,image,40);							// 가져온 image 영상을 RGB에서 HSV로 변환
		cvCvtPixToPlane(image,image_h,image_s,image_v,NULL);// 변환된 HSV 값을 H,S,V 별로 나누기

		data_h = (uchar *)image_h->imageData;				// 변환된 HSV 값을 데이터화
		data_s = (uchar *)image_s->imageData;				// 변환된 HSV 값을 데이터화
		data_v = (uchar *)image_v->imageData;				// 변환된 HSV 값을 데이터화

		for(int y=0;y<3;y++)								// 9개의 사각형 레이블링 입히기
			for(int x = 0;x<3;x++)
				cube_JK::color_print( data_h[ ( 200 + ( 136 * x ) ) + ( 640 * ( 120 + ( 136 * y ) ) ) ], ( x + y*3 ) );	// 색 판단 및 프린트

		cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image);// 나눠진 값을 하나로 합치기

		cvCvtColor(image,image,54);							// 가져온 image 영상을 RGB에서 HSV로 변환
		
//		if( cvWaitKey(5) == 97 ) break;						// 'a'라는 키를 누르면 종료
		cvWaitKey(5);	round++;
		system("cls");

		if( cvWaitKey(5) == 97 ) break;
	}
}

void cube_JK::color_print(int value,int num)
{
	for( int x = 18; x >= 0 ; x-- )
		cube_ave[x+1][num] = cube_ave[x][num];


		     if( value <= 26  && value >= 5 )	cube_ave[0][num] = value;//  18 > value >   0
		else if( value <= 38  && value >= 27 )	cube_ave[0][num] = value;//  38 > value >  15
		else if( value <= 100 && value >= 40 )	cube_ave[0][num] = value;//  80 > value >  50
		else if( value <= 120 && value >= 101 )	cube_ave[0][num] = value;// 110 > value > 100
		else if( value <= 169 && value >= 140 )	cube_ave[0][num] = value;// 155 > value > 140
		else if( value <= 180 && value >= 170 )	cube_ave[0][num] = value;// 180 > value > 170
		else cube_ave[0][num] = cube_ave[1][num];

	cube_ave[20][num] = 0;
	for( int y = 0 ; y < 20 ; y++ )
		cube_ave[20][num] = cube_ave[20][num] + cube_ave[y][num];
	cube_ave[20][num] = cube_ave[20][num] / 20;

	printf("( %d )",num);
	     if( cube_ave[20][num] <= 26  && cube_ave[20][num] >= 5 )	{	cube_data[num] = 10;		printf("   %3d   갈( 6 )    ",cube_ave[20][num]);	}//  18 > cube_ave[20][num] >   0
	else if( cube_ave[20][num] <= 38  && cube_ave[20][num] >= 27 )	{	cube_data[num] = 11;		printf("   %3d   노( 1 )    ",cube_ave[20][num]);	}//  38 > cube_ave[20][num] >  15
	else if( cube_ave[20][num] <= 100 && cube_ave[20][num] >= 40 )	{	cube_data[num] = 12;		printf("   %3d   초( 2 )    ",cube_ave[20][num]);	}//  80 > cube_ave[20][num] >  50
	else if( cube_ave[20][num] <= 120 && cube_ave[20][num] >= 101 )	{	cube_data[num] = 13;		printf("   %3d   파( 8 )    ",cube_ave[20][num]);	}// 110 > cube_ave[20][num] > 100
	else if( cube_ave[20][num] <= 169 && cube_ave[20][num] >= 140 )	{	cube_data[num] = 14;		printf("   %3d   분( 3 )    ",cube_ave[20][num]);	}// 155 > cube_ave[20][num] > 140
	else if( cube_ave[20][num] <= 180 && cube_ave[20][num] >= 170 )	{	cube_data[num] = 15;		printf("   %3d   빨( 7 )    ",cube_ave[20][num]);	}// 180 > cube_ave[20][num] > 170
	else										printf("   %3d    error     ",cube_ave[20][num]);
	if( num%3 == 2 )	printf("\n");
}

void cube_JK::camera_off()
{
	cvReleaseCapture(&capture);								// 메모리 반환
	cvDestroyWindow("CAM1");								// 윈도우 창 종료
}

void cube_JK::wait_key(int num)
{
	cvWaitKey(num);
}