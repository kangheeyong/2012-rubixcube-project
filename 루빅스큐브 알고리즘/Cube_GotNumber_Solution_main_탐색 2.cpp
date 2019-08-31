#include <stdio.h>
#include "Cube_GotNumber_1_Solution - 검색용.h"
#include "Cube_MySQL.h"
#include <string>
#include <string.h>
#include<stdlib.h>

#define R			rotation_10(pC)
#define R_			rotation_12(pC)
#define R2			rotation_11(pC)

#define L			rotation_9(pC)
#define L_			rotation_7(pC)
#define L2			rotation_8(pC)

#define F			rotation_15(pC)
#define F_			rotation_13(pC)
#define F2			rotation_14(pC)

#define B			rotation_16(pC)
#define B_			rotation_18(pC)
#define B2			rotation_17(pC)

#define U			rotation_3(pC)
#define U_			rotation_1(pC)
#define U2			rotation_2(pC)

#define D			rotation_4(pC)
#define D_			rotation_6(pC)
#define D2			rotation_5(pC)

#define X_Z				rotation_19(pC)
#define X_Y				rotation_20(pC)

GotNumber_1 c1;
Cube_MySQL m1;

int Cube[6][9]; // 인트형 데이터
int (*pC)[9] = Cube; //회전할려면 필요함
char _Cube[8][55]; //문자형 데이터

char data[20];
int data_n = 1;

char *mysql_p;

char query_data[100] = "select data from ";
char query_cube[100] = "select cube from ";
char query_surch[200] = "select data from ";
char query_save[200] = "insert into ";

void trans_int_char(int *ip,char *chp)
{
	for(int i = 0 ; i < 54 ; i++)
	{
	 if(ip[i] == 1) chp[i] = '1';
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
		 if(chp[i] == '1') ip[i] = 1;
		else if(chp[i] == '2') ip[i] = 2;
		else if(chp[i] == '3') ip[i] = 3;
		else if(chp[i] == '6') ip[i] = 6;
		else if(chp[i] == '7') ip[i] = 7;
		else if(chp[i] == '8') ip[i] = 8;
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

void quert_data_string_in_surch(char *p,int n,int m)
{
	int i;
	char a[18][7] = {{"cube11"},{"cube22"},{"cube33"},{"cube44"},{"cube55"},{"cube66"},{"cube77"},{"cube88"},{"cube99"}};
	char b[] = " where num = ";
	char c[20];

	itoa(m, c, 10);
	for(i = 17 ; i < 23 ; i++) p[i] = a[n][i - 17];
	for(i = 23 ; i < 36 ; i++) p[i] = b[i - 23];	
	for(i = 36 ; c[i-36] != NULL ; i++) p[i] = c[i - 36];
	p[i] = NULL;
}
void quert_data_surch(char *p,int n,char *pp)
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
void quert_data_string_in_save(char *p,int n,int m,char *pp,char *ppp)
{
	int i,j;
	char a[18][7] = {{"cube11"},{"cube22"},{"cube33"},{"cube44"},{"cube55"},{"cube66"},{"cube77"},{"cube88"},{"cube99"}};
	char b[] = "(num,cube,data) values (";
	char c[20];

	itoa(m, c, 10);
	for(i = 12 ; i < 18 ; i++) p[i] = a[n][i - 12];
	for(i = 18 ; i < 42 ; i++) p[i] = b[i - 18];
	for(i = 42 ; c[i-42] != NULL ; i++) p[i] = c[i - 42];
	p[i++] = ',';
	p[i++] = '\'';

	for(j = i ; pp[j-i] != NULL ; j++) p[j] = pp[j-i];
	p[j++]= '\'';
	p[j++]= ',';
	p[j++]= '\'';
	for(i = j ; ppp[i-j] != NULL ; i++) p[i] = ppp[i-j];
	p[i++] = '\'';
	p[i++] = ')';
	p[i] = NULL;
}

void cube_symmetry(int (*ppC)[9],char (*ppChar)[55])
{
	trans_int_char(ppC[0],ppChar[0]);
	



}

void surch_cube_gotnumber(int table_n)
{
	int num_data = 1;
	int i;

	while(1)
	{
		//------------------------------------------
		quert_data_string_in_surch(query_cube,table_n,num_data); //문장 ,n+1테이블 , n번째 자료검색
		m1.MySQL_Query(query_cube); // 쿼리문 전송
		//------------------------------------------	

		mysql_p = m1.MySQL_Data(); // 검색 데이터 꺼내오기

		if(mysql_p == NULL) break;    // 데이터가 없으면 탐색 종료

		trans_char_int(Cube[0],mysql_p); // 인트형으로 변환
		
		m1.MySQL_free();   // 다음 검색을 위해서 꼭 해주자

		quert_data_string_in_surch(query_data,table_n,num_data); //문장 ,n+1테이블 , n번째 큐브 위치
		m1.MySQL_Query(query_data); // 쿼리문 전송

		mysql_p = m1.MySQL_Data(); // 검색 데이터 꺼내오기);

		for(i = 0 ; mysql_p[i] != NULL ; i++) data[i] = mysql_p[i]; // 맞추는 방법 데이터 넣기
		data[i] = NULL;
		m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자





	    
		//----------------------- 여기까지는 기본 ---------------------
		//
		int fl= table_n+1,fl_n = 0; // fl-1 테이블 , fl_n 무조건 0~3까지 반복
		
		//------------------------------------------------------------
		

		data[i] = c1.L2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.L2;


		data[i] = c1.R2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.R2;

		data[i] = c1.U;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.U_;

		data[i] = c1.U_;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.U;

		data[i] = c1.U2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.U2;

	

		data[i] = c1.B2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.B2;



		data[i] = c1.F2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.F2;

		data[i] = c1.D;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.D_;

		data[i] = c1.D_;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.D;

		data[i] = c1.D2;
		cube_symmetry(Cube,_Cube); // 대칭 구조 만들기
		for(int k = fl ;k > -1 ; k--)
		{
			for(fl_n = 0 ; fl_n < 1 ; fl_n++)
			{
				quert_data_surch(query_surch,k,_Cube[fl_n]);
				m1.MySQL_Query(query_surch); // 쿼리문 전송
				mysql_p = m1.MySQL_Data();
				if(mysql_p != NULL)  // 다음 검색을 위해서 꼭 해주자
				{
					m1.MySQL_free();
					break;					
				}
				m1.MySQL_free(); // 다음 검색을 위해서 꼭 해주자
			}
			if(mysql_p != NULL) break; // 다음 검색을 위해서 꼭 해주자
			if( k == 0)
			{
				quert_data_string_in_save(query_save,fl,data_n,_Cube[0],data); //문장 ,n+1테이블 , n번째 자료검색
				m1.MySQL_Query(query_save); // 쿼리문 전송
				data_n++;
			}
		}
		c1.D2;

	printf("%d   %d\n",data_n-1,num_data);
	num_data++; //다음 탐색 번호
	}
}

void main(void)
{
	m1.MySQL_Connect();
		
	c1.CUBE_Data_initialization(Cube);

	surch_cube_gotnumber(1);

	c1.CUBE_Data_print(Cube);

	m1.MySQL_Close();
	while(1)      
	{
		
	} 
}   