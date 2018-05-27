//
// Created by Leonardo Fuso on 27/05/18.
//

#include <boost/python.hpp>
#include "SquareRoot.hpp"

using namespace boost::python;

// Defines a python module which will be named "sqrtlib"
BOOST_PYTHON_MODULE (sqrtlib)
{
	/* Defines a SquareRoot class with just one method:
	 * @calculate Returns the SquareRoot of a given double
	 */
	class_<SquareRoot> sqrt("SquareRoot");
	sqrt.def("calculate", &SquareRoot::calculate);
}
