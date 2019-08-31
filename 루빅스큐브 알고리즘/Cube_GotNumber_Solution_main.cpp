//#include <cv.h>
#include "opencv_cube_final.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Cube_GotNumber_1_Solution.h"
#include "Cube_MySQL.h"
#include "My_usart.h"
#include <windows.h>   // Sleep(3500);  약 3.5초 딜레이
#include <conio.h>  
#include "My_cube_source.h"
//#include <highgui.h>



/*
#define CUBE_R			rotation_10(pC)
#define CUBE_R_			rotation_12(pC)
#define CUBE_R2			rotation_11(pC)

#define CUBE_L			rotation_9(pC)
#define CUBE_L_			rotation_7(pC)
#define CUBE_L2			rotation_8(pC)

#define CUBE_F			rotation_15(pC)
#define CUBE_F_			rotation_13(pC)
#define CUBE_F2			rotation_14(pC)

#define CUBE_B			rotation_16(pC)
#define CUBE_B_			rotation_18(pC)
#define CUBE_B2			rotation_17(pC)
 
#define CUBE_U			rotation_3(pC)
#define CUBE_U_			rotation_1(pC)
#define CUBE_U2			rotation_2(pC)

#define CUBE_D			rotation_4(pC)
#define CUBE_D_			rotation_6(pC)
#define CUBE_D2			rotation_5(pC)

#define X_Z				rotation_19(pC)
#define X_Y				rotation_20(pC)*/

typedef struct _ARM_ALGORITHM_DATA
{
	int LR_01;
	int BF_10;
	int For_Back_ward_11;

} ARM_DATA;

opencv cube_JK;

ARM_DATA arm;
My_usart u1;
int LR = 64,BF = 128,R180 = 1,R90 = 2,R0 = 4,L180 = 8,L90 = 16,L0 = 32,F180 = 1,F90 = 2,F0 = 4,B180 = 8,B90 = 16,B0 = 32,For_Back_ward = 192,Width_in = 1,Width_out = 2,Height_length_in = 4,Height_length_out = 8;


//---------------------------------------------
GotNumber_1 c1;
Cube_MySQL m1;

int Gotnum_data[100];

int Cube[6][9]; // 인트형 데이터
int (*pC)[9] = Cube; //회전할려면 필요함
int icube[6][9]; // 카피 데이타
char _Cube[8][55]; //문자형 데이터

char data[20];
char ___data[20];
int _data[50];
int __data[10],__data_n,deep_max = 0;
int final_data[15],final_num;
int find_H = 1,find_final = 0;
int i__data[20];
int deep = 0;
int twin = 0,copy_Cube[6][9];

int total_ratation;

char *mysql_p;

char query_surch[200] = "select data from ";

