#include "tetris_shape.h"

tetris_shape::tetris_shape()
{

}

tetris_shape::tetris_shape(int shapeoption, int x, int y)
{
    for (int i=0; i<ShapeType; i++){
        Shape[i].setPosition(x, y);
        Shape[i].setSize(sf::Vector2f(BoxSize-1,BoxSize-1));
        Shape[i].setOutlineThickness(1);
        Shape[i].setOutlineColor(sf::Color::Black);
    }

    switch (shapeoption){
    case 0:
        //square
        Shape[1].setPosition(x-BoxSize,y);
        Shape[2].setPosition(x, y+BoxSize);
        Shape[3].setPosition(x-BoxSize,y+BoxSize);

        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Yellow);
        }
        break;
    case 1:
        //line
        Shape[1].setPosition(x+BoxSize, y);
        Shape[2].setPosition(x-(2*BoxSize), y);
        Shape[3].setPosition((x-BoxSize),y);
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Red);
        }
        break;
    case 2:
        //T
        Shape[1].setPosition(x-BoxSize,y);
        Shape[2].setPosition(x+BoxSize,y);
        Shape[3].setPosition(x,y+BoxSize);
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Green);
        }
        break;
    case 3:
        //backwards L
        Shape[1].setPosition(x+BoxSize,y);
        Shape[2].setPosition(x-(BoxSize),y);
        Shape[3].setPosition(x+BoxSize,y+(BoxSize));
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Blue);
        }
        break;
    case 4:
        //L
        Shape[1].setPosition(x+BoxSize,y);
        Shape[2].setPosition(x-(BoxSize),y);
        Shape[3].setPosition(x-BoxSize,y+BoxSize);
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Magenta);
        }
        break;
    case 5:
        //Z
        Shape[1].setPosition(x-BoxSize,y);
        Shape[2].setPosition(x, y+BoxSize);
        Shape[3].setPosition(x+BoxSize,y+BoxSize);
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color::Cyan);
        }
        break;
    case 6:
        //Backwards Z
        Shape[1].setPosition(x+BoxSize,y);
        Shape[2].setPosition(x, y+BoxSize);
        Shape[3].setPosition(x-BoxSize,y+BoxSize);
        for (int i=0; i<ShapeType; i++){
            Shape[i].setFillColor(sf::Color(100, 100, 100));
        }
        break;
    }
}



void tetris_shape::MoveLeft(){
    for (int i=0; i<ShapeType;i++){

        Shape[i].move(-BoxSize, 0);
        //move left

    }
}

void tetris_shape::MoveRight(){
    for (int i=0; i<ShapeType; i++){
        Shape[i].move(BoxSize, 0);
        //move right
    }

}




void tetris_shape::MoveDown(){
    for (int i=0; i<ShapeType; i++)
    {
        Shape[i].move(0, BoxSize);
    }
}


void tetris_shape::DrawShape(sf::RenderWindow &window){
    for (int i=0;i<ShapeType; i++)
    {
        window.draw(Shape[i]);
    }
}

void tetris_shape::DrawBottomShape(sf::RenderWindow &window, int count){
    for (int i=0;i<count; i++)
    {
        window.draw(Shape[i]);
    }
}



void tetris_shape::PivotShape(){
    for (int i=0; i<ShapeType; i++)
    {
        Shape[i].setPosition(Pivot(Shape[0].getPosition(), Shape[i].getPosition(), 90.0));
    }
}

void tetris_shape::PivotShapeBack(){
    for (int i=0; i<ShapeType; i++)
    {
        Shape[i].setPosition(Pivot(Shape[0].getPosition(), Shape[i].getPosition(), -90.0));
    }
}




float tetris_shape::rotatex(float x1, float x2, float y1, float y2, float theta) {
    float radians= DEG2RAD(theta);
    float x=((x2-x1)*cos(radians))-((y2-y1)*sin(radians))+x1;
    return x;
}




float tetris_shape::rotatey(float x1, float x2, float y1, float y2, float theta) {
    float radians = DEG2RAD(theta);
    float y=((x2-x1)*sin(radians))+((y2-y1)*cos(radians))+y1;
    return y;
}





