//
// Created by Leonardo Fuso on 27/05/18.
//

#include "SquareRoot.hpp"

SquareRoot::~SquareRoot() = default;

double
SquareRoot::calculate(const double t)
{
	double r = t / 2;
	int precision = 25;

	for (; precision > 1; precision -= 1)

		r = (r + t / r) / 2;

	return r;
}

double
SquareRoot::calculate(double *array)
{
	double sum = 0;
	unsigned long size = *(&array + 1) - array;
	for(int i = 0; i < size; i++)
		sum += calculate(array[i]);
}