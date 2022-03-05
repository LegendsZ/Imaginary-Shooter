#include "Heart.h"

Heart::Heart(int x, int y):
	m_X(x), m_Y(y), m_Rect(new Rect(50,50, x,y, heartPNG_path))
{
	
}

Heart::~Heart()
{
	m_Rect->~Rect();
	delete m_Rect;
}

void Heart::draw()
{
	m_Rect->draw();
}
