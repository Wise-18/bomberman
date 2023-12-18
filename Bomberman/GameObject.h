#pragma once
#include "Game.h"

//игровой объект
class GameObject
{
protected:
	Game* g; //текущая игра
	int w, h; //размеры поля
	int blockSize; //размер одной клетки
	sf::Vector2i pos; //положение на игровом поле
	sf::Sprite sprite; //текущий спрайт

public:

	//конструктор
	GameObject(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//отрисовка
	void paint();

	//получаем координаты
	sf::Vector2i getPos();

	//устанавливаем
	void setPos(sf::Vector2i pos);
};