#include "IfxPort.h"
#include "Blinky_LED.h"

/* 4颗板载LED引脚定义：硬件低电平点亮 */
#define LED_D107    &MODULE_P13,0
#define LED_D108    &MODULE_P13,1
#define LED_D109    &MODULE_P13,2
#define LED_D110    &MODULE_P13,3

/* 软件延时函数，替代BSP延时，无额外依赖 */
static void softwareDelay(uint32 cnt)
{
    volatile uint32 i;
    for(i = 0; i < cnt; i++);
}

/* 初始化4颗LED */
void initAllLEDs(void)
{
    // 配置4个引脚为推挽输出模式
    IfxPort_setPinModeOutput(LED_D107, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED_D108, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED_D109, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED_D110, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    // 默认熄灭（高电平熄灭）
    IfxPort_setPinHigh(LED_D107);
    IfxPort_setPinHigh(LED_D108);
    IfxPort_setPinHigh(LED_D109);
    IfxPort_setPinHigh(LED_D110);
}

/* 四灯同步闪烁 */
void blinkLED(void)
{
    // 翻转所有LED电平
    IfxPort_togglePin(LED_D107);
    IfxPort_togglePin(LED_D108);
    IfxPort_togglePin(LED_D109);
    IfxPort_togglePin(LED_D110);

    // 软件延时，数值越大闪烁越慢，可自行调整
    softwareDelay(50000);
}
