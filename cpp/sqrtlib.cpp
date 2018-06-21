//
// Created by Leonardo Fuso on 27/05/18.
//

#include "SquareRoot.hpp"
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
    unsigned int seq_len;

    /*
     * get one argument as a sequence
     * the '0' stands for the data type expected
     */
    if (!PyArg_ParseTuple(args, "0", &sequence))
        return nullptr;

    sequence = PySequence_Fast(sequence, "argument must be iterable");
    if (!sequence)
        return nullptr;

    /*
     * prepare data as an array of doubles
     * Compiler warns that Py_ssize_t differs from unsigned int
     */
    seq_len = PySequence_Fast_GET_SIZE(sequence);

    array = (double *) calloc(seq_len, sizeof(double));

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
    for (i = 0; i < seq_len; i++)
    {

        /* float value */
        PyObject *f_item;

        /* item of the python array */
        PyObject *item = PySequence_Fast_GET_ITEM(sequence, i);
        if (!item)
        {
            Py_DECREF(sequence);
            free(array);
            return nullptr;
        }

        f_item = PyNumber_Float(item);

        if (!f_item)
        {
            Py_DECREF(sequence);
            free(array);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return nullptr;
        }
        array[i] = PyFloat_AsDouble(f_item);
        Py_DECREF(f_item);
    }

    /* clean up */
    Py_DECREF(sequence);

    /* compute */
    SquareRoot squareRoot;
    result = squareRoot.calculate(array);

    free(array);

    /*
     * and return the result
     * the 'd' stands for Double data type
     */
    return Py_BuildValue("d", result);
}

static PyMethodDef module_methods_list[] =
    {
        {"calculate", (PyCFunction) calculate_wrapper, METH_VARARGS, "Sum of a sequence of square roots of numbers."},
        {nullptr, nullptr, 0, nullptr} /* sentinel */
    };

/*
 * @see https://docs.python.org/3/c-api/module.html#c.PyModuleDef
 */
static struct PyModuleDef moduleDef =
    {
        PyModuleDef_HEAD_INIT,
        "SquareRoot",           /* name of module */
        "Some description",     /* module documentation, may be NULL */
        -1,                     /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        module_methods_list,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };

PyMODINIT_FUNC
PyInit_SquareRoot()
{
    return PyModule_Create(&moduleDef);
}

/*
 * from SquareRoot import calculate
 * ImportError: dynamic module does not define init function (initSquareRoot)
 */