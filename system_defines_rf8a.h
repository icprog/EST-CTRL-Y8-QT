#ifndef SYSTEM_DEFINES_RF8_A_H
#define SYSTEM_DEFINES_RF8_A_H

///////////配置定义

///////////////////////////////////////////////////////////
#define RF8A_MOTION_MAX               ( 8 )
#define RF8A_SMART_MAX                ( 9 )
/*20160616 由于TI3358控制板键码扫描时有差异，因此额外增加2个物理键码在原来的系统中*/
/*20160616 在不影响原来系统，不增加系统复杂度的情况下,增加2组物理键码到逻辑键码的转换.*/
//#define RF8_A_KEY_FILM               ( 11 )  /*物理按键数量，薄膜按键*/
#define RF8_A_KEY_FILM               ( 13 )  /*物理按键数量，薄膜按键*/
#define RF8_A_KEY_SCREEN             ( 8 )  /*液晶屏幕按键数量*/
#define RF8A_MOTOR_FID                ( 0 )
#define RF8A_MOTOR_DTP                ( 1 )
#define RF8A_MOTOR_SID                ( 2 )
#define RF8A_MOTOR_ANG                ( 3 )
#define RF8A_MOTOR_PRL                ( 4 )
#define RF8A_MOTOR_PYP                ( 5 )
#define RF8A_MOTOR_SGH                ( 6 )
#define RF8A_MOTOR_SGV                ( 7 )



#endif // SYSTEM_DEFINES_RF8_A_H
