#include <Python.h>

/* a preexisting C-level function you want to expose -- e.g: */
static double
total(double *data, int len)
{
	double total = 0.0;
	int i;
	for (i = 0; i < len; ++i)
		total += data[i];
	return total;
}

/* here is how you expose it to Python code: */
static PyObject *
totalDoubles(PyObject *self, PyObject *args)
{
	PyObject *sequence;
	double *array;
	double result;
	int sequence_length;
	int i;

	/* get one argument as a sequence */
	if (!PyArg_ParseTuple(args, "O", &sequence))
		return 0;

	sequence = PySequence_Fast(sequence, "argument must be iterable");
	if (!sequence)
		return 0;

	/* prepare data as an array of doubles */
	sequence_length = PySequence_Fast_GET_SIZE(sequence);

	array = malloc(sequence_length * sizeof(double));

	if (!array)
	{
		Py_DECREF(sequence);
		return PyErr_NoMemory();
	}

	for (i = 0; i < sequence_length; i++)
	{
		PyObject *fitem;
		PyObject *item = PySequence_Fast_GET_ITEM(sequence, i);
		if (!item)
		{
			Py_DECREF(sequence);
			free(array);
			return 0;
		}
		fitem = PyNumber_Float(item);
		if (!fitem)
		{
			Py_DECREF(sequence);
			free(array);
			PyErr_SetString(PyExc_TypeError, "all items must be numbers");
			return 0;
		}
		array[i] = PyFloat_AS_DOUBLE(fitem);
		Py_DECREF(fitem);
	}

	/* clean up, compute, and return result */
	Py_DECREF(sequence);
	result = total(array, sequence_length);
	free(array);
	return Py_BuildValue("d", result);
}

/* the name of the function */
static PyMethodDef totalMethods[] = {
	{"getSum", totalDoubles, METH_VARARGS, "Sum a sequence of numbers."},
	{0} /* sentinel */
};

static struct PyModuleDef moduleDef =
	{
		PyModuleDef_HEAD_INIT,
		"Total",           /* name of module */
		"Some description",     /* module documentation, may be NULL */
		-1,                     /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
		totalMethods,
		NULL,
		NULL,
		NULL,
		NULL
	};

/*
 * method name has to be the same as Py_InitModule argument
 * also, the name of the file has to be the same as these two.
 */
PyMODINIT_FUNC
PyInit_Total(void)
{
	(void) PyModule_Create(&moduleDef);
}
