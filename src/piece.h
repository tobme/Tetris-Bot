

#ifndef PIECE_H
#define PIECE_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class Piece
{
public:
    Piece(bool currentpiece,int piecenmbr);
    virtual ~Piece() = default;
    virtual void rotate();
    virtual bool canrotate(bool playingfield[22][10]);
    virtual void Draw(sf::RenderWindow & window);
    virtual int rotatecount();
    bool Placed(bool playingfield[22][10]);
    void Update();
    virtual void setinPlay();
    virtual void setnotinPlay();
    std::vector<sf::Vector2f> getPos();
    int getnumber();
    bool reachGround();
    void Move(bool right);
    bool placedside(bool right,bool playingfield[22][10]);
    void clearLine(int row);
    bool empty();
    int getStage();
    void moveafterclear(int row);
    int piecenmbren;
    void setpos();
    void setblack();
    bool insideArea(bool right);
    virtual void setnormal();
protected:
    class Block : public sf::RectangleShape
    {
    public:
	Block(sf::Vector2f p,std::string c);
	void Draw(sf::RenderWindow & window);
	void Move();
	void Moveside(bool right);
	sf::Vector2f getPos();
	
	sf::Vector2f pos;
	std::string color;
    };
    bool inPlay;
    int stage;
    std::vector<Block> pieces;

private:


    
   
};
#endif
