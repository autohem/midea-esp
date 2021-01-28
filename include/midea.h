#ifndef __MIDEA_IR__
#define __MIDEA_IR__

#include <stdint.h>
#include <string.h>
#include "soc/rmt_struct.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

  typedef enum
  {
    midea_tx_buffer_size = 50,
    midea_payload_lenght = 3,
    midea_carrier_frequency = 38000,
    midea_t_period_us = 553
  } MideaSettings;
  // values definitions

  static const rmt_item32_t MIDEA_BIT_0 = {{{midea_t_period_us, 1, midea_t_period_us, 0}}};
  static const rmt_item32_t MIDEA_BIT_1 = {{{midea_t_period_us, 1, 3 * midea_t_period_us, 0}}};

  static const rmt_item32_t MIDEA_START_SEQUENCE = {{{8 * midea_t_period_us, 1, 8 * midea_t_period_us, 0}}};

  //static const rmt_item32_t MIDEA_STOP_SEQUENCE = {{{1 * midea_t_period_us, 0, 10 * midea_t_period_us, 1}}};
  static const rmt_item32_t MIDEA_STOP_SEQUENCE = {{{ midea_t_period_us, 1, 10 * midea_t_period_us, 0}}};

  typedef rmt_item32_t midea_tx_buffer_t[midea_tx_buffer_size];
 
  // types definitions
  typedef enum
  {
    T17C = 0x0,
    T18C = 0x1,
    T19C = 0x3,
    T20C = 0x2,
    T21C = 0x6,
    T22C = 0x7,
    T23C = 0x5,
    T24C = 0x4,
    T25C = 0xC,
    T26C = 0xD,
    T27C = 0x9,
    T28C = 0x8,
    T29C = 0xA,
    T30C = 0xB,
    T_OFF = 0xE
  } MideaTemperature;

  typedef enum
  {
    FAN_AUTO  = 0xB,
    FAN_LOW   = 0x9,
    FAN_MED   = 0x5,
    FAN_HIGH  = 0x3,
    FAN_OFF   = 0x1,
  } MideaFan;

  typedef enum
  {
    STATE_ON = 0xF,
    STATE_OFF = 0xB
  } MideaState;

  typedef enum
  {
    MODE_COOL = 0x0,
    MODE_HEAT = 0xC,
    MODE_AUTO = 0x8,
    MODE_DRY  = 0xD,
    MODE_FAN  = 0x4,
    MODE_VENTILATE = 0xF
  } MideaMode;

  typedef struct
  {
    uint8_t protocol_id;
    uint8_t state : 4;
    uint8_t fan : 4;
    uint8_t mode : 4;
    uint8_t temperature : 4;
  } MideaFrameData;

  typedef union
  {
    MideaFrameData data;
    uint8_t raw[sizeof(MideaFrameData)];
  } MideaFrame;

  // functions declarations
  void initialize_midea_tx_buffer(rmt_item32_t *buffer);
  void midea_byte2rmt(const uint8_t byte, rmt_item32_t **buffer);
  void midea_encode(uint8_t *data, rmt_item32_t *buffer);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif