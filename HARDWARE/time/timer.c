
#include "timer.h"



/*
 * ×¢Òâ£ºTIM_TimeBaseInitTypeDef½á¹¹ÌåÀïÃæÓĞ5¸ö³ÉÔ±£¬TIM6ºÍTIM7µÄ¼Ä´æÆ÷ÀïÃæÖ»ÓĞ
 * TIM_PrescalerºÍTIM_Period£¬ËùÒÔÊ¹ÓÃTIM6ºÍTIM7µÄÊ±ºòÖ»Ğè³õÊ¼»¯ÕâÁ½¸ö³ÉÔ±¼´¿É£¬
 * ÁíÍâÈı¸ö³ÉÔ±ÊÇÍ¨ÓÃ¶¨Ê±Æ÷ºÍ¸ß¼¶¶¨Ê±Æ÷²ÅÓĞ.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ¶¼ÓĞ
 *	TIM_CounterMode			     TIMx,x[6,7]Ã»ÓĞ£¬ÆäËû¶¼ÓĞ
 *  TIM_Period               ¶¼ÓĞ
 *  TIM_ClockDivision        TIMx,x[6,7]Ã»ÓĞ£¬ÆäËû¶¼ÓĞ
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]²ÅÓĞ
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */


/* ----------------   PWMĞÅºÅ ÖÜÆÚºÍÕ¼¿Õ±ÈµÄ¼ÆËã--------------- */
// ARR £º×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷µÄÖµ
// CLK_cnt£º¼ÆÊıÆ÷µÄÊ±ÖÓ£¬µÈÓÚ Fck_int / (psc+1) = 72M/(psc+1)
// PWM ĞÅºÅµÄÖÜÆÚ T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// Õ¼¿Õ±ÈP=CCR/(ARR+1)