sf::Vector2f tetris_shape::Pivot(sf::Vector2f p1, sf::Vector2f p2, float theta){
    sf::Vector2f coord;
    coord.x = rotatex(p1.x, p2.x, p1.y, p2.y, theta);
    coord.y = rotatey(p1.x, p2.x, p1.y, p2.y, theta);
    return coord;
}




float tetris_shape::DEG2RAD(float theta){
    float degree;
    degree=theta*PI/180;
    return degree;
}




void tetris_shape::MoveCenter()
{
    for(int i=0; i<ShapeType; i++){
        Shape[i].move(-190, -100-BoxSize);
    }
}




void tetris_shape::MoveToPosition(int x, int y)
{
    for (int i=0; i<ShapeType; i++){
        Shape[i].move(x, y);

    }
}




void tetris_shape::CopyShape(tetris_shape otherShape){
    for (int i=0; i<ShapeType; i++){
        Shape[i].setPosition(otherShape.Shape[i].getPosition());
        Shape[i].setFillColor(otherShape.Shape[i].getFillColor());
    }
}




void tetris_shape::MoveUp(){
    for (int i=0; i<ShapeType;i++){
        Shape[i].move(0, -BoxSize);
    }
}




//checks if the shape is within the border to the left
bool tetris_shape::within_bordersLeft(){
    if (leftmost_pos()<(LeftBorder+BoxSize)){
        return false;
    }
    else{
        return true;
    }
}

//checks if the shape is within the border to the right
bool tetris_shape::within_bordersRight(){
    if (rightmost_pos()>(RightBorder-BoxSize)){
        return false;
    }
    else{
        return true;
    }
}

//compares the bottom position of the shape to the bottom border
bool tetris_shape::within_bordersBottom(){
    if(bottom_pos()>=Floor-BoxSize){
        return false;
    }
    else{
        return true;
    }
}



bool tetris_shape::checkrightcollision(tetris_shape BottomStack, int count){
    sf::Vector2f positionBottom;
    sf::Vector2f positionShape;

    for(int i=0; i<ShapeType; i++){
        positionShape=Shape[i].getPosition();
        for(int j=0; j<count; j++){
            positionBottom=BottomStack.Shape[j].getPosition();
            if(((positionShape.x==positionBottom.x-BoxSize)&&(positionShape.y==positionBottom.y))
                    ||(positionShape.x>400-BoxSize)){
                return true;

            }
        }
    }
    return false;
}



bool tetris_shape::checkleftcollision(tetris_shape BottomStack, int count){
    sf::Vector2f positionBottom;
    sf::Vector2f positionShape;

    for(int i=0; i<ShapeType; i++){
        positionShape=Shape[i].getPosition();
        for(int j=0; j<count; j++){
            positionBottom=BottomStack.Shape[j].getPosition();
            if(((positionShape.x==positionBottom.x+BoxSize)&&(positionShape.y==positionBottom.y))||
                    (positionShape.x<150)){
                return true;
            }
        }
    }
    return false;
}




bool tetris_shape::checkbottomcollision(tetris_shape BottomStack, int count){
    sf::Vector2f positionBottom;
    sf::Vector2f positionShape;





    for(int i=0; i<ShapeType; i++){
        positionShape=Shape[i].getPosition();


        for(int j=0; j<count; j++){
            positionBottom=BottomStack.Shape[j].getPosition();


            if(((positionShape.x==positionBottom.x)&&(positionShape.y==(positionBottom.y-BoxSize)))||(within_bordersBottom()==false))
                {

                return true;
            }
        }

    }
    return false;
}




//finds the position closest to the left border
int tetris_shape::leftmost_pos(){
    sf::Vector2f position;
    int x_pos=Center;
    for (int i=0; i<ShapeType; i++){
        position=Shape[i].getPosition();
        if (position.x<x_pos){
            x_pos=position.x;
        }
    }
    return x_pos;
}




