//
// Created by Leonardo Fuso on 27/05/18.
//

#include "SquareRoot.hpp"
#include <Python.h>

static PyObject *getCalculate(PyObject *self, PyObject *args) {

    /* The following element of an array */
    PyObject *sequence;

    /* the Python Array supplier */
    double *array;

    /* the result of the function */
    double result;

    /* the sequence length */
    unsigned int seq_len;

    /* get one argument as a sequence */
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

    if (!array) {
        Py_DECREF(sequence);
        return PyErr_NoMemory();
    }

    /*
     * Starts filling up the array
     */
    unsigned int i;
    for (i = 0; i < seq_len; i++) {

        /* float value */
        PyObject *f_item;

        /* item of the python array */
        PyObject *item = PySequence_Fast_GET_ITEM(sequence, i);
        if(!item) {
            Py_DECREF(sequence);
            free(array);
            return nullptr;
        }

        f_item = PyNumber_Float(item);

        if(!f_item) {
            Py_DECREF(sequence);
            free(array);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return nullptr;
        }
        array[i] = PyFloat_AsDouble(f_item);
        Py_DECREF(f_item);
    }

    /* clean up, compute, and return result */
    Py_DECREF(sequence);

    result = SquareRoot::calculate(array);
    free(array);

    /* Probably the 'd' stands for Double data type */
    return Py_BuildValue("d", result);
}

static PyMethodDef calculateMethods[] = {
        {"calculate", getCalculate, METH_VARARGS, "Sum of a sequence of square roots of numbers."},
        {0} /* sentinel */
};

/* This must be changed to Python3 implementation... or not? */
void
initSquareRoot(void)
{
    (void) Py_InitModule("SquareRoot", calculateMethods);
}

/*
 * from SquareRoot import calculate
 * ImportError: dynamic module does not define init function (initSquareRoot)
 */