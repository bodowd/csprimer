#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cvarint_encode(PyObject *self, PyObject *args) {

  // https://docs.python.org/3/c-api/arg.html#arg-parsing
  // K --> Convert a C unsigned long long to a Python integer object
  unsigned long long n;
  int i = 0;
  char part, out[10];
  if (!PyArg_ParseTuple(args, "K", &n)) {
    return NULL;
  }

  while (n > 0) {
    part = n & 0x7f;
    n >>= 7;
    if (n > 0) {
      part |= 0x80; // set the highest bit on
    }
    out[i++] = part;
  }
  return PyBytes_FromStringAndSize(out, i);
}

static PyObject *cvarint_decode(PyObject *self, PyObject *args) {

  const char *varn;
  char b;
  unsigned long long n = 0;
  int shamt = 0; // shift amount

  if (!PyArg_ParseTuple(args, "y", &varn)) {
    return NULL;
  }

  for (int i = 0;; i++) {
    b = varn[i];
    if (b == 0)
      break;

    n |= ((unsigned long long)(b & 0x7f) << shamt);
    shamt += 7;
  }

  return PyLong_FromUnsignedLongLong(n);
}

static PyMethodDef CVarintMethods[] = {
    {"encode", cvarint_encode, METH_VARARGS, "Encode an integer as varint."},
    {"decode", cvarint_decode, METH_VARARGS,
     "Decode varint bytes to an integer."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cvarintmodule = {
    PyModuleDef_HEAD_INIT, "cvarint",
    "A C implementation of protobuf varint encoding", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cvarint(void) { return PyModule_Create(&cvarintmodule); }
