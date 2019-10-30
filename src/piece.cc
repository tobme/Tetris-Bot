#include "piece.h"
#include <iostream>

Piece::Piece(bool currentpiece, int piecenmbr) :  piecenmbren{piecenmbr}, inPlay{currentpiece}, stage{},pieces{}
{
    std::cout << "Piece made..." << std::endl;
}
void Piece::setpos()
{
    for (Block &b : pieces)
    {
	b.setPosition(0.0f,0.0f);
    }
}
void Piece::setblack()
{
    for (Block &b : pieces)
    {
	b.setFillColor(sf::Color(0,0,0));
    }
}
void Piece::setnormal()
{
    
}
Piece::Block::Block(sf::Vector2f p,std::string c) : sf::RectangleShape{sf::Vector2f(50.0f,50.0f)} ,pos{p}, color{c}
{
    std::cout << "Block made..." << std::endl;
    this->setPosition(pos);

    if (color == "orange")
    {
	this->setFillColor(sf::Color(255,165,0));
    }
    else if (color == "red")
    {
	this->setFillColor(sf::Color(255,0,0));
    }
    else if (color == "green")
    {
	this->setFillColor(sf::Color(0,255,0));
    }
    else if (color == "pink")
    {
	this->setFillColor(sf::Color(255,182,193));
    }
    else if (color == "yellow")
    {
	this->setFillColor(sf::Color(255,255,0));
    }
    else if (color == "blue")
    {
	this->setFillColor(sf::Color(0,0,255));
    }
    else if (color == "brown")
    {
	this->setFillColor(sf::Color(139,69,19));
    }
    else
    {
	this->setFillColor(sf::Color(139,69,19));
    }
}
sf::Vector2f Piece::Block::getPos()
{
    return this->getPosition();
}
int Piece::getStage()
{
    return stage;
}
void Piece::Block::Move()
{
    this->move(0.0f,50.0f);
}
void Piece::Block::Draw(sf::RenderWindow & window)
{
    window.draw(*this);
}
void Piece::setinPlay()
{
}
bool Piece::reachGround()
{
    for (Block &b : pieces)
    {
	if (b.getPos().y >= 950)
	    return true;
    }
    return false;
}
void Piece::Update()
{
    if (inPlay)
    {
	for (Block &b : pieces)
	{
	    b.Move();
	}
    }
}
void Piece::Draw(sf::RenderWindow & window)
{
    for (Block &b : pieces)
    {
	b.Draw(window);
    }
}
bool Piece::canrotate(__attribute__((unused)) bool playingfield[22][10])
{
    return false;
}
bool Piece::insideArea(bool right)
{
    for (Block &b : pieces)
    {
	if ((b.getPos().x >= 550 && right) || (b.getPos().x <= 100 && !right))
	    return false;
    }
    return true;
}
bool Piece::placedside(bool right,bool playingfield[20][10])
{
    int xpos;
    int ypos;

    for (auto &b : pieces)
    {
	xpos = b.getPos().x;
	if (right)
	    xpos+=50;
	else
	    xpos-=50;
	ypos = b.getPos().y;
	if (playingfield[(ypos+100)/50][(xpos-100)/50])
	{
	    return false;
	}
    }
    return true;
}
bool Piece::empty()
{
    return pieces.size() == 0;
}
void Piece::clearLine(int row)
{
    int blockrow{};
    
     for (unsigned int i {}; i<pieces.size(); i++)
     {
	 blockrow = (pieces.at(i).getPos().y + 100) / 50;
	 if (blockrow == row)
	 {
	     pieces.erase(pieces.begin()+i);
	 }
     }

}
void Piece::moveafterclear(int row)
{
    int blockrow{};
    
     for (unsigned int i {}; i<pieces.size(); i++)
     {
	 blockrow = (pieces.at(i).getPos().y + 100) / 50;
	 if (blockrow < row)
	     pieces.at(i).Move();
     }
}
void Piece::Move(bool right)
{
    if (insideArea(right))
    {
	for (Block &b : pieces)
	{
	    b.Moveside(right);
	}
    }
}
void Piece::Block::Moveside(bool right)
{
    if (right && this->getPosition().x <= 500)
    {
	this->move(50.0f,0.0f);
    }
    else if (!right && this->getPosition().x >= 100)
    {
	this->move(-50.0f,0.0f);
    }
}
std::vector<sf::Vector2f> Piece::getPos()
{
    std::vector<sf::Vector2f> temp;
    for (Block &b : pieces)
    {
	temp.push_back(b.getPos());
    }
    return temp;
}
int Piece::getnumber()
{
    return piecenmbren;
}
bool Piece::Placed(bool playingfield[22][10])
{
    int xpos;
    int ypos;

    for (auto &b : pieces)
    {
	xpos = b.getPos().x;
	ypos = b.getPos().y + 50;
	if (playingfield[(ypos + 100) / 50][(xpos-100)/50])
	{
	    return false;
	}
    }
    return true;
}
void Piece::rotate()
{
}
int Piece::rotatecount()
{
    return 0;
}
void Piece::setnotinPlay()
{
}
