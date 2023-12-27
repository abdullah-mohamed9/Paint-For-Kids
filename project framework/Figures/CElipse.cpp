#include "CElipse.h"


//CElipse::CElipse() {}
CElipse::CElipse(Point p1, Point p2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	One = p1;
	Two = p2;
}

void CElipse::DrawMe(GUI* pGUI) const
{
	// Call Output::DrawRect to draw a Square on the screen
	pGUI->DrawElipse(One, Two, FigGfxInfo, Selected);
}
bool CElipse::isInside(int x, int y) {
	double height = abs(Two.x - One.x) / 2;
	double width = abs(Two.y - One.y) / 2;
	double x0 = (Two.x + One.x) / 2;
	double y0 = (Two.y + One.y) / 2;
	return ((pow((x - x0) / height, 2) + pow((y - y0) / width, 2)) <= 1);
}
void CElipse::printInfo(GUI* pGUI, int x)
{
	pGUI->ClearStatusBar();
	Point center;
	center.x = 0.5 * (Two.x + One.x);
	center.y = 0.5 * (Two.y + One.y);
	float height = abs(Two.x - One.x) / 2;
	float width = abs(Two.y - One.y) / 2;
	stringstream msg;
	msg << "ID:" << x + 1 << " Ellipse , Center (" << center.x << " , " << center.y << " , Area:" << 3.14 * height * width << ")";
	pGUI->PrintMessage(msg.str());
}