/*
void trans_int_char(int *ip,char *chp)
{
	for(int i = 0 ; i < 54 ; i++)
	{
		if(ip[i] == 0) chp[i] = '0';
		else if(ip[i] == 1) chp[i] = '1';
		else if(ip[i] == 2) chp[i] = '2';
		else if(ip[i] == 3) chp[i] = '3';
		else if(ip[i] == 6) chp[i] = '6';
		else if(ip[i] == 7) chp[i] = '7';
		else if(ip[i] == 8) chp[i] = '8';
	}
	chp[54] = NULL;
}
void trans_char_int(int *ip,char *chp)
{
	for(int i = 0 ; i < 54 ; i++)
	{
		if(chp[i] == '0') ip[i] = 0;
		else if(chp[i] == '1') ip[i] = 1;
		else if(chp[i] == '2') ip[i] = 2;
		else if(chp[i] == '3') ip[i] = 3;
		else if(chp[i] == '6') ip[i] = 6;
		else if(chp[i] == '7') ip[i] = 7;
		else if(chp[i] == '8') ip[i] = 8;
	}
}
void trans_int_int(int *ip,int *chp)
{
	for(int i = 0 ; i < 54 ; i++)
	{
		chp[i] = ip[i];

	}
}
void trans(int *p)
{
	for(int i = 0 ; i < 54 ; i++)
	{
		if(p[i] == 2) p[i] = 5;
	}
	for(int i = 0 ; i < 54 ; i++)
	{
		if(p[i] == 3) p[i] = 2;
	}
	for(int i = 0 ; i < 54 ; i++)
	{
		if(p[i] == 5) p[i] = 3;
	}
}
void quert_data_surch(char *p,int n,char *pp)
{
	int i,j;
	char a[18][7] = {{"cube01"},{"cube02"},{"cube03"},{"cube04"},{"cube05"},{"cube06"},{"cube07"},{"cube08"},{"cube09"},{"cube_a"},{"cube_b"},{"cube_c"},{"cube_d"},{"cube_e"},{"cube_f"},{"cube_g"},{"cube_h"}};
//{{"cube_1"},{"cube_2"},{"cube_3"},{"cube_4"},{"cube_5"},{"cube_6"},{"cube_7"},{"cube_8"},{"cube_9"},{"cube_a"},{"cube_b"},{"cube_c"},{"cube_d"},{"cube_e"},{"cube_f"},{"cube_g"},{"cube_h"}};
	char b[] = " where cube = \'";

	for(i = 17 ; i < 23 ; i++) p[i] = a[n][i - 17];
	for(i = 23 ; i < 38 ; i++) p[i] = b[i - 23];

	for(j = i ; pp[j-i] != NULL ; j++) p[j] = pp[j-i];
	p[j++]= '\'';
	p[j++]= NULL;
}*/
void a()
{
	Cube[0][4] = 2; //빨강
	Cube[1][4] = 6; //노랑
	Cube[2][4] = 7; //초록
	Cube[3][4] = 1; //갈색
	Cube[4][4] = 3; //분홍
	Cube[5][4] = 8; //파랑
	  
	Cube[0][0] = 8;
	Cube[0][1] = 2;
	Cube[0][2] = 6;
	Cube[0][3] = 1;
	Cube[0][5] = 6;
	Cube[0][6] = 3;
	Cube[0][7] = 7;
	Cube[0][8] = 3;

	Cube[1][0] = 6;
	Cube[1][1] = 3;
	Cube[1][2] = 7;
	Cube[1][3] = 2;
	Cube[1][5] = 7;
	Cube[1][6] = 1;
	Cube[1][7] = 1;
	Cube[1][8] = 8;

	Cube[2][0] = 3;
	Cube[2][1] = 8;
	Cube[2][2] = 1;
	Cube[2][3] = 7;
	Cube[2][5] = 6;
	Cube[2][6] = 8;
	Cube[2][7] = 3;
	Cube[2][8] = 6;

	Cube[3][0] = 6;
	Cube[3][1] = 1;
	Cube[3][2] = 2;
	Cube[3][3] = 7;
	Cube[3][5] = 3;
	Cube[3][6] = 2;
	Cube[3][7] = 8;
	Cube[3][8] = 3;

	Cube[4][0] = 1;
	Cube[4][1] = 3;
	Cube[4][2] = 7;
	Cube[4][3] = 8;
	Cube[4][5] = 2;
	Cube[4][6] = 7;
	Cube[4][7] = 8;
	Cube[4][8] = 8;

	Cube[5][0] = 1;
	Cube[5][1] = 2;
	Cube[5][2] = 2;
	Cube[5][3] = 1;
	Cube[5][5] = 6;
	Cube[5][6] = 7;
	Cube[5][7] = 6;
	Cube[5][8] = 2;

}/*
void cube_tr_mod_1(int *p ,int *cp)
{
	for(int i = 0 ; i < 54 ; i++) cp[i] = p[i]%5;

	if(cp[9*1+0] == 1) cp[9*0+6] = cp[9*5+2] = 0;
	else if(cp[9*5+2] == 1) cp[9*0+6] = cp[9*1+0] = 0;
	else if(cp[9*0+6] == 1) cp[9*5+2] = cp[9*1+0] = 0;

	if(cp[9*1+2] == 1) cp[9*0+8] = cp[9*4+0] = 0;
	else if(cp[9*4+0] == 1) cp[9*1+2] = cp[9*0+8] = 0;
	else if(cp[9*0+8] == 1) cp[9*1+2] = cp[9*4+0] = 0;

	if(cp[9*1+6] == 1) cp[9*5+8] = cp[9*2+0] = 0;
	else if(cp[9*5+8] == 1) cp[9*1+6] = cp[9*2+0] = 0;
	else if(cp[9*2+0] == 1) cp[9*1+6] = cp[9*5+8] = 0;

	if(cp[9*1+8] == 1) cp[9*4+6] = cp[9*2+2] = 0;
	else if(cp[9*2+2] == 1) cp[9*1+8] = cp[9*4+6] = 0;
	else if(cp[9*4+6] == 1) cp[9*1+8] = cp[9*2+2] = 0;

	if(cp[9*3+0] == 1) cp[9*2+6] = cp[9*5+6] = 0;
	else if(cp[9*2+6] == 1) cp[9*3+0] = cp[9*5+6] = 0;
	else if(cp[9*5+6] == 1) cp[9*3+0] = cp[9*2+6] = 0;

	if(cp[9*2+8] == 1) cp[9*4+8] = cp[9*3+2] = 0;
	else if(cp[9*4+8] == 1) cp[9*2+8] = cp[9*3+2] = 0;
	else if(cp[9*3+2] == 1) cp[9*2+8] = cp[9*4+8] = 0;

	if(cp[9*5+0] == 1) cp[9*0+0] = cp[9*3+6] = 0;
	else if(cp[9*0+0] == 1) cp[9*3+6] = cp[9*5+0] = 0;
	else if(cp[9*3+6] == 1) cp[9*5+0] = cp[9*0+0] = 0;

	if(cp[9*4+2] == 1) cp[9*0+2] = cp[9*3+8] = 0;
	else if(cp[9*0+2] == 1) cp[9*3+8] = cp[9*4+2] = 0;
	else if(cp[9*3+8] == 1) cp[9*4+2] = cp[9*0+2] = 0;

		if(cp[9*0+1] == 1 ) cp[(9*3+7)] = 0;
		else if(cp[9*3+7] == 1 ) cp[(9*0+1)] = 0;

		if(cp[9*1+1] == 1 ) cp[(9*0+7)] = 0;
		else if(cp[9*0+7] == 1 ) cp[(9*1+1)] = 0;

		if(cp[9*2+1] == 1 ) cp[(9*1+7)] = 0;
		else if(cp[9*1+7] == 1 ) cp[(9*2+1)] = 0;

		if(cp[9*3+1] == 1 ) cp[(9*2+7)] = 0;
		else if(cp[9*2+7] == 1 ) cp[(9*3+1)] = 0;

		if(cp[9*1+3] == 1 ) cp[(9*5+5)] = 0;
		else if(cp[9*5+5] == 1 ) cp[(9*1+3)] = 0;

		if(cp[9*1+5] == 1 ) cp[(9*4+3)] = 0;
		else if(cp[9*4+3] == 1 ) cp[(9*1+5)] = 0;

		if(cp[9*4+5] == 1 ) cp[(9*3+5)] = 0;
		else if(cp[9*3+5] == 1 ) cp[(9*4+5)] = 0;

		if(cp[9*5+3] == 1 ) cp[(9*3+3)] = 0;
		else if(cp[9*3+3] == 1 ) cp[(9*5+3)] = 0;

		if(cp[9*0+5] == 1 ) cp[(9*4+1)] = 0;
		else if(cp[9*4+1] == 1 ) cp[(9*0+5)] = 0;

		if(cp[9*5+1] == 1 ) cp[(9*0+3)] = 0;
		else if(cp[9*0+3] == 1 ) cp[(9*5+1)] = 0;

		if(cp[9*4+7] == 1 ) cp[(9*2+5)] = 0;
		else if(cp[9*2+5] == 1 ) cp[(9*4+7)] = 0;

		if(cp[9*5+7] == 1 ) cp[(9*2+3)] = 0;
		else if(cp[9*2+3] == 1 ) cp[(9*5+7)] = 0;


}
void cube_symmetry(int (*ppC)[9],char (*ppChar)[55])
{
	trans_int_char(ppC[0],ppChar[0]);
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
	trans_int_char(ppC[0],ppChar[1]);
	c1.rotation_19(ppC); //X_Z
	c1.rotation_19(ppC); //X_Z
	trans_int_char(ppC[0],ppChar[2]);
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
	trans_int_char(ppC[0],ppChar[3]);
	c1.rotation_19(ppC); //X_Z
	c1.rotation_19(ppC); //X_Z
	trans(ppC[0]);
	c1.rotation_20(ppC); //X_Y
	trans_int_char(ppC[0],ppChar[4]);
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
	trans_int_char(ppC[0],ppChar[5]);
	c1.rotation_19(ppC); //X_Z
	c1.rotation_19(ppC); //X_Z
	trans_int_char(ppC[0],ppChar[6]);
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
	trans_int_char(ppC[0],ppChar[7]);
	c1.rotation_19(ppC); //X_Z
	c1.rotation_19(ppC); //X_Z
	trans(ppC[0]);
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
	c1.rotation_20(ppC); //X_Y
}
int surch()
{
	int j;
	cube_symmetry(icube,_Cube);
	for( j = 0 ; j < 8 ; j++)
	{
		for(int i = 7 ; i > -1 ; i--)
		{
			quert_data_surch(query_surch,i,_Cube[j]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(data, mysql_p);
				m1.MySQL_free();
				break;					
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
		}
		if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
		
	}
//	printf("%s %d\n",data,j);
	return j;
	
}
void ro_tr(char* cp, int *ip)
{
	int i = 0;

	while(cp[i] != NULL)
	{
		if(cp[i] == '1') ip[i] = 3;
		else if(cp[i] == '2') ip[i] = 2;
		else if(cp[i] == '3') ip[i] = 1;
		else if(cp[i] == '4') ip[i] = 6;
		else if(cp[i] == '5') ip[i] = 5;
		else if(cp[i] == '6') ip[i] = 4;
		else if(cp[i] == '7') ip[i] = 9;
		else if(cp[i] == '8') ip[i] = 8;
		else if(cp[i] == '9') ip[i] = 7;
		else if(cp[i] == 'a') ip[i] = 12;
		else if(cp[i] == 'b') ip[i] = 11;
		else if(cp[i] == 'c') ip[i] = 10;
		else if(cp[i] == 'd') ip[i] = 15;
		else if(cp[i] == 'e') ip[i] = 14;
		else if(cp[i] == 'f') ip[i] = 13;
		else if(cp[i] == 'g') ip[i] = 18;
		else if(cp[i] == 'h') ip[i] = 17;
		else if(cp[i] == 'i') ip[i] = 16;
		else ip[i] = 99;
		i++;
	}
	ip[i] = 0;
	//for(i = 0 ; i < 14 ; i++)
	//{
	//	cp[i] = NULCUBE_L;
	//	printf("%3d",ip[i]);
	//}
	//printf("\n");
}
int Z_X_rotation_restoration(int num)
{
	int save;

	if(num == 3) save = 15;  // U -> F
	else if(num == 1) save = 13;
	else if(num == 2) save = 14;
	else if(num == 15) save = 4; // F -> D
	else if(num == 13) save = 6;
	else if(num == 14) save = 5;
	else if(num == 4) save = 16; // D -> B
	else if(num == 6) save = 18;
	else if(num == 5) save = 17;
	else if(num == 16) save = 3; //B -> U
	else if(num == 18) save = 1;
	else if(num == 17) save = 2;
	else save = num;

	return save;
}
int Y_X_rotation_restoration(int num)
{
	int save;

	if(num == 10) save = 15;  // R -> F
	else if(num == 12) save = 13;
	else if(num == 11) save = 14;
	else if(num == 16) save = 10; // B -> R
	else if(num == 18) save = 12;
	else if(num == 17) save = 11;
	else if(num == 9) save = 16; // L -> B
	else if(num == 7) save = 18;
	else if(num == 8) save = 17;
	else if(num == 15) save = 9; // F -> L
	else if(num == 13) save = 7;
	else if(num == 14) save = 8;
	else save = num;
	
	return save;
}
void rotation_restoration(int *p,int n)
{
	int i= 0;

	if(n == 1) ;
	else if(n == 2)
	{
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
	}
	else if(n == 3)
	{
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
	}
	else if(n == 4)
	{

		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;

	}
	else if(n == 5)
	{
		
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;		
	}
	else if(n == 6)
	{
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
	}
	else if(n == 7)
	{
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
	}
	else if(n == 8)
	{
		while((p[i] = Y_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
		i = 0;
		while((p[i] = Z_X_rotation_restoration(p[i])) != 0 ) i++;
	
	}
}*/
/*
void rotation_tr(int m)
{
	int i = 0;
	char a[20] = {0};
	//------- 맞추는거 역회전 변환 --------
	while(data[i++] != NULL);
	for(int n = 0 ; n < i-2 ; n++)
	{
		a[n] = data[i-2-n];
		a[n+1] = NULL;
	}
	strcpy(data, a);
	//-----------------------------


	ro_tr(data,_data);
	rotation_restoration(_data, m+1);

}
void real_rotation(int p)
{
	if(p == 1) c1.CUBE_U_;
	else if(p == 2) c1.CUBE_U2;
	else if(p == 3) c1.CUBE_U;
	else if(p == 4) c1.CUBE_D;
	else if(p == 5) c1.CUBE_D2;
	else if(p == 6) c1.CUBE_D_;
	else if(p == 7) c1.CUBE_L_;
	else if(p == 8) c1.CUBE_L2;
	else if(p == 9) c1.CUBE_L;
	else if(p == 10) c1.CUBE_R;
	else if(p == 11) c1.CUBE_R2;
	else if(p == 12) c1.CUBE_R_;
	else if(p == 13) c1.CUBE_F_;
	else if(p == 14) c1.CUBE_F2;
	else if(p == 15) c1.CUBE_F;
	else if(p == 16) c1.CUBE_B;
	else if(p == 17) c1.CUBE_B2;
	else if(p == 18) c1.CUBE_B_;
	else if(p == 19) c1.X_Z;
	else if(p == 20) c1.X_Y;
}
void areal_rotation(int p)
{
	if(p == 1) c1.CUBE_U;
	else if(p == 2) c1.CUBE_U2;
	else if(p == 3) c1.CUBE_U_;
	else if(p == 4) c1.CUBE_D_;
	else if(p == 5) c1.CUBE_D2;
	else if(p == 6) c1.CUBE_D;
	else if(p == 7) c1.CUBE_L;
	else if(p == 8) c1.CUBE_L2;
	else if(p == 9) c1.CUBE_L_;
	else if(p == 10) c1.CUBE_R_;
	else if(p == 11) c1.CUBE_R2;
	else if(p == 12) c1.CUBE_R;
	else if(p == 13) c1.CUBE_F;
	else if(p == 14) c1.CUBE_F2;
	else if(p == 15) c1.CUBE_F_;
	else if(p == 16) c1.CUBE_B_;
	else if(p == 17) c1.CUBE_B2;
	else if(p == 18) c1.CUBE_B;
	else if(p == 19) 
	{
		c1.X_Z;
		c1.X_Z;
		c1.X_Z;
	}
	else if(p == 20)
	{
		c1.X_Y;
		c1.X_Y;
		c1.X_Y;
	}
}
int surch_pH()
{
	int m = 0;

	for(int i = 0 ; i < 9 ; i++)
	{
		if(Cube[1][i]%5 != 1)
		{
			m = 1;
			break;
		}
		if(Cube[3][i]%5 != 1)
		{
			m = 1;
			break;
		}
	}
	return m;

}
int ratation()
{
	int i = 0;
	int tf = 0;
	while(_data[i] != 0)
	{
		real_rotation(_data[i]);
		i++;
	}
	tf = surch_pH();
	//printf("%d a\n",tf);
	if(tf)
	{
		while(i != -1)
		{
			areal_rotation(_data[i]);
			i--;
		}
	}
	return tf;
}
void tree_surch_pattern1(int n)
{
	if(find_H == 0) goto go;

	if((__data[__data_n-1] != 10)&&(__data[__data_n-1] != 11)&&(__data[__data_n-1] != 12)&&(__data[__data_n-1] != 9)&&(__data[__data_n-1] != 7)&&(__data[__data_n-1] != 8))
	{

		__data[__data_n] = c1.CUBE_R;
		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}
		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_R_;
	

		__data[__data_n] = c1.CUBE_R_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}
	
		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_R;

		__data[__data_n] = c1.CUBE_R2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_R2;
		
	}
	//--------

	if((__data[__data_n-1] != 9)&&(__data[__data_n-1] != 7)&&(__data[__data_n-1] != 8))
	{
		__data[__data_n] = c1.CUBE_L;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_L_;

		__data[__data_n] = c1.CUBE_L_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_L;

		__data[__data_n] = c1.CUBE_L2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_L2;
	}
	//-----
	if((__data[__data_n-1] != 15)&&(__data[__data_n-1] != 13)&&(__data[__data_n-1] != 14)&&(__data[__data_n-1] != 16)&&(__data[__data_n-1] != 17)&&(__data[__data_n-1] != 18))
	{
		__data[__data_n] = c1.CUBE_F;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_F_;

		__data[__data_n] = c1.CUBE_F_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_F;

		__data[__data_n] = c1.CUBE_F2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_F2;
	}
	//-----
	if((__data[__data_n-1] != 16)&&(__data[__data_n-1] != 17)&&(__data[__data_n-1] != 18))
	{
		__data[__data_n] = c1.CUBE_B;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_B_;

		__data[__data_n] = c1.CUBE_B_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_B;

		__data[__data_n] = c1.CUBE_B2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_B2;
	}
	//-----
	if((__data[__data_n-1] != 3)&&(__data[__data_n-1] != 1)&&(__data[__data_n-1] != 2)&&(__data[__data_n-1] != 4)&&(__data[__data_n-1] != 5)&&(__data[__data_n-1] != 6))
	{
		__data[__data_n] = c1.CUBE_U;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_U_;

		__data[__data_n] = c1.CUBE_U_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_U;

		__data[__data_n] = c1.CUBE_U2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_U2;
	}
	//-----
	if((__data[__data_n-1] != 4)&&(__data[__data_n-1] != 5)&&(__data[__data_n-1] != 6))
	{
		__data[__data_n] = c1.CUBE_D;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_D_;

		__data[__data_n] = c1.CUBE_D_;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}

		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_D;

		__data[__data_n] = c1.CUBE_D2;

		if(__data_n ==deep_max)
		{
			cube_tr_mod_1(Cube[0],icube[0]); // 패턴 K로 변환
			rotation_tr(surch()); //역 탐색
			find_H = ratation(); //회전시켜라 패턴 H 찾으면 0 아니면 1
			if(find_H == 0) goto go;
		}


		if(__data_n !=deep_max)
		{
			__data_n++;
			tree_surch_pattern1(__data_n);
			if(find_H == 0) goto go;
		}
		c1.CUBE_D2;
	}
	__data[__data_n--] = 0;
	
	go:;


}
void _quert_data_surch(char *p,int n,char *pp)
{
	int i,j;
	char a[18][7] = {{"cube11"},{"cube22"},{"cube33"},{"cube44"},{"cube55"},{"cube66"},{"cube77"},{"cube88"},{"cube99"}};
	char b[] = " where cube = \'";

	for(i = 17 ; i < 23 ; i++) p[i] = a[n][i - 17];
	for(i = 23 ; i < 38 ; i++) p[i] = b[i - 23];

	for(j = i ; pp[j-i] != NULL ; j++) p[j] = pp[j-i];
	p[j++]= '\'';
	p[j++]= NULL;
}
void tree_surch_pattern2(void)
{
	int i =0;
	if(find_final) goto go1; // 맟추면 1 아니면 0


	trans_int_char( Cube[0],_Cube[0]); // 일단 변환
	for(i = 0 ; i < 9 ; i++)
	{
		_quert_data_surch(query_surch,i,_Cube[0]);
		m1.MySQL_Query(query_surch); // 쿼리문 전송
		mysql_p = m1.MySQL_Data();
		if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
		{
			strcpy(___data, mysql_p);
			m1.MySQL_free();
			goto go1;				
		}
		m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
	}


	//===============


	if((final_data[final_num-1] != 3)&&(final_data[final_num-1] != 2)&&(final_data[final_num-1] != 1)&&(final_data[final_num-1] != 4)&&(final_data[final_num-1] != 5)&&(final_data[final_num-1] != 6))
	{

		final_data[final_num] = c1.CUBE_U;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_U_;
	

		final_data[final_num] = c1.CUBE_U_;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_U;

		final_data[final_num] = c1.CUBE_U2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_U2;
		
	}
	if((final_data[final_num-1] != 4)&&(final_data[final_num-1] != 5)&&(final_data[final_num-1] != 6))
	{

		final_data[final_num] = c1.CUBE_D;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_D_;
	

		final_data[final_num] = c1.CUBE_D_;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_D;

		final_data[final_num] = c1.CUBE_D2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_D2;
		
	}

	if((final_data[final_num-1] != 11)&&(final_data[final_num-1] != 8))
	{


		final_data[final_num] = c1.CUBE_R2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_R2;
		
	}

	if(final_data[final_num-1] != 8)
	{

		final_data[final_num] = c1.CUBE_L2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_L2;
		
	}

	if((final_data[final_num-1] != 14)&&(final_data[final_num-1] != 17))
	{
		final_data[final_num] = c1.CUBE_F2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_F2;
		
	}

	if(final_data[final_num-1] != 17)
	{
		final_data[final_num] = c1.CUBE_B2;
		if(final_num == deep)
		{

			trans_int_char( Cube[0],_Cube[0]); // 일단 변환

			_quert_data_surch(query_surch,8,_Cube[0]);
			m1.MySQL_Query(query_surch); // 쿼리문 전송
			mysql_p = m1.MySQL_Data();
			if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
			{
				strcpy(___data, mysql_p);
				find_final =1;
				m1.MySQL_free();
				goto go1;				
			}
			m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			if(find_final) goto go1; // 맟추면 1 아니면 0
		}

		if(final_num !=deep)
		{
			final_num++;
			tree_surch_pattern2();
			if(find_final) goto go1;
		}
		c1.CUBE_B2;
		
	}

	
	final_data[final_num--] = 0;
	go1:;
	//printf("%s\n",___data);
}
void _rotation_tr()
{
	int i = 0;
	char a[20];

	//------- 맞추는거 역회전 변환 --------
	while(___data[i++] != NULL);
	for(int n = 0 ; n < i-2 ; n++)
	{
		a[n] = ___data[i-2-n];
		a[n+1] = NULL;
	}
	strcpy(___data, a);
	//-----------------------------


	ro_tr(___data,i__data);

	i = 0;
	while(i__data[i] != 0)
	{
		real_rotation(i__data[i]);
		i++;
	}
}
void tr_cube_data()
{
	int i = 0, n = 0;

	while(__data[i] != 0)
	{
		Gotnum_data[n++] = __data[i++];
	}
	i = 0;
	while(_data[i] != 0)
	{
		Gotnum_data[n++] = _data[i++];
	}
	i = 0;
	while(final_data[i] != 0)
	{
		Gotnum_data[n++] = final_data[i++];
	}
	i = 0;
	while(i__data[i] != 0)
	{
		Gotnum_data[n++] = i__data[i++];
	}
	i = 0;
	while(Gotnum_data[i] != 0)
	{
		printf("%3d",Gotnum_data[i++]);
	}
	printf("\n총 회전 수 :%3d\n\n",i);
}
void cube_solution()
{

	//m1.MySQL_Connect(); //DB접속
		
	//c1.CUBE_Data_initialization(Cube); //초기화

	//a(); //임시 큐브 모양
	c1.CUBE_Data_print(Cube);
	printf("\n탐색시작!!!\n");
	//c1.X_Z;
	//c1.X_Z;

	
	trans_int_int(Cube[0],copy_Cube[0]);
	while(deep_max != 9)
	{
		go2:;
		if(twin == 1)
		{	
			twin = 0;
			trans_int_int(copy_Cube[0],Cube[0]);
		}
		__data_n = 0;
		tree_surch_pattern1(1);
		deep_max++;
		if(find_H == 0)
		{
			find_H = 1;
			deep = 0 ;
			printf("패턴 찾기 성공\n");
			break;
		}
	}

	while(2)
	{		
		final_num = 0;
		tree_surch_pattern2();
		
		if(find_final == 1)	
		{
			printf("찾기 성공\n\n");
			break;
		}
		deep++;
		if(deep == 6)
		{
			twin = 1;
			printf("실패\n재탐색\n");
			goto go2;
		}		
	}
	
	 _rotation_tr();
	
	tr_cube_data();
	c1.CUBE_Data_print(Cube);

	//m1.MySQL_Close(); //DB종료
}
*/

