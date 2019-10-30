

#ifndef PIECE6_H
#define PIECE6_H
#include "piece.h"
#include <SFML/Graphics.hpp>
#include <string>
class Piece6 : public Piece
{
public:
    Piece6(bool currentpiece);
    void Draw(sf::RenderWindow & window) override;
    void setinPlay() override;
    void rotate() override;
    bool canrotate(bool playingfield[22][10]) override;
    int rotatecount() override;
    void setnormal() override;
    void setnotinPlay() override;
private:
};
#endif
