#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
using namespace sf;

int width = 30;
int height = 30;
int sizeo = 20;
int w = width * sizeo;
int h = height * sizeo;

float delay = 0.100;
float fdelay = 5;

bool hardmode = false; //hardmode
bool wallj = false;
bool snakeeattail = true;

bool admin = false; //devmod

int score = 0;

int dir = 0, numb = 1;

bool gameOver = false;

struct Snake {
	int x, y;
} s[900];

struct Fruit
{
	int x = rand() % width, y = rand() % height;
} f;

void Fruit()
{
	//speed
	if (hardmode == true)
	{
		delay -= 0.001;
	}

	bool newFruit = false;

	int fx, fy;

	fx = rand() % width;
	fy = rand() % height;

	for (int i = 0; i <= numb; i++)
	{
		if ((s[i].x == fx) && (s[i].y == fy))
		{
			newFruit = true;
		}
		else;
	}

	if (newFruit == false)
	{
		f.x = fx;
		f.y = fy;
	}
	else Fruit();
}

void Tick()
{
	//queue
	s[numb + 1].x = -10;
	s[numb + 1].y = -10;

	for (int i = numb; i > 0; i--)
	{
		//tail
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;

		//fruit ++
		if ((s[1].x == f.x) && (s[1].y == f.y))
		{
			Fruit();
			numb++;
			score = numb - 1;
			system("cls");
			cout << "Score: " << score;
			if (score == 800)
			{
				system("cls");
				cout << "You won!" << endl;
				system("pause");
			}
		}

		//tail colision
		if ((s[i + 1].x == s[0].x) && (s[i + 1].y == s[0].y) && snakeeattail == false) gameOver = true;
		else if ((s[i + 1].x == s[0].x) && (s[i + 1].y == s[0].y) && snakeeattail == true)
		{
			numb = i;
			if (hardmode == true)
			{
				score = numb - 1;
				delay = ((fdelay / 100.00 ) - (numb * 0.001));
			}
		}

	}

	//direction
	if (dir == 1) s[0].y--;
	if (dir == 2) s[0].x++;
	if (dir == 3) s[0].y++;
	if (dir == 4) s[0].x--;

	//wall colision
	if (!wallj)
	{
		if (s[0].x == width) gameOver = true;
		if (s[0].x == -1) gameOver = true;
		if (s[0].y == height) gameOver = true;
		if (s[0].y == -1) gameOver = true;
	}
	else
	{
		if (s[0].x == width ) s[0].x = 0;
		if (s[0].x == -1) s[0].x = width-1;
		if (s[0].y == height ) s[0].y = 0;
		if (s[0].y == -1) s[0].y = height-1;
	}

}


int main()
{
	for (;;)
	{
		Fruit();

		//restart
		fdelay;
		dir = 0;
		numb = 1;
		score = 0;
		system("cls");
		gameOver = false;
		s[0].x = width / 2;
		s[0].y = height / 2;
		int choice = 0;


		string passw;
		string hardmodeq;
		string wall;

		cout << "1. Play" << endl;
		cout << "2. Settings" << endl;
		cout << "3. Exit" << endl;

		choice = _getch();
		choice += _getch();

		switch (choice)
		{
		case 49:

			break;
		case 50:
			system("cls");
			cout << "Speed(1 = fast, 10 = slow): "; cin >> fdelay;
			cout << "Wall jump(1 = Yes, 2 = No): "; cin >> wall;
			cout << "Hardmode(1 = Yes, 2 = No): "; cin >> hardmodeq;
			cout << "Tail eat(1 = Yes, 2 = No): "; cin >> snakeeattail;
			cout << "Haslo admin: "; cin >> passw;

			if (hardmodeq == "1") hardmode = true;
			else hardmode = false;
			if (passw == "snake123") admin = true;
			else admin = false;
			if (wall == "1") wallj = true;
			else wallj = false;

			break;
		case 51:
			return 0;
			break;

		default:
			break;

		}
		delay = (fdelay / 100.00);
		choice = 0;

		system("cls");
		cout << "Score: " << score << endl;

		srand(time(0));

		RenderWindow window(VideoMode(w, h), "Snake", Style::Close | Style::Titlebar);
		window.setFramerateLimit(60);

		Texture t1, t2, t3, t4;
		t1.loadFromFile("image/t1.png");
		t2.loadFromFile("image/t2.png");
		t3.loadFromFile("image/t3.png");
		t4.loadFromFile("image/t4.png");

		Sprite spritet1(t1);
		Sprite spritet2(t2);
		Sprite spritet3(t3);
		Sprite spritet4(t4);

		Clock clock;
		float timer = 0;

		//BUG instalost
		s[2].x = -10;
		s[2].y = -10;
		//

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event e;
			while (window.pollEvent(e))
			{
				switch (e.type)
				{
				case Event::Closed:
					window.close();
					break;
				}
			}

			if (gameOver == true) window.close();

			if (timer > delay)
			{
				timer = 0;
				Tick();
			}

			//MOVE
			if (Keyboard::isKeyPressed(Keyboard::Key::Up) && dir != 3) dir = 1;
			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && dir != 4) dir = 2;
			if (Keyboard::isKeyPressed(Keyboard::Key::Down) && dir != 1) dir = 3;
			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && dir != 2) dir = 4;
			if (Keyboard::isKeyPressed(Keyboard::Key::F1) && admin == true) { Fruit(); numb++; score++; system("cls"); cout << "Score: " << score; };
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();

			//DRAW
			window.clear(Color(200, 0, 0));

			//map draw
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					spritet1.setPosition(x*sizeo, y*sizeo);
					window.draw(spritet1);
					if ((f.x == x) && (f.y == y))
					{
						spritet3.setPosition(x*sizeo, y*sizeo);
						window.draw(spritet3);
					}
				}
			}

			//snake draw
			for (int i = 1; i <= numb; i++)
			{
				if (i == 1)
				{
					spritet4.setPosition(s[i].x*sizeo, s[i].y*sizeo);
					window.draw(spritet4);
				}
				else
				{
					spritet2.setPosition(s[i].x*sizeo, s[i].y*sizeo);
					window.draw(spritet2);
				}

			}

			window.display();
		}


	}
}