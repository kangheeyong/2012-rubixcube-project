#include <stdio.h>

#define CUBE			(int (*)[9])CUBE_DATA.cube

#define CUBE_U			CUBE_DATA.cube[1][4]
#define CUBE_F			CUBE_DATA.cube[2][4]
#define CUBE_D			CUBE_DATA.cube[3][4]
#define CUBE_B			CUBE_DATA.cube[0][4]
#define CUBE_R			CUBE_DATA.cube[4][4]
#define CUBE_L			CUBE_DATA.cube[5][4]

#define Right1			rotation[10](CUBE)
#define Right_			rotation[12](CUBE)
#define Right2			rotation[11](CUBE)

#define Left1			rotation[9](CUBE)
#define Left_			rotation[7](CUBE)
#define Left2			rotation[8](CUBE)

#define Front1			rotation[15](CUBE)
#define Front_			rotation[13](CUBE)
#define Front2			rotation[14](CUBE)

#define Back1			rotation[16](CUBE)
#define Back_			rotation[18](CUBE)
#define Back2			rotation[17](CUBE)

#define Up1				rotation[3](CUBE)
#define Up_				rotation[1](CUBE)
#define Up2				rotation[2](CUBE)

#define Down1			rotation[4](CUBE)
#define Down_			rotation[6](CUBE)
#define Down2			rotation[5](CUBE)

#define X_Z				rotation[19](CUBE)
#define X_Y				rotation[20](CUBE)

typedef struct _ALGORITHM_DATA
{
	int cube[6][9];
	int CROSS[30];
	int F2L[4][30];
	int OLL[30];
	int PLL[30];
} ALGORITHM_DATA;

ALGORITHM_DATA CUBE_DATA;
int CNT,CNT_F2L[4],CNT_OLL,CNT_PLL;
int ARM_Transform[150];

int Z_X_rotation_restoration(int data)
{
	int save;

	if(data == 3) save = 15;  // U -> F
	else if(data == 1) save = 13;
	else if(data == 2) save = 14;
	else if(data == 15) save = 4; // F -> D
	else if(data == 13) save = 6;
	else if(data == 14) save = 5;
	else if(data == 4) save = 16; // D -> B
	else if(data == 6) save = 18;
	else if(data == 5) save = 17;
	else if(data == 16) save = 3; //B -> U
	else if(data == 18) save = 1;
	else if(data == 17) save = 2;
	else save = data;

	return save;
}
int Y_X_rotation_restoration(int data)
{
	int save;

	if(data == 10) save = 15;  // R -> F
	else if(data == 12) save = 13;
	else if(data == 11) save = 14;
	else if(data == 16) save = 10; // B -> R
	else if(data == 18) save = 12;
	else if(data == 17) save = 11;
	else if(data == 9) save = 16; // L -> B
	else if(data == 7) save = 18;
	else if(data == 8) save = 17;
	else if(data == 15) save = 9; // F -> L
	else if(data == 13) save = 7;
	else if(data == 14) save = 8;
	else save = data;
	
	return save;
}

