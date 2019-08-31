

#include <iostream>



using namespace std;

class My_usart
{
	
public :
	
	//unsigned char 로 사용하도록

	void usart_open();
	void usart_send(unsigned char data);
	void usart_close();
	void usart_read(unsigned char* data); // 데이터 새로운 데이터 읽을때까지 무한루프
};