#include <iostream>

#define CUBE			(int *(*)[9])CUBE_DATA.cube

#define CUBE_U			CUBE_DATA.cube[1][4]
#define CUBE_F			CUBE_DATA.cube[2][4]
#define CUBE_D			CUBE_DATA.cube[3][4]
#define CUBE_B			CUBE_DATA.cube[0][4]
#define CUBE_R			CUBE_DATA.cube[4][4]
#define CUBE_L			CUBE_DATA.cube[5][4]

#define Right1			rotation_10(CUBE)
#define Right_			rotation_12(CUBE)
#define Right2			rotation_11(CUBE)

#define Left1			rotation_9(CUBE)
#define Left_			rotation_7(CUBE)
#define Left2			rotation_8(CUBE)

#define Front1			rotation_15(CUBE)
#define Front_			rotation_13(CUBE)
#define Front2			rotation_14(CUBE)

#define Back1			rotation_16(CUBE)
#define Back_			rotation_18(CUBE)
#define Back2			rotation_17(CUBE)

#define Up1				rotation_3(CUBE)
#define Up_				rotation_1(CUBE)
#define Up2				rotation_2(CUBE)

#define Down1			rotation_4(CUBE)
#define Down_			rotation_6(CUBE)
#define Down2			rotation_5(CUBE)

#define X_Z				rotation_19(CUBE)
#define X_Y				rotation_20(CUBE)


typedef struct _ALGORITHM_DATA
{
	int cube[6][9];
	int CROSS[30];
	int F2L[4][30];
	int OLL[30];
	int PLL[30];
} ALGORITHM_DATA;

class Friedrch_Algorithm
{
	
public :
	ALGORITHM_DATA CUBE_DATA;
	int CNT,CNT_F2L[4],CNT_OLL,CNT_PLL;
	int ARM_Transform[150] ;

Friedrch_Algorithm();

int Z_X_rotation_restoration(int data);
int Y_X_rotation_restoration(int data);

int rotation_1(int *cube[6][9]); //보라색 위 왼쪽 1
int rotation_2(int *cube[6][9]); //보라색 위 왼쪽 2
int rotation_3(int *cube[6][9]); //보라색 위 오른쪽 1
int rotation_4(int *cube[6][9]);
int rotation_5(int *cube[6][9]);
int rotation_6(int *cube[6][9]);
int rotation_7(int *cube[6][9]);
int rotation_8(int *cube[6][9]);
int rotation_9(int *cube[6][9]);
int rotation_10(int *cube[6][9]);
int rotation_11(int *cube[6][9]);
int rotation_12(int *cube[6][9]);
int rotation_13(int *cube[6][9]);
int rotation_14(int *cube[6][9]);
int rotation_15(int *cube[6][9]);
int rotation_16(int *cube[6][9]);
int rotation_17(int *cube[6][9]);
int rotation_18(int *cube[6][9]);
int rotation_19(int *cube[6][9]);
int rotation_20(int *cube[6][9]);


void Replace_(int *p);
void CubeData_print(ALGORITHM_DATA *p);//int *cube[6][9],int* CROSS, int*P2L,int* OLL,int*PLL)

int U_PART_ROTATION(int comp, int obj);

void OPTIMIZATION_RATATION_X_Y(int* p);
void OPTIMIZATION_RATATION_X_Z(int* p);

void U_Rotation_Transposition(int* p,int *pp);
void D_Rotation_Transposition(int* p,int *pp);
void cube_CROSS_1(void);
void cube_CROSS_2(void);

void F2L_(int n);
void F2L(int n);

void OLL(void);
void PLL(void);

void ARM_Trans(int *p);
void Transform_ARM_ver(void);

void CUBE_MAIN(void);

};
