#include <math.h>
#include <time.h>

#include "cinder/app/RendererGl.h"
#include "cinder/Text.h"
#include "cinder/Rand.h"

#include "SnakeApp.hpp"


void SnakeApp::keyUp(KeyEvent event) {
    switch (event.getCode()) {
        case 275:
        case 276:
            if (gameIsRuning)
                game.stopTurning();
    }
}
void SnakeApp::keyDown(KeyEvent event) {
    switch(event.getCode()) {
        case 32:
            gameIsRuning = true;
            break;
        case 112:
            gameIsRuning = false;
            break;
        case 275: // turn right
            if (gameIsRuning)
                game.turnRight();
            break;
        case 276: // turn left
            if (gameIsRuning)
                game.turnLeft();
            break;
    }
}
void SnakeApp::drawStartDimmer() {
    gl::enableAlphaBlending();
    gl::color(0, 0, 0, .8);
    gl::drawSolidRect(Rectf(0, 0, getWindowWidth(), getWindowHeight()));
    gl::pushModelMatrix();
    gl::translate(getWindowCenter() - vec2(startHintTexture->getWidth() / 2,
                                           startHintTexture->getHeight() / 2));
    gl::color(1, 1, 1);
    gl::draw(startHintTexture);
    gl::popModelMatrix();
    gl::disableAlphaBlending();
}
void SnakeApp::setup()
{
    TextLayout layout = TextLayout();
    
    // create pause hint texture
    layout.clear(ColorA(0.f, 0.f, 0.f, 0.f));
    layout.setFont(Font("Arial", 24));
    layout.setColor(Color(0, 1, 0));
    layout.addCenteredLine("Please press whitespace to start.");
    startHintTexture = gl::Texture2d::create(layout.render(true, false));
    // seed rand
    srand((unsigned int)time(NULL));
    // load snake head
    auto img = loadImage("/Users/wahahab/repos/Snake/assets/dog-head.png");
    dogHeadTexture = gl::Texture2d::create(img);
}
void SnakeApp::update()
{
    if (gameIsRuning)
        game.tick();
    if (game.isDead())
        gameIsRuning = false;
}
void SnakeApp::draw()
{
    gl::clear(Color(1, 1, 1));
    // translate origin to game area
    gl::pushModelMatrix();
    gl::translate((getWindowWidth() - getWindowHeight()) / 2, 0.);
    // draw game area border
    gl::color(Color(0, 0, 0));
    gl::lineWidth(1.);
    gl::drawStrokedRect(Rectf(1, 1, getWindowHeight() - 1, getWindowHeight() - 1));
    // draw game content
    game.draw(dogHeadTexture);
    gl::popModelMatrix();
    // if game is stoping, draw dimmer
    if (!gameIsRuning)
        drawStartDimmer();
}

CINDER_APP( SnakeApp, RendererGl )
