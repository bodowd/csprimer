#include <stdio.h>
#define RED0 0x00
#define RED1 0x20
#define RED2 0x40
#define RED3 0x60
#define RED4 0x80
#define RED5 0xa0
#define RED6 0xc0
#define RED7 0xe0
#define GREEN0 0x00
#define GREEN1 0x04
#define GREEN2 0x08
#define GREEN3 0x0c
#define GREEN4 0x10
#define GREEN5 0x14
#define GREEN6 0x18
#define GREEN7 0x1c
#define BLUE0 0x00
#define BLUE1 0x01
#define BLUE2 0x02
#define BLUE3 0x03

unsigned char quantize(unsigned char red, unsigned char green,
                       unsigned char blue) {
  /*
    Example:
    Each color is given in 8 bits
    Red: 111-000-10
    Green: 111-001-01
    Blue:  111-011-11


    convert red and green to 3 bits and blue to 2 bits by keeping the highest
    order bits and then shifting them into their final places

    R & 0xe0 --> 111-000-10 & 111-000-00 --> 111-000-00

    (G & 0xe0) >> 3 --> 111-001-01 & 111-000-00 --> 111-000-00 >> 3
    --> 000-111-00

    (B >> 6) --> 111-011-11 >> 6 --> 000-000-11

    OR all to get the final out number:
    111-111-11



  */
  unsigned char out = (red & 0xe0) | ((green & 0xe0) >> 3) | (blue >> 6);

  // uncomment to see the numbers in binary and see how it works
  // printf("red: %b\n", red);
  // printf("green: %b\n", green);
  // printf("blue: %b\n", blue);
  // printf("out: %b\n\n", out);

  return out;
}

unsigned char quantize_prior(unsigned char red, unsigned char green,
                             unsigned char blue) {
  unsigned char out = 0;
  if (red < 0x20)
    out += RED0;
  else if (red < 0x40)
    out += RED1;
  else if (red < 0x60)
    out += RED2;
  else if (red < 0x80)
    out += RED3;
  else if (red < 0xa0)
    out += RED4;
  else if (red < 0xc0)
    out += RED5;
  else if (red < 0xe0)
    out += RED6;
  else
    out += RED7;

  if (green < 0x20)
    out += GREEN0;
  else if (green < 0x40)
    out += GREEN1;
  else if (green < 0x60)
    out += GREEN2;
  else if (green < 0x80)
    out += GREEN3;
  else if (green < 0xa0)
    out += GREEN4;
  else if (green < 0xc0)
    out += GREEN5;
  else if (green < 0xe0)
    out += GREEN6;
  else
    out += GREEN7;

  if (blue < 0x40)
    out += BLUE0;
  else if (blue < 0x80)
    out += BLUE1;
  else if (blue < 0xc0)
    out += BLUE2;
  else
    out += BLUE3;

  return out;
}

// unsigned char quantize(unsigned char red, unsigned char green,
//                        unsigned char blue) {
//   return (red & 0xe0) | ((green & 0xe0) >> 3) | (blue >> 6);
// }
