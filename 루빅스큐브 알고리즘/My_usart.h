

#include <iostream>



using namespace std;

class My_usart
{
	
public :
	
	//unsigned char �� ����ϵ���

	void usart_open();
	void usart_send(unsigned char data);
	void usart_close();
	void usart_read(unsigned char* data); // ������ ���ο� ������ ���������� ���ѷ���
};