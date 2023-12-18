#pragma once
#include "GameObject.h"

//взрывающаяся бомба
class Bomb : public GameObject
{
private:
	float timeOut; //сколько времени до взрыва
	float showTime; //сколько времени показывать взрыв
	vector<sf::Sprite> boom; //спрайты взрыва
	vector<sf::Vector2i> boomPos; //клетки на которых произошел взрыв
	sf::Texture* tex; //текстура игры

public:

	//конструктор
	Bomb(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//обратный отчет до взрыва
	int ticks(vector<vector<int>>& field, float dt);

	//отрисовка
	void paint();

	//получаем клетки
	vector<sf::Vector2i> getBoomPos();
};