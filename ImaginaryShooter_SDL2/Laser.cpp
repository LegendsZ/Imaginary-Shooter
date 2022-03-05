#include "Laser.h"

Laser::Laser(int w, int h, int x, int y, const std::string& img_path):
	m_Rect(new Rect(w, h, x, y, img_path))
{

}

Laser::~Laser()
{
	m_Rect->~Rect();
	delete m_Rect;
}

void Laser::draw()
{
	m_Rect->draw();
}

int* Laser::getPos()
{
	return m_Rect->getPos();
}

bool Laser::setPos(int x, int y)
{
	m_Rect->setPos(x, y);
	return true;
}