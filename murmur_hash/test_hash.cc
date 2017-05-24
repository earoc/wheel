#include "hash.h"
#include <assert.h>

using namespace zy;

int main()
{
  const unsigned char data1[1] = {0x62};
  const unsigned char data2[2] = {0xc3, 0x97};
  const unsigned char data3[3] = {0xe2, 0x99, 0xa5};
  const unsigned char data4[4] = {0xe1, 0x80, 0xb9, 0x32};
  const unsigned char data5[48] = {
    0x01, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00,
    0x00, 0x00, 0x00, 0x14,
    0x00, 0x00, 0x00, 0x18,
    0x28, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
  };

  assert(hash(0, 0, 0xbc9f1d34) == 0xbc9f1d34);
  assert(
      hash(reinterpret_cast<const char*>(data1), sizeof(data1), 0xbc9f1d34) ==
      0xef1345c4);
  assert(
      hash(reinterpret_cast<const char*>(data2), sizeof(data2), 0xbc9f1d34) ==
      0x5b663814);
  assert(
      hash(reinterpret_cast<const char*>(data3), sizeof(data3), 0xbc9f1d34) ==
      0x323c078f);
  assert(
      hash(reinterpret_cast<const char*>(data4), sizeof(data4), 0xbc9f1d34) ==
      0xed21633a);
  assert(
      hash(reinterpret_cast<const char*>(data5), sizeof(data5), 0x12345678) ==
      0xf333dabb);

  return 0;
}
