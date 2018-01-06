//
//  SnakeApp.hpp
//  Snake
//
//  Created by 林杰穎 on 2018/1/6.
//
//

#ifndef SnakeApp_h
#define SnakeApp_h

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "Snake.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class SnakeApp : public App {
private:
    Snake snake;
    SnakeGame game;
    gl::Texture2dRef startHintTexture;
    gl::Texture2dRef dogHeadTexture;
    bool gameIsRuning = false;
    
    void drawStartDimmer();
public:
    void setup() override;
    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
    void update() override;
    void draw() override;
};


#endif /* SnakeApp_h */
