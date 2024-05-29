#include <stdint.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b){
  
  /*
  *   This should return an unsigned value where byte i from variable
  *   x is replaced with char b.
  */
  
  unsigned char * ptr_value = (unsigned char*) &x;
  ptr_value[i] = b;

  return x; 
}

int main(){

  unsigned x = replace_byte(0x12345678, 2, 0xAB);
  printf("0x%08x", x);

  return 0;
}
