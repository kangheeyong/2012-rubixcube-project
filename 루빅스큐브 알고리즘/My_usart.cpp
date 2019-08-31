#include "My_usart.h"
#include <serialcomm.h>
#include <serialport.h>
CSerialPort _serial;
void My_usart :: usart_open()
{
	   
	if(_serial.OpenPort(L"COM6"))   // 실제 사용될 COM Port 를 넣어야합니다.  
	{
		_serial.ConfigurePort(CBR_115200, 8, FALSE, NOPARITY, ONESTOPBIT);
		_serial.SetCommunicationTimeouts(0, 0, 0, 0, 0);  
	}  
	
}
void My_usart ::usart_send(unsigned char data)
{
	_serial.WriteByte(data);
}

void My_usart :: usart_close()
{
	_serial.ClosePort();
}
void My_usart ::usart_read(unsigned char* data)
{
	_serial.ReadByte(data,1);
}