//------------------------------------
void Data_Tr_Arm(void)
{
	u1.usart_send(arm.BF_10);
	u1.usart_send(arm.LR_01);
	u1.usart_send(arm.For_Back_ward_11);	
}
void robot_rotstion(int data,int time)
{
	int a = 400;
	if(data == 10) //R
	{
		arm.LR_01 = LR + R0 + L90; 
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 12) //R_
	{
		arm.LR_01 = LR + R180 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 11) //R2
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		//arm.LR_01 = LR + R0 + L90;
		//Data_Tr_Arm();
		u1.usart_send(4);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.LR_01 = LR + R180 + L90;
		Data_Tr_Arm();
		//u1.usart_send(6);
		Sleep(time+a);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);
	}
	else if(data == 9) //L
	{
		arm.LR_01 = LR + R90 + L0;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 7) //L_
	{
		arm.LR_01 = LR + R90 + L180;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 8) //L2
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		//arm.LR_01 = LR + R90 + L0;
		//Data_Tr_Arm();
		u1.usart_send(10);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.LR_01 = LR + R90 + L180;
		Data_Tr_Arm();
		//u1.usart_send(12);
		Sleep(time+a);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);
	}
	else if(data == 16) //B
	{
		arm.BF_10 = BF + F90 + B0;
		u1.usart_send(arm.BF_10);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 18) //B_
	{
		arm.BF_10 = BF + F90 + B180;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 17) //B2
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		//arm.BF_10 = BF + F90 + B0;
		//Data_Tr_Arm();
		u1.usart_send(1);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F90 + B180;
		Data_Tr_Arm();
		//u1.usart_send(3);
		Sleep(time+a);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);
	}
	else if(data == 15) //F
	{
		arm.BF_10 = BF + F0 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		Data_Tr_Arm();
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 13) //F_
	{
		arm.BF_10 = BF + F180 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		Data_Tr_Arm();
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 14) //F2
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		//arm.BF_10 = BF + F0 + B90;
		u1.usart_send(7);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F180 + B90;
		Data_Tr_Arm();
		//u1.usart_send(9);
		Sleep(time+a);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);

		arm.BF_10 = BF + F90 + B90;
		Data_Tr_Arm();
		Sleep(time); 

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);
	}
	else if(data == 25) //Z_X
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		Data_Tr_Arm();
		Sleep(time);

		//arm.LR_01 = LR + R180 + L0;
		//Data_Tr_Arm();
		u1.usart_send(17);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		//Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		//Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = LR + R90 + L90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		Sleep(time);
	}
	else if(data == 26) //Y_Z
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

	//	arm.BF_10 = BF + B0 + F180;
	//	Data_Tr_Arm();
		u1.usart_send(20);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		//Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
		//Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = BF + B90 + F90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	else if(data == 27) //Z_Y
	{
		arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);

	//	arm.BF_10 = BF + B180 + F0;
	//	Data_Tr_Arm();

		u1.usart_send(19);
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		u1.usart_send(arm.For_Back_ward_11);
		//Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
		u1.usart_send(arm.For_Back_ward_11);
	//	Data_Tr_Arm();
		Sleep(time);

		arm.LR_01 = BF + B90 + F90;
		Data_Tr_Arm();
		Sleep(time);

		arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
		Data_Tr_Arm();
		Sleep(time);
	}
	
}
/*void Replace_(int *p)
{
	int i;

	for(i = 0 ; i < 150 ; i++)
	{
		if(p[i] == 0) break;
		if(p[i] == 1) printf("U_ ");
		if(p[i] == 2) printf("U2 ");
		if(p[i] == 3) printf("U ");
		if(p[i] == 4) printf("D ");
		if(p[i] == 5) printf("D2 ");
		if(p[i] == 6) printf("D_ ");
		if(p[i] == 7) printf("L_ ");
		if(p[i] == 8) printf("L2 ");
		if(p[i] == 9) printf("L ");
		if(p[i] == 10) printf("R ");
		if(p[i] == 11) printf("R2 ");
		if(p[i] == 12) printf("R_ ");
		if(p[i] == 13) printf("F_ ");
		if(p[i] == 14) printf("F2 ");
		if(p[i] == 15) printf("F ");
		if(p[i] == 16) printf("B ");
		if(p[i] == 17) printf("B2 ");
		if(p[i] == 18) printf("B_ ");
		if(p[i] == 19) printf("X_Z ");
		if(p[i] == 20) printf("X_Y ");
		if(p[i] == 25) printf("|Z_X| ");
		if(p[i] == 26) printf("|Y_X| ");
	}
	printf("\n\n");
}*/
void Transform_ARM_ver(int *p)
{ 
	// U -> F
	int i,j , CNT = 0;
	for(i = 0 ; i < 1000 ; i++)
	{
		if(((p[i] == 3)||(p[i] == 2)||(p[i] == 1)||(p[i] == 4)||(p[i] == 5)||(p[i] == 6)) == 1)
		{
			for(j = 99 ; j > i ; j--)
			{
				p[j] = p[j - 1];
				p[j] = Z_X_rotation_restoration(p[j]);
			}
			p[i] = 25;
		}
	}
	i = 0;
	while(p[i++] != 0);



	printf("\n회전수%d\n",i-1);
	total_ratation = i-1;
	
}

