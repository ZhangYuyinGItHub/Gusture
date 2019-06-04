#include "usart2.h"
#include "misc.h"
#include "stdio.h"
#include <stdarg.h>
#include "stm32f10x_usart.h"

#include "usart1.h"

static uint8_t USART2_RX_BUF[USART2_REC_LEN];
static uint16_t  USART2_RX_STA = 0;

void uart2_loop_proc(void)
{
    uint8_t t;
    uint8_t len;
    if (USART2_RX_STA & 0x8000)
    {
        len = USART2_RX_STA & 0x3f;
        printf("uart2 receive data from ble\r\n");
#if 1

        /*send through uart1*/
        for (t = 0; t < len; t++)
        {
            USART_SendData(USART1, USART2_RX_BUF[t]);
            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
        }
#endif
        USART2_RX_STA = 0;
    }
}

void USART2_Config(u32 My_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStrue;
    USART_InitTypeDef USART_InitStrue;
    NVIC_InitTypeDef NVIC_InitStrue;

    // ����ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    USART_DeInit(USART2);  //��λ����2 -> ����û��

    // ��ʼ�� ���ڶ�ӦIO��  TX-PA2  RX-PA3
    GPIO_InitStrue.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStrue.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStrue);

    GPIO_InitStrue.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStrue.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStrue);

    // ��ʼ�� ����ģʽ״̬
    USART_InitStrue.USART_BaudRate = My_BaudRate; // ������
    USART_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Ӳ��������
    USART_InitStrue.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // ���� ���� ģʽ��ʹ��
    USART_InitStrue.USART_Parity = USART_Parity_No; // û����żУ��
    USART_InitStrue.USART_StopBits = USART_StopBits_1; // һλֹͣλ
    USART_InitStrue.USART_WordLength = USART_WordLength_8b; // ÿ�η������ݿ��Ϊ8λ
    USART_Init(USART2, &USART_InitStrue);

    USART_Cmd(USART2, ENABLE); //ʹ�ܴ���
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //���������ж�

    // ��ʼ�� �ж����ȼ�
    NVIC_InitStrue.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStrue);
}

void USART2_IRQHandler(void) // ����2�жϷ�����
{
    uint8_t res;
    if (USART_GetITStatus(USART2, USART_IT_RXNE)) // �жϱ�־
    {
#if 1
        res = USART_ReceiveData(USART2); // ����2 ����
        //USART_SendData(USART1, res);  // ����1 ����
#if 1
        //res = USART_ReceiveData(USART1); //(USART1->DR);  //????????
        if ((USART2_RX_STA & 0x8000) == 0)
        {
            if (USART2_RX_STA & 0x4000)
            {
                if (res != 0x0a)
                {
                    USART2_RX_STA = 0;
                }
                else
                {
                    USART2_RX_STA |= 0x8000;
                }
            }
            else //0X0D
            {
                if (res == 0x0d)
                {
                    USART2_RX_STA |= 0x4000;
                }
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = res ;
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART_REC_LEN - 1))
                    {
                        USART2_RX_STA = 0;//reset length 0
                    }
                }
            }
        }
#endif
#else
        res = USART_ReceiveData(USART2); //(USART1->DR);  //????????
        if ((USART2_RX_STA & 0x8000) == 0)
        {
            if (USART2_RX_STA & 0x4000)
            {
                if (res != 0x0a)
                {
                    USART2_RX_STA = 0;
                }
                else
                {
                    USART2_RX_STA |= 0x8000;
                }
            }
            else //0X0D
            {
                if (res == 0x0d)
                {
                    USART2_RX_STA |= 0x4000;
                }
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = res ;
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART_REC_LEN - 1))
                    {
                        USART2_RX_STA = 0;//reset length 0
                    }
                }
            }
        }
#endif
    }

}

#if 0
/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
    /* ��Printf���ݷ������� */
    USART_SendData(USART2, (unsigned char) ch);
    while (!(USART2->SR & USART_FLAG_TXE));

    return (ch);
}
#endif
/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */
/*
 * ��������USART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���1����USART1
 *           -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *             -...    ��������
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 *         ����Ӧ��USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *                   USART1_printf( USART1, "\r\n %d \r\n", i );
 *                   USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART2_printf(USART_TypeDef *USARTx, uint8_t *Data, ...)
{
    const char *s;
    int d;
    char buf[16];

    va_list ap;
    va_start(ap, Data);

    while (*Data != 0)      // �ж��Ƿ񵽴��ַ���������
    {
        if (*Data == 0x5c)    //'\'
        {
            switch (*++Data)
            {
            case 'r':                                     //�س���
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;

            case 'n':                                     //���з�
                USART_SendData(USARTx, 0x0a);
                Data ++;
                break;

            default:
                Data ++;
                break;
            }
        }
        else if (*Data == '%')
        {
            //
            switch (*++Data)
            {
            case 's':                                         //�ַ���
                s = va_arg(ap, const char *);
                for (; *s; s++)
                {
                    USART_SendData(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                }
                Data++;
                break;

            case 'd':                                       //ʮ����
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++)
                {
                    USART_SendData(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                }
                Data++;
                break;
            default:
                Data++;
                break;
            }
        } /* end of else if */
        else { USART_SendData(USARTx, *Data++); }
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);

    }

    va_end(ap);
}

