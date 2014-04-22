// birdyflap.cpp: определяет точку входа для консольного приложения.
// Подключаем библиотеки

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> // Debug
#include <vector>	// Really need for vectors

int distanceView = 4;									// Дальность прорисовки (количество пайпов)
std::vector<sf::RectangleShape*> pipes;					// Инициализируем массив с пайпами
int lastGate = 0;										// Координата последнего гейта
int levelGate = 150;									// Уровень сложности (рандома между при генерации гейтов). Больше -- сложнее.
int levelGateWidth = 200;								// Ширина гейта. Меньше -- сложнее.
int levelPipeDistance = 350;							// Расстояние между пайпами. Меньше -- сложнее.
int freeRun = 1400;										// Отрезок без пайпов.
int speed = 8;											// Условная скорость игры
int itr = 0;											// Количество итераций основного цикла
int pipeCount = 0;										// Текущий пайп для перемещения
sf::RectangleShape playerObj(sf::Vector2f(70, 56));		// Объект игрока
int g = 6;												// Гравитационная постоянная
int t = 0;												// Время для рассчета скорости падения
int v = 0;												// Скорость начальная
int ctrScore = 0;										// Счет
int playerDistance = 0;									// Дистанция, пройденная игроком
int cross = -1;											// Номер пересекаемого пайпа (нужен для инкремента счета)
int rotateNum = 0;										// Переменная отвечающая за лимит вращения
int groundMove = 0;

// Текстуры
sf::Texture bird;
sf::Texture pipeUp;
sf::Texture pipeDown;
sf::Font font;
sf::Text score;
sf::Texture background;
sf::Texture Ground;
sf::RectangleShape bg(sf::Vector2f(800, 600));
sf::RectangleShape ground(sf::Vector2f(994, 112));

// Класс для работы с пайпами

class pipe
{
public:
	int start, gate, window;
public:
	void drawPipes(sf::RenderWindow &window)
	{
		for (int i = 0; i < distanceView; i++) {
			// Генерируем рандомное число для смещения пайпа
			lastGate = -rand() % levelGate;
			// Выделяем место в памяти для нового пайпа и калдем его в вектор
			pipes.push_back(new sf::RectangleShape(sf::Vector2f(90, 300)));
			// Задаем позицию для этого пайпа
			pipes[pipes.size() - 1]->setPosition(freeRun + i * levelPipeDistance, lastGate);
			pipes[pipes.size() - 1]->setTexture(&pipeUp);
			// Отрисовываем только что созданный пайп
			window.draw(*pipes[pipes.size() - 1], sf::RenderStates());

			// Тоже самое проделываем с нижним пайпом
			pipes.push_back(new sf::RectangleShape(sf::Vector2f(90, 400)));
			pipes[pipes.size() - 1]->setPosition(freeRun + i * levelPipeDistance, lastGate + levelGateWidth + 300);
			pipes[pipes.size() - 1]->setTexture(&pipeDown);
			window.draw(*pipes[pipes.size() - 1], sf::RenderStates());
		}
	}
	void update(sf::RenderWindow &window)
	{
		for (int i = 0; i < pipes.size()-1/2; i++) {
			pipes[i]->move(-speed, 0);
			window.draw(*pipes[i], sf::RenderStates());

			if (playerObj.getGlobalBounds().left + playerObj.getGlobalBounds().width - pipes[i]->getGlobalBounds().left < 15 && playerObj.getGlobalBounds().left + playerObj.getGlobalBounds().width - pipes[i]->getGlobalBounds().left > -15)
				cross = i;	

			if (cross != -1 && playerObj.getGlobalBounds().left > pipes[cross]->getGlobalBounds().left) {
				cross = -1;
				ctrScore++;
			}
			if (playerObj.getGlobalBounds().intersects(pipes[i]->getGlobalBounds()) || playerObj.getGlobalBounds().intersects(ground.getGlobalBounds()))
				std::cout << "traaaaaaaaaaaap" << std::endl;
		}
	}
	void transition()
	{
		// Генерируем рандомное смещение пайпа по y
		lastGate = -rand() % levelGate;
		// Если это последние два элемента вектора, то перебираем их вручную для того, чтобы избежать ошибки индексации
		if (pipeCount == distanceView * 2 - 2) {
			// Перемещаем верхний пайп по оси x
			pipes[pipes.size() - 2]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);

			// кол - во пайпов на их ширину + дистанция между пайпами на их кол - во - 1 дистанция и - 45 (magic!)

			// Перемещаем верхний пайп по оси y
			pipes[pipes.size() - 2]->setPosition(pipes[pipes.size() - 2]->getPosition().x, lastGate);
			// Перемещаем нижний пайп по оси x
			pipes[pipes.size() - 1]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			// Перемещаем верхний пайп по оси y
			pipes[pipes.size() - 1]->setPosition(pipes[pipes.size() - 1]->getPosition().x, lastGate + levelGateWidth + 300);
			pipeCount = 0;
		}
		else {
			// Двигаем текущий пайп (верхнюю и нижнюю его части)
			pipes[pipeCount]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			pipes[pipeCount]->setPosition(pipes[pipeCount]->getPosition().x, lastGate);
			pipes[pipeCount + 1]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			pipes[pipeCount + 1]->setPosition(pipes[pipeCount + 1]->getPosition().x, lastGate + levelGateWidth + 300);
			pipeCount = pipeCount + 2;
		}
	}
};

