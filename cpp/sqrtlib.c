#include "c_square_root.h"
#include <Python.h>

static PyObject *
calculate_wrapper(PyObject *self, PyObject *args)
{

	/* The following element of an array */
	PyObject *sequence;

	/* the Python Array supplier */
	double *array;

	/* the result of the function */
	double result;

	/* the sequence length */
	unsigned int sequence_length;

	/*
	 * get one argument as a sequence
	 * the '0' stands for the data type expected
	 */
	if (!PyArg_ParseTuple(args, "0", &sequence))
		return NULL;

	sequence = PySequence_Fast(sequence, "argument must be iterable");
	if (!sequence)
		return NULL;

	/*
	 * prepare data as an array of doubles
	 * Compiler warns that Py_ssize_t differs from unsigned int
	 */
	sequence_length = PySequence_Fast_GET_SIZE(sequence);

	array = (double *) calloc(sequence_length, sizeof(double));

	if (!array)
	{
		Py_DECREF(sequence);
		return PyErr_NoMemory();
	}

	/*
	 * Starts filling up the array
	 * This can be optimized
	 */
	unsigned int i;
	for (i = 0; i < sequence_length; i++)
	{

		/* float value */
		PyObject *f_item;

		/* item of the python array */
		PyObject *item = PySequence_Fast_GET_ITEM(sequence, i);
		if (!item)
		{
			Py_DECREF(sequence);
			free(array);
			return NULL;
		}

		f_item = PyNumber_Float(item);

		if (!f_item)
		{
			Py_DECREF(sequence);
			free(array);
			PyErr_SetString(PyExc_TypeError, "all items must be numbers");
			return NULL;
		}
		array[i] = PyFloat_AsDouble(f_item);
		Py_DECREF(f_item);
	}

	/* clean up */
	Py_DECREF(sequence);

	/* compute */;
	result = calculate(array);

	free(array);

	/*
	 * and return the result
	 * the 'd' stands for Double data type
	 */
	return Py_BuildValue("d", result);
}

static PyObject *
calculate_single_wrapper(PyObject *self, PyObject *args) { /* empty */ }

static PyMethodDef module_methods_list[] =
	{
		{"calculate", (PyCFunction) calculate_wrapper, METH_VARARGS, NULL},
		{"singleCalculate", (PyCFunction) calculate_single_wrapper, METH_VARARGS, NULL},
		{NULL, NULL, 0, NULL} /* sentinel */
	};

/*
 * @see https://docs.python.org/3/c-api/module.html#c.PyModuleDef
 */
static struct PyModuleDef moduleDef =
	{
		PyModuleDef_HEAD_INIT,
		"SquarePy",           /* name of module */
		"Some description",     /* module documentation, may be NULL */
		-1,                     /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
		module_methods_list,
		NULL,
		NULL,
		NULL,
		NULL
	};

PyMODINIT_FUNC
PyInit_SquarePy()
{
	return PyModule_Create(&moduleDef);
}