#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hSerial;

void ReadCOM() {
    DWORD iSize;
    char sReceivedChar;
    while (true) {
        ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // �������� 1 ����
        if (iSize > 0)   // ���� ���-�� �������, �������
            cout << sReceivedChar;
    }
}

int main() {
    LPCTSTR sPortName = "COM3";
    hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "error setting serial port state\n";
    }
    char data[] = "Hello from C++";  // ������ ��� ��������
    DWORD dwSize = sizeof(data);   // ������ ���� ������
    DWORD dwBytesWritten;    // ��� ����� ���������� ���������� ���������� ����
    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
    while (true) {
        ReadCOM();
    }
}