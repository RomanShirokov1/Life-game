#include <iostream>
#include <SFML/Graphics.hpp>
#include "world.h"

int main() 
{
	setlocale(LC_ALL, "RUS");
	std::cout << "����� ���������� � ���� �����!\n\n";
	std::cout << "������� ����: \n1) ����� ������, ������� �� ����� ����� ����� �������, �������� �� �����������.\n2) ����� ������, ������� 4 ��� ������ ����� �������, �������� �� �������������.\n";
	std::cout << "3) ̸����� ������ � ����� ������ �������� ������������.\n4) �� ���� ������ ������� ��������� ������ �� ����������.\n\n";
	std::cout << "����������:\n��������� ���, ����� �������/����� ������.\n" << "������� Space, ����� ���������/��������� �� ����� ����.\n";
	std::cout << "������� �� R, ����� �������� ����(����� ��� ������).\n";
	std::cout << "������� �� W, ����� ������� ����� 1 ��������� (������� ��� ������).\n";
	Game new_game;
	new_game.run();
	return 0;
}