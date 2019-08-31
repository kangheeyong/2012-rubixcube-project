#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "opencv_cube_final.h"
#include <cv.h>
#include "BlobLabeling.h"

int position[9][3],order;
IplImage *image,*image_h,*image_s,*image_v,*image_ready,*image_gray;
uchar *data,*data_h,*data_s,*data_v,*data_gray,*data_ready;
CvCapture *capture;

void filter(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)
	{
		for(x=0;x<640;x++)
		{
			if( ( data_h[ ( y * 640 ) + x ] >= 20+range || data_h[ ( y * 640 ) + x ] < 0+range ))	// || data_v[ ( y * 640 ) + x ] < 50
			{
				data_s[ ( y * 640 ) + x ] = 0;
				data_v[ ( y * 640 ) + x ] = 255;
			} 
		}
	}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,200,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����
}

void filter_p(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)
	{
		for(x=0;x<640;x++)
		{
			if( ( ( ( data_h[ ( y * 640 ) + x ] >= 170 || data_h[ ( y * 640 ) + x ] < 150 ) || data_s[ ( y * 640 ) + x ] >= 150 ) || data_s[ ( y * 640 ) + x ] < 80 ) || data_v[ ( y * 640 ) + x ] < 130 )	// || data_v[ ( y * 640 ) + x ] < 50
			{
				data_s[ ( y * 640 ) + x ] = 0;
				data_v[ ( y * 640 ) + x ] = 255;
			} 
		}
	}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,200,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����
}

void filter_r(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)	{		for(x=0;x<640;x++)		{			if( ( data_h[ ( y * 640 ) + x ] >= 10 && data_h[ ( y * 640 ) + x ] < 170 ))				{				data_s[ ( y * 640 ) + x ] = 0;				data_v[ ( y * 640 ) + x ] = 255;			} 			else			{				if( ( data_v[ ( y * 640 ) + x ] < 70 ))			{data_s[ ( y * 640 ) + x ] = 0;data_v[ ( y * 640 ) + x ] = 255;}}}}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,200,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����
}

void filter_b(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)
	{
		for(x=0;x<640;x++)
		{
			if( ( ( data_h[ ( y * 640 ) + x ] >= 30 || data_h[ ( y * 640 ) + x ] < 10 ) || data_s[ ( y * 640 ) + x ] > 220 ) || data_v[ ( y * 640 ) + x ] > 110 )	// || data_v[ ( y * 640 ) + x ] < 50
			{
				data_s[ ( y * 640 ) + x ] = 0;
				data_v[ ( y * 640 ) + x ] = 255;
			}
		}
	}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,250,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����
}

void filter_y(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)
	{
		for(x=0;x<640;x++)
		{
			if( ( ( data_h[ ( y * 640 ) + x ] >= 35 || data_h[ ( y * 640 ) + x ] < 20 ) || data_s[ ( y * 640 ) + x ] <= 130 ) || data_v[ ( y * 640 ) + x ] < 80 )	//   
			{
				data_s[ ( y * 640 ) + x ] = 0;
				data_v[ ( y * 640 ) + x ] = 255;
			} 
		}
	}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,250,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	//cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����
}

void filter_black(int range)
{
	int x,y;

	cvCvtColor(image,image_ready,40);							// ������ image ������ RGB���� HSV�� ��ȯ
	
	cvCvtPixToPlane(image_ready,image_h,image_s,image_v,NULL);// ��ȯ�� HSV ���� H,S,V ���� ������

	data_h = (uchar *)image_h->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_s = (uchar *)image_s->imageData;				// ��ȯ�� HSV ���� ������ȭ
	data_v = (uchar *)image_v->imageData;				// ��ȯ�� HSV ���� ������ȭ

	for(y=0;y<480;y++)
	{
		for(x=0;x<640;x++)
		{
			if( ( data_s[ ( y * 640 ) + x ] <= 150 ) || data_v[ ( y * 640 ) + x ] > 100 )	//   
			{
				data_s[ ( y * 640 ) + x ] = 0;
				data_v[ ( y * 640 ) + x ] = 255;
			} 
		}
	}

	cvCvtPlaneToPix(image_h,image_s,image_v,NULL,image_ready);// ������ ���� �ϳ��� ��ġ��

	data_ready = (uchar *)image_ready->imageData;

	cvCvtColor(image_ready,image_ready,54);							// ������ image ������ HSV���� RGB�� ��ȯ

	cvCvtColor(image_ready,image_gray,6);						// ������� �ٲٱ�

	data_gray = (uchar *)image_gray->imageData;

	cvThreshold(image_gray,image_gray,200,255,0);		// ������� �ٲ� �׸� ����ȭ
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	//cvErode(image_gray,image_gray);						// ����ȭ�� ħ�� ����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����
	cvDilate(image_gray,image_gray);						// ����ȭ�� ��â����

	//cvCanny(image_gray,image_gray,100,200,3);			// ����ȭ �� �׸� ���� ����

	cvNot(image_gray,image_gray);	// �̹��� ���� ����

}

