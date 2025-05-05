#include <iostream>
#include <functional>
#include <limits>
using namespace std;

size_t hashPIN(int pin){
	return hash<int>{}(pin);
}

class User {
private:
	string name;
	double balance;

public:

  size_t hashedPIN;

	User(string userName, int userPIN, double userBalance) {
		name = userName;
		hashedPIN = hashPIN(userPIN);
		balance = userBalance;
	}



	bool checkPIN(int PINN) {
		return hashedPIN == hashPIN(PINN);
	}

	void showBalance() {
		cout << "Balance : " << balance << endl;
	}

	void deposite(double amount) {
		if(amount < 0){
			cout << "Сумма должна быть положительной!" << endl;
		}else{
			balance += amount;
			cout << "Баланс пополнен на " << amount << endl;
		}
	}

	bool withdraw(double amount2) {
		if (amount2 > balance){
			cout << "Недостаточно средств на счете!" << endl;
			return false;
		}else if(amount2 < 0){
			cout << "Сумма должна быть положительной!" << endl;
			return false;
		}else{
			balance -= amount2;
			cout << "Снято " << amount2 << endl;
			return true;
		}
	}

void changePIN (int oldPIN,int newPIN){
	if(checkPIN(oldPIN)){
		hashedPIN = hashPIN(newPIN);
		cout << "PIN успешно изменен!" << endl;
	}else{
		cout << "Неверный старый PIN!" << endl;
	}
}

string getName() const{
	return name;
}
};

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
	User user("Vika", 1234, 1000.0);

	int attempts = 3;
	int pinn;

	while(attempts > 0){
		cout << "Введите PIN: ";
		cin >> pinn;
	  
		if(cin.fail()){
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка ввода! Пожалуйста, введите PIN!" << endl;
		continue;
		}
	  
		if(user.checkPIN(pinn)){
       cout << "PIN is correct " << user.getName() << "!" << endl;

		int choice;
		do{
			cout << "\n Меню: \n"
			     << "1.Показать баланс\n"
					 << "2.Пополнить баланс\n"
					 << "3.Снять деньги\n"
					 << "4.Сменить PIN \n"
					 << "5.Выйти\n"
					 << "Выберите действие: ";
			cin >> choice;

			if(cin.fail()){
				clearInput();
				cout << "Введите от 1 до 5!" << endl;
				continue;
			}

			switch (choice){
				case 1:
				user.showBalance();
				break;

				case 2:{
				double amount;
				cout << "Введите сумму для пополнения: ";
				cin >> amount;
        user.deposite(amount);
				break;
			}

				case 3:{
        double  amount2;
				cout << "Введите сумму для снятия: ";
				cin >> amount2;
				if(!cin.fail()){
					user.withdraw(amount2);
				}else{
					clearInput();
					cout << "Введите сумму для снятия!" << endl;
				}
				break;
			}

				case 4:{
				int oldPIN, newPIN;
				cout << "Введите старый PIN ";
				cin  >> oldPIN;
				cout << "Введите новый PIN ";
				cin >> newPIN;
				if(!cin.fail()){
					user.changePIN(oldPIN, newPIN);

				}else{
					clearInput();
					cout << "Введите старый и новый PIN" << endl;
				}
        break;
			}
				case 5:
				cout << "До свидания!" << endl;
				break;

				default:
				cout << "Неверный выбор!" << endl;
			}

		}while(choice != 5);

		break;

	}else{
		attempts--;
		cout << "Неверный PIN. Осталось попыток:" << attempts << endl;
		if(attempts == 0){
			cout << "Попытки закончились!" << endl;
		}
		
  }
}

return 0;
}

