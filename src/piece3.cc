#include "piece3.h"
#include <iostream>
using namespace std;
Piece3::Piece3(bool currentpiece) : Piece(currentpiece,3) 
{

    if (currentpiece)
    {
	pieces.push_back(Block{sf::Vector2f(350.0f,50.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(400.0f,50.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(450.0f,50.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(400.0f,0.0f),"red"});
    }
    else
    {
	pieces.push_back(Block{sf::Vector2f(650.0f,150.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(700.0f,150.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(750.0f,150.0f),"red"});
	pieces.push_back(Block{sf::Vector2f(700.0f,100.0f),"red"});
    }
}
void Piece3::Draw(sf::RenderWindow & window)
{
    for (Block &b : pieces)
    {
	b.Draw(window);
    }
}
void Piece3::setinPlay()
{
    pieces.at(0).setPosition(350.0f,50.0f);
    pieces.at(1).setPosition(400.0f,50.0f);
    pieces.at(2).setPosition(450.0f,50.0f);
    pieces.at(3).setPosition(400.0f,0.0f);
    inPlay = true;
    stage = 0;
}
void Piece3::rotate()
{
    sf::Vector2f p1 = pieces.at(0).getPos();
    sf::Vector2f p3 = pieces.at(2).getPos();
    sf::Vector2f p4 = pieces.at(3).getPos();
    if (stage == 0)
    {
	pieces.at(0).setPosition(p1.x + 50, p1.y+50);
	stage++;
    }
    else if (stage == 1)
    {
	pieces.at(3).setPosition(p4.x - 50, p4.y + 50);
	stage++;
    }
    else if (stage == 2)
    {
	pieces.at(2).setPosition(p3.x - 50, p3.y - 50);
	stage++;
    }
    else if (stage == 3)
    {
	pieces.at(0).setPosition(p1.x - 50, p1.y -50);
	pieces.at(2).setPosition(p3.x + 50,p3.y + 50);
	pieces.at(3).setPosition(p4.x + 50,p4.y -50);
	stage = 0;
    }   
}
bool Piece3::canrotate(bool playingfield[22][10])
{
    sf::Vector2f p1 = pieces.at(0).getPos();
    sf::Vector2f p3 = pieces.at(2).getPos();
    sf::Vector2f p4 = pieces.at(3).getPos();

    if (stage == 0)
    {
	return !playingfield[(int)(p1.y - 50) / 50 ][(int)( p1.x - 50) / 50];
    }
    else if (stage == 1)
    {
	return !(playingfield[(int)(p4.y - 50)/ 50][(int)(p4.x - 150) / 50]);
    }
    else if (stage == 2)
    {
        return !(playingfield[(int)(p3.y - 150)/ 50][(int)(p3.x - 150) / 50]);
    }
    else if (stage == 3)
    {
	if (playingfield[(int)(p1.y - 150)/ 50][(int)(p1.x - 150) / 50])
	{
	    return false;
	}
	else if (playingfield[(int)(p3.y - 50)/ 50][(int)(p3.x - 50) / 50])
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
int Piece3::rotatecount()
{
    return 4;
}
void Piece3::setnormal()
{
    for (Block &b : pieces)
    {
	b.setFillColor(sf::Color(255,0,0));
    }
}
void Piece3::setnotinPlay()
{
    pieces.at(0).setPosition(650.0f,150.0f);
    pieces.at(1).setPosition(700.0f,150.0f);
    pieces.at(2).setPosition(750.0f,150.0f);
    pieces.at(3).setPosition(700.0f,100.0f);
    inPlay = false;
    stage = 0;
}
