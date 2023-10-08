#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

unsigned char Vigener(unsigned char symbol, unsigned char key, int a) {
    return (symbol + a * key);
}

void EcryptOrDecipher(int a) {
    string FileNameInput, FileNameOutput;
    string key;
    cout << "\nВВЕДИТЕ НАЗВАНИЕ ФАЙЛА ДЛЯ СЧИТЫВАНИЯ\n";
    cin >> FileNameInput;
    cout << "\nВВЕДИТЕ НАЗВАНИЕ ФАЙЛА ДЛЯ ВЫВОДА\n";
    cin >> FileNameOutput;
    cout << "\nВВЕДИТЕ КЛЮЧ\n";
    cin >> key;
    ifstream f_in(FileNameInput + ".txt",ios::binary);
    ofstream f_out(FileNameOutput + ".txt", ios::binary);
    if (!f_in.is_open()) {
        cout << "\nОШИБКА СЧИТЫВАНИЯ ФАЙЛА!!!\n";
    }
    if (!f_out.is_open()) {
        cout << "\nОШИБКА!!!\n";
    }
    char symbol;
    int i = 0;
    unsigned char n;
    unsigned char k;
    while (f_in.get(symbol)) {
        k = key[i % key.size()];
        n = Vigener(symbol, k, a);
        f_out.put(n);
        i++;
    }
    f_in.close();
    f_out.close();
}
int main()
{
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    int num;
    while (1) {
        cout << "\nМЕНЮ\n 1. ЗАШИФРОВАТЬ\n 2. РАЗШИФРОВАТЬ\n 0.ВЫХОД\n";
        cin >> num;
        switch (num)
        {
        case(0):
            return 0;
        case(1):
            EcryptOrDecipher(1);
            break;
        case(2):
            EcryptOrDecipher(-1);
            break;
        }
    }
}

