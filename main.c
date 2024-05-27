
#include <stdint.h>
#include <stdio.h>

int is_little_endian(){
  union {
    unsigned int i;
    unsigned char c[4];
  } test;
  
  test.i = 1;
  return test.i == test.c[0];
}

void swap_hex(unsigned char* a, int size){
  for(int first = 0, last = size-1; first < last; first++, last--){
    a[last] = a[first] ^ a[last];
    a[first] = a[first] ^ a[last];
    a[last] = a[first] ^ a[last];
  }
}

int main(){

  if(is_little_endian()){
    printf("Little endian\n");
  }
  
  unsigned int x = 0x89ABCDEF;
  unsigned int y = 0x76543210;

  unsigned int part1 = x & 0x000000FF;
  unsigned int part2 = y & 0xFFFFFF00;
  unsigned int result = part1 | part2;

  printf("0x");

  unsigned char* ptr_result = (unsigned char *) &result;
  
  if(is_little_endian()){
    swap_hex(ptr_result, sizeof(uint32_t));
  }

  for(int i = 0 ; i < 4; i++){
    printf("%.2x", ptr_result[i]);
  }
  printf("\n");

  /*
  *
    *       Result = 0x765432EF
    *       
    *       Part 1 - Keep the lest signifcant byte of x.
    *         0x89ABCDEF
    *       & 0xFF
    *       --------------
    *       10001001 10101011 11001101 11101111
    *       00000000 00000000 00000000 11111111
    *       -----------------------------------
    *       00000000 00000000 00000000 11101111 = 0xEF
    *
    *       Part 2 - Keep the most signficant 3 bytes of y.
    *
    *       0x76543210
    *     & 0xFFFFFF00
    *
    *     01110110  01010100  00110010 00010000
    *     11111111  11111111  11111111 00000000
    *     --------------------------------------
    *     01110110  01010100  00110010 00000000 = 0x76543200
    *
    *     Part 3 - Join the 1st one with the 2nd one.
    *    
    *        00000000 00000000 00000000 11101111 
    *     OR 01110110  01010100  00110010 00000000  
    *     -----------------------------------------
    *        0111 0110 0101 0100 0011 0010 1110 1111 = 0x765432EF
    */

}
