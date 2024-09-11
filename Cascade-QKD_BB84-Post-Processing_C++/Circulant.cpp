#include <iostream>
#include <vector>
#include <fstream>
#include <Python.h>
#include <Windows.h>
#include "Circulant.h"
using namespace std;

void Circulant() {

    // Initialize Python configuration
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);

    // Set Python home directory
    status = PyConfig_SetString(&config, &config.home, L"C:\\Users\\hulma\\AppData\\Local\\Programs\\Python\\Python312");
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        throw runtime_error("Error occurred in yourFunction");
    }

    // Set Python module search paths
    status = PyWideStringList_Append(&config.module_search_paths, L"C:\\Users\\hulma\\AppData\\Local\\Programs\\Python\\Python312\\Lib");
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        throw runtime_error("Error occurred in yourFunction");
    }
    status = PyWideStringList_Append(&config.module_search_paths, L"C:\\Users\\hulma\\AppData\\Local\\Programs\\Python\\Python312\\DLLs");
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        throw runtime_error("Error occurred in yourFunction");
    }
    status = PyWideStringList_Append(&config.module_search_paths, L"C:\\Users\\hulma\\AppData\\Local\\Programs\\Python\\Python312\\Lib\\site-packages");
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        throw runtime_error("Error occurred in yourFunction");
    }

    // Initialize the Python interpreter with the specified configuration
    status = Py_InitializeFromConfig(&config);
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        throw runtime_error("Error occurred in yourFunction");
    }

    // Add the current directory to the Python path
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    // Execute PythonFile.py and call the Cryptomite_Priv_Amp function
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;

    // Convert the file name to a Python string
    pName = PyUnicode_DecodeFSDefault("Circulant");
    if (pName == NULL) {
        PyErr_Print();
        throw runtime_error("Failed to convert file name to Python string");
    }

    // Import the module
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        // Get the function from the module
        pFunc = PyObject_GetAttrString(pModule, "Func_Circulant");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Call the function without arguments
            pValue = PyObject_CallObject(pFunc, NULL);
            if (pValue != NULL) {
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                throw runtime_error("Call to Func_Circulant() failed");
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            throw runtime_error("Cannot find function Func_Circulant");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        throw runtime_error("Failed to load Circulant");
    }

    // Finalize the Python interpreter
    Py_Finalize();

    // Clear the configuration
    PyConfig_Clear(&config);

}
