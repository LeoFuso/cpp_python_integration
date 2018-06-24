//
// Created by Leonardo Fuso on 24/06/18.
//

#include "SquareRoot_C_Adapter.h"
#include "SquareRoot.hpp"

SquareRoot_type
_init_()
{
	return new SquareRoot;
}

void
_destroy_(SquareRoot_type untyped_ptr)
{
	SquareRoot *typed_ptr = static_cast<SquareRoot *>(untyped_ptr);
	delete typed_ptr;
}

double
_array_calculate_(SquareRoot_type untyped_self, double *array)
{
	SquareRoot *typed_ptr = static_cast<SquareRoot *>(untyped_self);
	return typed_ptr->calculate(array);
}

double
_calculate_(SquareRoot_type untyped_self, double value)
{
	SquareRoot *typed_ptr = static_cast<SquareRoot *>(untyped_self);
	return typed_ptr->calculate(value);
}