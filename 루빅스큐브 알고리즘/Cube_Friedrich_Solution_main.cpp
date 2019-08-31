#include <iostream>
#include "Cube_Friedrich_Solution.h"

using namespace std;

void main(void)
{
	Friedrch_Algorithm Cube;

	 
	Cube.CUBE_U = 1; //노란색 
	Cube.CUBE_B = 0; //주황색  
	Cube.CUBE_D = 3; // 
	Cube.CUBE_F = 2;    
	Cube.CUBE_R = 4;  
	Cube.CUBE_L = 5;   
	Cube.CUBE_DATA.cube[0][0] = 1; 
	Cube.CUBE_DATA.cube[0][1] = 3;  
	Cube.CUBE_DATA.cube[0][2] = 2;
	Cube.CUBE_DATA.cube[0][3] = 5;    
	Cube.CUBE_DATA.cube[0][5] = 5; 
	Cube.CUBE_DATA.cube[0][6] = 1;     
	Cube.CUBE_DATA.cube[0][7] = 3;  
	Cube.CUBE_DATA.cube[0][8] = 0;
	 
	Cube.CUBE_DATA.cube[1][0] = 0;
	Cube.CUBE_DATA.cube[1][1] = 5;
	Cube.CUBE_DATA.cube[1][2] = 4; 
	Cube.CUBE_DATA.cube[1][3] = 0;  
	Cube.CUBE_DATA.cube[1][5] = 2;
	Cube.CUBE_DATA.cube[1][6] = 3;  
	Cube.CUBE_DATA.cube[1][7] = 1;
	Cube.CUBE_DATA.cube[1][8] = 3;     
	      
	Cube.CUBE_DATA.cube[2][0] = 5;    
	Cube.CUBE_DATA.cube[2][1] = 2; 
	Cube.CUBE_DATA.cube[2][2] = 5;   
	Cube.CUBE_DATA.cube[2][3] = 3; 
	Cube.CUBE_DATA.cube[2][5] = 1;            
	Cube.CUBE_DATA.cube[2][6] = 2;     
	Cube.CUBE_DATA.cube[2][7] = 1;  
	Cube.CUBE_DATA.cube[2][8] = 2; 
	    
	Cube.CUBE_DATA.cube[3][0] = 5;     
	Cube.CUBE_DATA.cube[3][1] = 4;
	Cube.CUBE_DATA.cube[3][2] = 4;       
	Cube.CUBE_DATA.cube[3][3] = 3;  
	Cube.CUBE_DATA.cube[3][5] = 5; 
	Cube.CUBE_DATA.cube[3][6] = 0; 
	Cube.CUBE_DATA.cube[3][7] = 4;
	Cube.CUBE_DATA.cube[3][8] = 4;
	 
	Cube.CUBE_DATA.cube[4][0] = 3;
	Cube.CUBE_DATA.cube[4][1] = 0;
	Cube.CUBE_DATA.cube[4][2] = 3;
	Cube.CUBE_DATA.cube[4][3] = 4;
	Cube.CUBE_DATA.cube[4][5] = 2; 
	Cube.CUBE_DATA.cube[4][6] = 0; 
	Cube.CUBE_DATA.cube[4][7] = 0;     
	Cube.CUBE_DATA.cube[4][8] = 1;   
	  
	Cube.CUBE_DATA.cube[5][0] = 5;   
	Cube.CUBE_DATA.cube[5][1] = 1; 
	Cube.CUBE_DATA.cube[5][2] = 4;  
	Cube.CUBE_DATA.cube[5][3] = 2; 
	Cube.CUBE_DATA.cube[5][5] = 4;   
	Cube.CUBE_DATA.cube[5][6] = 1;  
	Cube.CUBE_DATA.cube[5][7] = 0;
	Cube.CUBE_DATA.cube[5][8] = 2;

	 
	Cube.CUBE_MAIN();


	while(1)      
	{
	;
	} 
}  