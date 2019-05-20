#include "key.h"
#include "SysTick.h"
#include "oled.h"
extern int mod;
extern int flag_s1;
extern int flag_s;
extern int flag_s2;
/*******************************************************************************
* �� �� ��         : KEY_Init
* ��������         : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����
    RCC_APB2PeriphClockCmd(RCC_key, ENABLE);

    GPIO_InitStructure.GPIO_Pin = KEY_LEFT_Pin ;   //ѡ����Ҫ���õ�IO��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //���ô�������
    GPIO_Init(KEY_Port, &GPIO_InitStructure);         /* ��ʼ��GPIO */

}


void KEY_Scan(void)
{
    static u8 key = 1;
    if (key == 1 && (K_UP == 0 || K_DOWN == 0 || K_LEFT == 0)) //����һ����������
    {
        delay_ms(10);  //����
        key = 0;
        if (K_UP == 0)
        {
            mod++;
            flag_s = 0;
            OLED_Clear();
            if (mod == 5)
            {
                mod = 1;
            }
        }
        else if (K_DOWN == 0)
        {

            flag_s = 1;

            if (mod == 1)

            {
                if (flag_s1 == 3)
                {

                    flag_s1 = 0;
                }
            }
            else if (mod == 3)
            {

                if (flag_s2 == 5)
                {
                    flag_s2 = 0;
                }
            }




        }
        else if (K_LEFT == 0)
        {

            flag_s = 0;

        }

    }
    else if (K_UP == 1 && K_DOWN == 1 && K_LEFT == 1) //�ް�������
    {

        key = 1;
    }


}

