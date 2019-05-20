#include "led.h"

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������         : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����

    RCC_APB2PeriphClockCmd(LED_PORT_RCC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_PIN; //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�����������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ô�������
    GPIO_Init(LED_PORT, &GPIO_InitStructure);      /* ��ʼ��GPIO */

    GPIO_SetBits(LED_PORT, LED_PIN);  //��LED�˿����ߣ�Ϩ������LED
}
void LED_Init1()
{
    GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����

    RCC_APB2PeriphClockCmd(LED_PORT_RCC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_PIN1; //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�����������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ô�������
    GPIO_Init(LED_PORT1, &GPIO_InitStructure);     /* ��ʼ��GPIO */

    GPIO_ResetBits(LED_PORT1, LED_PIN);  //��LED�˿����ߣ�Ϩ������LED



    RCC_APB2PeriphClockCmd(LED_PORT_RCC2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_PIN2; //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�����������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ô�������
    GPIO_Init(LED_PORT2, &GPIO_InitStructure);     /* ��ʼ��GPIO */

    GPIO_ResetBits(LED_PORT2, LED_PIN);  //��LED�˿����ߣ�Ϩ������LED
}




