#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hSerial;

void ReadCOM() {
    DWORD iSize;
    char sReceivedChar;
    while (true) {
        ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
        if (iSize > 0)   // если что-то принято, выводим
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
    char data[] = "Hello from C++";  // строка для передачи
    DWORD dwSize = sizeof(data);   // размер этой строки
    DWORD dwBytesWritten;    // тут будет количество собственно переданных байт
    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
    while (true) {
        ReadCOM();
    }
}