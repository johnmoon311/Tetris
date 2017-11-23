#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
const int ShapeType=4;
const int BoxSize=25;
const int Center=250;

const float PI=3.141592653589;

const int LeftBorder=Center-BoxSize*5;
const int RightBorder=Center+BoxSize*6;
const int Floor=BoxSize*20;

using namespace std;


class tetris_shape
{
public:
    tetris_shape();

    tetris_shape(int shapeoption, int x, int y);

    void MoveRight();
    void MoveLeft();
    void UpdateScreen();
    void MoveDown();
    void MoveUp();

    void CopyShape(tetris_shape otherShape);
    void InitalizeColor();


    void DrawShape(sf::RenderWindow &window);
    void DrawBottomShape(sf::RenderWindow &window, int count);
    bool CheckShapeCount(int filledline, int shapecount);



    void PivotShape();
    void PivotShapeBack();

    float rotatex(float x1, float x2, float y1, float y2, float theta);
    float rotatey(float x1, float x2, float y1, float y2, float theta);
    float DEG2RAD(float theta);
    sf::Vector2f Pivot(sf::Vector2f p1, sf::Vector2f p2, float theta);
    void Rotate(double positionX, double positionY, double reflectionx, double reflectiony, double theta);

    bool checkrightcollision(tetris_shape BottomStack, int count);
    bool checkbottomcollision(tetris_shape BottomStack, int count);
    bool checkleftcollision(tetris_shape BottomStack, int count);


    bool within_bordersRight();
    bool within_bordersLeft();
    bool within_bordersBottom();

    int leftmost_pos();
    int rightmost_pos();
    int bottom_pos();


    void MoveToPosition(int x, int y);
    void MoveCenter();
    bool CountFilledLines(int y, int &boxcount, int shapecount);
    tetris_shape clearfilledline(int filledline, int &count, int shapecount);
    void dropbottomstack(int filledline, int count);
    void CopyRectangle(sf::RectangleShape otherShape, int j);

    bool checkgameover(int count);
    bool checkrotatecollision(tetris_shape BottomStack, int count);
    bool moverotatecollision(tetris_shape BottomStack);

    sf::RectangleShape Shape[4];



};

#endif // TETRIS_SHAPE_H
