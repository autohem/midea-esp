#ifndef __MIDEA_IR__
#define __MIDEA_IR__

#include <stdint.h>
#include <string.h>

// esp32 rmt_item32_t mock
typedef struct {
  uint16_t period0 : 15;
  uint16_t level0 : 1;
  uint16_t period1 : 15;
  uint16_t level1 : 1;
} rmt_item32_t;


// values definitions
#define MIDEA_TX_BUFFER_SIZE 50
#define MIDEA_PAYLOAD_LENGTH 3
#define MIDEA_CARRIER_FREQUENCY 38000
#define MIDEA_T_PERIOD_US 505

const rmt_item32_t MIDEA_BIT_0 = {MIDEA_T_PERIOD_US, 0, MIDEA_T_PERIOD_US, 1};
const rmt_item32_t MIDEA_BIT_1 = {MIDEA_T_PERIOD_US, 0, 3 * MIDEA_T_PERIOD_US,
                                  1};

const rmt_item32_t MIDEA_START_SEQUENCE = {8 * MIDEA_T_PERIOD_US, 0,
                                           8 * MIDEA_T_PERIOD_US, 1};

const rmt_item32_t MIDEA_STOP_SEQUENCE = {1 * MIDEA_T_PERIOD_US, 0,
                                          10 * MIDEA_T_PERIOD_US, 1};

typedef rmt_item32_t midea_tx_buffer_t[MIDEA_TX_BUFFER_SIZE];


// types definitions
typedef enum {
  T17C = 0b0000,
  T18C = 0b0001,
  T19C = 0b0011,
  T20C = 0b0010,
  T21C = 0b0110,
  T22C = 0b0111,
  T23C = 0b0101,
  T24C = 0b0100,
  T25C = 0b1100,
  T26C = 0b1101,
  T27C = 0b1001,
  T28C = 0b1000,
  T29C = 0b1010,
  T30C = 0b1011,
  T_OFF = 0b1110
} MideaTemperature;

typedef enum {
  FAN_AUTO = 0b1011,
  FAN_LOW = 0b1001,
  FAN_MED = 0b0101,
  FAN_HIGH = 0b0011,
  FAN_OFF = 0b0001
} MideaFan;

typedef enum { STATE_ON = 0b1111, STATE_OFF = 0b1011 } MideaState;

typedef enum {
  COMMAND_COOL = 0b0000,
  COMMAND_HEAT = 0b1100,
  COMMAND_AUTO = 0b1000,
  COMMAND_FAN = 0b0100
} MideaCommand;

typedef struct {
  uint8_t protocol_id;
  uint8_t state : 4;
  uint8_t fan : 4;
  uint8_t command : 4;
  uint8_t temperature : 4;
} MideaFrameData;

typedef union {
  MideaFrameData data;
  uint8_t raw[sizeof(MideaFrameData)];
} MideaFrame;


// functions declarations
void initialize_midea_tx_buffer(midea_tx_buffer_t *buffer);
void midea_byte2rmt(const uint8_t byte, rmt_item32_t *buffer);
void midea_encode(const uint8_t *data, midea_tx_buffer_t *buffer);


#endif