//finds the position closest to the right border
int tetris_shape::rightmost_pos(){
    sf::Vector2f position;
    int x_pos=Center;
    for (int i=0; i<ShapeType; i++){
        position=Shape[i].getPosition();
        if (position.x>x_pos){
            x_pos=position.x;
        }

    }
    return x_pos;
}




//finds the position clostest to the bottom
int tetris_shape::bottom_pos(){
    sf::Vector2f position;
    int y_pos=0;
    for (int i=0; i<ShapeType; i++){
        position=Shape[i].getPosition();
        if (position.y>y_pos){
            y_pos=position.y;
        }
    }
    return y_pos;
}




void tetris_shape::InitalizeColor(){
    for (int i=0; i<ShapeType; i++){
        Shape[i].setFillColor(sf::Color::Transparent);
        Shape[i].setSize(sf::Vector2f(BoxSize-2,BoxSize-2));
        Shape[i].setOutlineThickness(2);
    }
}



//counts bottom stack
//returns true if there are 10 in a row, false if not
bool tetris_shape::CountFilledLines(int y, int &boxcount, int shapecount){
    sf::Vector2f ShapePosition;
    for(int i=0; i<shapecount; i++){
        ShapePosition=Shape[i].getPosition();
        if (ShapePosition.y==y){
            boxcount++;
        }
        if(boxcount==10){
            return true;
        }
    }
    return false;
}


//finds the rectangles with the same coordinates
//sends the rectangles without the same coordinates to copy to another temporary shape
//returns the shape
tetris_shape tetris_shape::clearfilledline(int filledline, int &count, int shapecount){
    sf::Vector2f ShapePosition;
    tetris_shape tempshape;

    int j=0;
    for(int i=0; i<shapecount; i++){
        ShapePosition=Shape[i].getPosition();
        if(ShapePosition.y!=filledline)
        {
            tempshape.CopyRectangle(Shape[i], j);
            j++;

        }
    }
        count=j;
        return tempshape;

}

//returns true if it is a real shape of atleast 1 rectangle
//returns false if the shape has cleared
bool tetris_shape::CheckShapeCount(int filledline, int shapecount){
    sf::Vector2f ShapePosition;
    int j=0;
    for(int i=0; i<shapecount; i++){
        ShapePosition=Shape[i].getPosition();
        if(ShapePosition.y!=filledline)
        {
            j++;
        }
    }
    if(j>0){
        return true;
    }
    else{
        return false;
    }
}


//copies a rectangle to a temporary shape
void tetris_shape::CopyRectangle(sf::RectangleShape otherShape, int j){
    Shape[j].setSize(sf::Vector2f(BoxSize-1,BoxSize-1));
    Shape[j].setOutlineThickness(1);
    Shape[j].setOutlineColor(sf::Color::Black);
    Shape[j].setPosition(otherShape.getPosition());
    Shape[j].setFillColor(otherShape.getFillColor());


}


//drops the bottom stack after line is cleared
void tetris_shape::dropbottomstack(int filledline, int count){
    sf::Vector2f ShapePosition;
    for(int i=0; i<count; i++){
        ShapePosition=Shape[i].getPosition();
        if(ShapePosition.y<filledline){
            Shape[i].move(0, BoxSize);
        }
    }
}




bool tetris_shape::checkgameover(int count){
    sf::Vector2f ShapePosition;
    for(int i=0; i<count; i++){
        ShapePosition=Shape[i].getPosition();
        if(ShapePosition.y==-BoxSize){
            return true;
        }
    }
    return false;
}



bool tetris_shape::checkrotatecollision(tetris_shape BottomStack, int count){
    sf::Vector2f positionBottom;
    sf::Vector2f positionShape;

    for(int i=0; i<ShapeType; i++){
        positionShape=Shape[i].getPosition();
        for(int j=0; j<count; j++){
            positionBottom=BottomStack.Shape[j].getPosition();
            if(((positionShape.x==positionBottom.x)&&(positionShape.y==positionBottom.y))
                    ||(positionShape.x<150)||(positionShape.x>400-BoxSize))
            {
                return true;
            }
        }
    }
    return false;
}

