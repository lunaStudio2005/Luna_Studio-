#include <Python.h>
#include <filesystem>
#include <string>

int main(int argc, char** argv) {
  Py_Initialize();

  std::filesystem::path cwd = std::filesystem::current_path();
  std::filesystem::path scriptsDir = cwd / "scripts";

  PyObject* sysPath = PySys_GetObject("path");
  PyObject* scriptsPath = PyUnicode_FromString(scriptsDir.string().c_str());
  PyList_Append(sysPath, scriptsPath);
  Py_DECREF(scriptsPath);

  std::filesystem::path entry = scriptsDir / "main.py";
  FILE* fp = fopen(entry.string().c_str(), "rb");
  if (!fp) {
    Py_Finalize();
    return 1;
  }

  int rc = PyRun_SimpleFile(fp, entry.string().c_str());
  fclose(fp);

  if (rc != 0) {
    if (PyErr_Occurred()) PyErr_Print();
    Py_Finalize();
    return 1;
  }

  Py_Finalize();
  return 0;
}
