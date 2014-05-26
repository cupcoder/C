// birdyflap.cpp: ���������� ����� ����� ��� ����������� ����������.
// ���������� ����������

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>		// Debug
#include <vector>		// Really need for vectors
#include <fstream>		// For work with data.ini
#include <windows.h>	// For window

int distanceView = 4;									// ��������� ���������� (���������� ������)
std::vector<sf::RectangleShape*> pipes;					// �������������� ������ � �������
int lastGate = 0;										// ���������� ���������� �����
int levelGate = 150;									// ������� ��������� (������� ����� ��� ��������� ������). ������ -- �������.
int levelGateWidth = 200;								// ������ �����. ������ -- �������.
int levelPipeDistance = 350;							// ���������� ����� �������. ������ -- �������.
int freeRun = 1100;										// ������� ��� ������.
int speed = 8;											// �������� �������� ����
int itr = 0;											// ���������� �������� ��������� �����
int pipeCount = 0;										// ������� ���� ��� �����������
sf::RectangleShape playerObj(sf::Vector2f(70, 56));		// ������ ������
int g = 6;												// �������������� ����������
int t = 0;												// ����� ��� �������� �������� �������
int v = 0;												// �������� ���������
int ctrScore = 0;										// ����
int bestScore;											// ����������, ��� ��������� ������� ����� �� ����� data.ini
int cross = -1;											// ����� ������������� ����� (����� ��� ���������� �����)
int rotateNum = 0;										// ���������� ���������� �� ����� ��������
int groundMove = 0;										// ����������� �������
int game = 0;											// ���������
int swing = 0;											// ����� �����
int goTime = 40;										// �������� ����� ������������� ������� Game Over � ���������� ����
int buffer;												// ������ ��� ������ � ������

// ������� ��� �������� ����� �� ������� (��� ������)

bool MouseTrigger(sf::RectangleShape &av_Sprite, sf::RenderWindow &av_Window)
{

	int mouseX = sf::Mouse::getPosition().x;
	int mouseY = sf::Mouse::getPosition().y;

	sf::Vector2i windowPosition = av_Window.getPosition();

	if (mouseX > av_Sprite.getPosition().x + windowPosition.x && mouseX < (av_Sprite.getPosition().x + av_Sprite.getGlobalBounds().width + windowPosition.x)
		&& mouseY > av_Sprite.getPosition().y + windowPosition.y + 30 && mouseY < (av_Sprite.getPosition().y + av_Sprite.getGlobalBounds().height + windowPosition.y + 30))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return true;
		}
		return false;
	}

	return false;

}

// �������� � �����

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
sf::Texture Getready;
sf::Texture Hint;
sf::Texture Start;
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
sf::RectangleShape getready(sf::Vector2f(250, 75));
sf::RectangleShape hint(sf::Vector2f(200, 200));
sf::RectangleShape start(sf::Vector2f(200, 65));

// ����� ��� ������ � �������

class pipe
{
public:
	int start, gate, window;
public:
	void drawPipes(sf::RenderWindow &window)
	{
		for (int i = 0; i < distanceView; i++) {
			// ���������� ��������� ����� ��� �������� �����
			lastGate = -rand() % levelGate;
			// �������� ����� � ������ ��� ������ ����� � ������ ��� � ������
			pipes.push_back(new sf::RectangleShape(sf::Vector2f(90, 300)));
			// ������ ������� ��� ����� �����
			pipes[pipes.size() - 1]->setPosition(freeRun + i * levelPipeDistance, lastGate);
			pipes[pipes.size() - 1]->setTexture(&pipeUp);
			// ������������ ������ ��� ��������� ����
			window.draw(*pipes[pipes.size() - 1], sf::RenderStates());

			// ���� ����� ����������� � ������ ������
			pipes.push_back(new sf::RectangleShape(sf::Vector2f(90, 400)));
			pipes[pipes.size() - 1]->setPosition(freeRun + i * levelPipeDistance, lastGate + levelGateWidth + 300);
			pipes[pipes.size() - 1]->setTexture(&pipeDown);
			window.draw(*pipes[pipes.size() - 1], sf::RenderStates());
		}
	}
	void update(sf::RenderWindow &window, int &game)
	{
		for (int i = 0; i < pipes.size() - 1 / 2; i++) {
			if (game == 1) // ���� ����, �� ������� �����
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
		// ���������� ��������� �������� ����� �� y
		lastGate = -rand() % levelGate;
		// ���� ��� ��������� ��� �������� �������, �� ���������� �� ������� ��� ����, ����� �������� ������ ����������
		if (pipeCount == distanceView * 2 - 2) {
			// ���������� ������� ���� �� ��� x
			pipes[pipes.size() - 2]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);

			// ��� - �� ������ �� �� ������ + ��������� ����� ������� �� �� ��� - �� - 1 ��������� � - 45 (magic!)

			// ���������� ������� ���� �� ��� y
			pipes[pipes.size() - 2]->setPosition(pipes[pipes.size() - 2]->getPosition().x, lastGate);
			// ���������� ������ ���� �� ��� x
			pipes[pipes.size() - 1]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			// ���������� ������� ���� �� ��� y
			pipes[pipes.size() - 1]->setPosition(pipes[pipes.size() - 1]->getPosition().x, lastGate + levelGateWidth + 300);
			pipeCount = 0;
		}
		else {
			// ������� ������� ���� (������� � ������ ��� �����)
			pipes[pipeCount]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			pipes[pipeCount]->setPosition(pipes[pipeCount]->getPosition().x, lastGate);
			pipes[pipeCount + 1]->move(distanceView * 90 + levelPipeDistance*distanceView - levelPipeDistance - 45, 0);
			pipes[pipeCount + 1]->setPosition(pipes[pipeCount + 1]->getPosition().x, lastGate + levelGateWidth + 300);
			pipeCount = pipeCount + 2;
		}
	}
};