int  rotation_1(int (*p)[9]) //보라색 위 왼쪽 1
{
	int temp[3]={p[0][6],p[0][7],p[0][8]};
	p[0][6] = p[4][0],p[0][7] = p[4][3],p[0][8] = p[4][6],
	p[4][0] = p[2][2],p[4][3] = p[2][1],p[4][6] = p[2][0],
	p[2][2] = p[5][8],p[2][1] = p[5][5],p[2][0] = p[5][2],
	p[5][8] = temp[0],p[5][5] = temp[1],p[5][2] = temp[2];
	temp[0] = p[1][0],temp[1] = p[1][1],
	p[1][0] = p[1][2],p[1][1] = p[1][5],p[1][2] = p[1][8],p[1][5] = p[1][7],
	p[1][8] = p[1][6],p[1][7] = p[1][3],p[1][6] = temp[0],p[1][3] = temp[1];
	return 1;
}
int  rotation_2(int (*p)[9]) //보라색 위 왼쪽 2
{
	rotation_1(p);
	rotation_1(p);
	return 2;
}
int  rotation_3(int (*p)[9]) //보라색 위 오른쪽 1
{
	rotation_1(p);
	rotation_1(p);
	rotation_1(p);
	return 3;
}
int  rotation_4(int (*p)[9])
{
	int temp[3]={p[0][0],p[0][1],p[0][2]};
	p[0][0] = p[4][2],p[0][1] = p[4][5],p[0][2] = p[4][8],
	p[4][2] = p[2][8],p[4][5] = p[2][7],p[4][8] = p[2][6],
	p[2][8] = p[5][6],p[2][7] = p[5][3],p[2][6] = p[5][0],
	p[5][6] = temp[0],p[5][3] = temp[1],p[5][0] = temp[2];
	temp[0] = p[3][0],temp[1] = p[3][1],
	p[3][1] = p[3][3],p[3][0] = p[3][6],p[3][3] = p[3][7],p[3][6] = p[3][8],
	p[3][7] = p[3][5],p[3][8] = p[3][2],p[3][5] = temp[1],p[3][2] = temp[0];
	return 4;
}
int rotation_5(int (*p)[9])
{
	rotation_4(p);
	rotation_4(p);
	return 5;
}
int rotation_6(int (*p)[9])
{
	rotation_4(p);
	rotation_4(p);
	rotation_4(p);
	return 6;
}
int rotation_7(int (*p)[9])
{
	int temp[3]={p[1][0],p[1][3],p[1][6]};
	p[1][0] = p[2][0],p[1][3] = p[2][3],p[1][6] = p[2][6],
	p[2][0] = p[3][0],p[2][3] = p[3][3],p[2][6] = p[3][6],
	p[3][0] = p[0][0],p[3][3] = p[0][3],p[3][6] = p[0][6],
	p[0][0] = temp[0],p[0][3] = temp[1],p[0][6] = temp[2];
	temp[0] = p[5][0],temp[1] = p[5][1],
	p[5][0] = p[5][2],p[5][1] = p[5][5],p[5][2] = p[5][8],p[5][5] = p[5][7],
	p[5][8] = p[5][6],p[5][7] = p[5][3],p[5][6] = temp[0],p[5][3] = temp[1];
	return 7;
}
int rotation_8(int (*p)[9])
{
	rotation_7(p);
	rotation_7(p);
	return 8;
}
int rotation_9(int (*p)[9])
{
	rotation_7(p);
	rotation_7(p);
	rotation_7(p);
	return 9;
}
int rotation_10(int (*p)[9])
{
	int temp[3]={p[1][2],p[1][5],p[1][8]};
	p[1][2] = p[2][2],p[1][5] = p[2][5],p[1][8] = p[2][8],
	p[2][2] = p[3][2],p[2][5] = p[3][5],p[2][8] = p[3][8],
	p[3][2] = p[0][2],p[3][5] = p[0][5],p[3][8] = p[0][8],
	p[0][2] = temp[0],p[0][5] = temp[1],p[0][8] = temp[2];
	temp[0] = p[4][0],temp[1] = p[4][1],
	p[4][1] = p[4][3],p[4][0] = p[4][6],p[4][3] = p[4][7],p[4][6] = p[4][8],
	p[4][7] = p[4][5],p[4][8] = p[4][2],p[4][5] = temp[1],p[4][2] = temp[0];
	return 10;
}
int rotation_11(int (*p)[9])
{
	rotation_10(p);
	rotation_10(p);
	return 11;
}
int  rotation_12(int (*p)[9])
{
	rotation_10(p);
	rotation_10(p);
	rotation_10(p);
	return 12;
}
int rotation_13(int (*p)[9])
{
	int temp[3]={p[1][6],p[1][7],p[1][8]};
	p[1][6] = p[4][6],p[1][7] = p[4][7],p[1][8] = p[4][8],
	p[4][6] = p[3][2],p[4][7] = p[3][1],p[4][8] = p[3][0],
	p[3][2] = p[5][6],p[3][1] = p[5][7],p[3][0] = p[5][8],
	p[5][6] = temp[0],p[5][7] = temp[1],p[5][8] = temp[2];
	temp[0] = p[2][0],temp[1] = p[2][1],
	p[2][0] = p[2][2],p[2][1] = p[2][5],p[2][2] = p[2][8],p[2][5] = p[2][7],
	p[2][8] = p[2][6],p[2][7] = p[2][3],p[2][6] = temp[0],p[2][3] = temp[1];
	return 13;
}
int  rotation_14(int (*p)[9])
{
	rotation_13(p);
	rotation_13(p);
	return 14;
}
int rotation_15(int (*p)[9])
{
	rotation_13(p);
	rotation_13(p);
	rotation_13(p);
	return 15;
}
int rotation_16(int (*p)[9])
{
	int temp[3]={p[1][0],p[1][1],p[1][2]};
	p[1][0] = p[4][0],p[1][1] = p[4][1],p[1][2] = p[4][2],
	p[4][0] = p[3][8],p[4][1] = p[3][7],p[4][2] = p[3][6],
	p[3][8] = p[5][0],p[3][7] = p[5][1],p[3][6] = p[5][2],
	p[5][0] = temp[0],p[5][1] = temp[1],p[5][2] = temp[2];
	temp[0] = p[0][0],temp[1] = p[0][1],
	p[0][1] = p[0][3],p[0][0] = p[0][6],p[0][3] = p[0][7],p[0][6] = p[0][8],
	p[0][7] = p[0][5],p[0][8] = p[0][2],p[0][5] = temp[1],p[0][2] = temp[0];
	return 16;
}
int  rotation_17(int (*p)[9])
{
	rotation_16(p);
	rotation_16(p);
	return 17;
}
int rotation_18(int (*p)[9])
{
	rotation_16(p);
	rotation_16(p);
	rotation_16(p);
	return 18;
}
int rotation_19(int (*p)[9])
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
	return 19;
}
int rotation_20(int (*p)[9])
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
	return 20;
}

int (*rotation[21])(int (*p)[9]) = {0,rotation_1,rotation_2,rotation_3,rotation_4,rotation_5,rotation_6,rotation_7,rotation_8,rotation_9,rotation_10,rotation_11,rotation_12,rotation_13,rotation_14,rotation_15,rotation_16,rotation_17,rotation_18,rotation_19,rotation_20};

