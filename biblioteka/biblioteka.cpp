#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Класс Книга
class Book {
private:
    string title;
    string author;
    string genre;
    string description;
    bool reserved;

public:
    // Конструктор
    Book(const string& title, const string& author, const string& genre, const string& description)
        : title(title), author(author), genre(genre), description(description), reserved(false) {}

    // Геттеры
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    const string& getGenre() const { return genre; }
    const string& getDescription() const { return description; }
    bool isReserved() const { return reserved; }

    // Резервирование книги
    void reserve() {
        reserved = true;
    }

    // Отмена резервации книги
    void cancelReservation() {
        reserved = false;
    }
};

// Класс Библиотека
class LibraryCatalog {
private:
    vector<Book> books;

public:
    // Добавление книги в каталог
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книга успешно добавлена в каталог." << endl;
    }

    // Поиск книги по названию, автору, жанру и другим критериям
    vector<Book> searchBooks(const string& keyword) {
        vector<Book> foundBooks;

        for (const auto& book : books) {
            if (book.getTitle().find(keyword) != string::npos ||
                book.getAuthor().find(keyword) != string::npos ||
                book.getGenre().find(keyword) != string::npos ||
                book.getDescription().find(keyword) != string::npos) {

                foundBooks.push_back(book);
            }
        }

        return foundBooks;
    }

    // Отображение подробной информации о найденных книгах
    void displayBookDetails(const Book& book) const {
        cout << "Название: " << book.getTitle() << endl;
        cout << "Автор: " << book.getAuthor() << endl;
        cout << "Жанр: " << book.getGenre() << endl;
        cout << "Описание: " << book.getDescription() << endl;
        cout << "Статус: " << (book.isReserved() ? "Зарезервирована" : "Доступна") << endl;
    }

    // Резервирование книги
    void reserveBook(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title && !book.isReserved()) {
                book.reserve();
                cout << "Книга '" << title << "' успешно зарезервирована." << endl;
                return;
            }
        }

        cout << "Книга с названием '" << title << "' уже зарезервирована или не найдена." << endl;
    }

    // Отмена резервации книги
    void cancelReservation(const string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title && book.isReserved()) {
                book.cancelReservation();
                cout << "Резервация книги '" << title << "' успешно отменена." << endl;
                return;
            }
        }

        cout << "Резервация книги с названием '" << title << "' не найдена." << endl;
    }

    // Просмотр списка зарезервированных книг пользователя
    void viewReservedBooks() const {
        bool found = false;

        for (const auto& book : books) {
            if (book.isReserved()) {
                displayBookDetails(book);
                cout << "-------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "У вас нет зарезервированных книг." << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    LibraryCatalog library;

    Book book1("Evgeniy Onegin", "Pushkin", "Роман в стихах", "Книга, о знатном дворянине Онегине и его жизни.");
    Book book2("Prestuplenie i nakaz", "Dostoevskiy", "Роман", "Книга, о бывшем студенте Раскольникове и о его истории.");
    Book book3("World War I", "Remark", "Роман", "Роман о жизини главного героя и его товарищей на передовой Первой Мировой Войны.");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    int choice = 0;
    while (choice != 7) {
        cout << "\nМеню:" << endl;
        cout << "1. Поиск книги" << endl;
        cout << "2. Отображение подробной информации о книге" << endl;
        cout << "3. Резервирование книги" << endl;
        cout << "4. Отмена резервации книги" << endl;
        cout << "5. Просмотр списка зарезервированных книг" << endl;
        cout << "6. Добавление книги в каталог" << endl;
        cout << "7. Выход" << endl;

        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string keyword;
            cout << "Введите ключевое слово для поиска: ";
            cin.ignore();
            getline(cin, keyword);
            auto foundBooks = library.searchBooks(keyword);
            if (!foundBooks.empty()) {
                cout << "Результаты поиска:" << endl;
                for (const auto& book : foundBooks) {
                    library.displayBookDetails(book);
                    cout << "-------------------------" << endl;
                }
            }
            else {
                cout << "Книги по запросу '" << keyword << "' не найдены." << endl;
            }
            break;
        }
        case 2: {
            string title;
            cout << "Введите название книги: ";
            cin.ignore();
            getline(cin, title);
            auto foundBooks = library.searchBooks(title);
            if (!foundBooks.empty()) {
                library.displayBookDetails(foundBooks[0]);
            }
            else {
                cout << "Книга с названием '" << title << "' не найдена." << endl;
            }
            break;
        }
        case 3: {
            string title;
            cout << "Введите название книги для резервации: ";
            cin.ignore();
            getline(cin, title);
            library.reserveBook(title);
            break;
        }
        case 4: {
            string title;
            cout << "Введите название книги для отмены резервации: ";
            cin.ignore();
            getline(cin, title);
            library.cancelReservation(title);
            break;
        }
        case 5:
            library.viewReservedBooks();
            break;
        case 6: {
            string title, author, genre, description;
            cout << "Введите название книги: ";
            cin.ignore();
            getline(cin, title);
            cout << "Введите автора книги: ";
            getline(cin, author);
            cout << "Введите жанр книги: ";
            getline(cin, genre);
            cout << "Введите описание книги: ";
            getline(cin, description);

            Book newBook(title, author, genre, description);
            library.addBook(newBook);
            break;
        }
        case 7:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите еще раз." << endl;
            break;
        }
    }

    return 0;
}
