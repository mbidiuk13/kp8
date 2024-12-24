#ifndef validation_h
#define validation_h

#include <stdio.h>
#include <stdbool.h>

typedef unsigned short ushort;

typedef enum {
  TYPE_USHORT,
  TYPE_DOUBLE
} DataType;

bool is_circuit_valid (void* value) {
  const ushort *temp = (ushort *)value;
  return *temp >= 1 && *temp <= 4;
}

bool is_positive (void *value) {
  const double *temp = (double *)value;
  return *temp > 0;
}

bool is_positive_in_range(void *value, double min, double max) {
  const double *temp = (double *)value;
  return *temp >= min && *temp <= max;
}

void get_input(const DataType type, void *variable, const char *print_msg, bool (*condition)(void*, double, double), double min, double max, const char *error_msg) {
  const char *format = NULL;
  switch (type) {
    case TYPE_USHORT:
      format = "%hu";
    break;
    case TYPE_DOUBLE:
      format = "%lf";
    break;
    default:
      printf("Error: unsupported data type\n");
    return;
  }

  do {
    printf(print_msg);
    if (scanf(format, variable) != 1) {
      printf("%s, Error: wrong input\n", error_msg);
    } else if (!condition(variable, min, max)) {
      printf("%s\n", error_msg);
    }
    fflush(stdin);
  } while (!condition(variable, min, max));
}

#endif // validation_h
