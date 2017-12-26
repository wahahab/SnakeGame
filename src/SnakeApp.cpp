#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SnakeApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void SnakeApp::setup()
{
}

void SnakeApp::mouseDown( MouseEvent event )
{
}

void SnakeApp::update()
{
}

void SnakeApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SnakeApp, RendererGl )
