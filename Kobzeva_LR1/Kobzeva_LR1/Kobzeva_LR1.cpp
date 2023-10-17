#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

unsigned char Vigener(unsigned char symbol, unsigned char key, int a) {
    return (symbol + a * key);
}

void EcryptOrDecipher1(string key,int length, const vector<unsigned char>& EncryptedText) {
    string FileNameOutput;
    cout << "\nВВЕДИТЕ НАЗВАНИЕ ФАЙЛА ДЛЯ ВЫВОДА\n";
    cin >> FileNameOutput;
    ofstream f_out(FileNameOutput + ".txt", ios::binary);
    if (!f_out.is_open()) {
        cout << "\nОШИБКА!!!\n";
    }
    int i = 0;
    unsigned char n;
    unsigned char k;
    for (unsigned char symbol :EncryptedText){
        k = key[i % length];
        n = Vigener(symbol, k, -1);
        f_out.put(n);
        i++;
    }
    f_out.close();
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

vector<int> SymbolFrequencies(const vector<unsigned char>& text) {
    vector<int> Frequencies(256, 0);
    for (unsigned char symbol : text) Frequencies[int(symbol)]++;
    return Frequencies;
}

float IC(const vector<int>& Frequencies, int N) {
    float IC = 0;
    for (int i : Frequencies) 
        IC += (i * (i - 1));
    return IC /= (N * (N - 1));
}

int KeyLength(const vector<unsigned char>& EncryptedText, const vector<unsigned char>& EtalonText) {
    float EtalonIC = IC(SymbolFrequencies(EtalonText),EtalonText.size());
    int length = 0;
    float ic = 0, DeltaIC = 1;
    int a, b;
    cout << "\nВВЕДИТЕ ДИАПОЗОН ДЛИННЫ КЛЮЧА: \n";
    cin >> a;
    cin >> b;
    vector <unsigned char> part;
    for (int len = a; len <= b; len++) {
        for (int i = len; i < EncryptedText.size(); i += len) {
            part.push_back(EncryptedText[i]);
        }
        ic = IC(SymbolFrequencies(part), part.size());
        part.clear();
        if (abs(ic - EtalonIC) < DeltaIC) {
            DeltaIC = abs(ic - EtalonIC);
            length = len;
        }
    }
    return length;
}

unsigned char PopularSymbol(const vector<unsigned char>& text) {
    vector <int> Frequency;
    Frequency = SymbolFrequencies(text);
    auto Symbol = max_element(Frequency.begin(), Frequency.end());
    unsigned char PopularSymbol = char(distance(Frequency.begin(), Symbol));
    return PopularSymbol;
}

string Key(const vector<unsigned char>& EncryptedText, const vector<unsigned char>& EtalonText, int length) {
    string key;
    vector <unsigned char> part;
    unsigned char PopularSymbolEtalon = PopularSymbol(EtalonText);
    for (int i = 0; i < length; i++) {
        for (int j = i; j < EncryptedText.size(); j += length) {
            part.push_back(EncryptedText[j]);
        }
        unsigned char PopularSymbolEncrypted = PopularSymbol(part);
        part.clear();
        key.push_back(PopularSymbolEncrypted-PopularSymbolEtalon);
    }
    return key;
}

vector <unsigned char> NameFile(bool f) {
    string FileName ="";
    if (f){
        cout << "\n ВВЕДИТЕ ИМЯ ФАЙЛА С ЗАШИФРОВАННЫМ ТЕКСТОМ: \n ";
    }
    else {
        cout << "\n ВВЕДИТЕ ИМЯ ФАЙЛА С ЭТАЛОННЫМИ ТЕКСТОМ: \n ";
    }
    cin >> FileName;
    ifstream in(FileName + ".txt", ios::binary);
    vector<unsigned char> Text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    return Text;
}


int main()
{
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    int num;
    while (1) {
        cout << "\nМЕНЮ\n 1. ЗАШИФРОВАТЬ\n 2. РАЗШИФРОВАТЬ\n 3.УЗНАТЬ ДЛИННУ И ЗНАЧЕНИЕ КЛЮЧА \n 0.ВЫХОД\n";
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
        case(3):
            vector <unsigned char> EncryptedText, EtalonText;
            EncryptedText = NameFile(true);
            EtalonText = NameFile(false);
            int Length = KeyLength(EncryptedText, EtalonText);
            string key = Key(EncryptedText, EtalonText, Length);
            cout << "Ключ: " << key << endl;
            cout << "Длина: " << Length << endl;
            EcryptOrDecipher1(key,Length, EncryptedText);

        }
    }
}

