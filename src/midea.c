#include "midea.h"

// functions implementation
void initialize_midea_tx_buffer(rmt_item32_t *buffer)
{
  memset(buffer, 0, sizeof(midea_tx_buffer_t));
  // set the start sequence
  memcpy(buffer, &MIDEA_START_SEQUENCE, sizeof(rmt_item32_t));
  // set the stop sequence
  memcpy(buffer + 49, &MIDEA_STOP_SEQUENCE, sizeof(rmt_item32_t));
}

void midea_byte2rmt(const uint8_t byte, rmt_item32_t *buffer)
{
  for (int j = 7; j >= 0; j--)
  {
    if ((byte >> j) & 1)
    {
      memcpy(buffer, &MIDEA_BIT_1, sizeof(rmt_item32_t));
    }
    else
    {
      memcpy(buffer, &MIDEA_BIT_0, sizeof(rmt_item32_t));
    }
    buffer++;
  }
}

void midea_encode(uint8_t *data, rmt_item32_t *buffer)
{
  uint8_t index = 1;
  // populate payload in the tx_buffer, always 3 bytes
  for (int i = 0; i < midea_payload_lenght; i++)
  {
    midea_byte2rmt(*data, &buffer[index]);
    midea_byte2rmt(~(*data), &buffer[index + 24]);
    data++;
    index += 8;
  }
}
