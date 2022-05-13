#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.h"

class Game
{
private:
	const int WINDOW_SIZE = 850;		//Размер окна
	const int CELL_SIZE = 17;		//Размер клетки
	const int GRID_SIZE = WINDOW_SIZE / 17;		//Размер сетки на поле
	const int ROWS = WINDOW_SIZE / CELL_SIZE;	//Ряды
	const int FPS = 60;		//Лимит FPS
	bool isRunning;		//Запущена ли программа

	sf::RenderWindow window;
	std::vector<Cell> grid, gridCopy;
	sf::Clock clockActivating;
	sf::Time elapsedActivated;
	sf::Clock clockStart;
	sf::Time elapsedStart;
	sf::Font font;
	sf::Text text1;

	int getLivingNeighbors(int x, int y);	//Получаем количество соседей клетки
public:
	int Generation = 1;
	Game();
	~Game();
	void run();
};
