//
// Created by Leonardo Fuso on 24/06/18.
//

#ifndef SquareRoot_C_Adapter
#define SquareRoot_C_Adapter

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

typedef void *SquareRoot_type;

EXTERN_C SquareRoot_type
_init_();

EXTERN_C void
_destroy_(SquareRoot_type SquareRoot);

EXTERN_C double
_array_calculate_(SquareRoot_type self, double *, unsigned int);

EXTERN_C double
_calculate_(SquareRoot_type self, double);

#undef EXTERN_C
#endif //SquareRoot_C_Adapter
