#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <windows.h>
using namespace std;

// Базовий інтерфейс для файлів і папок
class FileSystemComponent {
public:
    virtual void show() const = 0;
    virtual ~FileSystemComponent() = default;
};

// Клас для файлів
class File : public FileSystemComponent {
private:
    string name;

public:
    File(const string& name) : name(name) {}

    void show() const override {
        cout << "Файл: " << name << endl;
    }
};

// Клас для папок, що може містити файли та інші папки
class Folder : public FileSystemComponent {
private:
    string name;
    vector<unique_ptr<FileSystemComponent>> components;

public:
    Folder(const string& name) : name(name) {}

    // Метод додавання компонентів (файлів або папок)
    void add(unique_ptr<FileSystemComponent> component) {
        components.push_back(move(component));
    }

    void show() const override {
        cout << "Папка: " << name << endl;
        for (const auto& component : components) {
            component->show();
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення структури файлів і папок
    auto rootFolder = make_unique<Folder>("Коренева папка");

    auto subFolder1 = make_unique<Folder>("Папка 1");
    subFolder1->add(make_unique<File>("Файл 1-1.txt"));
    subFolder1->add(make_unique<File>("Файл 1-2.txt"));

    auto subFolder2 = make_unique<Folder>("Папка 2");
    subFolder2->add(make_unique<File>("Файл 2-1.txt"));

    rootFolder->add(move(subFolder1));
    rootFolder->add(move(subFolder2));
    rootFolder->add(make_unique<File>("Файл кореневий.txt"));

    cout << "Структура файлів і папок:" << endl;
    rootFolder->show();

}
