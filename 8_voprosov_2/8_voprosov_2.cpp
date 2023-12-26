#include <iostream>// подключение библиотеки ввода вывода
#include <fstream>
#include <string>
#include <windows.h>

using namespace std; // подключаем пространство имен std 

void saveAnswers(const char* filename, const bool answers[], int size) {
    ofstream file(filename, ios::out | ios::binary);
    if (file.is_open()) {
        char packedAnswers = 0;
        for (int i = 0; i < size; ++i) {
            packedAnswers |= (answers[i] << i);
        }
        file.write(reinterpret_cast<char*>(&packedAnswers), sizeof(packedAnswers));
        file.close();
        cout << "Ответы сохранены в файле " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для записи" << endl;
    }
}

void loadAnswers(const char* filename, bool answers[], int size) {
    ifstream file(filename, ios::in | ios::binary);
    if (file.is_open()) {
        char packedAnswers;
        file.read(reinterpret_cast<char*>(&packedAnswers), sizeof(packedAnswers));
        for (int i = 0; i < size; ++i) {
            answers[i] = (packedAnswers >> i) & 1;
        }
        file.close();
        cout << "Прошлые ответы загружены из файла " << filename << endl;
        cout << "Сохраненные ответы: ";
        for (int i = 0; i < size; ++i) {
            cout << answers[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "Не удалось открыть файл для чтения" << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* filename = "output.bin";
    bool answers[8] = { false };

    int loadChoice;
    cout << "Хотите загрузить прошлые ответы? (1 - да, 0 - нет): ";
    cin >> loadChoice;

    if (loadChoice == 1) {
        loadAnswers(filename, answers, 8); // загружаем прошлые ответы из файла
    }
    else {
        cout << "Ответы не были загружены" << endl;
    }

    cout << "Ответьте на 8 вопросов (1 - да, 0 - нет):" << endl;
    string questions[] = {
        "Любите ли вы играть в видеоигры?",
        "Вам нравится ананас?",
        "Нравится ли вам синий фон браузера?",
        "Вы носили когда-нибудь одежду задом наперед?",
        "Вы пробовали яблоки с медом?",
        "Ваш любимый цвет синий?",
        "Вы катались на водных горках?",
        "Умеете ли вы играть на каком-то музыкальном инструменте?"
    };
    for (int i = 0; i < 8; ++i) {
        cout << questions[i] << " (1 - да, 0 - нет): ";
        cin >> answers[i];
    }

    saveAnswers(filename, answers, 8); // сохраняем ответы в файл

    int changeChoice;
    cout << "Хотите изменить ответы? (1 - да, 0 - нет): ";
    cin >> changeChoice;

    if (changeChoice == 1) {
        cout << "Ответьте на вопросы заново (1 - да, 0 - нет):" << endl;
        for (int i = 0; i < 8; ++i) {
            cout << questions[i] << " (1 - да, 0 - нет): ";
            cin >> answers[i];
        }
        saveAnswers(filename, answers, 8);
    }

    return 0;
}