void Replace_(int *p)
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
}
void CubeData_print(ALGORITHM_DATA *p)//int *cube[6][9],int* CROSS, int*P2L,int* OLL,int*PLL)
{

	printf ("         %d %d %d\n",p->cube[0][0],p->cube[0][1],p->cube[0][2]);
	printf ("         %d %d %d\n",p->cube[0][3],p->cube[0][4],p->cube[0][5]);
	printf ("         %d %d %d\n\n",p->cube[0][6],p->cube[0][7],p->cube[0][8]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n",p->cube[5][0],p->cube[5][1],p->cube[5][2],p->cube[1][0],p->cube[1][1],p->cube[1][2],p->cube[4][0],p->cube[4][1],p->cube[4][2]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n",p->cube[5][3],p->cube[5][4],p->cube[5][5],p->cube[1][3],p->cube[1][4],p->cube[1][5],p->cube[4][3],p->cube[4][4],p->cube[4][5]);
	printf (" %d %d %d   %d %d %d   %d %d %d\n\n",p->cube[5][6],p->cube[5][7],p->cube[5][8],p->cube[1][6],p->cube[1][7],p->cube[1][8],p->cube[4][6],p->cube[4][7],p->cube[4][8]);
	printf ("         %d %d %d\n",p->cube[2][0],p->cube[2][1],p->cube[2][2]);
	printf ("         %d %d %d\n",p->cube[2][3],p->cube[2][4],p->cube[2][5]);
	printf ("         %d %d %d\n\n",p->cube[2][6],p->cube[2][7],p->cube[2][8]);
	printf ("         %d %d %d\n",p->cube[3][0],p->cube[3][1],p->cube[3][2]);
	printf ("         %d %d %d\n",p->cube[3][3],p->cube[3][4],p->cube[3][5]);
	printf ("         %d %d %d\n\n",p->cube[3][6],p->cube[3][7],p->cube[3][8]);
	printf("\nCROSS : ");
	Replace_(p->CROSS);
	printf("\nF2L[0] : ");
	Replace_(p->F2L[0]);
	printf("\nF2L[1] : ");
	Replace_(p->F2L[1]);
	printf("\nF2L[2] : ");
	Replace_(p->F2L[2]);
	printf("\nF2L[3] : ");
	Replace_(p->F2L[3]);
	printf("\nOLL : ");
	Replace_(p->OLL);
	printf("\nPLL : ");
	Replace_(p->PLL);
	printf("\nCNT : %d", CNT+CNT_F2L[0]+CNT_F2L[1]+CNT_F2L[2]+CNT_F2L[3]+CNT_OLL+CNT_PLL);
	printf("\n");
}


void cube_initialization(void)
{
	int i,j;

	for(i = 0 ; i <6 ; i++)
	{
		for(j = 0 ; j < 9 ; j++)
		{
			CUBE_DATA.cube[i][j]=9;
		}
	}
}

int U_PART_ROTATION(int comp, int obj)
{
	if(comp == obj)
	{
		CUBE_DATA.CROSS[CNT++]=Up1;
		return 1;
	}
	else return 0;
}

void OPTIMIZATION_RATATION_X_Y(int* p)
{
	int i,j;
	for(i = 29 ; i > -1 ; i--)
	{
		if(p[i] == 20)
		{
			CNT--;
			X_Y;
			X_Y;
			X_Y;
			for(j = i ; j <29 ; j++) p[j] = Y_X_rotation_restoration(p[j+1]);
		}
	}
}
void OPTIMIZATION_RATATION_X_Z(int* p)
{
	int i;

	X_Z;
	X_Z;	
	X_Z;
	for(i = 0 ; i < 30 ; i++) p[i] = Z_X_rotation_restoration(p[i]);
}

void U_Rotation_Transposition(int* p,int *pp)
{
	int i;

	if(p[0]== 3)
	{
		if(p[1]== 3)
		{
			if(p[2]== 3)
			{
				p[0] = 1;
				*pp = *pp - 2;
				for(i = 1 ; i < 27 ; i++)
				{		
					p[i] = p[i+2];
				}
			}
			else
			{
				*pp = *pp - 1;
				p[0] = 2;
				for(i = 1 ; i < 28 ; i++)
				{
					p[i] = p[i+1];
				}
			}
		}
	}
}
void D_Rotation_Transposition(int* p,int *pp)
{
	int i,j;
	for(i = 29 ; i > 2 ; i--)
	{
		if(p[i] == 4)
		{
			if(p[i-1] == 4)
			{
				if(p[i - 2] == 4)
				{
					*pp = *pp - 2;
					p[i - 2] = 6;
					for(j = i - 1 ; j < 28 ; j++)
					{
						p[j] = p[j + 2];
					}
				}
				else
				{
					*pp = *pp - 1;
					p[i - 1] = 5;
					for(j = i ; j < 29 ; j++)
					{
						p[j] = p[j + 1];
					}
				}
			}
		}
	}
}

void cube_CROSS_1(void)
{
	
	if((CUBE_DATA.cube[2][1]==CUBE_U)||(CUBE_DATA.cube[2][3]==CUBE_U)||(CUBE_DATA.cube[2][5]==CUBE_U)||(CUBE_DATA.cube[2][7]==CUBE_U))
	{
		if(CUBE_DATA.cube[2][5]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][5], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Right1;
		}
		if(CUBE_DATA.cube[2][3]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][3], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Left_;
		}
		if(CUBE_DATA.cube[2][1]==CUBE_U)
		{ 
			CUBE_DATA.CROSS[CNT++]=Front1;
			while(U_PART_ROTATION(CUBE_DATA.cube[1][5], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Right1;
		}
		if(CUBE_DATA.cube[2][7]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][7], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Front1;
			while(U_PART_ROTATION(CUBE_DATA.cube[1][3], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Left_;
		}
	}	
	if(((CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)) == 0) 
	{
		if(CUBE_DATA.cube[3][1]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][7], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Front2;
		}
		if(CUBE_DATA.cube[3][5]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][5], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Right2;
		}
		if(CUBE_DATA.cube[3][3]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][3], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Left2;
		}
		if(CUBE_DATA.cube[3][7]==CUBE_U)
		{
			while(U_PART_ROTATION(CUBE_DATA.cube[1][1], CUBE_U));
			CUBE_DATA.CROSS[CNT++]=Back2;
		}
		CUBE_DATA.CROSS[CNT++]=X_Y;
		cube_CROSS_1();
	}	
}
void cube_CROSS_2(void)
{
	int i;

	for(i = 0 ; i < 4 ; i++)
	{
		if(((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)) == 0)
		{
			if((((CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[0][7]==CUBE_B))||(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[2][1]==CUBE_F)) == 1)
			{
				if((CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[0][7]==CUBE_B))
				{
					CUBE_DATA.CROSS[CNT++]=Right2;
					CUBE_DATA.CROSS[CNT++]=Up_;
					CUBE_DATA.CROSS[CNT++]=Right2;
					CUBE_DATA.CROSS[CNT++]=Up1;
					CUBE_DATA.CROSS[CNT++]=Right2;
				}
				else if((CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[2][1]==CUBE_F))
				{
					CUBE_DATA.CROSS[CNT++]=Right2;
					CUBE_DATA.CROSS[CNT++]=Up2;
					CUBE_DATA.CROSS[CNT++]=Right2;
					CUBE_DATA.CROSS[CNT++]=Up2;
					CUBE_DATA.CROSS[CNT++]=Right2;
				}
			}
			else 
			{
				CUBE_DATA.CROSS[CNT++]=Up1;
			}
		}
	}
	if(((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)) == 0)
	{
		for(i = 0 ; i < 4 ; i++) CNT--;
		CUBE_DATA.CROSS[CNT++] = X_Y;
		cube_CROSS_2();
	}
}

