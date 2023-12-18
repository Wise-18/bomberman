#include "Player.h"

//конструктор
Player::Player(Game* game) {
	g = game;
	login = "";
	score = 0;
}

//получение логина
string Player::getLogin() {
	return login;
}

//получение счета
size_t Player::getScore() {
	return score;
}

//установка логина
void Player::setLogin(string login) {
	this->login = login;
}

//установка счета
void Player::setScore(size_t score) {
	this->score = score;
}

//получение данных из файла
void Player::loadData(string log) {
	ifstream reader{ g->getFile() };
	if (reader.is_open()) {
		string line;

		//читаем построчно из файла
		while (getline(reader, line)) {
			stringstream stream{ line };
			string login;
			string score;
			stream >> login >> score;
			if (login == log) {
				setLogin(login);
				setScore(stoi(score));
				cout << "Данные успешно прочитаны" << endl;
				break;
			}
		}
		reader.close();
	}
	else {
		cout << "Ошибка открытия файла " << g->getFile() << endl;
	}
}

//обновляем счет в файле для текущего пользователя
void Player::updateScore() {

	//загружаем весь список
	cout << "Обновление результатов" << endl;
	vector<string> list;
	ifstream reader{ g->getFile() };
	bool flag = false; //нужна перезапись или нет
	if (reader.is_open()) {
		string line;
		while (getline(reader, line)) {
			stringstream stream{ line };
			string log;
			string score;
			stream >> log >> score;
			if (login == log) {
				size_t sc = stoi(score);
				if (sc < getScore()) {
					list.push_back(log + " " + to_string(getScore()));
					flag = true;
				}
				else {
					list.push_back(log + " " + score);
				}
			}
			else {
				list.push_back(log + " " + score);
			}
		}
		reader.close();
	}
	else {
		cout << "Ошибка открытия файла " << g->getFile() << endl;
	}

	//сохраняем в файл
	if (flag) {
		ofstream writer{ g->getFile() };
		for (int i = 0; i < list.size(); i++) {
			writer << list[i] << endl;
		}
		writer.close();
		cout << "Результат для " << login << " успешно обновлен!" << endl;
	}
}