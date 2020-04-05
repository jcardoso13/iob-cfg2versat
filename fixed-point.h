#ifndef FIXEDPOINT_API
#define FIXEDPOINT_API


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int32_t fixed_t;

#define DEBUG 0
//MUST CHANGE THESE 3 VALUES FOR DIFFERENT Q FORMAT!
//Current Format Q8.24 
#define LEFT 8 // 127 max
#define RIGHT 24
#define POINT   ((int32_t)0x01000000) // VALUE 1.0
#define FIXED16 ((int32_t)0x00010000) // Value for 1.0 in Q16.16


#define EXP_ITERATIONS ((int8_t)10) // Number of iterations on EXP func. More = better precision

#define SHIFT_ORIENTATION TRUE // change to FALSE if RIGHT/2 > 16

//#define VARIANCE_CONST ((fixed_t).000001f*POINT)
#define VARIANCE_CONST ((fixed_t)0x10)





#define FIXED_E ((fixed_t)0x56fc2a00 >> (LEFT-3)) // 3.29 is the base for exp(1)
// don't know if compiler will correctly run this on IOB, if not, it must be computed manually and inserted here
#define MIN_INPUT_E  ((fixed_t)((1 << (LEFT)) << (RIGHT-1) ))
#define MAX_INPUT_E   ((fixed_t)0x04da1ea0)//((fixed_t)fixed_from_float(log(pow(2,LEFT-1))))
#define MAX_E ((fixed_t)((((1 << (LEFT-1)) << (RIGHT-1)) -0x1) & 0x7FFFFFFF) << 1)
#define FIXED_MIN 0x80000000
#define FIXED_OVERFLOW 0x80000000
//Q16.16 -> Q8.24 is what we must implement probably

#define RV32IM FALSE

fixed_t fixed_add(fixed_t a,fixed_t b);
fixed_t fixed_sub(fixed_t a, fixed_t b);
fixed_t fixed_mul(fixed_t a, fixed_t b);
fixed_t fixed_div(fixed_t a, fixed_t b);
fixed_t fixed_exp(fixed_t a);
fixed_t fixed_sqrt(fixed_t a);
int     fixed_floor(fixed_t a);
int     fixed_ceil(fixed_t a);
fixed_t fixed_div_for_ints(int32_t a, int32_t b);
fixed_t fixed16_mul(fixed_t a, fixed_t b);
fixed_t fixed16_div(fixed_t a,fixed_t b);



fixed_t fixed_logistic_activation(fixed_t x);
fixed_t fixed_image_scale(int c, fixed_t scale);
int floor_image_scale(int c, fixed_t scale);




static inline fixed_t fixed_from_int(int a) { return(fixed_t)(a*POINT);}
static inline fixed_t fixed_to_int(fixed_t a) {return(int)(a>>RIGHT);}

#if RV32IM == FALSE
static inline float   fixed_to_float(fixed_t a) { return (float)a /POINT; }
static inline fixed_t fixed_from_float(float a) { return (fixed_t)(a*POINT); }

#else 
#define MAX_E fixed_from_float(127.99)
#endif



#endif