void F2L_(int n)
{
	if((CUBE_DATA.cube[5][6]==CUBE_F)||(CUBE_DATA.cube[2][6]==CUBE_F)||(CUBE_DATA.cube[3][0]==CUBE_F))
	{
		if((CUBE_DATA.cube[5][6]==CUBE_D)||(CUBE_DATA.cube[2][6]==CUBE_D)||(CUBE_DATA.cube[3][0]==CUBE_D))
		{
			if((CUBE_DATA.cube[5][6]==CUBE_R)||(CUBE_DATA.cube[2][6]==CUBE_R)||(CUBE_DATA.cube[3][0]==CUBE_R))
			{
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left_;
				if((CUBE_DATA.cube[1][7]==CUBE_F)||(CUBE_DATA.cube[2][1]==CUBE_F))
				{
					if((CUBE_DATA.cube[1][7]==CUBE_R)||(CUBE_DATA.cube[2][1]==CUBE_R)) CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;				
				}
				else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;				
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left1;
			}
		}
	}
	if((CUBE_DATA.cube[5][7]==CUBE_F)||(CUBE_DATA.cube[2][3]==CUBE_F))
	{
		if((CUBE_DATA.cube[5][7]==CUBE_R)||(CUBE_DATA.cube[2][3]==CUBE_R))
		{
			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left_;
			if((CUBE_DATA.cube[1][8]==CUBE_F)||(CUBE_DATA.cube[4][6]==CUBE_F)||(CUBE_DATA.cube[2][2]==CUBE_F))
			{
				if((CUBE_DATA.cube[1][8]==CUBE_D)||(CUBE_DATA.cube[4][6]==CUBE_D)||(CUBE_DATA.cube[2][2]==CUBE_D))
				{
					if((CUBE_DATA.cube[1][8]==CUBE_R)||(CUBE_DATA.cube[4][6]==CUBE_R)||(CUBE_DATA.cube[2][2]==CUBE_R)) CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				}
				else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
			}
			else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left1;
			}
		
	}
//----------------------------------------------------------------------------------------------------------------
	if((CUBE_DATA.cube[5][0]==CUBE_F)||(CUBE_DATA.cube[0][0]==CUBE_F)||(CUBE_DATA.cube[3][6]==CUBE_F))
	{
		if((CUBE_DATA.cube[5][0]==CUBE_D)||(CUBE_DATA.cube[0][0]==CUBE_D)||(CUBE_DATA.cube[3][6]==CUBE_D))
		{
			if((CUBE_DATA.cube[5][0]==CUBE_R)||(CUBE_DATA.cube[0][0]==CUBE_R)||(CUBE_DATA.cube[3][6]==CUBE_R))
			{
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back_;
				if((CUBE_DATA.cube[5][5]==CUBE_F)||(CUBE_DATA.cube[1][3]==CUBE_F))
				{
					if((CUBE_DATA.cube[5][5]==CUBE_R)||(CUBE_DATA.cube[1][3]==CUBE_R)) CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				}
				else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back1;
			}
		}
	}
	if((CUBE_DATA.cube[5][1]==CUBE_F)||(CUBE_DATA.cube[0][3]==CUBE_F))
	{
		if((CUBE_DATA.cube[5][1]==CUBE_R)||(CUBE_DATA.cube[0][3]==CUBE_R))
		{
			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back_;

				if((CUBE_DATA.cube[5][8]==CUBE_F)||(CUBE_DATA.cube[1][6]==CUBE_F)||(CUBE_DATA.cube[2][0]==CUBE_F))
				{
					if((CUBE_DATA.cube[5][8]==CUBE_D)||(CUBE_DATA.cube[1][6]==CUBE_D)||(CUBE_DATA.cube[2][0]==CUBE_D))
					{
						if((CUBE_DATA.cube[5][8]==CUBE_R)||(CUBE_DATA.cube[1][6]==CUBE_R)||(CUBE_DATA.cube[2][0]==CUBE_R))
						{
							CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
						}
						else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					}
					else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				}
				else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back1;
		}
	}
//----------------------------------------------------------------------------------------------------------------
	if((CUBE_DATA.cube[0][2]==CUBE_F)||(CUBE_DATA.cube[4][2]==CUBE_F)||(CUBE_DATA.cube[3][8]==CUBE_F))
	{
		if((CUBE_DATA.cube[0][2]==CUBE_D)||(CUBE_DATA.cube[4][2]==CUBE_D)||(CUBE_DATA.cube[3][8]==CUBE_D))
		{
			if((CUBE_DATA.cube[0][2]==CUBE_R)||(CUBE_DATA.cube[4][2]==CUBE_R)||(CUBE_DATA.cube[3][8]==CUBE_R))
			{
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
			}
		}
	}
	if((CUBE_DATA.cube[0][5]==CUBE_F)||(CUBE_DATA.cube[4][1]==CUBE_F))
	{
		if((CUBE_DATA.cube[0][5]==CUBE_R)||(CUBE_DATA.cube[4][1]==CUBE_R))
		{
			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;

				if((CUBE_DATA.cube[5][2]==CUBE_F)||(CUBE_DATA.cube[1][0]==CUBE_F)||(CUBE_DATA.cube[0][6]==CUBE_F))
				{
					if((CUBE_DATA.cube[5][2]==CUBE_D)||(CUBE_DATA.cube[1][0]==CUBE_D)||(CUBE_DATA.cube[0][6]==CUBE_D))
					{
						if((CUBE_DATA.cube[5][2]==CUBE_R)||(CUBE_DATA.cube[1][0]==CUBE_R)||(CUBE_DATA.cube[0][6]==CUBE_R))
						{
							CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
						}
						else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					}
					else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
				}
				else CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;

			CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
		}
	}

}
void F2L(int n)
{
	int i;
	
	 F2L_(n);
	 for(i = 0 ; i < 4 ; i++) 
	 {
		 if((CUBE_DATA.cube[2][8]==CUBE_F)&&(CUBE_DATA.cube[2][5]==CUBE_F)==1) //F2L3
		 {
			 if((CUBE_DATA.cube[4][7]==CUBE_R)&&(CUBE_DATA.cube[4][8]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[3][2]==CUBE_D)==1) break;
			 }
		 }

		 if((CUBE_DATA.cube[1][8]==CUBE_F)&&(CUBE_DATA.cube[1][5]==CUBE_F)==1) //F2L1A
		 {
			 if((CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[2][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][8]==CUBE_R)&&(CUBE_DATA.cube[1][7]==CUBE_R)==1)  //F2L1B
		 {
			 if((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)==1)
			 {
				 if((CUBE_DATA.cube[4][6]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][8]==CUBE_F)&&(CUBE_DATA.cube[4][7]==CUBE_F)==1) //F2L2
		 {
			 if((CUBE_DATA.cube[2][5]==CUBE_R)&&(CUBE_DATA.cube[4][8]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[3][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][5]==CUBE_F)&&(CUBE_DATA.cube[4][8]==CUBE_F)==1) //F2L4A
		 {
			 if((CUBE_DATA.cube[3][2]==CUBE_R)&&(CUBE_DATA.cube[4][7]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[2][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][5]==CUBE_F)&&(CUBE_DATA.cube[3][2]==CUBE_F)==1) //F2L4B
		 {
			 if((CUBE_DATA.cube[2][8]==CUBE_R)&&(CUBE_DATA.cube[4][7]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[4][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][7]==CUBE_F)&&(CUBE_DATA.cube[4][8]==CUBE_F)==1) //F2L5A
		 {
			 if((CUBE_DATA.cube[2][5]==CUBE_R)&&(CUBE_DATA.cube[3][2]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[2][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Back_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][7]==CUBE_F)&&(CUBE_DATA.cube[3][2]==CUBE_F)==1) //F2L5B
		 {
			 if((CUBE_DATA.cube[2][5]==CUBE_R)&&(CUBE_DATA.cube[2][8]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[4][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][5]==CUBE_F)&&(CUBE_DATA.cube[4][6]==CUBE_F)==1) //F2L6
		 {
			 if((CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[4][7]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[1][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_F)==1) //F2L7
		 {
			 if((CUBE_DATA.cube[2][5]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[1][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][5]==CUBE_F)&&(CUBE_DATA.cube[1][8]==CUBE_F)==1) //F2L8A
		 {
			 if((CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[4][7]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[2][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][5]==CUBE_F)&&(CUBE_DATA.cube[5][8]==CUBE_F)==1) //F2L8B
		 {
			 if((CUBE_DATA.cube[4][7]==CUBE_R)&&(CUBE_DATA.cube[1][6]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[2][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][7]==CUBE_F)&&(CUBE_DATA.cube[1][6]==CUBE_F)==1) //F2L9A
		 {
			 if((CUBE_DATA.cube[2][5]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[5][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][7]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)==1) //F2L9B
		 {
			 if((CUBE_DATA.cube[1][8]==CUBE_R)&&(CUBE_DATA.cube[2][5]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[4][6]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][8]==CUBE_F)&&(CUBE_DATA.cube[5][5]==CUBE_F)==1) //F2L10A
		 {
			 if((CUBE_DATA.cube[4][8]==CUBE_R)&&(CUBE_DATA.cube[1][3]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[3][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][8]==CUBE_F)&&(CUBE_DATA.cube[1][7]==CUBE_F)==1) //F2L10B
		 {
			 if((CUBE_DATA.cube[4][8]==CUBE_R)&&(CUBE_DATA.cube[2][1]==CUBE_R)==1)
			 {
				 if((CUBE_DATA.cube[3][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][8]==CUBE_F)&&(CUBE_DATA.cube[1][5]==CUBE_F)==1) //F2L11A
		 {
			 if((CUBE_DATA.cube[3][2]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[3][2]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)==1) //F2L11B
		 {
			 if((CUBE_DATA.cube[2][8]==CUBE_R)&&(CUBE_DATA.cube[1][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][8]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)==1) //F2L12A
		 {
			 if((CUBE_DATA.cube[3][2]==CUBE_R)&&(CUBE_DATA.cube[1][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][5]==CUBE_F)&&(CUBE_DATA.cube[3][2]==CUBE_F)==1) //F2L12B
		 {
			 if((CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[2][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][8]==CUBE_F)&&(CUBE_DATA.cube[5][5]==CUBE_F)==1) //F2L13A
		 {
			 if((CUBE_DATA.cube[1][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[5][8]==CUBE_F)&&(CUBE_DATA.cube[1][5]==CUBE_F)==1) //F2L13B
		 {
			 if((CUBE_DATA.cube[1][6]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][7]==CUBE_F)&&(CUBE_DATA.cube[1][2]==CUBE_F)==1) //F2L14A
		 {
			 if((CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[0][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[5][8]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_F)==1) //F2L14B
		 {
			 if((CUBE_DATA.cube[1][6]==CUBE_R)&&(CUBE_DATA.cube[1][5]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[0][8]==CUBE_F)&&(CUBE_DATA.cube[0][7]==CUBE_F)==1) //F2L15A
		 {
			 if((CUBE_DATA.cube[1][1]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][1]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_F)==1) //F2L15B
		 {
			 if((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][6]==CUBE_F)&&(CUBE_DATA.cube[1][5]==CUBE_F)==1) //F2L16A
		 {
			 if((CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[4][6]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)==1) //F2L16B
		 {
			 if((CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[1][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][7]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)==1) //F2L17A
		 {
			 if((CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[1][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][6]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][8]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_F)==1) //F2L17B
		 {
			 if((CUBE_DATA.cube[1][5]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_F)==1) //F2L18A
		 {
			 if((CUBE_DATA.cube[1][5]==CUBE_R)&&(CUBE_DATA.cube[1][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][6]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][7]==CUBE_F)&&(CUBE_DATA.cube[1][8]==CUBE_F)==1) //F2L18B
		 {
			 if((CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[2][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][1]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_F)==1) //F2L19A
		 {
			 if((CUBE_DATA.cube[1][2]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[0][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][6]==CUBE_F)&&(CUBE_DATA.cube[5][5]==CUBE_F)==1) //F2L19B
		 {
			 if((CUBE_DATA.cube[2][0]==CUBE_R)&&(CUBE_DATA.cube[1][3]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[5][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][5]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_F)==1) //F2L20A
		 {
			 if((CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[0][6]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_F)==1) //F2L20B
		 {
			 if((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[1][7]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[1][5]==CUBE_F)==1) //F2L21A
		 {
			 if((CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[5][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][6]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_F)==1) //F2L21B
		 {
			 if((CUBE_DATA.cube[1][7]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[1][2]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][7]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_F)==1) //F2L22A
		 {
			 if((CUBE_DATA.cube[1][2]==CUBE_R)&&(CUBE_DATA.cube[2][1]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[0][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][6]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_F)==1) //F2L22B
		 {
			 if((CUBE_DATA.cube[1][5]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[5][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_F)==1) //F2L23A
		 {
			 if((CUBE_DATA.cube[1][7]==CUBE_R)&&(CUBE_DATA.cube[1][2]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[0][8]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Front1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Left_;
					 break;
				 }
			 }
		 }

		 if((CUBE_DATA.cube[1][3]==CUBE_F)&&(CUBE_DATA.cube[1][2]==CUBE_F)==1) //F2L23B
		 {
			 if((CUBE_DATA.cube[5][5]==CUBE_R)&&(CUBE_DATA.cube[0][8]==CUBE_R)==1)
			 { 
				 if((CUBE_DATA.cube[4][0]==CUBE_D)==1)
				 {
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up2;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right1;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up_;
					 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Right_;
					 break;
				 }
			 }
		 }
		 CUBE_DATA.F2L[n][CNT_F2L[n]++] = Up1;
	 }
	 

}

void OLL(void)
{
	int i;

	for(i = 0 ; i < 4 ; i++) 
	{
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U))==1) break;
		//1
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Left2;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			break;
		}
		//2
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			break;
		}
		//3
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front2;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//4
		if(((CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left2;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//5
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Down_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Down1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//6
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//7
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front2;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//8
		if(((CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//9
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//10
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//11
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//12
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//13
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//14
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//15
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//16
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			break;
		}
		//17
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			break;
		}
		//18
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//19
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//20
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//21
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//22
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[5][5]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//23
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[2][1]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//24
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//25
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//26
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//27
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//28
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			break;
		}
		//29
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//30
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//31
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Left2;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//32
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//33
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Front2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//34
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//35
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//36
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//37
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//38
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Down_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Down1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//39
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			break;
		}
		//40
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Down1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Down_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//41
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//42
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//43
		if(((CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			break;
		}
		//44
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//45
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			break;
		}
		//46
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			break;
		}
		//47
		if(((CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Left2;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//48
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			break;
		}
		//49
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U)&&(CUBE_DATA.cube[2][0]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Back2;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			break;
		}
		//50
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][2]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][7]==CUBE_U)&&(CUBE_DATA.cube[4][3]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Back_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Back1;
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Front2;
			break;
		}
		//51
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//52
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//53
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[4][6]==CUBE_U)&&(CUBE_DATA.cube[5][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Up_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			break;
		}
		//54
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[4][0]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Up1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//55
		if(((CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][6]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right2;
			CUBE_DATA.OLL[CNT_OLL++] = Down_;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Down1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Up2;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			break;
		}
		//56
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][6]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[2][2]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			break;
		}
		//57
		if(((CUBE_DATA.cube[1][0]==CUBE_U)&&(CUBE_DATA.cube[1][1]==CUBE_U)&&(CUBE_DATA.cube[1][3]==CUBE_U)&&(CUBE_DATA.cube[1][5]==CUBE_U)&&(CUBE_DATA.cube[1][7]==CUBE_U)&&(CUBE_DATA.cube[1][8]==CUBE_U)&&(CUBE_DATA.cube[0][8]==CUBE_U)&&(CUBE_DATA.cube[5][8]==CUBE_U))==1)
		{
			CUBE_DATA.OLL[CNT_OLL++] = Right_;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left_;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			CUBE_DATA.OLL[CNT_OLL++] = Right1;
			CUBE_DATA.OLL[CNT_OLL++] = Front_;
			CUBE_DATA.OLL[CNT_OLL++] = Left1;
			CUBE_DATA.OLL[CNT_OLL++] = Front1;
			break;
		}

		CUBE_DATA.OLL[CNT_OLL++] = Up1;
	}
}

void PLL(void)
{
	int i,j;
	for(j = 0 ; j< 4 ; j++)
	{
	for(i = 0 ; i< 4 ; i++)
	{
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&
			(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&
			(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&
			(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 ) break;
		// 1
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_F)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_L)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_R)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			goto go;
		}
		// 2
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_L)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_F)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			goto go;
		}
		// 3
		if(((CUBE_DATA.cube[0][6]==CUBE_F)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_B)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[5][2]==CUBE_R)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			goto go;
		}
		// 4
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_L)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_L)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_B)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			goto go;
		}
		//5
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_L)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_F)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_B)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			goto go;
		}
		//6
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_L)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_B)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_R)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			goto go;
		}
		//7
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_F)&&(CUBE_DATA.cube[2][0]==CUBE_R)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_L)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_F)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			goto go;
		}
		//8
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_B)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Front2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			goto go;
		}
		//9
		if(((CUBE_DATA.cube[0][6]==CUBE_F)&&(CUBE_DATA.cube[0][7]==CUBE_R)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_B)&&(CUBE_DATA.cube[4][6]==CUBE_L)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_B)&&(CUBE_DATA.cube[5][2]==CUBE_R)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			goto go;
		}
		//10
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_B)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_B)&&(CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			goto go;
		}
		//11
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_F)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up2;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			goto go;
		}
		//12
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_L)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_F)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up2;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			goto go;
		}
		//13
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_F)&&(CUBE_DATA.cube[4][6]==CUBE_B)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_R)&&(CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			goto go;
		}
		//14
		if(((CUBE_DATA.cube[0][6]==CUBE_L)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_L)&&(CUBE_DATA.cube[2][1]==CUBE_L)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_F)&&(CUBE_DATA.cube[5][5]==CUBE_F)&&(CUBE_DATA.cube[5][8]==CUBE_B)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			goto go;
		}
		//15
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_B)&&(CUBE_DATA.cube[0][8]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_L)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_B)&&(CUBE_DATA.cube[2][1]==CUBE_L)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_F)&&(CUBE_DATA.cube[5][8]==CUBE_R)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Back2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			goto go;
		}
		//16
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_L)&&(CUBE_DATA.cube[0][8]==CUBE_R)&&(CUBE_DATA.cube[4][0]==CUBE_F)&&(CUBE_DATA.cube[4][3]==CUBE_B)&&(CUBE_DATA.cube[4][6]==CUBE_L)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_B)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_R)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			goto go;
		}
		//17
		if(((CUBE_DATA.cube[0][6]==CUBE_F)&&(CUBE_DATA.cube[0][7]==CUBE_R)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_L)&&(CUBE_DATA.cube[4][6]==CUBE_B)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_R)&&(CUBE_DATA.cube[5][2]==CUBE_R)&&(CUBE_DATA.cube[5][5]==CUBE_B)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			goto go;
		}	
		//18
		if(((CUBE_DATA.cube[0][6]==CUBE_L)&&(CUBE_DATA.cube[0][7]==CUBE_R)&&(CUBE_DATA.cube[0][8]==CUBE_L)&&(CUBE_DATA.cube[4][0]==CUBE_B)&&(CUBE_DATA.cube[4][3]==CUBE_L)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_B)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_F)&&(CUBE_DATA.cube[5][5]==CUBE_B)&&(CUBE_DATA.cube[5][8]==CUBE_R)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			goto go;
		}
		//19
		if(((CUBE_DATA.cube[0][6]==CUBE_R)&&(CUBE_DATA.cube[0][7]==CUBE_L)&&(CUBE_DATA.cube[0][8]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_L)&&(CUBE_DATA.cube[4][3]==CUBE_B)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_L)&&(CUBE_DATA.cube[2][1]==CUBE_F)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_B)&&(CUBE_DATA.cube[5][5]==CUBE_R)&&(CUBE_DATA.cube[5][8]==CUBE_B)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Up_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Up1;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			goto go;
		}
		//20
		if(((CUBE_DATA.cube[0][6]==CUBE_B)&&(CUBE_DATA.cube[0][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_F)&&(CUBE_DATA.cube[4][0]==CUBE_L)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_R)&&(CUBE_DATA.cube[2][0]==CUBE_B)&&(CUBE_DATA.cube[2][1]==CUBE_B)&&(CUBE_DATA.cube[2][2]==CUBE_F)&&(CUBE_DATA.cube[5][2]==CUBE_L)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_R)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Front_;
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Left2;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			goto go;
		}	
		//21
		if(((CUBE_DATA.cube[0][6]==CUBE_F)&&(CUBE_DATA.cube[0][7]==CUBE_F)&&(CUBE_DATA.cube[0][8]==CUBE_B)&&(CUBE_DATA.cube[4][0]==CUBE_R)&&(CUBE_DATA.cube[4][3]==CUBE_R)&&(CUBE_DATA.cube[4][6]==CUBE_L)&&(CUBE_DATA.cube[2][0]==CUBE_F)&&(CUBE_DATA.cube[2][1]==CUBE_B)&&(CUBE_DATA.cube[2][2]==CUBE_B)&&(CUBE_DATA.cube[5][2]==CUBE_R)&&(CUBE_DATA.cube[5][5]==CUBE_L)&&(CUBE_DATA.cube[5][8]==CUBE_L)) == 1 )
		{
			CUBE_DATA.PLL[CNT_PLL++] = Right_;
			CUBE_DATA.PLL[CNT_PLL++] = Down1;
			CUBE_DATA.PLL[CNT_PLL++] = Back_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Left_;
			CUBE_DATA.PLL[CNT_PLL++] = Front1;
			CUBE_DATA.PLL[CNT_PLL++] = Left1;
			CUBE_DATA.PLL[CNT_PLL++] = Down2;
			CUBE_DATA.PLL[CNT_PLL++] = Right2;
			CUBE_DATA.PLL[CNT_PLL++] = Back1;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			CUBE_DATA.PLL[CNT_PLL++] = Down_;
			CUBE_DATA.PLL[CNT_PLL++] = Right1;
			goto go;
		}
			
		CUBE_DATA.PLL[CNT_PLL++] = Up1;
		if(i == 3) CNT_PLL = CNT_PLL - 4;
	}
	CUBE_DATA.PLL[CNT_PLL++] = X_Y;
	}
	go:;
}

