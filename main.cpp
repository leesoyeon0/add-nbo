#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t my_ntohl(uint32_t n){
        uint32_t n1 = (n & 0xFF000000) >> 24;
        uint32_t n2 = (n & 0x00FF0000) >> 8;
        uint32_t n3 = (n & 0x0000fFF0) << 8;
        uint32_t n4 = (n & 0x000000FF) << 24;
        return n1 | n2 | n3 | n4;
}

int main(int argc, char **argv){
  FILE* fp1 = NULL;
  FILE* fp2 = NULL;

  fp1 = fopen(argv[1], "rb");
  fp2 = fopen(argv[2], "rb");

  uint8_t buffer[4] = {0, };
  fread(buffer, sizeof(uint32_t), 4, fp1);
  uint32_t* p = reinterpret_cast<uint32_t*>(buffer);
  uint32_t n = my_ntohl(*p);

  uint8_t buffer2[4] = {0, };
  fread(buffer2, sizeof(uint32_t), 4, fp2);
  uint32_t* p2 = reinterpret_cast<uint32_t*>(buffer2);
  uint32_t n2 = my_ntohl(*p2);

  uint32_t n3 = n+n2;

  printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",n,n,n2,n2,n3,n3);

  fclose(fp1);
  fclose(fp2);
}
