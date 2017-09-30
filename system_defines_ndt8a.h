#ifndef SYSTEM_DEFINES_NDT8_A_H
#define SYSTEM_DEFINES_NDT8_A_H

///////////配置定义

///////////////////////////////////////////////////////////
#define NDT8a_MOTION_MAX               ( 8 )
#define NDT8a_SMART_MAX                ( 9 )
/*20160616 由于TI3358控制板键码扫描时有差异，因此额外增加2个物理键码在原来的系统中*/
/*20160616 在不影响原来系统，不增加系统复杂度的情况下,增加2组物理键码到逻辑键码的转换.*/
#define NDT8a_KEY_FILM                ( 13 )  /*物理按键数量，薄膜按键*/
#define NDT8a_KEY_SCREEN              ( 8 )  /*液晶屏幕按键数量*/
#define NDT8a_MOTOR_FID               ( 0 )
#define NDT8a_MOTOR_X1                ( 1 )
#define NDT8a_MOTOR_Y1                ( 2 )
#define NDT8a_MOTOR_X2                ( 3 )
#define NDT8a_MOTOR_Y2                ( 4 )



#endif // SYSTEM_DEFINES_NDT8_A_H
