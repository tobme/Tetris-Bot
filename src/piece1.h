#ifndef PIECE1_H
#define PIECE1_H
#include "piece.h"
#include <string>
#include <SFML/Graphics.hpp>
class Piece1 : public Piece
{
public:
    Piece1(bool currentpiece);
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
