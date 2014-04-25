// birdyflap.cpp: определяет точку входа для консольного приложения.
// Подключаем библиотеки

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> // Debug
#include <vector>	// Really need for vectors
#include <fstream>	// For work with data.txt

int distanceView = 4;									// Дальность прорисовки (количество пайпов)
std::vector<sf::RectangleShape*> pipes;					// Инициализируем массив с пайпами
int lastGate = 0;										// Координата последнего гейта
int levelGate = 150;									// Уровень сложности (рандома между при генерации гейтов). Больше -- сложнее.
int levelGateWidth = 200;								// Ширина гейта. Меньше -- сложнее.
int levelPipeDistance = 350;							// Расстояние между пайпами. Меньше -- сложнее.
int freeRun = 1100;										// Отрезок без пайпов.
int speed = 8;											// Условная скорость игры
int itr = 0;											// Количество итераций основного цикла
int pipeCount = 0;										// Текущий пайп для перемещения
sf::RectangleShape playerObj(sf::Vector2f(70, 56));		// Объект игрока
int g = 6;												// Гравитационная постоянная
int t = 0;												// Время для рассчета скорости падения
int v = 0;												// Скорость начальная
int ctrScore = 102;										// Счет
int bestScore = 305;																												////////////////////////////////////   ЧТЕНИЕ ИЗ 
int playerDistance = 0;									// Дистанция, пройденная игроком
int cross = -1;											// Номер пересекаемого пайпа (нужен для инкремента счета)
int rotateNum = 0;										// Переменная отвечающая за лимит вращения
int groundMove = 0;										// Перемещение граунда
int game = 1;											// Состояние
int swing = 0;											// Взмах крыла
int goTime = 0;											// Интервал между срабатыванием события Game Over и появлением меню

