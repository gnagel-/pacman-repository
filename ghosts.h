#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

class Ghosts{
private:
	char mode; //(c)hase, (f)rightened, (s)catter, (h)ouse
	char name; //(b)linky, (i)nky, (p)inky, (c)lyde
	sf::Sprite sprite;
	//sf::Clock timer;

	double row;
	double column;
	char direction; //(u)p, (d)own, (l)eft, (r)ight

	float speed;
	float speedAdjust;
	float speedInc;

	int homeTileRow;
	int homeTileColumn;
	int targetTileRow;
	int targetTileColumn;
	
public:
	Ghosts();
	Ghosts(char m, char n, sf::Sprite spr, float r, float c);
	bool inc = true;

	void scatterMode();
	void move();
	char chooseDirection(char toTileType);
	float distanceCheck(int r, int c);
	
	void reverse(char dir);
	char getDirection();
	void setDirection(char d);

	double getRow();
	double getColumn();
	void setRow(double r);
	void setCol(double c);
	void setPos(double r, double c);

	void setHomeTile(int r, int c);
	int getHomeRow();
	int getHomeColumn();

	void setTarget(int r, int c);
	int getTargetRow();
	int getTargetColumn();

	char getMode();
	void setMode(char m);
	void changeMode(char newMode);

	char getName();
	void setName(char n);

	sf::Sprite getSprite();
	void setSprite(sf::Sprite spr);

	float getSpeed();
	void setSpeed(float s);
	float getSpeedAdjust();
	float getSpeedInc();

	void frightenGhost(sf::IntRect f);

	void resetGhost();

};