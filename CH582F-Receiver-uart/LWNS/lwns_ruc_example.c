/********************************** (C) COPYRIGHT *******************************
 * File Name          : lwns_ruc_example.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2021/06/30
 * Description        : reliable unicast，可靠单播传输例子
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "lwns_ruc_example.h"
#include "stdbool.h"

//每个文件单独debug打印的开关，置0可以禁止本文件内部打印
#define DEBUG_PRINT_IN_THIS_FILE    0
#if DEBUG_PRINT_IN_THIS_FILE
  #define PRINTF(...)    PRINT(__VA_ARGS__)
#else
  #define PRINTF(...) \
    do                \
    {                 \
    } while(0)
#endif


static lwns_ruc_controller ruc; //声明可靠单播控制结构体

static uint8_t RX_DATA[10] = {0};
static uint8_t TX_DATA[8] = {  0xff,0xc0,
                                0x11,0x00,  // hall
                                0x11,0x11,  // tem
                                0x11,0x11  // hum
                                };

uint8_t hall_status = 0;
uint8_t hum_data[2] = {0};
uint8_t tem_data[2] = {0};

static uint8_t ruc_taskID;
uint16_t lwns_ruc_ProcessEvent(uint8_t task_id, uint16_t events);


static void recv_ruc(lwns_controller_ptr ptr,
                     const lwns_addr_t  *sender);
static void sent_ruc(lwns_controller_ptr ptr, const lwns_addr_t *to, uint8_t retransmissions);
static void timedout_ruc(lwns_controller_ptr ptr, const lwns_addr_t  *to);


/*********************************************************************
 * @fn      recv_ruc
 *
 * @brief   lwns ruc接收回调函数
 *
 * @param   ptr     -   本次接收到的数据所属的可靠单播控制结构体指针.
 * @param   sender  -   本次接收到的数据的发送者地址指针.
 *
 * @return  None.
 */
static void recv_ruc(lwns_controller_ptr ptr, const lwns_addr_t  *sender)
{
    //ruc中接收到发送给自己的数据后，才会调用该回调
    uint8_t len;
    len = lwns_buffer_datalen(); //获取当前缓冲区接收到的数据长度

    if (len == 8) {
        // hall
        lwns_buffer_save_data(RX_DATA); //接收数据到用户数据区域
        if (RX_DATA[0] == 0xff
            && RX_DATA[6] == 0xff
            && RX_DATA[1] == 0xc0
            && RX_DATA[7] == 0xc0)
        {
            hall_status = RX_DATA[4];
        }
    }
    else if (len == 10) {
        // temhum
        lwns_buffer_save_data(RX_DATA); //接收数据到用户数据区域
        if (RX_DATA[0] == 0xff
            && RX_DATA[8] == 0xff
            && RX_DATA[1] == 0xc0
            && RX_DATA[9] == 0xc0)
        {
            tem_data[0] = RX_DATA[4];
            tem_data[1] = RX_DATA[5];
            hum_data[0] = RX_DATA[6];
            hum_data[1] = RX_DATA[7];
        }
    }
    else {
        // pass
    }
    memset(RX_DATA,0,10);
}

/*********************************************************************
 * @fn      sent_ruc
 *
 * @brief   lwns ruc发送完成回调函数
 *
 * @param   ptr     -   本次发送完成的可靠单播控制结构体指针.
 *
 * @return  None.
 */
static void sent_ruc(lwns_controller_ptr ptr,
                     const lwns_addr_t *to, uint8_t retransmissions)
{
    //ruc中发送成功，并且收到目标节点的ack回复后，才会调用该回调
    PRINTF("ruc %d sent %d\r\n", get_lwns_object_port(ptr), retransmissions);
//    tmos_start_task(ruc_taskID, RUC_EXAMPLE_TX_PERIOD_EVT, MS1_TO_SYSTEM_TIME(1000)); //更新任务时间，发送并收到回复后，1秒钟后再发送
}

/*********************************************************************
 * @fn      timedout_ruc
 *
 * @brief   lwns ruc发送超时回调函数
 *
 * @param   ptr     -   本次发送完成的ruc控制结构体指针.
 *
 * @return  None.
 */
static void timedout_ruc(lwns_controller_ptr ptr, const lwns_addr_t  *to)
{
    PRINTF("ruc %d timedout\n", get_lwns_object_port(ptr));
//    tmos_start_task(ruc_taskID, RUC_EXAMPLE_TX_PERIOD_EVT, MS1_TO_SYSTEM_TIME(1000));
}

/**
 * lwns 可靠单播回调函数结构体，注册回调函数
 */
static const struct lwns_ruc_callbacks ruc_callbacks = {
    recv_ruc, sent_ruc, timedout_ruc}; //声明可靠单播回调结构体

/*********************************************************************
 * @fn      lwns_ruc_process_init
 *
 * @brief   lwns ruc例程初始化.
 *
 * @param   None.
 *
 * @return  None.
 */
void lwns_ruc_process_init(void)
{
    lwns_ruc_init(&ruc,
                  155,               //打开一个端口号为155的可靠单播
                  HTIMER_SECOND_NUM, //等待ack时间间隔，没收到就会重发
                  &ruc_callbacks);   //返回0代表打开失败。返回1打开成功。
    ruc_taskID = TMOS_ProcessEventRegister(lwns_ruc_ProcessEvent);
    tmos_start_task(ruc_taskID, RUC_EXAMPLE_TX_PERIOD_EVT, MS1_TO_SYSTEM_TIME(1000));
}

/*********************************************************************
 * @fn      lwns_ruc_ProcessEvent
 *
 * @brief   lwns ruc Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id - The TMOS assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed.
 */
uint16_t lwns_ruc_ProcessEvent(uint8_t task_id, uint16_t events)
{
    if(events & RUC_EXAMPLE_TX_PERIOD_EVT)
    {
        TX_DATA[2] = hall_status;

        TX_DATA[4] = tem_data[0];
        TX_DATA[5] = tem_data[1];

        TX_DATA[6] = hum_data[0];
        TX_DATA[7] = hum_data[1];

        UART1_SendString(TX_DATA, 8);

        tmos_start_task(ruc_taskID, RUC_EXAMPLE_TX_PERIOD_EVT, MS1_TO_SYSTEM_TIME(1000));
        return events ^ RUC_EXAMPLE_TX_PERIOD_EVT;
    }
    if(events & SYS_EVENT_MSG)
    {
        uint8_t *pMsg;

        if((pMsg = tmos_msg_receive(task_id)) != NULL)
        {
            // Release the TMOS message
            tmos_msg_deallocate(pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }
    return 0;
}
