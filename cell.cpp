#include "cell.h"
#include <iostream>

Cell::Cell(int i, int j, int w)
{
    this->alive = false;    //��� ������ ���������� ������
    this->shape.setFillColor(sf::Color(250, 128, 114));     //��������� ������ ��������� ������
    this->shape.setOutlineThickness(1);     //������� �������
    this->shape.setOutlineColor(sf::Color(220, 20, 60, 0));     //�������� ���� ������ ������
    this->shape.setSize(sf::Vector2f(15.0, 15.0));      //������������� ������ ������
    this->x = i;
    this->y = j;
    this->cellSize = w; 
}

Cell::~Cell() {}

bool Cell::isAlive()    //�������� ���� �� ������
{
    return this->alive;
}

int Cell::getX() 
{ 
    return this->x; 
}

int Cell::getY() 
{ 
    return this->y;
}

void Cell::draw(sf::RenderWindow& window) 
{
    int xCoord = 1 + this->x * this->cellSize;
    int yCoord = 1 + this->y * this->cellSize;
    this->shape.setPosition(sf::Vector2f(xCoord, yCoord));      
    window.draw(this->shape);       //������ ������
}

void Cell::setPosition(sf::Vector2f pos) 
{
    this->shape.setPosition(pos);
}

void Cell::kill() 
{
    this->alive = false;    //������ �������
    this->shape.setFillColor(sf::Color(250, 128, 114));     //������������� ���� ��� ������� ������
}

void Cell::ressurect()
{
    this->alive = true;     //������ �������
    this->shape.setFillColor(sf::Color::Black);     //������������� ���� ��� ����� ������
}

void Cell::update(sf::RenderWindow& window, sf::Clock& clockActivating, sf::Time& elapsedActivated) 
{
    if (elapsedActivated.asSeconds() >= 0.2)   //���� � ������� ������ ������������ ���-�� �������
    {
        clockActivating.restart();      //�������� ������
        if (this->alive)        //��������� ������ �� ������� ������ ��� �����������
        {
            this->alive = false;
            this->kill();
        }
        else 
        {
            this->alive = true;
            this->ressurect();
        }
    }
}