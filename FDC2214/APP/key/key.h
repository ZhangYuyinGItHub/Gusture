#ifndef _key_H
#define _key_H


#include "system.h"

#define KEY_LEFT_Pin     GPIO_Pin_13| GPIO_Pin_14  |GPIO_Pin_15   //����K_LEFT�ܽ�


#define KEY_Port (GPIOB) //����˿�
#define RCC_key RCC_APB2Periph_GPIOB


//ʹ��λ��������
#define K_UP PBin(13)
#define K_DOWN PBin(14)
#define K_LEFT PBin(15)








void KEY_Init(void);
void KEY_Scan(void);
#endif
