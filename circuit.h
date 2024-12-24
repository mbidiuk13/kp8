#ifndef circuit_h
#define circuit_h

#include <stdio.h>

void circuit_output () {
  printf("Available circuit types:\n");
  printf("1.\n");
  printf("  o---[R]---{L}---o\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  o-----|C|-------o\n\n");

  printf("2.\n");
  printf("  o---[R]---|C|---o\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  |               |\n");
  printf("  o-----{L}-------o\n\n");

  printf("3.\n");
  printf("  o---[R2]---|C|---o\n");
  printf("  |                |\n");
  printf(" [R1]              |\n");
  printf("  |                |\n");
  printf("  |                |\n");
  printf("  |                |\n");
  printf("  o-----{L}--------o\n\n");

  printf("4.\n");
  printf("  o---[R2]---------o\n");
  printf("  |                |\n");
  printf(" [R1]              |\n");
  printf("  |                |\n");
  printf(" |C|               |\n");
  printf("  |                |\n");
  printf("  o-----{L}--------o\n\n");
}
#endif
