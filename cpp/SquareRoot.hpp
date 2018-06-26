//
// Created by Leonardo Fuso on 27/05/18.
//

#ifndef SQUAREROOT_HPP
#define SQUAREROOT_HPP

#include <type_traits>
#include <cstddef>

class SquareRoot
{
public:
	~SquareRoot();
	double
	calculate(double);
	double
	calculate(double *, unsigned int);
};

#endif //SQUAREROOT_HPP
