#include "c_square_root.h"
#include <Python.h>

static PyObject *
calculate_sequence_wrapper(PyObject *self, PyObject *args)
{

    /* The following element of an array */
    PyObject *sequence;

    /* the Python Array supplier */
    double *array;

    /* the result of the function */
    double result;

    /* the sequence length */
    Py_ssize_t sequence_length;

    /* Check if the single argument is iterable or not */
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &sequence))
    {
        PyErr_SetString(PyExc_TypeError, "Single argument must be iterable");
        return NULL;
    }

    /* store the single argument as a PySequence_Fast into a PyObject variable */
    sequence = PySequence_Fast(sequence, "Single argument must be iterable");
    if (!sequence)
        return NULL;

    /*
     * Get the size of a given sequence
     */
    sequence_length = PySequence_Fast_GET_SIZE(sequence);
    if(sequence_length == 0)
    {
        PyErr_SetString(PyExc_TypeError, "Sequence is empty!");
        return NULL;
    }

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

        array[i] = PyFloat_AS_DOUBLE(f_item);
        Py_DECREF(f_item);
    }

    /* clean up */
    Py_DECREF(sequence);

    /* compute */;
    result = calculate_sequence(array);

    free(array);

    /*
     * and return the result as a PyLong
     */
    return PyLong_FromDouble(result);
}

static PyObject *
calculate_single_wrapper(PyObject *self, PyObject *args)
{
    const double value;
    double result;

    /* get the one argument */
    if (!PyArg_ParseTuple(args, "d", &value))
        return NULL;

    result = calculate_single(value);

    return PyLong_FromDouble(result);
}

static PyMethodDef module_methods_list[] =
    {
        {"calculate_single", (PyCFunction) calculate_single_wrapper, METH_VARARGS, NULL},
        {"calculate_sequence", (PyCFunction) calculate_sequence_wrapper, METH_VARARGS, NULL},
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