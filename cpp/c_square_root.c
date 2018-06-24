//
// Created by Leonardo Fuso on 24/06/18.
//

#include "c_square_root.h"

double
calculate(double* array){

	/* The type of the C++ object */
	SquareRoot_type object = NULL;

	double result = 0.0;

	/* invoking 'new ClassType' */
	object = _init_();

	if(!object)
	{
		return 0.0;
	}

	/* operation on the object */
	result = _array_calculate_(object, array);

	/* cleaning up memory */
	_destroy_(object);

	return result;
}

double
calculate_single(double number){

	/* The type of the C++ object */
	SquareRoot_type object = NULL;

	double result = 0.0;

	/* invoking 'new ClassType' */
	object = _init_();

	if(!object)
	{
		return 0.0;
	}

	/* operation on the object */
	result = _calculate_(object, number);

	/* cleaning up memory */
	_destroy_(object);

	return result;
}