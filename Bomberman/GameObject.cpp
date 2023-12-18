#include "GameObject.h"

//конструктор
GameObject::GameObject(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos) {
	g = game;
	this->w = w;
	this->h = h;
	this->blockSize = blockSize;
	this->pos = pos;
	sprite.setTexture(*tex);
	sprite.setTextureRect({ j * size, i * size, size, size });
	sprite.setScale({ (float)blockSize / size, (float)blockSize / size });
	sprite.setPosition(
		{
				(float)pos.x * blockSize + (g->getSize().width - w * blockSize) / 2,
				(float)pos.y * blockSize + (g->getSize().height - h * blockSize) / 2
		});
}

//отрисовка
void GameObject::paint() {
	g->getRenderWindow().draw(sprite);
}

//получаем координаты
sf::Vector2i GameObject::getPos() {
	return pos;
}

//устанавливаем
void GameObject::setPos(sf::Vector2i pos) {
	this->pos = pos;
}