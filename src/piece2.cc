#include "piece2.h"
#include <iostream>
using namespace std;
Piece2::Piece2(bool currentpiece) : Piece(currentpiece,2) 
{
    
    if (currentpiece)
    {
	pieces.push_back(Block{sf::Vector2f(300.0f,0.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(350.0f,0.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(300.0f,50.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(350.0f,50.0f),"orange"});
    }
    else
    {
	pieces.push_back(Block{sf::Vector2f(600.0f,100.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(650.0f,100.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(600.0f,150.0f),"orange"});
	pieces.push_back(Block{sf::Vector2f(650.0f,150.0f),"orange"});
    }
}
void Piece2::Draw(sf::RenderWindow & window)
{
    for (Block &b : pieces)
    {
	b.Draw(window);
    }
}
void Piece2::setinPlay()
{
    pieces.at(0).setPosition(300.0f,0.0f);
    pieces.at(1).setPosition(350.0f,0.0f);
    pieces.at(2).setPosition(300.0f,50.0f);
    pieces.at(3).setPosition(350.0f,50.0f);
    inPlay = true;
    stage = 0;
}
void Piece2::rotate()
{  
}
bool Piece2::canrotate(__attribute__((unused)) bool playingfield[22][10])
{
    return false;
}
int Piece2::rotatecount()
{
    return 1;
}
void Piece2::setnormal()
{
    for (Block &b : pieces)
    {
	b.setFillColor(sf::Color(255,165,0));
    }
}
void Piece2::setnotinPlay()
{
    pieces.at(0).setPosition(600.0f,100.0f);
    pieces.at(1).setPosition(650.0f,100.0f);
    pieces.at(2).setPosition(600.0f,150.0f);
    pieces.at(3).setPosition(650.0f,150.0f);
    inPlay = false;
    stage = 0;
}
