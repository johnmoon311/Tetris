#ifndef VECTOR_SHAPES_H
#define VECTOR_SHAPES_H
#include "tetris_shape.h"
#include <iostream>

using namespace std;


class Vector_shapes
{
public:
    Vector_shapes();
    void IntializeShapes();
    void IntializeShapeOutline(Vector_shapes CurrentShape);

    void MoveCurrentShapeLeft();
    void MoveCurrentShapeRight();
    void MoveCurrentShapeDown();
    void MoveCurrentShapeUp();

    void RotateCurrentShape(Vector_shapes BottomStack, int bottomcount);
    void CopyShapetoVector(Vector_shapes CurrentShape);
    void KeepShapeCount(int Shapecount);


    void DrawVector(sf::RenderWindow &window, int totalcount);
    void DrawBottomVector(sf::RenderWindow &window, int totalcount);

    void GetNextShape();

    bool CheckBottomCollision(Vector_shapes BottomStack, int bottomcount);
    bool CheckRightCollision(Vector_shapes BottomStack, int bottomcount);
    bool CheckLeftCollision(Vector_shapes BottomStack, int bottomcount);

    bool CheckFilledLines(int totalcount, int &filledline);
    void ClearFilledLine(int &totalcount, int filledline);
    void DropBottomStack(int totalcount, int filledline);

    bool CheckShapeCount(int filledline);

    bool CheckGameOver(int bottomcount);
    void ClearAll();





    vector<tetris_shape> VectorShape;
    int count[1000];
};

#endif // VECTOR_SHAPES_H