// Класс для работы игроком

class player
{
public:
	int start, gate, window;
public:
	void drawPlayer(sf::RenderWindow &window)
	{	
		playerObj.setPosition(200, 200);
		playerObj.setTexture(&bird, true);
		window.draw(playerObj, sf::RenderStates());
	}
	void gravity(sf::RenderWindow &window)
	{
		v = v + g * t; // Формула для нахождения скорости через ускорение
		playerObj.move(0,v*0.03);

		if (v < 0 && rotateNum > -5) {
			playerObj.rotate(-5);
			rotateNum--;
		}
		if (v == 0)
			rotateNum = 0;
		if (v > 0 && rotateNum < 30) {
			playerObj.rotate(5);
			rotateNum++;
		}

		//std::cout << playerObj.getRotation() << '\n';

		window.draw(playerObj, sf::RenderStates());
		t++;
	}
	void up()
	{	
		t = 0;
		v = -250;
	}
};

// utils

class utils
{
public:
	int start, gate, window;
public:
	void drawScore(sf::RenderWindow &window)
	{
		score.setString(std::to_string(ctrScore));
		score.setFont(font);
		score.setColor(sf::Color(255,255,255));
		score.setCharacterSize(64);
		score.setStyle(sf::Text::Bold);

		if (ctrScore < 9)
			score.setPosition(385, 30);
		if (ctrScore > 10 && ctrScore < 100)
			score.setPosition(375, 30);
		if (ctrScore > 10 && ctrScore < 100)
			score.setPosition(365, 30);
		if (ctrScore > 100)
			score.setPosition(345, 30);

		window.draw(score, sf::RenderStates());
	}
	void drawBackground(sf::RenderWindow &window)
	{
		bg.setTexture(&background);
		window.draw(bg, sf::RenderStates());
	}
	void drawGround(sf::RenderWindow &window)
	{
		ground.setTexture(&Ground);
		ground.setPosition(0, 525);
		window.draw(ground, sf::RenderStates());
	}
	void updateGround(sf::RenderWindow &window)
	{
		if (groundMove > 10) {
			ground.setPosition(0, 525);
			groundMove = 0;
		}
		groundMove++;
		ground.move(-speed, 0);
		window.draw(ground, sf::RenderStates());
	}
};


// Создаем объекты классов пайп и игрок
pipe AllPipes;
player Player;
utils Utils;

// Основная функция
int _tmain(int argc, _TCHAR* argv[])
{

	if (!bird.loadFromFile("bird.png"))
	{
		std::cout << "pic!!";
	}
	if (!font.loadFromFile("04B_19__.ttf"))
	{
		std::cout << "font!!";
	}
	if (!pipeUp.loadFromFile("pipeUp.png"))
	{
		std::cout << "font!!";
	}
	if (!pipeDown.loadFromFile("pipeDown.png"))
	{
		std::cout << "font!!";
	}
	if (!background.loadFromFile("background.png"))
		return -1;

	if (!Ground.loadFromFile("ground.png"))
		return -1;
	//04B_19__
	// Инициализируем окно
	sf::RenderWindow window(sf::VideoMode(800, 600), "Birdy Flap");
	window.setFramerateLimit(30); // Ограничиваем FPS
	// Создаем таймер
	sf::Clock clock;

	// Добавляем все пайпы и игрока на карту
	AllPipes.drawPipes(window);
	Player.drawPlayer(window);
	Utils.drawScore(window);
	Utils.drawGround(window);
	window.display();
	
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		//std::cout << elapsed.asMicroseconds() << '\n';
		clock.restart();
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::Space)
				Player.up();
		}
		
		// Периодически перемещаем пайпы из начала в конец
		if (pipes[pipeCount]->getPosition().x + 90 < 0) {
			AllPipes.transition();
		}
		 
		//std::cout << rotateNum << std::endl;
		
		// Обновление в этом кадре
		window.clear();
		Utils.drawBackground(window);
		AllPipes.update(window); // пайпы
		Utils.updateGround(window);
		Player.gravity(window);
		Utils.drawScore(window);
		window.display();
		
		// Добавляем итерацию к счетчику
		itr++;
	}
		return 0;
}

