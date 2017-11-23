#include "vector_shapes.h"

Vector_shapes::Vector_shapes()
{
    count[0]=4;
    for(int i=0; i<100; i++){
        count[i]=4;
    }
}



void Vector_shapes::IntializeShapes(){
    for (int i=0; i<5; i++){
        VectorShape.push_back(tetris_shape (rand()%7, 465, (i*100)+75));

    }
    VectorShape[0].MoveCenter();


    for(int i=1; i<4; i++){
        VectorShape[i].MoveToPosition(0, -100);
    }
}




void Vector_shapes::MoveCurrentShapeLeft(){
    VectorShape[0].MoveLeft();
    if (VectorShape[0].within_bordersLeft()==false){
        VectorShape[0].MoveRight();
    }
}




void Vector_shapes::MoveCurrentShapeRight(){
    VectorShape[0].MoveRight();
    if (VectorShape[0].within_bordersRight()==false){
        VectorShape[0].MoveLeft();
    }
}




void Vector_shapes::MoveCurrentShapeDown(){
    if(VectorShape[0].within_bordersBottom()==true){
        VectorShape[0].MoveDown();
    }

}




void Vector_shapes::GetNextShape(){
    for (int i=0; i<3; i++){
        VectorShape[i].CopyShape(VectorShape[i+1]);

    }
    for(int i=1; i<4; i++){
        VectorShape[i].MoveToPosition(0, -100);

    }
    VectorShape[0].MoveCenter();

    VectorShape[3].CopyShape(tetris_shape(rand()%7, 465, 275));

}




void Vector_shapes::RotateCurrentShape(Vector_shapes BottomStack, int bottomcount){


    int moveleftcount=0;
    int moverightcount=0;
    int rotatedirection=0;
    int rotatecount=0;
    bool checkbottom, is_rotatable=false;

    for(int i=0; i<bottomcount; i++){
        if(VectorShape[0].checkrightcollision(BottomStack.VectorShape[i], count[i])==false){
            rotatecount++;

        }

    }
    for(int i=0; i<bottomcount ;i++){
        if(VectorShape[0].checkleftcollision(BottomStack.VectorShape[i], count[i])==false){
            rotatecount++;

        }

        checkbottom=VectorShape[0].checkbottomcollision(BottomStack.VectorShape[i], count[i]);
    }

    if(rotatecount>(bottomcount*2)-2){
        is_rotatable=true;
    }

    if(bottomcount>0){
        if(is_rotatable){

            if(checkbottom==false){


                for (int i=0;i<bottomcount; i++){


                    if(VectorShape[0].checkrightcollision(BottomStack.VectorShape[i], count[i])==true){
                        rotatedirection=1;
                    }
                    else if(VectorShape[0].checkleftcollision(BottomStack.VectorShape[i], count[i])==true){
                        rotatedirection=2;
                    }
                    else if((VectorShape[0].checkleftcollision(BottomStack.VectorShape[i], count[i])==false)&&
                            (VectorShape[0].checkrightcollision(BottomStack.VectorShape[i], count[i])==false))
                    {
                        rotatedirection=3;
                    }


                }


                VectorShape[0].PivotShape();


                for(int i=0; i<bottomcount; i++){
                    if(VectorShape[0].checkbottomcollision(BottomStack.VectorShape[i], count[i])==true){
                        VectorShape[0].PivotShapeBack();
                        return;
                    }

                    switch(rotatedirection){
                    case 1:
                        while(VectorShape[0].checkrotatecollision(BottomStack.VectorShape[i],count[i])){
                            VectorShape[0].MoveLeft();
                            moveleftcount++;
                            for(int j=0; j<bottomcount; j++){
                                if((VectorShape[0].checkrotatecollision(BottomStack.VectorShape[j], count[j])==true)&&
                                        (VectorShape[0].checkleftcollision(BottomStack.VectorShape[j], count[j]))){
                                    for(int i=0; i<moveleftcount; i++){
                                        VectorShape[0].MoveRight();


                                    }

                                    VectorShape[0].PivotShapeBack();
                                    return;
                                }
                            }
                        }

                        break;


                    case 2:
                        while(VectorShape[0].checkrotatecollision(BottomStack.VectorShape[i],count[i])){
                            VectorShape[0].MoveRight();
                            moverightcount++;
                            for(int j=0; j<bottomcount; j++){
                                if((VectorShape[0].checkrotatecollision(BottomStack.VectorShape[j],count[j])==true)&&
                                        (VectorShape[0].checkrightcollision(BottomStack.VectorShape[j], count[j])))
                                    for(int i=0; i<moverightcount; i++){
                                        VectorShape[0].MoveLeft();


                                    }

                                VectorShape[0].PivotShapeBack();
                                return;
                            }

                        }



                        break;


                    case 3:

                        if((VectorShape[0].checkleftcollision(BottomStack.VectorShape[i], count[i])==true)){
                            while(VectorShape[0].checkrotatecollision(BottomStack.VectorShape[i], count[i])){
                                VectorShape[0].MoveRight();
                                moverightcount++;
                                for(int j=0; j<bottomcount; j++){
                                    if((VectorShape[0].checkrotatecollision(BottomStack.VectorShape[j],count[j])==true)){
                                        for(int i=0; i<moverightcount; i++){
                                            VectorShape[0].MoveLeft();


                                        }

                                        VectorShape[0].PivotShapeBack();
                                        return;
                                    }
                                }
                            }

                        }

                        else if(VectorShape[0].checkrightcollision(BottomStack.VectorShape[i], count[i])==true){

                            while(VectorShape[0].checkrotatecollision(BottomStack.VectorShape[i],count[i])){
                                VectorShape[0].MoveLeft();
                                moveleftcount++;
                                for(int j=0; j<bottomcount; j++){
                                    if((VectorShape[0].checkrotatecollision(BottomStack.VectorShape[j], count[j])==true)){
                                        for(int i=0; i<moveleftcount; i++){
                                            VectorShape[0].MoveRight();


                                        }

                                        VectorShape[0].PivotShapeBack();
                                        return;
                                    }
                                }

                            }
                        }

                        break;




                    }


                }

            }

        }
    }
    else{
        VectorShape[0].PivotShape();
        while(VectorShape[0].within_bordersRight()==false){
            VectorShape[0].MoveLeft();

        }
        while(VectorShape[0].within_bordersLeft()==false){
            VectorShape[0].MoveRight();
        }

    }



}



