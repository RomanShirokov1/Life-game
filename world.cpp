#include "world.h"
#include <iostream>
#include <sstream>

void Game::copyGrid(std::vector<Cell>& v1, std::vector<Cell>& v2)  //����������� ������� ��� ����� ���������
{
    v2.clear();
    for (int i = 0; i < v1.size(); i++) 
    {
        v2.push_back(v1[i]);
    }
}

Game::Game()
{
    window.create(sf::VideoMode(this->WINDOW_SIZE, this->WINDOW_SIZE + 30), "Game of life");     //������� ���� � ����� ���� � ������ ��������
    window.setFramerateLimit(FPS);
    for (int i = 0; i < this->GRID_SIZE; i++) 
    {
        for (int j = 0; j < this->GRID_SIZE; j++)
        {
            Cell newCell(i, j, this->CELL_SIZE);    //������� ��� ������ �� ������
            this->grid.push_back(newCell);      //��� ������ ������ � ������
            this->gridCopy.push_back(newCell);
        }
    }
    isRunning = false;      //���������� ��������� �����������
}

Game::~Game() {}

int Game::getLivingNeighbors(int x, int y)      //��������� ���-�� ����� �������
{
    int livingNeighbors = 0;
    if (x < GRID_SIZE - 1 && grid[y * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;  //����� ������
    if (x > 0 && grid[y * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;  //����� �����
    if (y < GRID_SIZE - 1 && grid[(y + 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;    //����� �����
    if (y > 0 && grid[(y - 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;    //����� ������
    if (y < GRID_SIZE - 1 && x < GRID_SIZE - 1 && grid[(y + 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;   //����� ������ �����
    if (y < GRID_SIZE - 1 && x > 0 && grid[(y + 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;   //����� ����� �����
    if (y > 0 && x < GRID_SIZE - 1 && grid[(y - 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;   //����� ������ ������
    if (y > 0 && x > 0 && grid[(y - 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;   //����� ����� ������

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

        while (window.pollEvent(event))     //�������� �� ������������ ��������
        {
            if (event.type == sf::Event::Closed)    //�������� �� �������� ����
            {
                window.close();
            }
            else if (event.mouseButton.button == sf::Mouse::Left && !isRunning)     //�������� �� ������� ���
            {
                if (event.mouseButton.y < WINDOW_SIZE && event.mouseButton.y > 1)
                {
                    int yCell = event.mouseButton.x / CELL_SIZE;
                    int xCell = event.mouseButton.y / CELL_SIZE;
                    grid[yCell * ROWS + xCell].update(this->window, this->clockActivating, this->elapsedActivated);     //��������� ������, �� ������� ������ ���
                }
            }
            else if (event.type == sf::Event::KeyPressed)   //�������� �� ������� �������
            {
                if (event.key.code == sf::Keyboard::Space)  //�������� �� ������� �������
                {
                    if (isRunning)      //������ �� �����, ���� ���� ��������, ��������� ����, ���� ���� �� �����
                    {
                        std::cout << "���� �����������!\n";
                        isRunning = !isRunning;
                        clockStart.restart();
                    }
                    else
                    {
                        std::cout << "���� ��������!\n";
                        isRunning = !isRunning;
                        clockStart.restart();
                    }
                }
                if (event.key.code == sf::Keyboard::R && !isRunning)    //�������� �� ������� ������� R
                {
                    std::cout << "�� �������� ������� ����!\n";
                    Generation = 1;
                    for (int i = 0; i < grid.size(); i++)   //� ������� ����� ���������� ��� ������
                    {
                        grid[i].kill();     
                    }
                }
                if (event.key.code == sf::Keyboard::W && !isRunning)    //�������� �� ������� ������� W
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
                    copyGrid(gridCopy, grid);     // ������ ���������
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
                if (elapsedStart.asSeconds() >= 0.1)    //������ 0.1 ��� ������ �������� � ������������, ������� �� ���-�� �������
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
            copyGrid(gridCopy, grid);     // ������ ���������
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