// ����� ��� ������ �������

class player
{
public:
	int start, gate, window;
public:
	void drawPlayer(sf::RenderWindow &window)
	{	
		playerObj.setPosition(200, 400);
		playerObj.setTexture(&bird, true);
		window.draw(playerObj, sf::RenderStates());
	}
	void gravity(sf::RenderWindow &window,int &game)
	{
		//std::cout << game << '\n';
		v = v + g * t; // ������� ��� ���������� �������� ����� ���������
		if (goTime < 30) {
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
		}
		if (game != -1) {
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
	void up(int &game)
	{
		if (playerObj.getPosition().y > 10 && game == 1) { // ���� ���� 
			t = 0;
			v = -250;
		}
	}
};

// utils

class utils
{
public:
	void drawScore(sf::RenderWindow &window)
	{
		score.setString(std::to_string(ctrScore));
		score.setFont(font);
		score.setColor(sf::Color(255,255,255));
		score.setCharacterSize(64);
		score.setStyle(sf::Text::Bold);

		// ������������ ����������
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
	void updateGround(sf::RenderWindow &window, int &game)
	{
		if (groundMove > 2) {
			ground.setPosition(0, 535);
			groundMove = 0;
		}
		if (game != -1) {
			groundMove++;
			ground.move(-speed, 0);
		}
			window.draw(ground, sf::RenderStates());
	}
	void gameOver(sf::RenderWindow &window, int &game)
	{
		game = -1;
		goTime++;
		if (goTime > 30) {
			
			// ������� "Game Over"
			gameover.setTexture(&GameOver);
			gameover.setPosition(275, 60);

			// �������� ������ ��� ����
			menu.setTexture(&Menu);
			menu.setPosition(200, 170);
			
			// ������ �������
			restart.setTexture(&Restart);
			restart.setPosition(300, 400);

			// ��������
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

			// ������������ ����������
			if (ctrScore < 9)
				score.setPosition(540, 230);
			if (ctrScore >= 10 && ctrScore < 100)
				score.setPosition(525, 230);
			if (ctrScore > 100)
				score.setPosition(510, 230);

			best.setString(std::to_string(bestScore));
			best.setFont(font);
			best.setColor(sf::Color(255, 255, 255));
			best.setCharacterSize(32);
			best.setStyle(sf::Text::Bold);

			// ������������ ����������
			if (bestScore < 9)
				best.setPosition(540, 300);
			if (bestScore >= 10 && ctrScore < 100)
				best.setPosition(525, 300);
			if (bestScore >= 100)
				best.setPosition(505, 300);

			// ����� ������
			newrecord.setTexture(&Newrecord);
			newrecord.setPosition(445, 275);

			// ������������ ��� ���
			window.draw(menu, sf::RenderStates());
			window.draw(gameover, sf::RenderStates());
			window.draw(restart, sf::RenderStates());
			if (ctrScore >= 10 && ctrScore < 20)
				window.draw(medal_b, sf::RenderStates());
			if (ctrScore >= 20 && ctrScore < 30)
				window.draw(medal_s, sf::RenderStates());
			if (ctrScore >= 30 && ctrScore < 40)
				window.draw(medal_g, sf::RenderStates());
			if (ctrScore >= 40)
				window.draw(medal_p, sf::RenderStates());
			window.draw(score, sf::RenderStates());
			window.draw(best, sf::RenderStates());
			if (ctrScore >= bestScore) {
				window.draw(newrecord, sf::RenderStates());
				
				std::ofstream fout("data.ini", std::ios_base::out | std::ios_base::trunc);
				fout << ctrScore;
				fout.close();
				bestScore = ctrScore;
			}
		}

	}

	void gameStart(sf::RenderWindow &window, int &game) {
		game = 0;
		getready.setTexture(&Getready);
		getready.setPosition(270, 135);
		
		hint.setTexture(&Hint);
		hint.setPosition(300, 220);

		start.setTexture(&Start);
		start.setPosition(300, 450);

		window.draw(hint, sf::RenderStates());
		window.draw(getready, sf::RenderStates());
		window.draw(start, sf::RenderStates());

		playerObj.setPosition(200, 300);
		playerObj.setRotation(0);
	}

	void realStart(sf::RenderWindow &window, int &game, int &ctrScore, int &goTime, int &v, int &t, int &lastGate, int &itr, int &pipeCount, int &rotateNum, int &groundMove, int &swing, int &bestScore) {
		game = 1;
		pipes.clear();
		ctrScore = 0;
		goTime = 0;
		v = 0;
		t = 0;
		itr = 0;
		pipeCount = 0;
		rotateNum = 0;
		groundMove = 0;
		swing = 0;
		
		std::ifstream fin("data.ini");
		fin >> buffer;
		fin.close();

		bestScore = buffer;

		//std::cout << bestScore << '\n';
		//AllPipes.drawPipes(window);
	}

};


// ������� ������� ������� ���� � �����
pipe AllPipes;
player Player;
utils Utils;

// �������� �������
int _tmain(int argc, _TCHAR* argv[])
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	if (!bird_d.loadFromFile("res/textures/bird-d.png"))
	{
		std::cout << "pic!!";
	}
	if (!bird.loadFromFile("res/textures/bird.png"))
	{
		std::cout << "pic!!";
	}
	if (!bird_u.loadFromFile("res/textures/bird-u.png"))
	{
		std::cout << "pic!!";
	}

	if (!font.loadFromFile("res/fonts/04B_19__.ttf"))
	{
		std::cout << "font!!";
	}
	if (!pipeUp.loadFromFile("res/textures/pipeUp.png"))
	{
		std::cout << "font!!";
	}
	if (!pipeDown.loadFromFile("res/textures/pipeDown.png"))
	{
		std::cout << "font!!";
	}
	if (!background.loadFromFile("res/textures/background.png"))
		return -1;

	if (!Ground.loadFromFile("res/textures/ground.png"))
		return -1;
	
	if (!Menu.loadFromFile("res/textures/menu_bg.png"))
		return -1;
	
	if (!GameOver.loadFromFile("res/textures/gameOver.png"))
		return -1;

	if (!Restart.loadFromFile("res/textures/restart.png"))
		return -1;
	
	if (!Medal_b.loadFromFile("res/textures/medal-b.png"))
		return -1;

	if (!Medal_s.loadFromFile("res/textures/medal-s.png"))
		return -1;

	if (!Medal_g.loadFromFile("res/textures/medal-g.png"))
		return -1;

	if (!Medal_p.loadFromFile("res/textures/medal-p.png"))
		return -1;

	if (!Newrecord.loadFromFile("res/textures/newrecord.png"))
		return -1;

	if (!Getready.loadFromFile("res/textures/getready.png"))
		return -1;

	if (!Hint.loadFromFile("res/textures/hint.png"))
		return -1;

	if (!Start.loadFromFile("res/textures/start.png"))
		return -1;
	// ������� ������ ��� ������ �� �����
	std::ifstream fin("data.ini");
	fin >> buffer;
	fin.close();
	bestScore = buffer;

	//std::cout << bestScore << '\n';


	//04B_19__
	// �������������� ����
	sf::RenderWindow window(sf::VideoMode(800, 600), "Birdy Flap");
	window.setFramerateLimit(30); // ������������ FPS
	// ������� ������
	sf::Clock clock;

	// ��������� ��� ����� � ������ �� �����
	AllPipes.drawPipes(window);
	Player.drawPlayer(window);
	Utils.drawScore(window);
	Utils.drawGround(window);
	if (game == 0) {
		Utils.gameStart(window, game);
	}
	window.display();
	
	while (window.isOpen())
	{
		sf::Time elapsed = clock.getElapsedTime();
		//std::cout << elapsed.asMicroseconds() << '\n';
		clock.restart();
		sf::Event event;
		if (game == 1 && pipes.size() == 0)
		AllPipes.drawPipes(window);

		while (window.pollEvent(event))
		{
			if ((((sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseTrigger(start, window)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) && game == 0)
			{
				std::cout << game << "\n";
				//if ((MouseTrigger(start, window) || sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) && game != 1)
				Utils.realStart(window, game, ctrScore, goTime, v, t, lastGate, itr, pipeCount, rotateNum, groundMove, swing, bestScore);
			}

			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				Player.up(game);

			if ((((sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseTrigger(restart, window)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) && game == -1 && goTime >= 30)
			{
					Utils.gameStart(window, game);
			}
		}
		
		// ������������ ���������� ����� �� ������ � �����
		if (pipes[pipeCount]->getPosition().x + 90 < 0) {
			AllPipes.transition();
		}

		//std::cout << game << std::endl;
		
		// ���������� � ���� �����
		window.clear();
		Utils.drawBackground(window);
		if (game == 1 || game == -1)
		AllPipes.update(window,game); // �����
		Player.gravity(window,game);
		Utils.updateGround(window,game);
		if (goTime < 30) 
			Utils.drawScore(window);
		if (game == -1)
			Utils.gameOver(window,game);
		if (game == 0) {
			Utils.gameStart(window, game);
		}
		window.display();
		
		// ��������� �������� � ��������
		itr++;
	}
		return 0;
}

