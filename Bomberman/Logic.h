#pragma once
#include "Game.h"
#include "Bomber.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Player.h"

//игровая логика вкл игровое поле и все остальные объекты
//описывает их взаимодействие
class Logic
{
private:
	vector<vector<int>> field; //игровое поле
	//(0 - пусто, 1 - стена, 2 - кирпич, 3 - бомбер, 4 - враг, 5 - взрыв, 6 - дверь / выход)

	Game* g; //текущая игра
	Player* p; //текущий игрок
	int size; //ориг размер спрайта

	//текстура для всех объектов
	sf::Texture* gameTexture = nullptr;
	vector<sf::Sprite> sprites; //отдельные спрайты полученные из текстуры
	int w, h; //размеры поля
	int blockSize; //размер одной клетки поля

	//бомбермен
	Bomber* bomber = nullptr; //игрок

	//стены
	vector<GameObject*> walls;

	//разрушаемые стены
	vector<GameObject*> bricks;

	//враги
	vector<Enemy*> enemies;

	//выход
	GameObject* exit = nullptr;

	//бомбы
	vector<Bomb*> bombs;

	//счет
	int score;
	sf::Text scoreText;

	//информация
	sf::Text info;

	int status; //статус игры

public:

	//конструктор
	Logic(Game* game, int width, int height, int blockSize, Player* player);

	//сброс игры
	void reset();

	//очистка динамических переменных
	void clear();

	//обновление состояний остальных объектов
	void update(float dt);

	//движение бомбермена
	void move(int vx, int vy);

	//установка бомбы
	void setBomb();

	//отрисовка
	void paint();

	//конец игры
	void over(int newStatus, string title);

	//деструктор
	~Logic();
};