#include "cell.h"
#include <iostream>

Cell::Cell(int i, int j, int w)
{
    this->alive = false;    //Все клетки изначально мертвы
    this->shape.setFillColor(sf::Color(250, 128, 114));     //Заполняем клетку выбранным цветом
    this->shape.setOutlineThickness(1);     //Толщина границы
    this->shape.setOutlineColor(sf::Color(220, 20, 60, 0));     //Выбираем цвет границ клетки
    this->shape.setSize(sf::Vector2f(15.0, 15.0));      //Устанавливаем размер клетки
    this->x = i;
    this->y = j;
    this->cellSize = w; 
}

Cell::~Cell() {}

bool Cell::isAlive()    //Проверка жива ли клетка
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
    window.draw(this->shape);       //Рисуем клетки
}

void Cell::setPosition(sf::Vector2f pos) 
{
    this->shape.setPosition(pos);
}

void Cell::kill() 
{
    this->alive = false;    //Клетка умирает
    this->shape.setFillColor(sf::Color(250, 128, 114));     //Устанавливаем цвет для мертвой клетки
}

void Cell::ressurect()
{
    this->alive = true;     //Клетка оживает
    this->shape.setFillColor(sf::Color::Black);     //Устанавливаем цвет для живой клетки
}

void Cell::update(sf::RenderWindow& window, sf::Clock& clockActivating, sf::Time& elapsedActivated) 
{
    if (elapsedActivated.asSeconds() >= 0.2)   //Если с запуска прошло определенное кол-во времени
    {
        clockActivating.restart();      //Обнуляем таймер
        if (this->alive)        //Проверяем должна ли умереть клетка или возводиться
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