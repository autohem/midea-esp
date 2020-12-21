
#include <midea.h>



// functions implementation
void initialize_midea_tx_buffer(midea_tx_buffer_t *buffer) {
  // set the start sequence
  memcpy(buffer, &MIDEA_START_SEQUENCE, sizeof(rmt_item32_t));
  // set the stop sequence
  memcpy(buffer + 49, &MIDEA_STOP_SEQUENCE, sizeof(rmt_item32_t));
}

void midea_byte2rmt(const uint8_t byte, rmt_item32_t *buffer) {
  uint8_t i = 0;
  for (int j = 7; j >= 0; j--) {
    buffer[i++] = ((byte >> j) & 1) ? MIDEA_BIT_1 : MIDEA_BIT_0;
  }
}

void midea_encode(const uint8_t *data, midea_tx_buffer_t *buffer) {
  uint8_t index = 1;
  // populate payload in the tx_buffer, always 3 bytes
  for (int i = 0; i < MIDEA_PAYLOAD_LENGTH; i++) {
    midea_byte2rmt(data[i], buffer[index]);
    midea_byte2rmt(~data[i], buffer[index + 24]);
    index += 8;
  }
}

// #include <stdio.h>

// int test_midea_byte2rmt(void);
// int test_midea_union_endianess_swap(void);
// int test_midea_encode(void);

// int main() {

//   if (test_midea_byte2rmt() == 0) {
//     printf("test_midea_byte2rmt PASSED!\n");
//   } else {
//     printf("test_midea_byte2rmt FAILED!\n");
//   }

//   if (test_midea_union_endianess_swap() == 0) {
//     printf("test_midea_union_endianess_swap PASSED!\n");
//   } else {
//     printf("test_midea_union_endianess_swap FAILED!\n");
//   }

//   if (test_midea_encode() == 0) {
//     printf("test_midea_encode PASSED!\n");
//   } else {
//     printf("test_midea_encode FAILED!\n");
//   }
// }

// int test_midea_byte2rmt(void) { return -1; }
// int test_midea_union_endianess_swap(void) { return -1; }
// int test_midea_encode(void) { return -1; }