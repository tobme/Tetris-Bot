

#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include "piece.h"
#include <vector>
#include <thread>
class Screen
{
public:
    Screen(int sleep, bool f);
    ~Screen();
    Screen(Screen const &) = delete;
    Screen& operator=(Screen const &) = delete;
    void Draw(sf::RenderWindow & window);
    void Update();
    void makepiece();
    void Move(bool right);
    void Down();
    void rotate();
    void fullLine();
    void removeEmpty();
    bool gameover;
private:

    class Bot
    {
    public:
	Bot(int sl, Screen* s, bool f);
	void simulate();
    private:

	void makemove(int rotater);
	void makesecondmove(int rotater,int rights,int rotate);
	void setleft(int rotater, bool second);
	void calcscore();
	double findhighestscore();
	Bot(Bot const &) = delete;
	Bot& operator=(Bot const &) = delete;

	void simulatemove();

	int sleep;
	std::vector<int> countleft;
	Screen* screenptr;
	std::vector<std::pair<int,int>> moves;
	std::vector<double> score;
	bool fast;

    };


    bool compareField(int side,bool right = true);
    void clearField();
    void fillField(bool second);
    void checklose();
    void coutfield();

    Piece* make_random_piece(bool currentPiece);
    bool playingfield [22][10];
    sf::Texture screenTexture;
    sf::RectangleShape screen;
    std::vector<Piece*> memory;
    Piece* currentPiece;
    Piece* nextPiece;
    std::thread updatethread;
    std::thread botthread;
    int currentnumber;
    Bot b;
    int clearedlines;
    int time;
    int longcounter;
    int zetacounter;
};
#endif
