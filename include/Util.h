//
// Created by shoham on 6/17/22.
//
#include <cmath>
#include <iostream>

template <typename T> void assertEquals(T expected, T actual, const std::string& message);
#ifndef RAYTRACER_UTIL_H
#define RAYTRACER_UTIL_H


class Util {
    // It is binary, equivalent to ~1/1,000,000,000,000 in decimal (12 digits)
    static const int ACCURACY = -40;

    // double store format (bit level):
    //    seee eeee eeee (1.)mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
    // 1 bit sign, 11 bits exponent, 53 bits (52 stored) normalized mantissa
    // the number is m+2^e where 1<=m<2
    // NB: exponent is stored "normalized" (i.e. always positive by adding 1023)

    static int getExp(double num) {
        // 1. doubleToRawLongBits: "convert" the stored number to set of bits
        // 2. Shift all 52 bits to the right (removing mantissa)
        // 3. Zero the sign of number bit by mask 0x7FF
        // 4. "De-normalize" the exponent by subtracting 1023
        int *exp;
        frexp(num, exp);
        return *exp;
    }

    /**
     * Checks whether the number is [almost] zero
     *
     * @param number the number to check
     * @return true if the number is zero or almost zero, false otherwise
     */
public:

    static bool isZero(double number) {
        return getExp(number) < ACCURACY;
    }

    /**
     * Aligns the number to zero if it is almost zero
     *
     * @param number the number to align
     * @return 0.0 if the number is very close to zero, the number itself otherwise
     */
    static double alignZero(double number) {
        return getExp(number) < ACCURACY ? 0.0 : number;
    }

    static double pow(double base, int exponent){
        double a = base;
        for (int i = 0; i < exponent-1; ++i) {
            a*=base;
        }
        return a;
    }
};


#endif //RAYTRACER_UTIL_H