#if	TIM1_Int
void TIM1_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	#if TIM1_OCInitStructure
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	#endif
	#if TIM1_BDTRInitStructure
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	#endif
	#if TIM1_NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif
	
	// ¿ªÆô¶¨Ê±Æ÷Ê±ÖÓ,¼´ÄÚ²¿Ê±ÖÓCK_INT=72M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	/*--------------------Ê±»ù½á¹¹Ìå³õÊ¼»¯-------------------------*/
	// ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷µÄÖµ£¬ÀÛ¼ÆTIM_Period+1¸öÆµÂÊºó²úÉúÒ»¸ö¸üĞÂ»òÕßÖĞ¶Ï
	TIM_TimeBaseStructure.TIM_Period=1999;
	// Çı¶¯CNT¼ÆÊıÆ÷µÄÊ±ÖÓ = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= 719;
	// Ê±ÖÓ·ÖÆµÒò×Ó £¬ÅäÖÃËÀÇøÊ±¼äÊ±ĞèÒªÓÃµ½
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ¼ÆÊıÆ÷¼ÆÊıÄ£Ê½£¬ÉèÖÃÎªÏòÉÏ¼ÆÊı
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// ÖØ¸´¼ÆÊıÆ÷µÄÖµ£¬Ã»ÓÃµ½²»ÓÃ¹Ü
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ³õÊ¼»¯¶¨Ê±Æ÷
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	#if TIM1_BDTRInitStructure
	// Êä³ö±È½ÏÍ¨µÀÉ²³µÍ¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	// BKINÒı½ÅÄ¬ÈÏÏÈÊä³öµÍµçÆ½
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	#endif
	
	#if TIM1_CH1
  // Êä³ö±È½ÏÍ¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	#if TIM1_CH1N
  // Êä³ö±È½ÏÍ¨µÀ»¥²¹Í¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	#endif
	
	/*--------------------Êä³ö±È½Ï½á¹¹Ìå³õÊ¼»¯-------------------*/		
	// ÅäÖÃÎªPWMÄ£Ê½2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 // »¥²¹Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	// ³õÊ¼»¯ÉèÖÃÕ¼¿Õ±È´óĞ¡
	// TIM_OCInitStructure.TIM_Pulse = 1800;
	// Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// »¥²¹Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNIdleState_Reset;
	// »¥²¹Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	#endif
	
	#if TIM1_CH2
  // Êä³ö±È½ÏÍ¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	#if TIM1_CH2N
  // Êä³ö±È½ÏÍ¨µÀ»¥²¹Í¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	#endif
	
	/*--------------------Êä³ö±È½Ï½á¹¹Ìå³õÊ¼»¯-------------------*/		
	// ÅäÖÃÎªPWMÄ£Ê½2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 // »¥²¹Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	// ³õÊ¼»¯ÉèÖÃÕ¼¿Õ±È´óĞ¡
	// TIM_OCInitStructure.TIM_Pulse = 1800;
	// Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// »¥²¹Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNIdleState_Reset;
	// »¥²¹Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	#endif
	
	#if TIM1_CH3
  // Êä³ö±È½ÏÍ¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	#if TIM1_CH3N
  // Êä³ö±È½ÏÍ¨µÀ»¥²¹Í¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	#endif
	
	/*--------------------Êä³ö±È½Ï½á¹¹Ìå³õÊ¼»¯-------------------*/		
	// ÅäÖÃÎªPWMÄ£Ê½2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 // »¥²¹Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	// ³õÊ¼»¯ÉèÖÃÕ¼¿Õ±È´óĞ¡
	// TIM_OCInitStructure.TIM_Pulse = 1800;
	// Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// »¥²¹Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNIdleState_Reset;
	// »¥²¹Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	#endif
	
	#if TIM1_CH4
  // Êä³ö±È½ÏÍ¨µÀ GPIO ³õÊ¼»¯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*--------------------Êä³ö±È½Ï½á¹¹Ìå³õÊ¼»¯-------------------*/		
	// ÅäÖÃÎªPWMÄ£Ê½2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// Êä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ³õÊ¼»¯ÉèÖÃÕ¼¿Õ±È´óĞ¡
	// TIM_OCInitStructure.TIM_Pulse = 1800;
	// Êä³öÍ¨µÀµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// Êä³öÍ¨µÀ¿ÕÏĞµçÆ½¼«ĞÔÅäÖÃ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	#endif
	
	#if TIM1_BDTRInitStructure
	/*-------------------É²³µºÍËÀÇø½á¹¹Ìå³õÊ¼»¯-------------------*/
	// ÓĞ¹ØÉ²³µºÍËÀÇø½á¹¹ÌåµÄ³ÉÔ±¾ßÌå¿É²Î¿¼BDTR¼Ä´æÆ÷µÄÃèÊö
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	// Êä³ö±È½ÏĞÅºÅËÀÇøÊ±¼äÅäÖÃ£¬¾ßÌåÈçºÎ¼ÆËã¿É²Î¿¼ BDTR:UTG[7:0]µÄÃèÊö
	// ÕâÀïÅäÖÃµÄËÀÇøÊ±¼äÎª152ns
  TIM_BDTRInitStructure.TIM_DeadTime = 11;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	// µ±BKINÒı½Å¼ì²âµ½¸ßµçÆ½µÄÊ±ºò£¬Êä³ö±È½ÏĞÅºÅ±»½ûÖ¹£¬¾ÍºÃÏñÊÇÉ²³µÒ»Ñù
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	#endif
	
	#if TIM1_NVIC
	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM1ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï
	#endif	/*TIM1_NVIC*/
	
	// Ê¹ÄÜ¼ÆÊıÆ÷
	TIM_Cmd(TIM1, ENABLE);	
	// Ö÷Êä³öÊ¹ÄÜ£¬µ±Ê¹ÓÃµÄÊÇÍ¨ÓÃ¶¨Ê±Æ÷Ê±£¬Õâ¾ä²»ĞèÒª
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


#if TIM1_NVIC
//¶¨Ê±Æ÷1ÖĞ¶Ï·şÎñ³ÌĞò
void TIM1_UP_IRQHandler(void)   //TIM1ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //¼ì²éTIM1¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif	/*TIM1_NVIC*/
#endif	/*TIM1_Int*/



#if	TIM2_Int
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	#if TIM2_OCInitStructure
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	#endif
	#if TIM2_NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM2³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	#if TIM2_CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM2_CH2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM2_CH3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM2_CH4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	
	#if TIM2_NVIC
	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM2ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï
	#endif
	
	TIM_Cmd(TIM2, ENABLE);  //Ê¹ÄÜTIMx					 
}

#if TIM2_NVIC
//¶¨Ê±Æ÷2ÖĞ¶Ï·şÎñ³ÌĞò
void TIM2_IRQHandler(void)   //TIM2ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //¼ì²éTIM2¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif
#endif	/*TIM2_Int*/


#if	TIM3_Int
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	#if TIM3_OCInitStructure
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	#endif
	#if TIM3_NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM3³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	#if TIM3_CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM3_CH2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM3_CH3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM3_CH4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM3_NVIC
	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM3ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï
	#endif
	
	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIMx					 
}

