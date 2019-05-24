#include "time.h"
#include "key.h"

extern key_msg_dat g_key_data;
int flag_10s = 1;
int i = 0;

/*******************************************************************************
* �� �� ��         : TIM4_Init
* ��������         : TIM4��ʼ������
* ��    ��         : per:��װ��ֵ
                     psc:��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
void TIM3_Init(u16 per, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��TIM4ʱ��

    TIM_TimeBaseInitStructure.TIM_Period = per; //�Զ�װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //��Ƶϵ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //�������ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //������ʱ���ж�
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//��ʱ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;      //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);

    //TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��
}
void TIM4_Init(u16 per, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��TIM4ʱ��

    TIM_TimeBaseInitStructure.TIM_Period = per; //�Զ�װ��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //��Ƶϵ��
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //�������ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //������ʱ���ж�
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//��ʱ���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);

//  TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��
}

/*******************************************************************************
* �� �� ��         : TIM4_IRQHandler
* ��������         : TIM4�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
        g_key_data.key_flag = 1;
        g_key_data.key_value = get_key_value();
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

}


void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update))
    {
        i++;
        if (i == 5)
        {
            flag_10s = 0;
            i = 0;
        }

    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}


