//
//  Snake.cpp
//  Snake
//
//  Created by 林杰穎 on 2018/1/6.
//
//

#include <stdio.h>

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/Rand.h"

#include "Snake.h"

using namespace ci;
using namespace ci::app;

Snake::Snake() {
    MyLine startLine;
    Dot startPoint;
    
    foodIntake = 0;
    width = .05;
    turning = false;
    turningRight = false;
    startPoint.x = .5;
    startPoint.y = .5;
    startLine.origin = startPoint;
    startLine.length = .1;
    startLine.deg = deg = M_PI / 4.5;
    lines.push_back(startLine);
}
list<MyLine> & Snake::getLines() {
    return lines;
}

SnakeGame::SnakeGame() {
    candyDot = { static_cast<float>(((rand() % 99) + 1) / 100.),
        static_cast<float>(((rand() % 99) + 1) / 100.) };
}
void SnakeGame::turnRight() {
    snake.turning = true;
    snake.turningRight = true;
}
void SnakeGame::turnLeft() {
    snake.turning = true;
    snake.turningRight = false;
}
void SnakeGame::stopTurning() {
    snake.turning = false;
}
bool SnakeGame::gameIsOver() {
    auto snakeLines = snake.getLines();
    auto lineIt = snakeLines.begin();
    auto head = snakeLines.front();
    auto headPoint = head.getPoint(1.);
    float dist;
    
    for (; lineIt != snakeLines.end(); lineIt++) {
        dist = lineIt->minDistToDot(headPoint);
        if (dist > snake.width * 2)
            break;
    }
    for (; lineIt != snakeLines.end(); lineIt++) {
        dist = lineIt->minDistToDot(headPoint);
        if (dist <= snake.width * 2)
            return true;
    }
    return false;
}
void SnakeGame::draw(gl::Texture2dRef snakeHeadTexture) {
    float length;
    float x;
    float y;
    int windowHeight = getWindowHeight();
    auto snakeLines = snake.getLines();
    int width;
    MyLine headLine = snakeLines.front();
    Color bodyColor;
    
    bodyColor = snake.foodIntake > 0 ?
        Color(0, 1, 0) : Color(1, 0, 0);
    cout << snake.foodIntake << endl;
    gl::color(bodyColor);
    // draw dog image on head
    for(auto &l : snakeLines) {
        x = windowHeight * l.origin.x;
        y = windowHeight * l.origin.y;
        length = windowHeight * l.length;
        width = windowHeight * snake.width;
        gl::pushModelMatrix();
        gl::translate(vec2(x, y));
        gl::rotate(l.deg);
        gl::drawSolidRect(Rectf(0, 0 + width / 2,
                                length, 0 - width / 2));
        gl::popModelMatrix();
    }
//    draw snake head
    x = windowHeight * headLine.origin.x;
    y = windowHeight * headLine.origin.y;
    length = windowHeight * headLine.length;
    width = windowHeight * snake.width;
    gl::pushModelMatrix();
    gl::translate(vec2(x, y));
    gl::rotate(headLine.deg - M_PI);
    gl::color(1, 1, 1);
    gl::draw(snakeHeadTexture,
             Rectf(-length - width,
                   width,
                   -length + width,
                   -width));
    gl::popModelMatrix();
    // draw candy
    gl::color(Color(0, 0, 1));
    gl::drawSolidCircle(vec2(windowHeight * candyDot.x, windowHeight * candyDot.y),
                        windowHeight * candyRadius);
}
void SnakeGame::tick() {
    auto &snakeLines = snake.getLines();
    auto &head = snakeLines.front();
    auto &tail = snakeLines.back();
    MyLine newLine;
    Dot headDot;
    vec2 dir;
    float distToCandy;
    
    if (snake.turning) {
        snake.deg = snake.turningRight ? snake.deg + turnDeg :
        snake.deg - turnDeg;
    }
    if (head.deg == snake.deg) {
        head.length += speed;
    } else {
        newLine.origin = head.getPoint(1.);
        newLine.deg = snake.deg;
        newLine.length = speed;
        snakeLines.push_front(newLine);
    }
    headDot = head.getPoint(1.);
    if (headDot.x > 1. || headDot.x < 0.
        || headDot.y > 1. || headDot.y < 0.) {
        head.length -= speed;
        newLine.origin = {
            static_cast<float>(fmod(headDot.x + 1., 1.)),
            static_cast<float>(fmod(headDot.y + 1., 1.))
        };
        newLine.deg = snake.deg;
        newLine.length = speed;
        if (head.length <= 0)
            snakeLines.pop_front();
        snakeLines.push_front(newLine);
    }
    // check game is over or not
    if (gameIsOver())
        dead = true;
    // check distance between candy and snake
    headDot = snakeLines.front().getPoint(1.);
    dir = vec2(candyDot.x, candyDot.y) - vec2(headDot.x, headDot.y);
    distToCandy = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (distToCandy <= (candyRadius + snake.width)) {
        snake.foodIntake += static_cast<int>(candyRadius * 100);
        candyDot = {
            randFloat(.01, .99),
            randFloat(.01, .99),
        };
        candyRadius = randFloat(.01, .05);
    }
    if (snake.foodIntake > 0)
        snake.foodIntake--;
    else {
        tail.origin = tail.getPoint(speed / tail.length);
        tail.length -= speed;
        if (tail.length <= 0)
            snakeLines.pop_back();
    }
}
bool SnakeGame::isDead() {
    return dead;
}
