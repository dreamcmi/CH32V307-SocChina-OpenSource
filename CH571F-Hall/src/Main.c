#include "CONFIG.h"
#include "CH57x_common.h"
#include "HAL.h"
#include "stdlib.h"
#include "lwns_adapter_blemesh_mac.h"
#include "lwns_ruc_example.h"

//每个文件单独debug打印的开关，置0可以禁止本文件内部打印
#define DEBUG_PRINT_IN_THIS_FILE    1
#if DEBUG_PRINT_IN_THIS_FILE
  #define PRINTF(...)    PRINT(__VA_ARGS__)
#else
  #define PRINTF(...) \
    do                \
    {                 \
    } while(0)
#endif

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
u8C MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   tmos主循环.
 *
 * @param   None.
 *
 * @return  None.
 */
__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数.
 *
 * @param   None.
 *
 * @return  None.
 */
int main(void)
{
#if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
    PWR_DCDCCfg(ENABLE);
#endif
    SetSysClock(CLK_SOURCE_PLL_60MHz);
#if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
    GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
#endif
#ifdef DEBUG
    GPIOA_SetBits(bTXD1);
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
    UART1_DefInit();
#endif
    GPIOA_ModeCfg( GPIO_Pin_4, GPIO_ModeIN_PU );
    PRINTF("start.\n");
    {
        PRINTF("%s\n", VER_LIB);
    }
    CH57X_BLEInit();
    HAL_Init();
    RF_RoleInit();
    RF_Init();
    lwns_init(); //初始lwns协议栈
    lwns_ruc_process_init();//可靠单播例子初始化
    Main_Circulation();
}
/******************************** endfile @ main ******************************/