#if TIM3_NVIC
//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
void TIM3_IRQHandler(void)   //TIM3ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //¼ì²éTIM3¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif
#endif	/*TIM3_Int*/


#if	TIM4_Int
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	#if TIM4_OCInitStructure
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	#endif
	#if TIM4_NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM4³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	#if TIM4_CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	
	
	#if TIM4_NVIC
	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM4ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï
	#endif
	
	TIM_Cmd(TIM4, ENABLE);  //Ê¹ÄÜTIMx					 
}

#if TIM4_NVIC
//¶¨Ê±Æ÷4ÖĞ¶Ï·şÎñ³ÌĞò
void TIM4_IRQHandler(void)   //TIM4ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //¼ì²éTIM4¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif
#endif	/*TIM4_Int*/


#if	TIM5_Int
void TIM5_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	#if TIM5_OCInitStructure
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	#endif
	#if TIM5_NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	#endif

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM4³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	#if TIM5_CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	#if TIM4_CH4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	#endif
	
	
	
	#if TIM5_NVIC
	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM4ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM4ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï
	#endif
	
	TIM_Cmd(TIM5, ENABLE);  //Ê¹ÄÜTIMx
}


//¶¨Ê±Æ÷5ÖĞ¶Ï·şÎñ³ÌĞò
void TIM5_IRQHandler(void)   //TIM5ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //¼ì²éTIM5¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif	/*TIM5_Int*/


#if	TIM6_Int
void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM6³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM6ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷

	TIM_Cmd(TIM6, ENABLE);  //Ê¹ÄÜTIMx					 
}


//¶¨Ê±Æ÷6ÖĞ¶Ï·şÎñ³ÌĞò
void TIM6_IRQHandler(void)   //TIM6ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //¼ì²éTIM6¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif	/*TIM6_Int*/


#if	TIM7_Int
void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM7³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM7ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM7ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷

	TIM_Cmd(TIM7, ENABLE);  //Ê¹ÄÜTIMx					 
}


//¶¨Ê±Æ÷7ÖĞ¶Ï·şÎñ³ÌĞò
void TIM7_IRQHandler(void)   //TIM7ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //¼ì²éTIM7¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif	/*TIM7_Int*/


#if	TIM8_Int
void TIM8_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //Ê±ÖÓÊ¹ÄÜ
	
	//¶¨Ê±Æ÷TIM8³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM8ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	//ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;  //TIM8ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷

	TIM_Cmd(TIM8, ENABLE);  //Ê¹ÄÜTIMx					 
}


//¶¨Ê±Æ÷1ÖĞ¶Ï·şÎñ³ÌĞò
void TIM8_UP_IRQHandler(void)   //TIM1ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)  //¼ì²éTIM8¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
		{
			TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //Çå³ıTIMx¸üĞÂÖĞ¶Ï±êÖ¾ 
			
		}
}
#endif	/*TIM1_Int*/


void PWM1_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM1, Compare);
}


/*
SG90 - 180
High Pulse Duration (ms)    Angle (°)
--------------------------  --------
0.5                         0
1.0                         45
1.5                         90
2.0                         135
2.5                         180

SG90 - 360
High Pulse Duration (ms)    Servo Direction and Speed
--------------------------  -------------------------
0.5 ~ 1.5                   Forward, speed decreasing
1.5                         Stop
1.5 ~ 2.5                   Reverse, speed increasing

*/

/*******************************************************************
 * @name       :void timer1_ch1_task(void *pvParameters)
 * @date       :2024-10-28
 * @function   :TIMER1_CH1ÈÎÎñº¯Êı
 * @parameters :*pvParameters:ÈÎÎñ²ÎÊı
 * @retvalue   :ÎŞ
********************************************************************/
void timer1_ch1_task(void *pvParameters)
{
    const uint16_t delay_ms = 500;         // Delay time in milliseconds
    const uint16_t compare_values[] = {5, 10, 15, 20, 25}; // Array of compare values
    const uint8_t compare_count = sizeof(compare_values) / sizeof(compare_values[0]);

    TIM1_Int_Init(199, 7199); // Initialize timer interrupt with given parameters

    while (1)
    {
        for (uint8_t i = 0; i < compare_count; i++)
        {
            PWM1_SetCompare1(compare_values[i]); // Set PWM compare value
            vTaskDelay(delay_ms);                 // Delay for a specified time
        }
    }
}