void first_()
{
	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_out;
	Data_Tr_Arm();

	printf("큐브를 올려주세요 \n");
	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_out;
	Data_Tr_Arm();
	getch();
	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
	Data_Tr_Arm();
	Sleep(800);
	printf("영상 입력 \n");
} // 



void camera(int i)
{

	cube_JK.camera_capture(3);

	Cube[i][0] = cube_JK.cube_data[6];
	Cube[i][1] = cube_JK.cube_data[7];
	Cube[i][2] = cube_JK.cube_data[8];
	Cube[i][3] = cube_JK.cube_data[3];
	Cube[i][4] = cube_JK.cube_data[4];
	Cube[i][5] = cube_JK.cube_data[5];
	Cube[i][6] = cube_JK.cube_data[0];
	Cube[i][7] = cube_JK.cube_data[1];
	Cube[i][8] = cube_JK.cube_data[2];

	
	
}

void second_()
{
	int t;
	c1.CUBE_Data_initialization(Cube);

	t = 780;

	cube_JK.camera_on();

	cube_JK.image_set();

	//arm.LR_01 = LR + R0 + L90; 
	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
	Data_Tr_Arm();
	Sleep(t);

	//arm.LR_01 = LR + R180 + L0; 									
	//Data_Tr_Arm();
	u1.usart_send(17);
	Sleep(t);
//	cube.camera_kb(0);

	camera(0);

	//arm.LR_01 = LR + R0 + L180; 
	//Data_Tr_Arm();
	u1.usart_send(18);
	Sleep(t);
//	cube.camera_kb(2);
	camera(2);

	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
	//Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
	//Data_Tr_Arm();
	Sleep(t);

	arm.LR_01 = LR + R90 + L90; 
	Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
//	Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_out;
	u1.usart_send(arm.For_Back_ward_11);
//	Data_Tr_Arm();
	Sleep(t);

	//arm.LR_01 = LR + R0 + L180; 
	//Data_Tr_Arm();
	u1.usart_send(18);
	Sleep(t);
//	cube.camera_kb(3);
	camera(3);

	//arm.LR_01 = LR + R180 + L0; 
	//Data_Tr_Arm();
	u1.usart_send(17);
	Sleep(t);
//	cube.camera_kb(1);
	camera(1);

	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
	//Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
//	Data_Tr_Arm();
	Sleep(t);

	arm.LR_01 = LR + R90 + L90; 
	Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
	//Data_Tr_Arm();
	Sleep(t);

	//arm.BF_10 = BF + F0 + B180;
	//Data_Tr_Arm();
	u1.usart_send(19);
	Sleep(t);
//	cube.camera_kb(5);
	 camera(4);

	//arm.BF_10 = BF + F180 + B0;
	//Data_Tr_Arm();
	u1.usart_send(20);
	Sleep(t);
//	cube.camera_kb(4);
	 camera(5);

	arm.BF_10 = BF + F90 + B90;
	Data_Tr_Arm();
	Sleep(t);

	arm.For_Back_ward_11 = For_Back_ward + Width_in + Height_length_in;
	u1.usart_send(arm.For_Back_ward_11);
	//Data_Tr_Arm();
	Sleep(t);

//	cam_copy();
	cube_JK.camera_off();


	
}

