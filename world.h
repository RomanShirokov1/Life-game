#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.h"

class Game
{
private:
	const int WINDOW_SIZE = 850;		//������ ����
	const int CELL_SIZE = 17;		//������ ������
	const int GRID_SIZE = WINDOW_SIZE / 17;		//������ ����� �� ����
	const int ROWS = WINDOW_SIZE / CELL_SIZE;	//����
	const int FPS = 60;		//����� FPS
	bool isRunning;		//�������� �� ���������

	sf::RenderWindow window;
	std::vector<Cell> grid, gridCopy;
	sf::Clock clockActivating;
	sf::Time elapsedActivated;
	sf::Clock clockStart;
	sf::Time elapsedStart;
	sf::Font font;
	sf::Text text1;

	int getLivingNeighbors(int x, int y);	//�������� ���������� ������� ������
public:
	int Generation = 1;
	Game();
	~Game();
	void run();
};
