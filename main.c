#include <stdio.h>
#include <math.h>
#include <conio.h>
#include "validation.h"
#include "common.h"
#include "circuit.h"

#define FMIN 0.1
#define FMAX 1000.0

#define STEP_MIN 0.1
#define STEP_MAX 1000.0

#define RMIN 0.1
#define RMAX 1000.0

#define LMIN 0.1
#define LMAX 1000.0

#define CMIN 0.1
#define CMAX 1000.0

#define PRECISION_MIN 1
#define PRECISION_MAX 15

int main() {
    printf("This program calculates the complex resistance of a given oscillatory circuit depending on the current frequency\n");

    do {
        ushort circuit = 0;

        circuit_output();

        get_input(TYPE_USHORT, &circuit, "Choose the circuit type (from 1 to 4):\n", is_circuit_valid, 1, 4, "Error: Invalid circuit type. Choose a number between 1 and 4.");

        double R1 = 0, R2 = 0;
        switch (circuit) {
            case 1:
            case 2:
                get_input(TYPE_DOUBLE, &R1, "Enter R (Ohm):\n", is_positive_in_range, RMIN, RMAX, "Error: R must be between %.2lf and %.2lf.");
                break;
            case 3:
            case 4:
                get_input(TYPE_DOUBLE, &R1, "Enter R1 (Ohm):\n", is_positive_in_range, RMIN, RMAX, "Error: R1 must be between %.2lf and %.2lf.");
                get_input(TYPE_DOUBLE, &R2, "Enter R2 (Ohm):\n", is_positive_in_range, RMIN, RMAX, "Error: R2 must be between %.2lf and %.2lf.");
                break;
            default:
                printf("Error: Invalid circuit type.\n");
                break;
        }

        double L = 0;
        get_input(TYPE_DOUBLE, &L, "Enter L (mHn):\n", is_positive_in_range, LMIN, LMAX, "Error: L must be between %.2lf and %.2lf.");

        double C = 0;
        get_input(TYPE_DOUBLE, &C, "Enter C (mcF):\n", is_positive_in_range, CMIN, CMAX, "Error: C must be between %.2lf and %.2lf.");

        double Fmin = 0;
        do {
            get_input(TYPE_DOUBLE, &Fmin, "Enter Fmin:\n", is_positive_in_range, FMIN, FMAX, "Error: Fmin must be between %.2lf and %.2lf");
            if (Fmin < FMIN || Fmin > FMAX) {
                printf("Error: Fmin must be between %.2lf and %.2lf\n", FMIN, FMAX);
            }
        } while (Fmin < FMIN || Fmin > FMAX);

        double Fmax = 0;
        do {
            get_input(TYPE_DOUBLE, &Fmax, "Enter Fmax:\n", is_positive_in_range, FMIN, FMAX, "Error: Fmax must be between %.2lf and %.2lf");
            if (Fmax < FMIN || Fmax > FMAX) {
                printf("Error: Fmax must be between %.2lf and %.2lf\n", FMIN, FMAX);
            }
            if (Fmin > Fmax) {
                printf("Error: Fmax must be greater than Fmin.\n");
            }
        } while (Fmax < FMIN || Fmax > FMAX || Fmin > Fmax);

        double step = 0;
        do {
            get_input(TYPE_DOUBLE, &step, "Enter step:\n", is_positive_in_range, STEP_MIN, STEP_MAX, "Error: Step must be between %.2lf and %.2lf");
            if (step < STEP_MIN || step > STEP_MAX) {
                printf("Error: Step must be in the range %.2lf to %.2lf\n", STEP_MIN, STEP_MAX);
            }
        } while (step < STEP_MIN || step > STEP_MAX);

        int precision = 0;
        printf("Enter the number of decimal places (from %d to %d): ", PRECISION_MIN, PRECISION_MAX);
        if (scanf("%d", &precision) != 1 || precision < PRECISION_MIN || precision > PRECISION_MAX) {
            fflush(stdin);
            printf("Invalid input. Please enter a valid integer between %d and %d.\n", PRECISION_MIN, PRECISION_MAX);
        }

        Complex numerator = {0, 0}, denomirator = {0, 0}, z = {0, 0};

        const double res_freq = 1.0 / (2.0 * M_PI * sqrt(L * C));
        printf("Resonant frequency: %.*lf\n", precision, res_freq);

        double F = Fmin;
        int i = 0;
        do {
            const double omega = 2.0 * M_PI * F;
            switch (circuit) {
                case 1:
                    calculate_RLC(&numerator, &denomirator, &z, omega, R1, L, C);
                    break;
                case 2:
                    calculate_RCL(&numerator, &denomirator, &z, omega, R1, L, C);
                    break;
                case 3:
                    calculate_R1R2СL(&numerator, &denomirator, &z, omega, R1, R2, L, C);
                    break;
                case 4:
                    calculate_R1R2LC(&numerator, &denomirator, &z, omega, R1, R2, L, C);
                    break;
                default:
                    printf("Error: Invalid circuit type\n");
                    break;
            }
            printf("F%d = %.*lf\t", i + 1, precision, F);
            printf("Z%d = ", i + 1);
            print_complex(z, precision);
            F += step;
            i++;
        } while (F <= Fmax);

        printf("\nPress '0' to exit or another key to continue.\n");
    } while (getchar() != '0');

    return 0;
}
