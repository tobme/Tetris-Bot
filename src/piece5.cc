#include "piece5.h"
#include <iostream>
using namespace std;
Piece5::Piece5(bool currentpiece) : Piece(currentpiece,5) 
{

    
    if (currentpiece)
    {
	pieces.push_back(Block{sf::Vector2f(300.0f,0.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(350.0f,0.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(350.0f,50.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(400.0f,50.0f),"yellow"});
    }
    else
    {
	pieces.push_back(Block{sf::Vector2f(600.0f,100.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(650.0f,100.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(650.0f,150.0f),"yellow"});
	pieces.push_back(Block{sf::Vector2f(700.0f,150.0f),"yellow"});
    }
}
void Piece5::Draw(sf::RenderWindow & window)
{
    for (Block &b : pieces)
    {
	b.Draw(window);
    }
}
void Piece5::setinPlay()
{
    pieces.at(0).setPosition(300.0f,0.0f);
    pieces.at(1).setPosition(350.0f,0.0f);
    pieces.at(2).setPosition(350.0f,50.0f);
    pieces.at(3).setPosition(400.0f,50.0f);
    inPlay = true;
    stage = 0;
}
void Piece5::rotate()
{
    sf::Vector2f p1 = pieces.at(0).getPos();
    sf::Vector2f p2 = pieces.at(1).getPos();
    sf::Vector2f p4 = pieces.at(3).getPos();
    if (stage == 0)
    {
	pieces.at(0).setPosition(p1.x + 100, p1.y);
	pieces.at(1).setPosition(p2.x + 50, p2.y + 50);
	pieces.at(3).setPosition(p4.x - 50, p4.y + 50);
	stage++;
    }
    else
    {
	pieces.at(0).setPosition(p1.x - 100, p1.y);
	pieces.at(1).setPosition(p2.x - 50, p2.y - 50);
	pieces.at(3).setPosition(p4.x + 50, p4.y - 50);
	stage = 0;
    }  
}
bool Piece5::canrotate(bool playingfield[22][10])
{
    sf::Vector2f p1 = pieces.at(0).getPos();
    sf::Vector2f p2 = pieces.at(1).getPos();
    sf::Vector2f p4 = pieces.at(3).getPos();

    if (stage == 0)
    {
	if (playingfield[(int)(p1.y - 100)/ 50][(int)(p1.x) / 50])
	{
	    return false;
	}
	else if (playingfield[(int)(p2.y - 50)/ 50][(int)(p2.x - 50) / 50])
	{
	    return false;
	}
	else if (playingfield[(int)(p4.y - 50)/ 50][(int)(p4.x - 150) / 50])
	{
	    return false;
	}
	return true;
    }
    else if (stage == 1)
    {
	if (playingfield[(int)(p1.y - 100)/ 50][(int)(p1.x - 200) / 50])
	{
	    return false;
	}
	else if (playingfield[(int)(p2.y - 150)/ 50][(int)(p2.x - 150) / 50])
	{
	    return false;
	}
	else if (playingfield[(int)(p4.y - 150)/ 50][(int)(p4.x - 50) / 50])
	{
	    return false;
	}
	return true;
    }
    return true;
}
int Piece5::rotatecount()
{
    return 2;
}
void Piece5::setnormal()
{
    for (Block &b : pieces)
    {
	b.setFillColor(sf::Color(255,255,0));
    }
}
void Piece5::setnotinPlay()
{
    pieces.at(0).setPosition(600.0f,100.0f);
    pieces.at(1).setPosition(650.0f,100.0f);
    pieces.at(2).setPosition(650.0f,150.0f);
    pieces.at(3).setPosition(700.0f,150.0f);
    inPlay = false;
    stage = 0;
}

