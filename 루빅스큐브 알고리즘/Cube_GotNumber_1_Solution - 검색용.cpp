#include "Cube_GotNumber_1_Solution - 검색용.h"
#include <stdio.h>

void GotNumber_1 :: CUBE_Data_initialization(int (*p)[9])
{
	int i,j;
	for(i = 0 ; i <6 ; i++)
	{
		for(j = 0 ; j < 9 ; j++) p[i][j]=0;
	} 
	for(j = 0 ; j < 9 ; j++) p[1][j]=p[3][j]=1;
	p[5][1]=p[5][4]=p[5][7]=p[4][1]=p[4][4]=p[4][7]=2;

}
void GotNumber_1 :: CUBE_Data_print(int (*p)[9])
{
	printf ("         %d %d %d\n",p[0][0],p[0][1],p[0][2]);
	printf ("         %d %d %d\n",p[0][3],p[0][4],p[0][5]);
	printf ("         %d %d %d\n\n",p[0][6],p[0][7],p[0][8]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n",p[5][0],p[5][1],p[5][2],p[1][0],p[1][1],p[1][2],p[4][0],p[4][1],p[4][2]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n",p[5][3],p[5][4],p[5][5],p[1][3],p[1][4],p[1][5],p[4][3],p[4][4],p[4][5]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n\n",p[5][6],p[5][7],p[5][8],p[1][6],p[1][7],p[1][8],p[4][6],p[4][7],p[4][8]);
	printf ("         %d %d %d\n",p[2][0],p[2][1],p[2][2]);
	printf ("         %d %d %d\n",p[2][3],p[2][4],p[2][5]);
	printf ("         %d %d %d\n\n",p[2][6],p[2][7],p[2][8]);
	printf ("         %d %d %d\n",p[3][0],p[3][1],p[3][2]);
	printf ("         %d %d %d\n",p[3][3],p[3][4],p[3][5]);
	printf ("         %d %d %d\n\n\n\n",p[3][6],p[3][7],p[3][8]);

}

char GotNumber_1 :: rotation_1(int (*p)[9]) //보라색 위 왼쪽 1
{
	int temp[3]={p[0][6],p[0][7],p[0][8]};
	p[0][6] = p[4][0],p[0][7] = p[4][3],p[0][8] = p[4][6],
	p[4][0] = p[2][2],p[4][3] = p[2][1],p[4][6] = p[2][0],
	p[2][2] = p[5][8],p[2][1] = p[5][5],p[2][0] = p[5][2],
	p[5][8] = temp[0],p[5][5] = temp[1],p[5][2] = temp[2];
	temp[0] = p[1][0],temp[1] = p[1][1],
	p[1][0] = p[1][2],p[1][1] = p[1][5],p[1][2] = p[1][8],p[1][5] = p[1][7],
	p[1][8] = p[1][6],p[1][7] = p[1][3],p[1][6] = temp[0],p[1][3] = temp[1];
	return '1';
}
char GotNumber_1 :: rotation_2(int (*p)[9]) //보라색 위 왼쪽 2
{
	rotation_1(p);
	rotation_1(p);
	return '2';
}
char GotNumber_1 :: rotation_3(int (*p)[9]) //보라색 위 오른쪽 1
{
	rotation_1(p);
	rotation_1(p);
	rotation_1(p);
	return '3';
}
char GotNumber_1 :: rotation_4(int (*p)[9])
{
	int temp[3]={p[0][0],p[0][1],p[0][2]};
	p[0][0] = p[4][2],p[0][1] = p[4][5],p[0][2] = p[4][8],
	p[4][2] = p[2][8],p[4][5] = p[2][7],p[4][8] = p[2][6],
	p[2][8] = p[5][6],p[2][7] = p[5][3],p[2][6] = p[5][0],
	p[5][6] = temp[0],p[5][3] = temp[1],p[5][0] = temp[2];
	temp[0] = p[3][0],temp[1] = p[3][1],
	p[3][1] = p[3][3],p[3][0] = p[3][6],p[3][3] = p[3][7],p[3][6] = p[3][8],
	p[3][7] = p[3][5],p[3][8] = p[3][2],p[3][5] = temp[1],p[3][2] = temp[0];
	return '4';
}
char GotNumber_1 :: rotation_5(int (*p)[9])
{
	rotation_4(p);
	rotation_4(p);
	return '5';
}
char GotNumber_1 :: rotation_6(int (*p)[9])
{
	rotation_4(p);
	rotation_4(p);
	rotation_4(p);
	return '6';
}
char GotNumber_1 :: rotation_7(int (*p)[9])
{
	int temp[3]={p[1][0],p[1][3],p[1][6]};
	p[1][0] = p[2][0],p[1][3] = p[2][3],p[1][6] = p[2][6],
	p[2][0] = p[3][0],p[2][3] = p[3][3],p[2][6] = p[3][6],
	p[3][0] = p[0][0],p[3][3] = p[0][3],p[3][6] = p[0][6],
	p[0][0] = temp[0],p[0][3] = temp[1],p[0][6] = temp[2];
	temp[0] = p[5][0],temp[1] = p[5][1],
	p[5][0] = p[5][2],p[5][1] = p[5][5],p[5][2] = p[5][8],p[5][5] = p[5][7],
	p[5][8] = p[5][6],p[5][7] = p[5][3],p[5][6] = temp[0],p[5][3] = temp[1];
	return '7';
}
char GotNumber_1 :: rotation_8(int (*p)[9])
{
	rotation_7(p);
	rotation_7(p);
	return '8';
}
char GotNumber_1 :: rotation_9(int (*p)[9])
{
	rotation_7(p);
	rotation_7(p);
	rotation_7(p);
	return '9';
}
char GotNumber_1 :: rotation_10(int (*p)[9])
{
	int temp[3]={p[1][2],p[1][5],p[1][8]};
	p[1][2] = p[2][2],p[1][5] = p[2][5],p[1][8] = p[2][8],
	p[2][2] = p[3][2],p[2][5] = p[3][5],p[2][8] = p[3][8],
	p[3][2] = p[0][2],p[3][5] = p[0][5],p[3][8] = p[0][8],
	p[0][2] = temp[0],p[0][5] = temp[1],p[0][8] = temp[2];
	temp[0] = p[4][0],temp[1] = p[4][1],
	p[4][1] = p[4][3],p[4][0] = p[4][6],p[4][3] = p[4][7],p[4][6] = p[4][8],
	p[4][7] = p[4][5],p[4][8] = p[4][2],p[4][5] = temp[1],p[4][2] = temp[0];
	return 'a';
}
char GotNumber_1 :: rotation_11(int (*p)[9])
{
	rotation_10(p);
	rotation_10(p);
	return 'b';
}
char GotNumber_1 :: rotation_12(int (*p)[9])
{
	rotation_10(p);
	rotation_10(p);
	rotation_10(p);
	return 'c';
}
char GotNumber_1 :: rotation_13(int (*p)[9])
{
	int temp[3]={p[1][6],p[1][7],p[1][8]};
	p[1][6] = p[4][6],p[1][7] = p[4][7],p[1][8] = p[4][8],
	p[4][6] = p[3][2],p[4][7] = p[3][1],p[4][8] = p[3][0],
	p[3][2] = p[5][6],p[3][1] = p[5][7],p[3][0] = p[5][8],
	p[5][6] = temp[0],p[5][7] = temp[1],p[5][8] = temp[2];
	temp[0] = p[2][0],temp[1] = p[2][1],
	p[2][0] = p[2][2],p[2][1] = p[2][5],p[2][2] = p[2][8],p[2][5] = p[2][7],
	p[2][8] = p[2][6],p[2][7] = p[2][3],p[2][6] = temp[0],p[2][3] = temp[1];
	return 'd';
}
char GotNumber_1 :: rotation_14(int (*p)[9])
{
	rotation_13(p);
	rotation_13(p);
	return 'e';
}
char GotNumber_1 :: rotation_15(int (*p)[9])
{
	rotation_13(p);
	rotation_13(p);
	rotation_13(p);
	return 'f';
}
char GotNumber_1 :: rotation_16(int (*p)[9])
{
	int temp[3]={p[1][0],p[1][1],p[1][2]};
	p[1][0] = p[4][0],p[1][1] = p[4][1],p[1][2] = p[4][2],
	p[4][0] = p[3][8],p[4][1] = p[3][7],p[4][2] = p[3][6],
	p[3][8] = p[5][0],p[3][7] = p[5][1],p[3][6] = p[5][2],
	p[5][0] = temp[0],p[5][1] = temp[1],p[5][2] = temp[2];
	temp[0] = p[0][0],temp[1] = p[0][1],
	p[0][1] = p[0][3],p[0][0] = p[0][6],p[0][3] = p[0][7],p[0][6] = p[0][8],
	p[0][7] = p[0][5],p[0][8] = p[0][2],p[0][5] = temp[1],p[0][2] = temp[0];
	return 'g';
}
char GotNumber_1 :: rotation_17(int (*p)[9])
{
	rotation_16(p);
	rotation_16(p);
	return 'h';
}
char GotNumber_1 :: rotation_18(int (*p)[9])
{
	rotation_16(p);
	rotation_16(p);
	rotation_16(p);
	return 'i';
}
char GotNumber_1 :: rotation_19(int (*p)[9])
{
	int temp[2] ={p[4][0],p[4][1]},temp1[9] = {p[0][0],p[0][1],p[0][2],p[0][3],p[0][4],p[0][5],p[0][6],p[0][7],p[0][8]};
	int i,j;
	p[4][1] = p[4][3],p[4][0] = p[4][6],p[4][3] = p[4][7],p[4][6] = p[4][8],
	p[4][7] = p[4][5],p[4][8] = p[4][2],p[4][5] = temp[1],p[4][2] = temp[0];
	temp[0] = p[5][0],temp[1] = p[5][1],
	p[5][0] = p[5][2],p[5][1] = p[5][5],p[5][2] = p[5][8],p[5][5] = p[5][7],
	p[5][8] = p[5][6],p[5][7] = p[5][3],p[5][6] = temp[0],p[5][3] = temp[1];
	
	for(i=0;i < 3 ;i++)
	{
		for(j=0;j<9;j++)
		{
			p[i][j] = p[i+1][j];
		}		
	}
	for(j=0;j<9;j++)
	{
		p[3][j] = temp1[j];
	}
	return 'j';
}
char GotNumber_1 :: rotation_20(int (*p)[9])
{
	int temp[2]={p[1][0],p[1][1]},temp1[9] = {p[0][0],p[0][1],p[0][2],p[0][3],p[0][4],p[0][5],p[0][6],p[0][7],p[0][8]};
	p[1][0] = p[1][2],p[1][1] = p[1][5],p[1][2] = p[1][8],p[1][5] = p[1][7],
	p[1][8] = p[1][6],p[1][7] = p[1][3],p[1][6] = temp[0],p[1][3] = temp[1];
	temp[0] = p[3][0],temp[1] = p[3][1],
	p[3][1] = p[3][3],p[3][0] = p[3][6],p[3][3] = p[3][7],p[3][6] = p[3][8],
	p[3][7] = p[3][5],p[3][8] = p[3][2],p[3][5] = temp[1],p[3][2] = temp[0];

	p[0][6] = p[4][0],p[0][7] = p[4][3],p[0][8] = p[4][6],p[0][3] = p[4][1],p[0][4] = p[4][4],p[0][5] = p[4][7],p[0][0] = p[4][2],p[0][1] = p[4][5],p[0][2] = p[4][8];
	p[4][0] = p[2][2],p[4][3] = p[2][1],p[4][6] = p[2][0],p[4][1] = p[2][5],p[4][4] = p[2][4],p[4][7] = p[2][3],p[4][2] = p[2][8],p[4][5] = p[2][7],p[4][8] = p[2][6];
	p[2][2] = p[5][8],p[2][1] = p[5][5],p[2][0] = p[5][2],p[2][5] = p[5][7],p[2][4] = p[5][4],p[2][3] = p[5][1],p[2][8] = p[5][6],p[2][7] = p[5][3],p[2][6] = p[5][0];
	p[5][8] = temp1[6],p[5][5] = temp1[7],p[5][2] = temp1[8],p[5][7] = temp1[3],p[5][4] = temp1[4],p[5][1] = temp1[5],p[5][6] = temp1[0],p[5][3] = temp1[1],p[5][0] = temp1[2];
	return 'k';
}