// Текстуры
sf::Texture bird;
sf::Texture bird_d;
sf::Texture bird_u;
sf::Texture pipeUp;
sf::Texture pipeDown;
sf::Font font;
sf::Text score;
sf::Text best;
sf::Texture background;
sf::Texture Ground;
sf::Texture Menu;
sf::Texture GameOver;
sf::Texture Restart;
sf::Texture Medal_b;
sf::Texture Medal_s;
sf::Texture Medal_g;
sf::Texture Medal_p;
sf::Texture Newrecord;
sf::RectangleShape bg(sf::Vector2f(800, 600));
sf::RectangleShape ground(sf::Vector2f(994, 112));
sf::RectangleShape menu(sf::Vector2f(400, 204));
sf::RectangleShape gameover(sf::Vector2f(250, 75));
sf::RectangleShape restart(sf::Vector2f(200, 65));
sf::RectangleShape medal_b(sf::Vector2f(75, 75));
sf::RectangleShape medal_s(sf::Vector2f(75, 75));
sf::RectangleShape medal_g(sf::Vector2f(75, 75));
sf::RectangleShape medal_p(sf::Vector2f(75, 75));
sf::RectangleShape newrecord(sf::Vector2f(50, 20));

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
		for (int i = 0; i < pipes.size() - 1 / 2; i++) {
			if (game == 1) // Если игра, то двигаем пайпы
				pipes[i]->move(-speed, 0);

			window.draw(*pipes[i], sf::RenderStates());

			if (playerObj.getGlobalBounds().left + playerObj.getGlobalBounds().width - pipes[i]->getGlobalBounds().left < 15 && playerObj.getGlobalBounds().left + playerObj.getGlobalBounds().width - pipes[i]->getGlobalBounds().left > -15)
				cross = i;

			if (cross != -1 && playerObj.getGlobalBounds().left > pipes[cross]->getGlobalBounds().left) {
				cross = -1;
				ctrScore++;
			}
			if (playerObj.getGlobalBounds().intersects(pipes[i]->getGlobalBounds()) || playerObj.getGlobalBounds().intersects(ground.getGlobalBounds())) {
				game = -1;

			}
			if (playerObj.getGlobalBounds().intersects(pipes[i]->getGlobalBounds()) && playerObj.getPosition().x < pipes[i]->getGlobalBounds().left)
				playerObj.setPosition(pipes[i]->getGlobalBounds().left-60, playerObj.getPosition().y);
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
		if (playerObj.getPosition().y < 485) {
			playerObj.move(0, v*0.03);
		}
		else {
			playerObj.setPosition(playerObj.getPosition().x, 485);
		}
		if (v < 0 && rotateNum > -8) {
			playerObj.rotate(-1);
			rotateNum--;
		}
		if (v == 0)
			rotateNum = 0;
		if (v > 0 && rotateNum < 8) {
			playerObj.rotate(1);
			rotateNum++;
		}
		if (game == 1) {
			swing++;
		} else {
			swing = 13;
		}
		
		if (swing < 5) {
			playerObj.setTexture(&bird_d, true);
		}
		if (swing >= 5 && swing <= 10) {
			playerObj.setTexture(&bird, true);
		}
		if (swing > 10) {
			playerObj.setTexture(&bird_u, true);
		}
		
		if (swing > 15)
			swing = 0;
		
		//std::cout << playerObj.getRotation() << '\n';

		window.draw(playerObj, sf::RenderStates());
		t++;
	}
	void up()
	{
		if (playerObj.getPosition().y > 10 && game == 1) { // Если игра 
			t = 0;
			v = -250;
		}
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

		// Выравнивание результата
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
		ground.setPosition(0, 535);
		window.draw(ground, sf::RenderStates());
	}
	void updateGround(sf::RenderWindow &window)
	{
		if (groundMove > 2) {
			ground.setPosition(0, 535);
			groundMove = 0;
		}
		if (game == 1) {
			groundMove++;
			ground.move(-speed, 0);
		}
			window.draw(ground, sf::RenderStates());
	}
	void gameOver(sf::RenderWindow &window)
	{
		game = -1;
		goTime++;
		if (goTime > 30) {
			
			// Надпись "Game Over"
			gameover.setTexture(&GameOver);
			gameover.setPosition(275, 60);

			// Основная плашка под меню
			menu.setTexture(&Menu);
			menu.setPosition(200, 170);
			
			// Кнопка рестарт
			restart.setTexture(&Restart);
			restart.setPosition(300, 400);

			// Медальки
			medal_b.setTexture(&Medal_b);
			medal_b.setPosition(247, 245);
			medal_s.setTexture(&Medal_s);
			medal_s.setPosition(247, 245);
			medal_g.setTexture(&Medal_g);
			medal_g.setPosition(247, 245);
			medal_p.setTexture(&Medal_p);
			medal_p.setPosition(247, 245);

			score.setString(std::to_string(ctrScore));
			score.setFont(font);
			score.setColor(sf::Color(255, 255, 255));
			score.setCharacterSize(32);
			score.setStyle(sf::Text::Bold);

			// Выравнивание результата
			if (ctrScore < 9)
				score.setPosition(540, 230);
			if (ctrScore > 10 && ctrScore < 100)
				score.setPosition(525, 230);
			if (ctrScore > 100)
				score.setPosition(510, 230);

			best.setString(std::to_string(bestScore));
			best.setFont(font);
			best.setColor(sf::Color(255, 255, 255));
			best.setCharacterSize(32);
			best.setStyle(sf::Text::Bold);

			// Выравнивание результата
			if (bestScore < 9)
				best.setPosition(540, 300);
			if (bestScore > 10 && ctrScore < 100)
				best.setPosition(525, 300);
			if (bestScore > 100)
				best.setPosition(505, 300);

			// Новый рекорд
			newrecord.setTexture(&Newrecord);
			newrecord.setPosition(445, 275);

			// Отрисовываем все это
			window.draw(menu, sf::RenderStates());
			window.draw(gameover, sf::RenderStates());
			window.draw(restart, sf::RenderStates());
			if (ctrScore < 10)
				window.draw(medal_b, sf::RenderStates());
			if (ctrScore >= 10 && ctrScore <= 20)
				window.draw(medal_s, sf::RenderStates());
			if (ctrScore > 20 && ctrScore < 30)
				window.draw(medal_g, sf::RenderStates());
			if (ctrScore >= 30)
				window.draw(medal_p, sf::RenderStates());
			window.draw(score, sf::RenderStates());
			window.draw(best, sf::RenderStates());
			if (ctrScore > bestScore)
			window.draw(newrecord, sf::RenderStates());


			////////////////////////////////////   ЗАПИСЬ В ФАЙЛ \\\\\\\\\\\\\\\\\\\\\\\\\\\\

		}

	}

};


// Создаем объекты классов пайп и игрок
pipe AllPipes;
player Player;
utils Utils;

// Основная функция
int _tmain(int argc, _TCHAR* argv[])
{
		if (!bird_d.loadFromFile("bird-d.png"))
		{
			std::cout << "pic!!";
		}
		if (!bird.loadFromFile("bird.png"))
		{
			std::cout << "pic!!";
		}
		if (!bird_u.loadFromFile("bird-u.png"))
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
	
	if (!Menu.loadFromFile("menu_bg.png"))
		return -1;
	
	if (!GameOver.loadFromFile("gameOver.png"))
		return -1;

	if (!Restart.loadFromFile("restart.png"))
		return -1;
	
	if (!Medal_b.loadFromFile("medal-b.png"))
		return -1;

	if (!Medal_s.loadFromFile("medal-s.png"))
		return -1;

	if (!Medal_g.loadFromFile("medal-g.png"))
		return -1;

	if (!Medal_p.loadFromFile("medal-p.png"))
		return -1;

	if (!Newrecord.loadFromFile("newrecord.png"))
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
		 
		//std::cout << swing << std::endl;
		
		// Обновление в этом кадре
		window.clear();
		Utils.drawBackground(window);
		AllPipes.update(window); // пайпы
		Player.gravity(window);
		Utils.updateGround(window);
		if (goTime < 30) 
			Utils.drawScore(window);
		if (game == -1)
			Utils.gameOver(window);
		window.display();
		
		// Добавляем итерацию к счетчику
		itr++;
	}
		return 0;
}