void trans__(int j)
{
	int colar;
	//int num[6] = {2,6,7,1,3,8};
	int num[6] = {0,1,2,3,4,5};
	int *p = Cube[0];

	colar = Cube[j][4];
	for(int i = 0 ; i < 54 ; i++)
	{
		if(p[i] == colar)
		{
			p[i] = num[j];
		}
	}
}

void third_()
{
	for(int i = 0 ; i < 6 ; i++) trans__(i);

	//cube_solution();
//	Replace_(Gotnum_data);
	//Transform_ARM_ver(Gotnum_data);
	//Replace_(Gotnum_data);
}
void last_()
{
	printf("완료\n\n");
	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_out;
	Data_Tr_Arm();

	Sleep(1000);
	system("cls");
	deep = 0;
	twin = 0;
	deep_max = 0;
	find_final = 0;
	find_H = 1;

	int i;
	for(i = 0; i < 20 ; i++)
	{
		data[i] = ___data[i] = NULL;
		i__data[i] = 0;
	}
	for(i = 0; i < 50 ; i++)
	{
		_data[i] = 0;
		Gotnum_data[i] = 0;
	}
	for(i = 0; i < 10 ; i++)
	{
		__data[i] = 0;
	}
	for(i = 0; i < 15 ; i++)
	{
		final_data[i] = 0;
	}
}
void main(void)
{
	int s = 0;

	u1.usart_open();

	arm.LR_01 = LR + R90 + L90; 
	arm.For_Back_ward_11 = For_Back_ward + Width_out + Height_length_out;
	arm.BF_10 = BF + F90 + B90;
	Data_Tr_Arm();

	//m1.MySQL_Connect(); //DB접속


	//char a;
	while(1)      
	{
	
		//a(); // 가상 큐브 모양


		first_(); //초기 입력
		system("cls");

		
		

		second_(); //영상 받는부분
		//third_(); //큐브 탐색
		
		for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		CUBE_DATA.cube[i][j] = Cube[i][j];
	}


	CUBE_MAIN();
	CubeData_print(&CUBE_DATA);

	Replace_(ARM_Transform);

	while(ARM_Transform[s] != 0)
		{
			printf("회전수 : %2d  d%%\n",s+1);

			robot_rotstion(ARM_Transform[s++],650);		
		}


		//system("cls");
/*
		while(Gotnum_data[s] != 0)
		{
			printf("회전수 : %2d  진행률 : %3d%%\n",s+1,(s+1)*100/total_ratation);
			robot_rotstion(Gotnum_data[s++],650);		
		}
	*/	
		s = 0;		
		last_();
	//	scanf("%d",&a);
	//	u1.usart_send(a);
	} 
}   