void ARM_Trans(int *p)
{
	int i = 0,j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.CROSS[j];
		i++;
		if(CUBE_DATA.CROSS[++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.F2L[0][j];
		i++;
		if(CUBE_DATA.F2L[0][++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.F2L[1][j];
		i++;
		if(CUBE_DATA.F2L[1][++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.F2L[2][j];
		i++;
		if(CUBE_DATA.F2L[2][++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.F2L[3][j];
		i++;
		if(CUBE_DATA.F2L[3][++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.OLL[j];
		i++;
		if(CUBE_DATA.OLL[++j] == 0) break;
	}
	j = 0;
	while(1)
	{
		p[i] = CUBE_DATA.PLL[j];
		i++;
		if(CUBE_DATA.PLL[++j] == 0) break;
	}
}

void Transform_ARM_ver(void)
{ 
	// U -> F
	int i,j;
	for(i = 0 ; i < 150 ; i++)
	{
		if(((ARM_Transform[i] == 3)||(ARM_Transform[i] == 2)||(ARM_Transform[i] == 1)||(ARM_Transform[i] == 4)||(ARM_Transform[i] == 5)||(ARM_Transform[i] == 6)) == 1)
		{
			for(j = 149 ; j > i ; j--)
			{
				ARM_Transform[j] = ARM_Transform[j - 1];
				ARM_Transform[j] = Z_X_rotation_restoration(ARM_Transform[j]);
			}
			ARM_Transform[i] = 25;
			CNT++;
		}
	}


	
}

void CUBE_MAIN(void)
{
	/* 1단계 십자가 */
	X_Z;
	
	X_Z;
	
	cube_CROSS_1();
	cube_CROSS_2();
	U_Rotation_Transposition(CUBE_DATA.CROSS,&CNT);
	OPTIMIZATION_RATATION_X_Y(CUBE_DATA.CROSS);
	OPTIMIZATION_RATATION_X_Z(CUBE_DATA.CROSS);
	OPTIMIZATION_RATATION_X_Z(CUBE_DATA.CROSS);
	D_Rotation_Transposition(CUBE_DATA.CROSS,&CNT);
	
	/* 2단계 F2L */
	 F2L(0);
	 U_Rotation_Transposition(CUBE_DATA.F2L[0],&CNT_F2L[0]);

	 CUBE_DATA.F2L[1][CNT_F2L[1]++] = X_Y;
	 F2L(1);
	 OPTIMIZATION_RATATION_X_Y(CUBE_DATA.F2L[1]);
	 U_Rotation_Transposition(CUBE_DATA.F2L[1],&CNT_F2L[1]);


	 CUBE_DATA.F2L[2][CNT_F2L[2]++] = X_Y;
	 CUBE_DATA.F2L[2][CNT_F2L[2]++] = X_Y;
	 F2L(2);
	 OPTIMIZATION_RATATION_X_Y(CUBE_DATA.F2L[2]);
	 U_Rotation_Transposition(CUBE_DATA.F2L[2],&CNT_F2L[2]);
  
	 CUBE_DATA.F2L[3][CNT_F2L[3]++] = X_Y;
	 CUBE_DATA.F2L[3][CNT_F2L[3]++] = X_Y;
	 CUBE_DATA.F2L[3][CNT_F2L[3]++] = X_Y;
	 F2L(3);
	 OPTIMIZATION_RATATION_X_Y(CUBE_DATA.F2L[3]);
	 U_Rotation_Transposition(CUBE_DATA.F2L[3],&CNT_F2L[3]);
	 
	 /*3단계 OLL*/
     OLL();
	 U_Rotation_Transposition(CUBE_DATA.OLL,&CNT_OLL);

	 /*4단계 PLL*/
	 PLL();
	 OPTIMIZATION_RATATION_X_Y(CUBE_DATA.PLL);
	 U_Rotation_Transposition(CUBE_DATA.PLL,&CNT_PLL);

	 ARM_Trans(ARM_Transform);

	 Transform_ARM_ver();
}



