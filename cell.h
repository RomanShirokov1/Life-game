#pragma once
#include <SFML/Graphics.hpp>

class Cell 
{
private:
	bool alive;
	sf::RectangleShape shape;	//��������� ��������(����, ������ � ��)
	int x, y;
	int cellSize;

public:
	Cell(int i, int j, int w);	//�����������
	~Cell();	//����������
	bool isAlive();		//���� �� ������
	void draw(sf::RenderWindow& window);	//��������� ������
	void setPosition(sf::Vector2f pos);		//������� ������
	void ressurect();	//����������� ������
	void kill();	//�������� ������
	void update(sf::RenderWindow& window, sf::Clock& clockActivating, sf::Time& elapsedActivated);		//���������� ������
	int getX();
	int getY();
};

