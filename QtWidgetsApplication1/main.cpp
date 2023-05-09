#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <python.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    //w.show();

    //��ʼ��pythonģ��
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        return -1;
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['Timer.py']");
    PyRun_SimpleString("sys.path.append('./')");

    //����scriptSecond.pyģ��
    PyObject* pModule = PyImport_ImportModule("scriptSecond");
    if (!pModule) {
        printf("Cant open python file!\n");
        return -1;
    }
    //��ȡscriptSecondģ���е�temperImg����
    PyObject* pFunhello = PyObject_GetAttrString(pModule, "temperImg");
    //ע�͵����ⲿ������һ�ֻ��scriptSecondģ���е�temperImg�����ķ���
//    PyObject* pDict = PyModule_GetDict(pModule);
//       if (!pDict) {
//           printf("Cant find dictionary.\n");
//           return -1;
//       }
//    PyObject* pFunhello = PyDict_GetItemString(pDict, "temperImg");

    if (!pFunhello) {
        cout << "Get function hello failed" << endl;
        return -1;
    }
    //����temperImg����
    PyObject_CallFunction(pFunhello, NULL);
    //�������ͷ�python
    Py_Finalize();
    return a.exec();
}
