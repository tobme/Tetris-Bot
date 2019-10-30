#include "screen.h"
#include <SFML/Graphics.hpp>
#include <random>
#include "piece1.h"
#include "piece2.h"
#include "piece3.h"
#include "piece4.h"
#include "piece5.h"
#include "piece6.h"
#include "piece7.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>

using namespace std;

int rng(const int low,const int high)
{
    std::random_device rnd;
    return rnd() % (high - low + 1) + low;
}

Screen::Screen(int sleep, bool f) : 
    gameover{}, screenTexture{}, screen{sf::Vector2f(500.0f,1000.0f)},memory{}, currentPiece{make_random_piece(true)}, nextPiece{make_random_piece(false)}, updatethread{} , botthread{}, currentnumber{}, b{sleep, this, f}, clearedlines{}, time{1}, longcounter{},zetacounter{}
{
    cout << "Screen made..." << endl;
    screenTexture.loadFromFile("field2.png");
    screen.setTexture(&screenTexture);
    screen.setPosition(sf::Vector2f(100.0f,0.0f));
    memory.push_back(currentPiece);

    updatethread = std::thread(&Screen::Update, this);
    if (sleep != 0)
	botthread = std::thread(&Screen::Bot::simulate, &b);
}
Screen::~Screen()
{
    for (Piece* &p : memory)
    {
	delete p;
    }
    delete nextPiece;
    memory.clear();
}
void Screen::Draw(sf::RenderWindow & window)
{
    window.draw(screen);
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");

     text.setFont(font); 

    text.setString("Cleared Lines: " + std::to_string(clearedlines));
    text.setPosition(600.0f,00.0f);

    text.setCharacterSize(24);

    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	window.draw(text);

    sf::Text text2;

     text2.setFont(font); 

    text2.setString("Time: " + std::to_string(time));
    text2.setPosition(600.0f,50.0f);

    text2.setCharacterSize(24);


    text2.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text2);
    sf::Text text3;
    text3.setFont(font);
    text3.setString("Blocks per second: " + std::to_string(clearedlines/time));
    text3.setPosition(600.0f,200.0f);
    text3.setCharacterSize(24);
    text3.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text3);


     for (Piece* &p : memory)
     {
     	p->Draw(window);
     }
     nextPiece->Draw(window);
}
Piece* Screen::make_random_piece(bool currentPiece)
{
    currentnumber = rng(1,7);

    if (currentnumber == 1 || longcounter == 10)
    {
	longcounter = 0;
	zetacounter = 0;
	return new Piece1{currentPiece};
    }
    else if (currentnumber == 2)
    {
	longcounter++;
	zetacounter = 0;
	return new Piece2{currentPiece};
    }
    else if (currentnumber == 3)
    {
	longcounter++;
	return new Piece3{currentPiece};
    }
    else if (currentnumber == 4)
    {
	longcounter++;
	zetacounter = 0;
	return new Piece4{currentPiece};
    }
    else if (currentnumber == 5 && zetacounter != 3)
    {
	longcounter++;
	zetacounter++;
	return new Piece5{currentPiece};
    }
    else if (currentnumber == 6)
    {
	longcounter++;
	zetacounter = 0;
	return new Piece6{currentPiece};
    }
    else if (currentnumber == 7 && zetacounter != 3)
    {
	longcounter++;
	zetacounter++;
	return new Piece7{currentPiece};
    }
    return make_random_piece(currentPiece);
}
void Screen::Update()
{
    if (!gameover)
    {

    fillField(false);
    std::this_thread::sleep_for (std::chrono::seconds(1));
    time++;
    if (!currentPiece->reachGround() && compareField(1))
	currentPiece->Update();
    // else
    // {
    // 	fullLine();
    // 	makepiece();
    // }

    Update();
    }
    else
	updatethread.detach();
}
void Screen::checklose()
{
    int xpos;
    int ypos;
    for (sf::Vector2f f : currentPiece->getPos())
    {
	xpos = (f.x - 100) / 50;
	ypos = (f.y + 100) / 50;
	if (playingfield[ypos][xpos])
	{
	    gameover = true;
	    cout << "GAMEOVER" << endl;
	}
    }
}
void Screen::makepiece()
{
    if (!gameover)
    {
	std::cout << "Piece made..." << std::endl;
	currentPiece = nextPiece;
	currentPiece->setinPlay();
	fillField(false);
	checklose();
	nextPiece = make_random_piece(false);
	memory.push_back(currentPiece);
	fillField(false);
    }
}
void Screen::clearField()
{
    for (int i{}; i<22; i++)
    {
	for (int j{}; j<10; j++)
	{
	    playingfield[i][j] = false;
	}
    }
}
void Screen::coutfield()
{
    for (int i{}; i<14; i++)
    {
      	for (int j{}; j<10; j++)
      	{
      	    if (playingfield[i][j])
      		std::cout << "1" << " ";
      	    else
      		std::cout << "0" << " ";
     	}
      	cout << std::endl;
    }
    cout << std::endl;
}
void Screen::fillField(bool second)
{
    clearField();
    std::vector<sf::Vector2f> vpos;
    int xpos;
    int ypos;
    for (Piece* p : memory)
    {
	vpos = p->getPos();
	for (sf::Vector2f f : vpos)
	{
	    xpos = (f.x-100)/50;
	    ypos  = (f.y + 100) /50;
	    playingfield[ypos][xpos] = true;
	}
    }
    if (second)
    {
	for (sf::Vector2f f : nextPiece->getPos())
	{
	    xpos = (f.x-100)/50;
	    ypos = (f.y + 100)/50;
	    playingfield[ypos][xpos] = true;
	}
    }
}
bool Screen::compareField(int side,bool right)
{
    bool tempfield [22][10];

    for (int i{}; i<22; i++)
    {
	for (int j{}; j<10; j++)
	{
	    tempfield[i][j] = false;
	}
    }

    std::vector<sf::Vector2f> vpos;
    int xpos;
    int ypos;
    for (auto it = memory.begin(); it != memory.end()-1; ++it)
    {
	vpos  = (**it).getPos();
	for (sf::Vector2f f : vpos)
	{
	    xpos = (f.x-100)/50;
	    ypos  = (f.y+100)/50;
	    tempfield[ypos][xpos] = true;
	}
    }
    if (side == 1 && !right)
	return currentPiece->Placed(tempfield);
    else if (side == 1 && right)
	return nextPiece->Placed(tempfield);
    else if (side == 2)
	return currentPiece->placedside(right,tempfield);
    else
	return currentPiece->canrotate(tempfield);
}
void Screen::Move(bool right)
{
    if (compareField(2,right))
	currentPiece->Move(right);
}
void Screen::Down()
{
    while (!currentPiece->reachGround() && compareField(1,false))
    {
	currentPiece->Update();
    }
    fullLine();
    makepiece();

}
void Screen::rotate()
{
    if (compareField(3))
	currentPiece->rotate();
}
void Screen::fullLine()
{

    int count{};
    for (int j{}; j<2; j++)
    {
    
	for (int i{0}; i<22; i++)
	{
	    fillField(false);
	    for (int j{}; j<10; j++)
	    {
		if (playingfield[i][j])
		    count++;
	    }
	    if (count == 10)
	    {
		clearedlines++;
		for (Piece* p : memory)
		{
		    p->clearLine(i);
		}
		for (Piece* p : memory)
		{
		    p->moveafterclear(i);
		}
	    
		removeEmpty();
	    }
	    count = 0;
	}
    }
}
void Screen::removeEmpty()
{
    std::vector<Piece*> temp{memory};
     for (unsigned int i{}; i<temp.size(); i++)
     {
	 if (temp.at(i)->empty())
     	{
     	    delete temp.at(i);
     	    temp.erase(temp.begin()+i);
     	}
    }
     memory = temp;
}


