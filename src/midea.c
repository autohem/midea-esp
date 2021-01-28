#include "midea.h"

#define SET_MIDEA_HIGH(X) memcpy((*X)++, &MIDEA_BIT_1, sizeof(rmt_item32_t))
#define SET_MIDEA_LOW(X) memcpy((*X)++, &MIDEA_BIT_0, sizeof(rmt_item32_t))


// functions implementation
void initialize_midea_tx_buffer(rmt_item32_t *buffer)
{
  //clear the buffer
  memset(buffer, 0, sizeof(midea_tx_buffer_t));
  // set the start sequence
  memcpy(buffer, &MIDEA_START_SEQUENCE, sizeof(rmt_item32_t));
  // set the stop sequence
  memcpy((buffer + 49), &MIDEA_STOP_SEQUENCE, sizeof(rmt_item32_t));
}

void midea_byte2rmt(const uint8_t byte, rmt_item32_t **buffer)
{
  //for each bit checks if is 0 or 1
  for (int j = 7; j >= 0; j--)
  {
    ((byte >> j) & 1) ? SET_MIDEA_HIGH(buffer) : SET_MIDEA_LOW(buffer);
  }
}

void midea_encode(uint8_t *data, rmt_item32_t *buffer)
{
  // populate payload in the tx_buffer, always 3 bytes
  for (int i = 0; i < midea_payload_lenght; i++)
  {
    midea_byte2rmt((*data), &buffer);  // encode normal byte
    midea_byte2rmt(~(*data), &buffer); // encode the inverted byte
    data++;
  }
}
