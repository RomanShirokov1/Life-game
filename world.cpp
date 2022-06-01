#include "world.h"
#include <iostream>
#include <sstream>

void Game::copyGrid(std::vector<Cell>& v1, std::vector<Cell>& v2)  //Копирование вектора для смены поколения
{
    v2.clear();
    for (int i = 0; i < v1.size(); i++) 
    {
        v2.push_back(v1[i]);
    }
}

Game::Game()
{
    window.create(sf::VideoMode(this->WINDOW_SIZE, this->WINDOW_SIZE + 30), "Game of life");     //Создаем окно в видео моде с нужным размером
    window.setFramerateLimit(FPS);
    for (int i = 0; i < this->GRID_SIZE; i++) 
    {
        for (int j = 0; j < this->GRID_SIZE; j++)
        {
            Cell newCell(i, j, this->CELL_SIZE);    //Создаем все клетки на экране
            this->grid.push_back(newCell);      //Все клетки кладем в вектор
            this->gridCopy.push_back(newCell);
        }
    }
    isRunning = false;      //Изначально программа остановлена
}

Game::~Game() {}

int Game::getLivingNeighbors(int x, int y)      //Проверяем кол-во живых соседей
{
    int livingNeighbors = 0;
    if (x < GRID_SIZE - 1 && grid[y * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;  //Сосед справа
    if (x > 0 && grid[y * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;  //Сосед слева
    if (y < GRID_SIZE - 1 && grid[(y + 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;    //Сосед снизу
    if (y > 0 && grid[(y - 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;    //Сосед сверху
    if (y < GRID_SIZE - 1 && x < GRID_SIZE - 1 && grid[(y + 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;   //Сосед справа снизу
    if (y < GRID_SIZE - 1 && x > 0 && grid[(y + 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;   //Сосед слева снизу
    if (y > 0 && x < GRID_SIZE - 1 && grid[(y - 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;   //Сосед справа сверху
    if (y > 0 && x > 0 && grid[(y - 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;   //Сосед слева сверху

    return livingNeighbors;
}

void Game::run() 
{
    this->elapsedActivated = this->clockActivating.getElapsedTime();
    while (window.isOpen()) 
    {
        window.clear(sf::Color(220, 20, 60, 0));
        font.loadFromFile("arialmt.ttf");   
        std::ostringstream curr_generation;
        curr_generation << Generation;
        sf::Text text1("", font);
        text1.setString("Current generation: " + curr_generation.str());
        text1.setCharacterSize(20);
        text1.setPosition(10, 851);
        text1.setFillColor(sf::Color::Black);
        window.draw(text1);

        sf::Event event;
        this->elapsedActivated = this->clockActivating.getElapsedTime();
        elapsedStart = clockStart.getElapsedTime();

        while (window.pollEvent(event))     //Проверка на определенные действия
        {
            if (event.type == sf::Event::Closed)    //Проверка на закрытие окна
            {
                window.close();
            }
            else if (event.mouseButton.button == sf::Mouse::Left && !isRunning)     //Проверка на нажатие ЛКМ
            {
                if (event.mouseButton.y < WINDOW_SIZE && event.mouseButton.y > 1)
                {
                    int yCell = event.mouseButton.x / CELL_SIZE;
                    int xCell = event.mouseButton.y / CELL_SIZE;
                    grid[yCell * ROWS + xCell].update(this->window, this->clockActivating, this->elapsedActivated);     //Обновляет клетку, на которую нажали ЛКМ
                }
            }
            else if (event.type == sf::Event::KeyPressed)   //Проверка на нажатие клавиши
            {
                if (event.key.code == sf::Keyboard::Space)  //Проверка на нажатие Пробела
                {
                    if (isRunning)      //Ставит на паузу, если игра запущена, запускает игру, если игра на паузе
                    {
                        std::cout << "Игра остановлена!\n";
                        isRunning = !isRunning;
                        clockStart.restart();
                    }
                    else
                    {
                        std::cout << "Игра запущена!\n";
                        isRunning = !isRunning;
                        clockStart.restart();
                    }
                }
                if (event.key.code == sf::Keyboard::R && !isRunning)    //Проверка на нажатие клавиши R
                {
                    std::cout << "Вы очистили игровое поле!\n";
                    Generation = 1;
                    for (int i = 0; i < grid.size(); i++)   //С помощье цикла уничножаем все клетки
                    {
                        grid[i].kill();     
                    }
                }
                if (event.key.code == sf::Keyboard::W && !isRunning)    //Проверка на нажатие клавиши W
                {
                    copyGrid(grid, gridCopy);
                    for (int i = 0; i < grid.size(); i++)
                    {
                        int nb = getLivingNeighbors(grid[i].getY(), grid[i].getX());
                        bool lives = gridCopy[i].isAlive();
                        if (nb < 2) 
                        {
                            gridCopy[i].kill();
                        }
                        else if (nb > 3) 
                        {
                            gridCopy[i].kill();
                        }
                        else if (nb == 3)
                        {
                            gridCopy[i].ressurect();
                        }
                        
                    }
                    copyGrid(gridCopy, grid);     // Меняем поколение
                        Generation++;
                }
            }
        }
        if (isRunning)
        {
            sf::Text text2("", font);
            text2.setString("Game is running");
            text2.setCharacterSize(20);
            text2.setPosition(700, 851);
            text2.setStyle(sf::Text::Underlined);
            text2.setFillColor(sf::Color::Black);
            window.draw(text2);

            copyGrid(grid, gridCopy);
            for (int i = 0; i < grid.size(); i++) 
            {
                int nb = getLivingNeighbors(grid[i].getY(), grid[i].getX());
                bool lives = gridCopy[i].isAlive();
                if (elapsedStart.asSeconds() >= 0.1)    //Каждые 0.1 сек клетки погибают и возрождаются, зависит от кол-во соседей
                {
                    if (nb < 2) {
                        gridCopy[i].kill();
                    }
                    else if (nb > 3) {
                        gridCopy[i].kill();
                    }
                    else if (nb == 3) {
                        gridCopy[i].ressurect();
                    }
                    clockStart.restart();
                }
            }
            copyGrid(gridCopy, grid);     // Меняем поколение
            if (elapsedStart.asSeconds() >= 0.1)
            {
                Generation++;
            }
        }
        else
        {
            sf::Text text2("", font);
            text2.setString("Game on pause");
            text2.setCharacterSize(20);
            text2.setPosition(700, 851);
            text2.setStyle(sf::Text::Underlined);
            text2.setFillColor(sf::Color::Black);
            window.draw(text2);
        }
        for (int i = 0; i < grid.size(); i++) 
        {
            grid[i].draw(window);
        }
        window.display();
    }
}