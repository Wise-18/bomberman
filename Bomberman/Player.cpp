#include "Player.h"

//�����������
Player::Player(Game* game) {
	g = game;
	login = "";
	score = 0;
}

//��������� ������
string Player::getLogin() {
	return login;
}

//��������� �����
size_t Player::getScore() {
	return score;
}

//��������� ������
void Player::setLogin(string login) {
	this->login = login;
}

//��������� �����
void Player::setScore(size_t score) {
	this->score = score;
}

//��������� ������ �� �����
void Player::loadData(string log) {
	ifstream reader{ g->getFile() };
	if (reader.is_open()) {
		string line;

		//������ ��������� �� �����
		while (getline(reader, line)) {
			stringstream stream{ line };
			string login;
			string score;
			stream >> login >> score;
			if (login == log) {
				setLogin(login);
				setScore(stoi(score));
				cout << "������ ������� ���������" << endl;
				break;
			}
		}
		reader.close();
	}
	else {
		cout << "������ �������� ����� " << g->getFile() << endl;
	}
}

//��������� ���� � ����� ��� �������� ������������
void Player::updateScore() {

	//��������� ���� ������
	cout << "���������� �����������" << endl;
	vector<string> list;
	ifstream reader{ g->getFile() };
	bool flag = false; //����� ���������� ��� ���
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
		cout << "������ �������� ����� " << g->getFile() << endl;
	}

	//��������� � ����
	if (flag) {
		ofstream writer{ g->getFile() };
		for (int i = 0; i < list.size(); i++) {
			writer << list[i] << endl;
		}
		writer.close();
		cout << "��������� ��� " << login << " ������� ��������!" << endl;
	}
}