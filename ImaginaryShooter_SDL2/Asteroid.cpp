#include "Asteroid.h"

int Asteroid::minMax[] = {2,2};

Asteroid::Asteroid(int w, int h, int x, int y, const std::string& img_path):
	m_Rect(new Rect(w,h,x,y,img_path))
{
	
}

Asteroid::~Asteroid()
{
	m_Rect->~Rect();
	delete m_Rect;
}

void Asteroid::draw()
{
	m_Rect->draw();
}

int* Asteroid::getPos()
{
	return m_Rect->getPos();
}

bool Asteroid::setPos(int x, int y)
{
	m_Rect->setPos(x, y);
	return true;
}