Screen::Bot::Bot(int sl, Screen* s, bool f) : sleep{sl}, countleft(5), screenptr{s}, moves{}, score{}, fast{f}
{
}
void Screen::Bot::setleft(int rotater, bool second)
{
    if (!second)
	countleft.at(rotater) = 0;
    bool done{};
    while (!done)
    {
	if (!second)
	{
	    countleft.at(rotater)++;
	    screenptr->currentPiece->Move(false);

	    for (sf::Vector2f f : screenptr->currentPiece->getPos())
	    {
		if (f.x <= 100)
		    done = true;
	    }
	}
	else
	{
	    screenptr->nextPiece->Move(false);
	    for (sf::Vector2f f : screenptr->nextPiece->getPos())
	    {
		if (f.x <= 100)
		    done = true;
	    }
	}

    }
}
void Screen::Bot::makesecondmove(int rotater,int rights,int rotate)
{
    screenptr->nextPiece->setinPlay();
    int right{};
    while (screenptr->nextPiece->insideArea(true))
    {
     screenptr->nextPiece->setinPlay();

     for (int i{}; i<rotater; i++)
     	screenptr->nextPiece->rotate();
     
     setleft(rotater,true);
     for (int i{}; i<right; i++)
     {
	 screenptr->nextPiece->Move(true);
     }
     right++;
     while (!screenptr->nextPiece->reachGround() && screenptr->nextPiece->Placed(screenptr->playingfield))
     {
	 screenptr->fillField(false);
	 screenptr->nextPiece->Update();
     }
     screenptr->fillField(true);
     calcscore();
     moves.push_back(std::pair<int,int>(rights,rotate));
     

    }


}
void Screen::Bot::makemove(int rotater)
{
    setleft(rotater,false);
    int right{};
    while (screenptr->currentPiece->insideArea(true))
    {
	screenptr->currentPiece->setinPlay();
	
	for (int i{}; i<rotater; i++)
	    screenptr->currentPiece->rotate();
	setleft(rotater,false);
	for (int i{}; i<right; i++)
	{
	    screenptr->currentPiece->Move(true);
	}
	right++;
	while (!screenptr->currentPiece->reachGround() && screenptr->compareField(1,false))
	{
	    screenptr->currentPiece->Update();
	}
	if (!fast)
	{
	    int stagecounter{};
	    do
	    {
		makesecondmove(stagecounter,right-1, rotater);
		stagecounter++;
	    }while(stagecounter < screenptr->nextPiece->rotatecount());
	    screenptr->nextPiece->setnotinPlay();
	}
	else
	{
	    screenptr->fillField(false);
	    calcscore();
	    moves.push_back(std::pair<int,int>(right-1,rotater));
	}

    }
       screenptr->currentPiece->setinPlay();
    
}
void Screen::Bot::calcscore()
{
    double tempscore{};
    int count{};
    bool checkhight{};
    int block{};
    int blockind{};
    std::vector<std::pair<bool,int>> bumpi(10);

    for (int i{}; i<22; i++)
    {
	for (int j{}; j<10; j++)
	{
	    if (screenptr->playingfield[i][j])
	    {
		count++;
		if (!bumpi.at(j).second)
		{
		    bumpi.at(j).second = true;
		    bumpi.at(j).first = 21 - i;
		}
		if (!checkhight)
		{
		    checkhight = true;
		    if (i <= 6)
			tempscore -= (21 - i) * 8;
		    else if ( i <= 10)
		      	tempscore -= (21 - i) * 6;
		    else
		      	tempscore -=  (21 - i) * 3;
		}
	    }
	     if (!(screenptr->playingfield[i][j]) && screenptr->playingfield[i-1][j] && i != 0)
	     {
		 blockind = i - 1;
		 while (screenptr->playingfield[blockind][j] && blockind != 0)
		 {
		     blockind--;
		     block++;
		 }
		 tempscore -= 12.5;
	     }
	     if (screenptr->playingfield[i][j] && i == 21)
	     {
		 tempscore += 2.5;
	     }
	    if (screenptr->playingfield[i][j] && j == 0)
		tempscore += 1.2;
	    if (screenptr->playingfield[i][j] && j == 9)
		tempscore -= 0.5;
	    if (screenptr->playingfield[i][j] && screenptr->playingfield[i][j+1] && j != 9)
		tempscore += 1.5;
	}
	if (count == 10)
	    tempscore += 15.5;
	count = 0;
    }
    sort(bumpi.begin(),bumpi.end(),[](std::pair<bool,int> p,std::pair<bool,int> p2){return p.second < p2.second;});
    int midval = bumpi.at(bumpi.size()/2).second;
    int endbumpival{};
    for (std::pair<bool,int> b : bumpi)
    {
	endbumpival += abs(midval - b.second);
    }
    tempscore -= double(0.7 * endbumpival);
    tempscore -= double(0.5 * block);
    
    //  cout << "Score " << tempscore << endl;
    //          std::this_thread::sleep_for (std::chrono::milliseconds(300));
    score.push_back(tempscore);
}
double Screen::Bot::findhighestscore()
{
    double highest{score.at(0)};
    int index{};
    int counter{};
    for (double i : score)
    {
	if (i > highest)
	{
	    highest = i;
	    index = counter;
	}
	counter ++;
    }
    cout << "Highest score.. " << highest << endl;
    return index;
}

