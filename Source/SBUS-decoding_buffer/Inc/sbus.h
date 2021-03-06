/**********************************************************************
 *     sbus.h                                                         *
 *     written by Soomin Lee (MagmaTart)                              *
 *     Last modify date : 2017.11.20                                  *
 *     Description : Structures and Functions to use SBUS protocol.   *
 **********************************************************************/

#ifndef __SBUS_H__
#define __SBUS_H__

#include "stm32f4xx_hal.h"

#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__)/sizeof(*(__BUFFER__)))
#define BUFFERSIZE(buffer) (COUNTOF(buffer))

#define SBUS_DATA_SIZE 25
#define UART_DATA_SIZE 25
#define DMA_RECEIVE_SIZE 1024
#define STACKING_SIZE 250
#define ROW_SIZE 128
#define START_BYTE 0x0f
#define END_BYTE 0x04



typedef struct _SBUS_PWM
{
  float pwm;
  float min_pwm;
  float max_pwm;
  float min_duty;
  float max_duty; 
}SBUS_pwm;

typedef struct _SBUS
{
  uint8_t         dma_receive_buff[DMA_RECEIVE_SIZE];
  uint8_t         packet_buff[SBUS_DATA_SIZE];

  uint16_t        data_buff[18];
  
  uint16_t        prev_ndt;
  uint16_t        curr_ndt;
  uint16_t        received_size;
  
  uint16_t        front;
  uint16_t        rear;
  
  uint8_t         new_packet_flag;
  uint8_t         packet_ok_flag;
  
  uint16_t new_data_start_idx;
  uint16_t next_data_start_idx;                         //현재 새롭게 들어온 데이터의 인덱스, 다음 루틴에 들어올 데이터의 인덱스  
  uint16_t packet_start_idx;
  uint16_t packet_end_idx;        //온전한 패킷의 시작 인덱스, 끝 인덱스
  uint16_t check_idx;  
  uint16_t count;
}SBUS;

void SystemClock_Config(void);

void read_sbus();

void init_sbus_pwm();

void init_sbus();

void test();

// make next decodeable buffer : Returns 1 when it able to decode.
void update_buffer();

void make_next_decodeable_buffer();
  
// decode sbus data
void decode_sbus_data();

// make pwm signal based on sbus data
void sbus_pwm_make_with_value(TIM_HandleTypeDef*);

extern SBUS sbus;
extern uint8_t dma_receive_buff[DMA_RECEIVE_SIZE];
extern uint8_t packet_buff[SBUS_DATA_SIZE];
#endif
