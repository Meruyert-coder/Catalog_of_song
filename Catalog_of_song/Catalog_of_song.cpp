#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Song {
    string title;
    string author;
    int year;
    string lyrics;
};

const int maxCatalogSize = 100; 
int catalogSize = 0; 
Song catalog[maxCatalogSize]; 

void addSong() {
    if (catalogSize < maxCatalogSize) {
        Song newSong;
        cout << "Введите название песни: ";
        getline(cin >> ws, newSong.title);
        cout << "Введите автора текста песни: ";
        getline(cin >> ws, newSong.author);
        cout << "Введите год создания песни (если известен): ";
        cin >> newSong.year;
        cin.ignore(); 

        cout << "Введите текст песни (введите 'end' для завершения):\n";
        string line, lyrics;
        while (true) {
            getline(cin >> ws, line);
            if (line == "end") {
                break;
            }
            lyrics += line + "\n";
        }
        newSong.lyrics = lyrics;
        catalog[catalogSize] = newSong;
        catalogSize++;
        cout << "Песня успешно добавлена!\n";
    }
    else {
        cout << "Ошибка: достигнут максимальный размер каталога.\n";
    }
}

void displaySong(const Song& song) {
    cout << "Название: " << song.title << endl;
    cout << "Автор: " << song.author << endl;
    cout << "Год создания: " << song.year << endl;
    cout << "Текст песни:\n" << song.lyrics << endl;
    cout << endl;
}

void displayAllSongs() {
    if (catalogSize == 0) {
        cout << "Каталог пуст.\n";
        return;
    }

    for (int i = 0; i < catalogSize; i++) {
        displaySong(catalog[i]);
    }
}

void displayOneSong() {

    string title;
    cout << "Введите название песни для вывода: ";
    getline(cin >> ws, title);

    bool found = false;
    for (int i = 0; i < catalogSize; i++) {
        if (catalog[i].title == title) {
            displaySong(catalog[i]);
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "Песня не найдена.\n";
    }
}

void deleteSong() {
    string title;
    cout << "Введите название песни для удаления: ";
    getline(cin >> ws, title);

    int songIndex = -1;
    for (int i = 0; i < catalogSize; i++) {
        if (catalog[i].title == title) {
            songIndex = i;
            break;
        }
    }

    if (songIndex != -1) {
        for (int i = songIndex; i < catalogSize - 1; i++) {
            catalog[i] = catalog[i + 1];
        }
        catalogSize--;
        cout << "Песня успешно удалена!\n";
    }
    else {
        cout << "Песня не найдена.\n";
    }
}


void modifySong() {
    string title;
    cout << "Введите название песни для изменения: ";
    getline(cin >> ws, title);

    int songIndex = -1;
    for (int i = 0; i < catalogSize; i++) {
        if (catalog[i].title == title) {
            songIndex = i;
            break;
        }
    }

    if (songIndex != -1) {
        Song& song = catalog[songIndex];
        cout << "Введите новый текст песни (введите 'END' для завершения):\n";
        string line, lyrics;
        while (true) {
            getline(cin >> ws, line);
            if (line == "END") {
                break;
            }
            lyrics += line + "\n";
        }
        song.lyrics = lyrics;
        cout << "Песня успешно изменена!\n";
    }
    else {
        cout << "Песня не найдена.\n";
    }
}


void saveToFile() {
    string filename;
    cout << "Введите имя файла для сохранения: ";
    getline(cin >> ws, filename);

    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < catalogSize; i++) {
            file << "Название: " << catalog[i].title << "\n";
            file << "Автор: " << catalog[i].author << "\n";
            file << "Год создания: " << catalog[i].year << "\n";
            file << "Текст песни:\n" << catalog[i].lyrics << "\n";
            file << "\n";
        }
        file.close();
        cout << "Песни успешно сохранены в файл " << filename << "\n";
    }
    else {
        cout << "Ошибка: невозможно открыть файл " << filename << "\n";
    }
}

void searchByAuthor() {
    string author;
    cout << "Введите имя автора: ";
    getline(cin >> ws, author);

    bool found = false;
    for (int i = 0; i < catalogSize; i++) {
        if (catalog[i].author == author) {
            if (!found) {
                cout << "Песни автора " << author << ":\n";
                found = true;
            }
            displaySong(catalog[i]);
        }
    }

    if (!found) {
        cout << "Песни данного автора не найдены.\n";
    }
}

void searchByWord() {
    string word;
    cout << "Введите слово для поиска: ";
    getline(cin >> ws, word);

    bool found = false;
    for (int i = 0; i < catalogSize; i++) {
        if (catalog[i].lyrics.find(word) != string::npos) {
            if (!found) {
                cout << "Песни, содержащие слово \"" << word << "\":\n";
                found = true;
            }
            displaySong(catalog[i]);
        }
    }

    if (!found) {
        cout << "Песни с указанным словом не найдены.\n";
    }
}

// Главная функция main без изменений
int main() {
    setlocale(LC_ALL, "rus");
    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить песню\n";
        cout << "2. Отобразить все песни\n";
        cout << "3. Отобразить одну песню\n";
        cout << "4. Удалить песню\n";
        cout << "5. Изменить текст песни\n";
        cout << "6. Сохранить песни в файл\n";
        cout << "7. Поиск песен по автору\n";
        cout << "8. Поиск песен по слову\n";
        cout << "0. Выйти\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            addSong();
            break;
        case 2:
            displayAllSongs();
            break;
        case 3:
            displayOneSong();
            break;
        case 4:
            deleteSong();
            break;
        case 5:
            modifySong();
            break;
        case 6:
            saveToFile();
            break;
        case 7:
            searchByAuthor();
            break;
        case 8:
            searchByWord();
            break;
        case 0:
            cout << "Выход из программы.\n";
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}