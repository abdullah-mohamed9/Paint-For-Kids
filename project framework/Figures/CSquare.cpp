#include <sstream>
#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}


void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}
bool CSquare::isInside(int x, int y) {
	int x1 = TopLeftCorner.x;
	int y1 = TopLeftCorner.y;
	int x2 = TopLeftCorner.x + length;
	int y2 = TopLeftCorner.y + length;
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
void CSquare::printInfo(GUI* pGUI, int x)
{
	pGUI->ClearStatusBar();
	stringstream msg;
	msg << "ID:" << x + 1 << " Square , P1 (" << TopLeftCorner.x << " , " << (TopLeftCorner.y) << ") , P2 (" << TopLeftCorner.x + length << " , " << TopLeftCorner.y + length << " , Area:" << pow(length, 2);
	pGUI->PrintMessage(msg.str());
}