void Screen::Bot::simulate()
{
    int stagecounter = 0;
    screenptr->currentPiece->setblack();
    screenptr->nextPiece->setblack();

    cout << "Calculating moves..." << endl;
    do
    {

	makemove(stagecounter);
	stagecounter++;
    }while(stagecounter < screenptr->currentPiece->rotatecount());
    screenptr->currentPiece->setnormal();
    screenptr->nextPiece->setnormal();
    screenptr->currentPiece->setinPlay();

    simulatemove();


    
}
void Screen::Bot::simulatemove()
{

    int index;
    std::this_thread::sleep_for (std::chrono::milliseconds(sleep*2));

	index = findhighestscore();
    cout << "Index: " << index << endl;
    cout << "Highest index: " << ceil(double(score.size()/(25*screenptr->nextPiece->rotatecount()))) << endl;
    cout << "moves size..: " << moves.size() << endl;
    for (int i{}; i<moves.at(index).second; ++i)
    {
	cout << "Rotating..." << endl;
	screenptr->currentPiece->rotate();
	std::this_thread::sleep_for (std::chrono::milliseconds(sleep/2));
    }
    if (moves.at(index).first < countleft.at(moves.at(index).second))
    {
	while (countleft.at(moves.at(index).second) != moves.at(index).first)
	{
	    cout << "countleft: " << countleft.at(moves.at(index).second) << " moves: " << moves.at(index).first << endl;
	    cout << "Moving Left..." << endl;
	    countleft.at(moves.at(index).second)--;
	    screenptr->Move(false);
	    std::this_thread::sleep_for (std::chrono::milliseconds(sleep/2));
	}
    }
    else
    {
	while (countleft.at(moves.at(index).second) != moves.at(index).first)
	{
	    cout << "countleft: " << countleft.at(moves.at(index).second) << " moves: " << moves.at(index).first << endl;
	    cout << "Moving Right..." << endl;
	    countleft.at(moves.at(index).second)++;
	    screenptr->Move(true);
	    std::this_thread::sleep_for (std::chrono::milliseconds(sleep/2));
	}
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(sleep/2));
    cout << "Moving down..." << endl;
    screenptr->Down();
    screenptr->coutfield();

    moves.clear();
    score.clear();
    for (int &i : countleft)
    {
	i = 0;
    }
    if (!screenptr->gameover)
	simulate();
    else
	screenptr->botthread.detach();
}

