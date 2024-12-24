#ifndef common_h
#define common_h

#include <stdio.h>

typedef unsigned short ushort;

typedef struct Complex {
  double real;
  double imag;
} Complex;

Complex divide_complex (const Complex a, const Complex b){
  Complex result = {0, 0};
  const double denomirator = b.real * b.real + b.imag * b.imag;
  result.real = (a.real * b.real + a.imag * b.imag) / denomirator;
  result.imag = (a.imag * b.real - a.real * b.imag) / denomirator;
  return result;
}

void print_complex(const Complex a, const ushort precision){
  printf("%.*g %+.*e*i\n", precision, a.real, precision, a.imag);
}

void calculate_RLC (Complex *numerator, Complex *denominator, Complex *z, const double omega, const double R, const double L, const double C){
  numerator -> real = L / C;
  numerator -> imag = -R / (omega * C);
  denominator -> real = R;
  denominator -> imag = omega * L - 1.0 / (omega * C);
  *z = divide_complex(*numerator, *denominator);
}

void calculate_RCL (Complex *numerator, Complex *denominator, Complex *z, const double omega, const double R, const double L, const double C){
  numerator -> real = L / C;
  numerator -> imag = R / (omega * C);
  denominator -> real = R;
  denominator -> imag = omega * L - 1.0 / (omega * C);
  *z = divide_complex(*numerator, *denominator);
}

void calculate_R1R2СL (Complex *numerator, Complex *denominator, Complex *z, const double omega, const double R1, const double R2, const double L, const double C){
  numerator -> real = R1 * R2;
  numerator -> imag = R1 * (omega * L - 1.0 / (omega * C));
  denominator -> real = R1 + R2;
  denominator -> imag = omega * L - 1.0 / (omega * C);
  *z = divide_complex(*numerator, *denominator);
}

void calculate_R1R2LC (Complex *numerator, Complex *denominator, Complex *z, const double omega, const double R1, const double R2, const double L, const double C){
  numerator -> real = R1 * R2 + L / C;
  numerator -> imag = omega * L * R1 - R2 / (omega * C);
  denominator -> real = R1 + R2;
  denominator -> imag = omega * L - 1.0 / (omega * C);
  *z = divide_complex(*numerator, *denominator);
}

#endif common_h