void labeling_r(int range)
{
	int a;

	filter_r(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

		position[order][0] = ( blob.m_recBlobs[a].x + pt1.x + blob.m_recBlobs[a].width )/2;
		position[order][1] = ( blob.m_recBlobs[a].y + pt1.y + blob.m_recBlobs[a].height )/2;
		position[order][2] = 17;
		order++;
	}
}

void labeling_b(int range)
{
	int a;

	filter_b(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

		position[order][0] = ( blob.m_recBlobs[a].x + pt1.x + blob.m_recBlobs[a].width )/2;
		position[order][1] = ( blob.m_recBlobs[a].y + pt1.y + blob.m_recBlobs[a].height )/2;
		position[order][2] = 10;
		order++;
	}
}

void labeling_p(int range)
{
	int a;

	filter_p(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

		position[order][0] = ( blob.m_recBlobs[a].x + pt1.x + blob.m_recBlobs[a].width )/2;
		position[order][1] = ( blob.m_recBlobs[a].y + pt1.y + blob.m_recBlobs[a].height )/2;
		position[order][2] = 15;
		order++;
	}
}

void labeling_y(int range)
{
	int a;

	filter_y(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

		position[order][0] = ( blob.m_recBlobs[a].x + pt1.x + blob.m_recBlobs[a].width )/2;
		position[order][1] = ( blob.m_recBlobs[a].y + pt1.y + blob.m_recBlobs[a].height )/2;
		position[order][2] = 20;
		order++;
	}
}

void labeling_black(int range)
{
	int a;

	filter_black(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

	}
}

void labeling(int range)
{
	int a;

	filter(range);

	CBlobLabeling blob;
	blob.SetParam(image_gray,1000);
	blob.DoLabeling();

	for(a=0;a<blob.m_nBlobs;a++)
	{
		CvPoint pt1 = cvPoint(blob.m_recBlobs[a].x,blob.m_recBlobs[a].y);
		CvPoint pt2 = cvPoint(pt1.x + blob.m_recBlobs[a].width, pt1.y + blob.m_recBlobs[a].height);

		CvScalar color = cvScalar(0,0,255);

		cvDrawRect(image,pt1,pt2,color);

		position[order][0] = ( blob.m_recBlobs[a].x + pt1.x + blob.m_recBlobs[a].width )/2;
		position[order][1] = ( blob.m_recBlobs[a].y + pt1.y + blob.m_recBlobs[a].height )/2;
		position[order][2] = range;
		order++;
	}
}

void change(int i)
{
	int temp[3];

	temp[0] = position[i][0];	temp[1] = position[i][1];	temp[2] = position[i][2];
	position[i][0] = position[i+1][0];	position[i][1] = position[i+1][1];	position[i][2] = position[i+1][2];
	position[i+1][0] = temp[0];	position[i+1][1] = temp[1];	position[i+1][2] = temp[2];
}

void line_up()
{
	int r,i;
	for(r = 0;r < 8;r++)
	{
		for(i=0;i<8;i++)
		{
			if( ( position[i][0] - position[i+1][0] ) > 50 ) change(i);
		}
		for(i=0;i<8;i++)
		{
			if( ( position[i+1][0] - position[i][0] ) < 50 && position[i][1] > position[i+1][1] ) change(i);
		}
	}
}

void opencv::camera_on()
{
	capture = cvCaptureFromCAM(2);
}

void opencv::camera_off()
{
	cvReleaseCapture(&capture);
	cvDestroyWindow("image");
}

void opencv::image_set()
{
	image = cvCreateImage(cvSize(640,480),8,3);				// ī�޶� Ȯ�� ���� ���� ����
	image_h = cvCreateImage(cvSize(640,480),8,1);			// HSV �� ���� ���� ����
	image_s = cvCreateImage(cvSize(640,480),8,1);			// HSV �� ���� ���� ����
	image_v = cvCreateImage(cvSize(640,480),8,1);			// HSV �� ���� ���� ����
	image_gray = cvCreateImage(cvSize(640,480),8,1);		// ��� �����
	image_ready = cvCreateImage(cvSize(640,480),8,3);
}

void opencv::camera_capture(int time)
{
	int a,time_check=0;
	while(time_check != time )
	{
		cvGrabFrame(capture);
		image = cvRetrieveFrame(capture);
		data = (uchar *)image->imageData;

		cvSubS(image,CV_RGB(30,30,30),image);

		order = 0;

		labeling(100);							// blue
		labeling(50);							// green
		labeling_p(150);						// pink
		labeling_r(170);						// red
		labeling_b(0);							// brown
		labeling_y(0);							// yellow

		line_up();

		cvShowImage("image",image);
/*
		for(a = 0; a<9 ; a++ )
			printf("%3d  %3d  %3d\n",position[a][0],position[a][1],position[a][2]);
		for(a = 0; a<3 ; a++)
			printf("   %3d    %3d   %3d\n\n",position[a][2],position[a+3][2],position[a+6][2]);
*/
		if( cvWaitKey(5) == 97 )
			break;

		time_check++;

		cvWaitKey(10);
		system("cls");
	}
	for( int r=0 ; r<9 ; r++)
	{
		cube_data[r] = position[r][2];
	}
}