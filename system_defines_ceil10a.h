#ifndef SYSTEM_DEFINES_CEIL10_A_H
#define SYSTEM_DEFINES_CEIL10_A_H

///////////配置定义

///////////////////////////////////////////////////////////
#define CEIL10a_MOTION_MAX               ( 8 )
#define CEIL10a_SMART_MAX                ( 9 )
/*20160616 由于TI3358控制板键码扫描时有差异，因此额外增加2个物理键码在原来的系统中*/
/*20160616 在不影响原来系统，不增加系统复杂度的情况下,增加2组物理键码到逻辑键码的转换.*/
//#define CEIL10_A_KEY_FILM               ( 11 )  /*物理按键数量，薄膜按键*/
#define CEIL10_A_KEY_FILM               ( 13 )  /*物理按键数量，薄膜按键*/
#define CEIL10_A_KEY_SCREEN             ( 8 )  /*液晶屏幕按键数量*/
#define CEIL10a_MOTOR_FID                ( 0 )
#define CEIL10a_MOTOR_SID                ( 1 )
#define CEIL10a_MOTOR_ANG                ( 2 )
#define CEIL10a_MOTOR_DTH                ( 3 )
#define CEIL10a_MOTOR_DTA                ( 4 )
#define CEIL10a_MOTOR_CEP                ( 5 )
#define CEIL10a_MOTOR_BEH                ( 6 )
#define CEIL10a_MOTOR_DTP                ( 7 )


#endif // SYSTEM_DEFINES_CEIL10_A_H
