//
//  Snake.h
//  Snake
//
//  Created by 林杰穎 on 2018/1/6.
//
//

#ifndef Snake_h
#define Snake_h

using namespace std;
using namespace cinder;

typedef struct _Dot {
    float x;
    float y;
    
    float disTo(_Dot p) {
        auto xDiff = x - p.x;
        auto yDiff = y - p.y;
        return sqrt(xDiff * xDiff + yDiff * yDiff);
    };
} Dot;

typedef struct {
    Dot origin;
    float length;
    float deg;
public:
    Dot getPoint(float percent) {
        float len = (length * percent);
        Dot to_return = {
            origin.x + len * cos(deg),
            origin.y + len * sin(deg)
        };
        return to_return;
    }
    float minDistToDot(Dot point) {
        float percent = 0;
        float minDist = MAXFLOAT;
        float dist;
        
        while (percent <= 1.0) {
            dist = getPoint(percent).disTo(point);
            if (dist < minDist)
                minDist = dist;
            percent += .25;
        }
        return minDist;
    }
} MyLine;

class Snake {
private:
    list<MyLine> lines;
public:
    float width;
    float deg;
    bool turning;
    bool turningRight;
    int foodIntake;
    
    Snake();
    list<MyLine> & getLines();
};

class SnakeGame {
private:
    Snake snake;
    Dot candyDot;
    float speed = .005;
    float candyRadius = .01;
    float turnDeg = M_PI / 50;
    bool dead = false;
public:
    SnakeGame();
    void draw(gl::Texture2dRef);
    void tick();
    void turnRight();
    void turnLeft();
    void stopTurning();
    bool gameIsOver();
    bool isDead();
};

#endif /* Snake_h */
