#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

/*
    Macros for replicating other templated macros for particular bit-widths.
    These macros accept a single macro as an argument and that argument must
    accept a single argument which will be the bit-width.

    Example:
        #define IM_A_TEMPLATE(N)            \
            int func##N(uint##N##_t arg) {  \
                assert(N > 0);              \
                return arg == N;             \
            }
        TEMPLATE_STD(IM_A_TEMPLATE)

    Example:
        bool func(int n) {
            switch (n) {
                #define FUNC_CASE_TEMPLATE(N)  \
                    case N:                    \
                        return calc##N(n);
                TEMPLATE_STD(FUNC_CASE_TEMPLATE)
                default:
                    return false;
            }
        }
*/

#define TEMPLATE_STD(T)   T(8) T(16) T(32) T(64) T(128)
#define TEMPLATE_SQR(T)   T(4) T(16) T(64)

#endif // _TEMPLATE_H_
