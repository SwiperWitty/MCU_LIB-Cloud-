#include "uart_handle.h"

struct _Uart_Data CV_UART[5];

void Uart_Init(char Channel, int Baud,int SET)
{
    #ifdef Exist_UART
        switch (Channel)
		{
		case 1:
			Uart1_Init(Baud,SET);
			break;
		case 2:
			Uart2_Init(Baud,SET);
			break;
		case 3:
			Uart3_Init(Baud,SET);
			break;
		case 4:
			Uart4_Init(Baud,SET);
			break;
		case 5:
			Uart5_Init(Baud,SET);
			break;
		default:
			break;
		}

    #endif

}

void Get_RXD(struct _Uart_Data *Target, char res) //接收处理函数
{
    if (!Target->Rxd_Received)		// 0 允许接收，1 不允许接收
    {
        Target->DATA.Buff[Target->DATA.Length++] = res;
        if (END_Data != 'N')		//如果设有 停止位
        {
            if (res == END_Data)	//Get停止位
            {
                Target->Rxd_Received = 1;
            }
        }
        if (Target->DATA.Length > Length_MAX) //超长（异常需要清零）
        {
            Target->Rxd_Received = 1;
        }
    }
}

#ifdef Exist_UART
void UART1_Interrupt()
{
    char temp,Channel = 1;
    if (UART_Interrupt_RXDFalg(Channel) != 0)
    {
        UART_Interrupt_RXDFalgClear(Channel);
        temp = UART_RXD_DATA(Channel);
        Get_RXD(&CV_UART[Channel], temp);
    }
}
void UART2_Interrupt()
{
    char temp,Channel = 2;
    if (UART_Interrupt_RXDFalg(Channel) != 0)
    {
        UART_Interrupt_RXDFalgClear(Channel);
        temp = UART_RXD_DATA(Channel);
        Get_RXD(&CV_UART[Channel], temp);
    }
}
void UART3_Interrupt()
{
    char temp,Channel = 3;
    if (UART_Interrupt_RXDFalg(Channel) != 0)
    {
        UART_Interrupt_RXDFalgClear(Channel);
        temp = UART_RXD_DATA(Channel);
        Get_RXD(&CV_UART[Channel], temp);
    }
}
void UART4_Interrupt()
{
    char temp,Channel = 4;
    if (UART_Interrupt_RXDFalg(Channel) != 0)
    {
        UART_Interrupt_RXDFalgClear(Channel);
        temp = UART_RXD_DATA(Channel);
        Get_RXD(&CV_UART[Channel], temp);
    }
}
void UART5_Interrupt()
{
    char temp,Channel = 5;
    if (UART_Interrupt_RXDFalg(Channel) != 0)
    {
        UART_Interrupt_RXDFalgClear(Channel);
        temp = UART_RXD_DATA(Channel);
        Get_RXD(&CV_UART[Channel], temp);
    }
}

#endif // DEBUG

char UART_Send_Data(char Channel, const U8 *Data, int Length)
{
    if (Length > Length_MAX)
        return 0;
	if (Channel > UART_Channel_MAX)
		return (char)-1;
	#ifdef Exist_UART
    int temp;
    int i = 0;
    while (temp--)
    {
		UART_TXD_DATA(Channel,Data[i++]);
    }
    #endif
    return 1;
}

void UART_Send_String(char Channel, const char *String)
{
    int Length = strlen(String);
    if (Length > Length_MAX)
        return;

	UART_Send_Data(Channel,(U8 *)String,Length);
}
