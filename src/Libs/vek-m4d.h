#include <stdio.h>
#include <string.h>
#include "cpat.h"

//TELEGRAM FRAME
#define DLE                             0x10    //Short telefram Start
#define STX                             0x02    //Long telegram Start
#define EOT                             0x04    //Stop byte
#define ACK                             0x06    //Confirmation character

//ADDRESS BYTE
#define ADDR_NOS                        0x00    //No station address
#define ADDR_ALL                        0xFF    //All station address

//CONTROL BYTES SETUP
#define DETECTOR_RESET                  0x01
#define FACTORY_STTINGS                 0x02
#define CONUTER_RESET                   0x03
#define HANDSHAKE                       0x0A

//CONTROL BYTES REQUESTS
#define REQ_SENSOR_PARAMETER            0x11
#define REQ_RS485_PARAMETR              0x12
#define REQ_I_O_MATRIX                  0x31
#define REQ_DATA                        0x51
#define REQ_TIMER_MS                    0x5A
#define REQ_TIMER_S                     0x5B
#define REQ_TIMER_M                     0x5C
#define REQ_COUNTER                     0x71

//CONTROL BYTES SETTINGS
#define SET_SENSOR_PARAMETER            0x21
#define SET_RS485_PARAMETER             0x22
#define SET_I_O_MATRIX                  0x41
#define SET_DATA                        0x61

//ERROR MESSAGES
#define ERR_BLK1_OUT_OF_BOUNDS          0xF1
#define ERR_BLK2_OUT_OF_BOUNDS          0xF2
#define ERR_BLK3_OUT_OF_BOUNDS          0xF3
#define ERR_BLK4_OUT_OF_BOUNDS          0xF4
#define ERR_BLK5_OUT_OF_BOUNDS          0xF5
#define ERR_BLK6_OUT_OF_BOUNDS          0xF6
#define ERR_BLK7_OUT_OF_BOUNDS          0xF7
#define ERR_BLK8_OUT_OF_BOUNDS          0xF8
#define ERR_PARAM_OUT_OF_BOUNDS         0xFA
#define ERR_REQUEST_MASK                0xFD
#define ERR_PROTOCOL_LENGH              0xFE
#define ERR_UNKNOWN_REQUEST             0xFF

//SENSOR PARAMETER (0x11)
#define MASK_MUX_MODE                   0b00000001
#define MASK_FREQ_RANGE                 0b00000010
#define MASK_SENSITIVITY                0b00000100
#define MASK_HOLD_TIME                  0b00001000
#define MASK_OUTPUT_MODE                0b00010000
#define MASK_DIRECTION_LOGIC            0b00100000
#define MASK_OUTPUT_TIMING              0b01000000

//RS485 PARAMETER (0x12)
#define MASK_INTERFACE                  0b00000001
#define MASK_ADDRESS                    0b00000010
#define MASK_PROTOCOL                   0b00000100

//IO MATRIX PARAMETER (0x31)
#define MASK_PRESENCE                   0b00000001
#define MASK_DIRECTION                  0b00000010
#define MASK_CLASSIFICATION             0b00000100

//DATA PARAMETER (0x51)
#define MASK_FREQUENCY                  0b00000001
#define MASK_AMPLITUDE                  0b00000010
#define MASK_LOOP_STATUS                0b00000100
#define MASK_BUSY_TIME                  0b00001000
#define MASK_MAX_AMPLITUDE              0b00010000
#define MASK_DEVICE_INFO                0b00100000
#define MASK_HW_SIGNAL                  0b01000000

//TIMER PARAMETER (0x5A)
#define MASK_TIMER_LOOP                 0b00000001
#define MASK_TIMER_TIME_BASE            0b00000010
#define MASK_TIMER_START_TIME           0b00000100
#define MASK_TIMER_STOP_TIME            0b00001000
#define MASK_TIMER_BUSY_TIME            0b00010000
#define MASK_TIMER_GAP_TIME             0b00100000

int vekRequest(int address, int control, int data);
int shortTelegram(int address, int control);