void Vector_shapes::CopyShapetoVector(Vector_shapes CurrentShape){
    VectorShape.push_back(CurrentShape.VectorShape[0]);


}

bool Vector_shapes::CheckBottomCollision(Vector_shapes BottomStack, int bottomcount){
    if (VectorShape[0].within_bordersBottom()==false){
        return true;
    }


    for(int i=0; i<bottomcount; i++){
        if(VectorShape[0].checkbottomcollision(BottomStack.VectorShape[i], count[i])){
            return true;
        }
    }



    return false;


}
bool Vector_shapes::CheckLeftCollision(Vector_shapes BottomStack, int bottomcount){
    for(int i=0; i<bottomcount; i++){
        if(VectorShape[0].checkleftcollision(BottomStack.VectorShape[i], count[i])){
            return false;
        }
    }
    return true;
}

bool Vector_shapes::CheckRightCollision(Vector_shapes BottomStack, int bottomcount){
    for(int i=0; i<bottomcount; i++){
        if(VectorShape[0].checkrightcollision(BottomStack.VectorShape[i], count[i])){
            return false;
        }
    }
    return true;
}

//keeps the count of rectangles when shapes get copied on the bottom stack

void Vector_shapes::KeepShapeCount(int Shapecount){
    count[Shapecount]=4;
}

//draws the current shape, next shape, and bottom shape outline
void Vector_shapes::DrawVector(sf::RenderWindow &window, int totalcount){
    for (int i=0; i<totalcount; i++){
        VectorShape[i].DrawShape(window);
    }
}

//draws bottom  stack
void Vector_shapes::DrawBottomVector(sf::RenderWindow &window, int totalcount){
    for (int i=0; i<totalcount; i++){
        VectorShape[i].DrawBottomShape(window, count[i]);
    }
}


//for shape outline on bottom
void Vector_shapes::IntializeShapeOutline(Vector_shapes CurrentShape){
    VectorShape[0].CopyShape(CurrentShape.VectorShape[0]);
    VectorShape[0].InitalizeColor();
}


//moves shape up
void Vector_shapes::MoveCurrentShapeUp(){
    VectorShape[0].MoveUp();
}


//checks filled lines
//returns true if there are 10 filled lines, returns false if not
bool Vector_shapes::CheckFilledLines(int totalcount, int &filledline){
    for(int i=0; i<20; i++){
        int boxcount=0;
        for(int j=0; j<totalcount; j++){
            if(VectorShape[j].CountFilledLines(i*BoxSize, boxcount, count[j])){
                filledline=i*BoxSize;
                return true;


            }
        }
    }

    return false;

}

//drops the bottom stack when there are 10 lines filled
void Vector_shapes::DropBottomStack(int totalcount, int filledline){
    for(int j=0; j<totalcount; j++){
        VectorShape[j].dropbottomstack(filledline, count[j]);
    }

}

//if the shape is real with atleast one rectangle bottomstack will be copied to a temporary vector
//all rectangles will be copied execpt the line we need to clear
//the temporary vector without the line is then copied back to the regular bottomstack

void Vector_shapes::ClearFilledLine(int &totalcount, int filledline){
    vector<tetris_shape> TempBackground;
    int ShapeCount=0, stackedshapecount=0;

    for(int j=0; j<totalcount; j++){
        if(VectorShape[j].CheckShapeCount(filledline, count[j])){
            TempBackground.push_back(VectorShape[j].clearfilledline(filledline, ShapeCount, count[j]));
            count[stackedshapecount]=ShapeCount;
            stackedshapecount++;

        }

    }


    VectorShape.clear();

    for(int i=0; i<stackedshapecount; i++){
        VectorShape.push_back(TempBackground[i]);
    }

    totalcount=stackedshapecount;
}

bool Vector_shapes::CheckGameOver(int bottomcount){
    for(int i=0; i<bottomcount; i++){
        if(VectorShape[i].checkgameover(count[i])){
            return true;
        }
    }
    return false;
}

void Vector_shapes::ClearAll(){
    VectorShape.clear();

}
