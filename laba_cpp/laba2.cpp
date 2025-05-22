
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <locale>

using namespace std;


struct Smartphone {
    string brand;
    string model;
    string os_phone;
    string color;
    int ram;
    int storage;
    double price;
};


void addSmartphone(vector<Smartphone>& phones) {
    Smartphone phone;
    cout << "\nВведите данные смартфона:\n";
    cout << "Бренд: "; cin >> phone.brand;
    cout << "Модель: "; cin >> phone.model;
    cout << "ОС (Android/iOS): "; cin >> phone.os_phone;
    cout << "Цвет: "; cin >> phone.color;
    cout << "ОЗУ (ГБ): "; cin >> phone.ram;
    cout << "Память (ГБ): "; cin >> phone.storage;
    cout << "Цена (руб): "; cin >> phone.price;
    phones.push_back(phone);
    cout << "Смартфон добавлен!\n";
}


void displaySmartphones(vector<Smartphone>& phones) {
    if (phones.empty()) {
        cout << "Список смартфонов пуст!\n";
        return;
    }
    cout << "\n=== Список смартфонов ===\n";

    cout << "Бренд" << "\t" << "Модель" << "\t" << "ОС" << "\t" << "Цвет" << "\t" << "ОЗУ" << "\t" << "Память" << "\t" << "Цена" << endl;

    for (Smartphone phone : phones) 
        cout << phone.brand << "\t" << phone.model << "\t" << phone.os_phone << "\t" << phone.color << "\t" << phone.ram 
            << "\t" << phone.storage << "\t" << phone.price << endl;
    
}

void saveToFile(vector<Smartphone>& phones) {
    char filename[20];
    cout << "Ввидите имя файла: ";
    cin >> filename;

    FILE* file = fopen(filename, "wb");
    if (!file) {
        cout << "Ошибка открытия файла для записи!\n";
        return;
    }

    int size = phones.size();
    fwrite(&size, sizeof(int), 1, file);

    if (size > 0 && fwrite(&phones[0], sizeof(Smartphone), size, file) == phones.size()) {
        cout << "Данные успешно сохранены в файл " << filename << endl;
    }
    else {
        cout << "Произошла ошибка записи в файл!\n";
    }

    fclose(file);
}

void loadFromFile(vector<Smartphone>& phones) {
    char filename[20];
    cout << "Ввидите имя файла: ";
    cin >> filename;
    FILE* file = fopen(filename, "rb");
    if (!file) {
        cout << "Ошибка открытия файла для чтения!" << filename << endl;
        return;
    }

    int size;
    if (fread(&size, sizeof(int), 1, file) != 1) {
        cout << "Ошибка чтения размера данных из файла!\n";
        fclose(file);
        return;
    }

    phones.resize(size);

    if (size > 0) {
        if (fread(&phones[0], sizeof(Smartphone), size, file) != size) {
            cout << "Ошибка чтения данных из файла! Прочитано не все.\n";
            phones.clear();  
        }
    }

    fclose(file);
    cout << "Данные успешно загружены из файла " <<  filename << endl;
}


void findMostExpensive(vector<Smartphone>& phones) {
    if (phones.empty()) {
        cout << "Нет данных для анализа!\n";
        return;
    }

    double best = phones[0].price;
    for (auto phone : phones) {
        if (phone.price > best) {
            best = phone.price;
        }
    }

    vector<Smartphone> mostExpensive;
    for (auto phone : phones) {
        if (phone.price == best) {
            mostExpensive.push_back(phone);
        }
    }

    if (mostExpensive.size() == 1) {
        cout << "Самый дорогой смартфон: "
            << mostExpensive[0].brand << " " << mostExpensive[0].model
            << " (Цена: " << mostExpensive[0].price << " руб.)\n";
    }
    else {
        cout << "Найдено " << mostExpensive.size() << " самых дорогих смартфонов:\n";
        for (auto phone : mostExpensive) {
            cout << phone.brand << " " << phone.model
                << " (Цена: " << phone.price << " руб.)\n";
        }
    }
}


void countByOS(vector<Smartphone>& phones) {
    if (phones.empty()) {
        cout << "Нет данных для анализа!\n";
        return;
    }

    map<string, int> os_counts;

    for (auto phone : phones) {
        os_counts[phone.os_phone] ++;  
    }

    cout << "Количество смартфонов по ОС:\n";
    cout << "----------------------------\n";
    for (auto o_c : os_counts) {
        cout << o_c.first << ": " << o_c.second << " шт.\n";
    }
    cout << "----------------------------\n";
    cout << "Всего ОС: " << os_counts.size() << endl;
}


void showBrandStats(vector<Smartphone>& phones) {
    if (phones.empty()) {
        cout << "Нет данных для анализа!\n";
        return;
    }

    map<string, double> totalPrices;
    map<string, int> brandCounts;

    for (auto phone : phones) {
        totalPrices[phone.brand] += phone.price;
        brandCounts[phone.brand]++;
    }

    cout << "Средние цены по брендам:\n";
    for (auto brand : totalPrices) {
        double avg = brand.second / brandCounts[brand.first];
        cout << brand.first << ": " << avg << " руб.\n";
    }
}


int main() {

    setlocale(LC_ALL, "Russian");

    vector<Smartphone> phones;
    string filename;
    int req = 1;

    while (req) {
        cout << "\n=== Меню управления базой смартфонов ===\n";
        cout << "1. Добавить смартфон\n";
        cout << "2. Просмотреть все смартфоны\n";
        cout << "3. Сохранить в файл\n";
        cout << "4. Загрузить из файла\n";
        cout << "5. Самый дорогой смартфон\n";
        cout << "6. Статистика по ОС\n";
        cout << "7. Средняя цена по брендам\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> req;
        switch (req) {
            case 1: addSmartphone(phones); break;
            case 2: displaySmartphones(phones); break;
            case 3: saveToFile(phones); break;
            case 4: loadFromFile(phones); break;
            case 5: findMostExpensive(phones); break;
            case 6: countByOS(phones); break;
            case 7: showBrandStats(phones); break;
            case 0: cout << "Выход\n"; break;
        default: cout << "Неверный выбор!\n";
        }
    }
    return 0;
}
