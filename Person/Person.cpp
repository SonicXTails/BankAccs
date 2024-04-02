#include <iostream>
#include <string>
#include <Windows.h>
#pragma execution_character_set("utf-8")

using namespace std;

class BankAccount {
private:
    int accountNumber; // Номер банковского счёта
    double balance; // Баланс
    double interestRate; // Процентная ставка

public:
    // Конструктор для инициализации номера счёта и начального баланса
    BankAccount(int accountNumber, double initialBalance)
        : accountNumber(accountNumber), balance(initialBalance), interestRate(0.0) {}

    // Функция для внесения средств на счёт
    void Deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;
            cout << "Пополнение счёта прошло успешно. Новый баланс: " << this->balance << endl;
        }
        else {
            cout << "Невозможно внести отрицательную сумму." << endl;
        }
    }

    // Функция для снятия средств со счёта
    void Withdraw(double amount) {
        if (amount > 0 && amount <= this->balance) {
            this->balance -= amount;
            cout << "Снятие средств со счёта прошло успешно. Новый баланс: " << this->balance << endl;
        }
        else {
            cout << "Недостаточно средств на счёте или сумма снятия отрицательна." << endl;
        }
    }

    // Функция для получения текущего баланса
    double GetBalance() {
        return this->balance;
    }

    // Функция для обновления процентной ставки
    void SetInterestRate(double newInterestRate) {
        this->interestRate = newInterestRate;
        cout << "Процентная ставка обновлена до: " << this->interestRate << endl;
        cout << "Текущая сумма процентов, заработанных на счёте: " << this->GetInterest() << endl;
    }

    // Функция для расчёта и возврата суммы процентов, заработанных на счёте
    double GetInterest() {
        return this->balance * this->interestRate * (1.0 / 12.0);
    }

    // Функция для получения номера банковского счёта
    int GetAccountNumber() {
        return this->accountNumber;
    }
};

// Дружественная функция для перевода средств
bool Transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
    if (amount > 0 && amount <= fromAccount.GetBalance()) {
        fromAccount.Withdraw(amount);
        toAccount.Deposit(amount);
        cout << "Перевод средств выполнен успешно." << endl;
        return true;
    }
    else {
        cout << "Перевод средств не выполнен. Недостаточно средств на первом счёте." << endl;
        return false;
    }
}

int main() {
    SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8
    SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8

    // Создание двух объектов BankAccount
    BankAccount account1(123456, 1000), account2(654321, 2000);


    double updatedInterestRate;
    // Цикл для выбора действий
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Внести средства на счёт" << endl;
        cout << "2. Снять средства со счёта" << endl;
        cout << "3. Получить текущий баланс" << endl;
        cout << "4. Расчёт и вывод суммы процентов, заработанных на счёте" << endl;
        cout << "5. Обновление процентной ставки" << endl;
        cout << "6. Получение номера банковского счёта" << endl;
        cout << "7. Перевод средств" << endl;
        cout << "0. Выход\n" << endl;

        int choice;
        cin >> choice;

        double amount;

        switch (choice) {
        case 1:
            cin >> amount;
            account1.Deposit(amount);
            break;
        case 2:
            cin >> amount;
            account2.Withdraw(amount);
            break;
        case 3:
            cout << "Текущий баланс первого счёта: " << account1.GetBalance() << endl;
            break;
        case 4:
            updatedInterestRate = account1.GetInterest();

            if (updatedInterestRate <= 0) {
                cout << "Вы некорректно ввели данные! Попробуйте снова!" << endl;
                break;
            }
            else {
                cout << "Проценты, заработанные на счёте: " << updatedInterestRate << endl;
                break;
            }
        case 5:
            updatedInterestRate;
            cin >> updatedInterestRate;
            account1.SetInterestRate(updatedInterestRate);
            break;
        case 6:
            cout << "Номер первого счёта: " << account1.GetAccountNumber() << endl;
            break;
        case 7:
            cin >> amount;
            Transfer(account2, account1, amount);
            break;
        case 0:
            return 0;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите действие из списка." << endl;
        }
    }

    return 0;
}