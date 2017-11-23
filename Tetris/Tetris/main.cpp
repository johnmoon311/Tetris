#include <iostream>
#include <SFML/Graphics.hpp>
#include "tetris_shape.h"
#include "Vector_shapes.h"
#include <time.h>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

string int2String (int number);


using namespace std;

int main()
{   srand(time(0));

    Vector_shapes NextShape;
    Vector_shapes BottomStack;
    Vector_shapes CurrentShapeOutline;
    double difficulty=1.3*1000;// calls moveDown this many times every second. 1000 cuz in miliseconds
    //int count=0;

    bool pause=false;
    bool gamestartscreen=true;
    bool gameinplay=false;

    int BottomStackCount=0, filledline=0, total_lines_cleared=0;

    NextShape.IntializeShapes();
    CurrentShapeOutline.CopyShapetoVector(NextShape);
    CurrentShapeOutline.IntializeShapeOutline(NextShape);

    sf::RenderWindow window(sf::VideoMode(550,500), "Tetris", sf::Style::Resize | sf::Style::Close); //opens a 800x600 window called Tetris, that is resizeable and has a close button.

    sf::RectangleShape backgroud(sf::Vector2f(10.0*BoxSize,20.0*BoxSize));


    sf::Clock clock; //keeps track in microSeconds how much time has elapsed  (1 second= 1,000,000 microSeconds)

    sf:: Time time; //holds the value from clock, but time can return micro,mili, or normal seconds.


    window.setKeyRepeatEnabled(false); //disables the thing that when you hold down a button it spams that key

    //--------------------------text-----------------------------------------------

    sf::Font MarioFont;
    if (!MarioFont.loadFromFile("RealMarioFont.ttf"))
        cout<<"Font file not found!"<<endl;

    sf::Text pausedText;
    pausedText.setFont(MarioFont);
    pausedText.setString("PAUSED");
    pausedText.setCharacterSize(50);
    pausedText.setColor(sf::Color::Yellow);
    pausedText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    pausedText.setPosition(170,120);


    sf::Text startText;
    startText.setFont(MarioFont);
    startText.setString("START");
    startText.setCharacterSize(50);
    startText.setColor(sf::Color::White);
    startText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    startText.setPosition(175,250);




    //--------------------------image-----------------------------------------------

    sf::Texture HUDTexture;
    sf::Sprite HUD;
    if (!HUDTexture.loadFromFile("TetrisBackgroundv3.png"))
        cout<<"File not found."<<endl;

    HUD.setTexture(HUDTexture);
    HUD.setPosition(0,0);


    sf::Texture startMenuTexture;
    sf::Sprite startMenu;
    if (!startMenuTexture.loadFromFile("RealTetrisStartMenu.png"))
        cout<<"File not found."<<endl;

    startMenu.setTexture(startMenuTexture);
    startMenu.setPosition(0,0);
    //-----------------------------GameOver---------------------------------------

    sf::Texture gameoverTexture;
    sf::Sprite gameover;
    if (!gameoverTexture.loadFromFile("game_over_by_mikeandlex.png"))
        cout<<"File not found."<<endl;

    gameover.setTexture(gameoverTexture);
    gameover.setPosition(0,0);
    gameover.setScale(.65, .57);

    sf::Text restartText;
    restartText.setFont(MarioFont);
    restartText.setString("RESTART?");
    restartText.setCharacterSize(50);
    restartText.setColor(sf::Color::Red);
    restartText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    restartText.setPosition(150,425);

    sf::RectangleShape restarttextBox; //when mouse goes in or clicks this box, run some kind of program...
    int restarttextBox_Xpos=150;
    int restarttextBox_Ypos=435;
    int restarttextBox_Xsize=280;
    int restarttextBox_Ysize=60;
    restarttextBox.setFillColor(sf::Color::Transparent);
    restarttextBox.setSize(sf::Vector2f(restarttextBox_Xsize,restarttextBox_Ysize));
    restarttextBox.setPosition(restarttextBox_Xpos,restarttextBox_Ypos);


    sf::Text linesClearedText;
    linesClearedText.setFont(MarioFont);
    linesClearedText.setString("0");
    linesClearedText.setCharacterSize(40);
    linesClearedText.setColor(sf::Color::White);
    linesClearedText.setStyle(sf::Text::Bold);
    linesClearedText.setPosition(75,325);

    //-------------------------------sound-------------------------------------------
    sf::Music music;
    if(!music.openFromFile("Super Mario Bros Official Theme Song.wav")){
        cout<<"didnt load";
    }

    sf::SoundBuffer gameoverbuffer;
    sf::Sound gameoversound;
    if(!gameoverbuffer.loadFromFile("Homer Simpson Doh sound effect.wav")){
        cout<<"didn't load!!";
    }

    gameoversound.setBuffer(gameoverbuffer);



    sf::SoundBuffer play_pausebuffer;
    sf::Sound play_pause;
    if(!play_pausebuffer.loadFromFile("Nelson.wav")){
        cout<<"didnt load nelson";
    }

    play_pause.setBuffer(play_pausebuffer);

    sf::SoundBuffer startsoundbuffer;
    sf::Sound startsound;
    if(!startsoundbuffer.loadFromFile("&quot;Let's Get Ready To Rumble&quot; Phrase From Rocky VI.wav")){
        cout<<"didnt load sparta";
    }

    startsound.setBuffer(startsoundbuffer);


    sf::SoundBuffer lineclearedbuffer;
    sf::Sound lineclearsound;
    if(!lineclearedbuffer.loadFromFile(("Homer Simpson Woohoo Sound FX.wav"))){
        cout<<"didnt load sound";
    }

    lineclearsound.setBuffer((lineclearedbuffer));
    //---------------------------------------------------------------------

    while(window.isOpen())
    {
        sf::Event event;
        //---------------------Title screen---------------------------------
        sf::RectangleShape textBox; //when mouse goes in or clicks this box, run some kind of program...
        int textBox_Xpos=175;
        int textBox_Ypos=263;
        int textBox_Xsize=180;
        int textBox_Ysize=50;
        textBox.setFillColor(sf::Color::Transparent);
        textBox.setSize(sf::Vector2f(textBox_Xsize,textBox_Ysize));
        textBox.setPosition(textBox_Xpos,textBox_Ypos);

        while(gamestartscreen)
        {
            window.draw(startMenu);
            window.draw(textBox);
            window.draw(startText);



            window.display();

            sf::Vector2i mousePosition=sf::Mouse::getPosition(window); //debug: outputs current mouse position

            if ((mousePosition.x>=textBox_Xpos && mousePosition.x<=textBox_Xpos+textBox_Xsize) && (mousePosition.y>=textBox_Ypos && mousePosition.y<=textBox_Ypos+textBox_Ysize)) //if mouse is within the box...
            {
                startText.setColor(sf::Color::Yellow); //sets the text to yellow if mouse is inside box

            }
            else
            {
                startText.setColor(sf::Color::White);//sets text color to white if mouse is outside the box
            }

            while(window.pollEvent(event))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //when left mouse button is clicked run this
                {
                    if ((mousePosition.x>=textBox_Xpos && mousePosition.x<=textBox_Xpos+textBox_Xsize) && (mousePosition.y>=textBox_Ypos && mousePosition.y<=textBox_Ypos+textBox_Ysize)) //if mouse clicks the box...                    {
                    {
                        startsound.play();
                        startsound.setPlayingOffset(sf::seconds(6));
                        music.play();
                        music.setLoop(true);
                        gamestartscreen=false;//if mouse clicks the box, turn the game on.
                        gameinplay=true;
                    }
                }

                if((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) //closes the window when X is clicked or esc is pressed
                {
                    window.close();
                    exit(0);
                }
            }

        }


        //----------------------------------------------GAMEOVER-----------------------------------------------

        while(!gameinplay)
        {
            window.clear();
            window.draw(gameover);
            window.draw(restarttextBox);
            window.draw(restartText);

            window.display();



            sf::Vector2i mousePosition=sf::Mouse::getPosition(window);



            if ((mousePosition.x>=restarttextBox_Xpos && mousePosition.x<=restarttextBox_Xpos+restarttextBox_Xsize) && (mousePosition.y>=restarttextBox_Ypos && mousePosition.y<=restarttextBox_Ypos+textBox_Ysize)) //if mouse is within the box...
            {
                restartText.setColor(sf::Color::Yellow); //sets the text to yellow if mouse is inside box

            }
            else
            {
                restartText.setColor(sf::Color::Red);//sets text color to white if mouse is outside the box
            }

            while(window.pollEvent(event))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //when left mouse button is clicked run this
                {
                    if ((mousePosition.x>=restarttextBox_Xpos && mousePosition.x<=restarttextBox_Xpos+restarttextBox_Xsize) && (mousePosition.y>=restarttextBox_Ypos && mousePosition.y<=restarttextBox_Ypos+restarttextBox_Ysize)) //if mouse clicks the box...                    {
                    {
                        startsound.play();
                        startsound.setPlayingOffset(sf::seconds(6));
                        music.play();
                        music.setLoop(true);
                        gameinplay=true;
                    }
                }

                if((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) //closes the window when X is clicked or esc is pressed
                {
                    window.close();
                    exit(0);

                }
            }

        }

        //------------------------------------------------------------------------------------------------------

        while(gameinplay){
            while(window.pollEvent(event))
            {
                if(!pause)
                {

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        if(NextShape.CheckLeftCollision(BottomStack, BottomStackCount)){
                            NextShape.MoveCurrentShapeLeft();
                            CurrentShapeOutline.IntializeShapeOutline(NextShape);
                        }


                    }


                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        if(NextShape.CheckRightCollision(BottomStack, BottomStackCount)){
                            NextShape.MoveCurrentShapeRight();
                            CurrentShapeOutline.IntializeShapeOutline(NextShape);

                        }


                    }


                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        if(NextShape.CheckBottomCollision(BottomStack, BottomStackCount)){
                            BottomStack.CopyShapetoVector(NextShape);
                            NextShape.GetNextShape();
                            CurrentShapeOutline.IntializeShapeOutline(NextShape);
                            BottomStack.KeepShapeCount(BottomStackCount);
                            BottomStackCount++;

                        }
                        else{
                            NextShape.MoveCurrentShapeDown();

                        }


                    }

                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        if (window.waitEvent(event)){
                            NextShape.RotateCurrentShape(BottomStack, BottomStackCount);
                            CurrentShapeOutline.IntializeShapeOutline(NextShape);
                        }

                    }
                }
                if (event.type==sf::Event::KeyReleased) // pause function is in progress... (can pause, but user is still able to move around)
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        pause = (pause == true ? false : true); //turnary operator: if pause=true, change it to false. if pause=false, change it to true.

                        if (pause)
                        {
                            play_pause.play();
                            music.pause();
                        }

                        if (!pause)
                        {

                            music.play();
                        }

                    }

                    if(event.key.code == sf::Keyboard::Space)
                    {
                        while(NextShape.CheckBottomCollision(BottomStack, BottomStackCount)==false){
                            NextShape.MoveCurrentShapeDown();
                        }
                        BottomStack.CopyShapetoVector(NextShape);
                        NextShape.GetNextShape();
                        CurrentShapeOutline.IntializeShapeOutline(NextShape);
                        BottomStack.KeepShapeCount(BottomStackCount);
                        BottomStackCount++;

                    }
                }

                if (event.type==sf::Event::LostFocus) //pauses the game if window isn't focused
                {
                    pause=true;
                    music.pause();

                }

                if (event.type==sf::Event::GainedFocus)// resumes the game if window is focused again
                {
                    pause=false;
                    music.play();

                }

                if ((event.type == sf::Event::Closed)||(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                {
                    window.close();
                    exit(0);
                }



            }


            if(!pause)
            {
                //-----------time----------------
                time=clock.getElapsedTime(); //sets the time variable to the elapsed time, given by clock.

                if (time.asMilliseconds()>=difficulty-time.asMilliseconds()) //every 1 second move [difficulty] amount of times while accounting for lag
                {

                    if(NextShape.CheckBottomCollision(BottomStack, BottomStackCount))
                    {
                        BottomStack.CopyShapetoVector(NextShape);
                        NextShape.GetNextShape();
                        CurrentShapeOutline.IntializeShapeOutline(NextShape);
                        BottomStack.KeepShapeCount(BottomStackCount);
                        BottomStackCount++;

                    }
                    else
                    {
                        NextShape.MoveCurrentShapeDown();
                    }
                    //                    cout<<"DEBUG time: "<<time.asMilliseconds()<<" Lag: "<<time.asMilliseconds()-(difficulty-time.asMilliseconds())<<endl;
                    clock.restart();

                }

                while(CurrentShapeOutline.CheckBottomCollision(BottomStack, BottomStackCount)==false){
                    CurrentShapeOutline.MoveCurrentShapeDown();
                }

                if(BottomStack.CheckFilledLines(BottomStackCount, filledline)){

                    lineclearsound.play();
                    lineclearsound.setPlayingOffset(sf::seconds(1));
                    BottomStack.ClearFilledLine(BottomStackCount, filledline);
                    BottomStack.DropBottomStack(BottomStackCount, filledline);
                    total_lines_cleared++;
                    linesClearedText.setString(int2String(total_lines_cleared)); //converts the amount of lines cleared into a string
                    filledline=0;

                    if(total_lines_cleared%7==0){
                        difficulty=difficulty-(.1*1000);
                        cout<<"difficulty is: "<<difficulty<<endl;
                    }
                }


                if(BottomStack.CheckGameOver(BottomStackCount)){
                    music.stop();
                    startsound.stop();
                    gameoversound.play();
                    BottomStack.ClearAll();
                    NextShape.ClearAll();
                    NextShape.IntializeShapes();
                    CurrentShapeOutline.CopyShapetoVector(NextShape);
                    CurrentShapeOutline.IntializeShapeOutline(NextShape);
                    total_lines_cleared=0;
                    linesClearedText.setString("0");
                    BottomStackCount=0;
                    difficulty=1.3*1000;
                    gameinplay=false;
                }

                window.clear();


                backgroud.setPosition(sf::Vector2f(150.0, 0.0));

                backgroud.setFillColor(sf::Color(500, 200, 200));
                window.draw(backgroud);
                window.draw(HUD);
                window.draw(linesClearedText);


                NextShape.DrawVector(window, 4);
                BottomStack.DrawBottomVector(window, BottomStackCount);
                CurrentShapeOutline.DrawVector(window, 1);



                window.display();
            }
            else
            {
                window.draw(pausedText);
                window.display();
            }

        }


    }
    return 0;

}
string int2String (int number)
{
    string aString="";
    char aChar;

    int i=1;//can't divide by 0
    for  (i; i<=number; i=i*10); //this chunk finds how many places a number has, by multiplying i by 10 until it is bigger than the number, then dividing i by 10 once, cuz it is now off by one.
    i=i/10; //accounts for off by one

    while (i>0)
    {
        aChar=(number/i)+'0'; //converts a int to a char
        aString=aString+aChar; //adds the char at the end of the string

        number=number%i; //12345 becomes 2345 becomes 345 etc...
        i=i/10; //changes the decimal place
    }

    return aString;
}


