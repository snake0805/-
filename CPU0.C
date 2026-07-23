#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Ifx_Cfg_Ssw.h"
#include "Blinky_LED.h"  // 引入LED驱动头文件

IFX_ALIGN(4) IfxCpu_syncEvent cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* 关闭看门狗 */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* 多核同步等待 */
    IfxCpu_emitEvent(&cpuSyncEvent);
    IfxCpu_waitEvent(&cpuSyncEvent, 1);

    initAllLEDs();  // CPU0执行，点亮全部4颗LED

    while(1)
    {
        blinkLED();
    }
}