#pragma once
#include <SFML/Graphics.hpp>

class Cell 
{
private:
	bool alive;
	sf::RectangleShape shape;	//Параметры квадрата(цвет, размер и тд)
	int x, y;
	int cellSize;

public:
	Cell(int i, int j, int w);	//Конструктор
	~Cell();	//Деструктор
	bool isAlive();		//Жива ли клетка
	void draw(sf::RenderWindow& window);	//Отрисовка клетки
	void setPosition(sf::Vector2f pos);		//Позиция клетки
	void ressurect();	//Воскрешение клетки
	void kill();	//Убийство клетки
	void update(sf::RenderWindow& window, sf::Clock& clockActivating, sf::Time& elapsedActivated);		//Обновление клеток
	int getX();
	int getY();
};

