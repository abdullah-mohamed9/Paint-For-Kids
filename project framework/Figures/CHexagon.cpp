#include "CHexagon.h"


CHexagon::CHexagon(Point point, int len, int height, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	TopLeft = point;
	SideLength = len;
	Height = height;

}

void CHexagon::DrawMe(GUI* pGUI) const
{
	pGUI->DrawHexagon(TopLeft, SideLength, Height, FigGfxInfo, Selected);
}
void CHexagon::printInfo(GUI* pGUI, int x)
{
	pGUI->ClearStatusBar();

	stringstream msg;
	msg << "ID:" << x + 1 << " Hexagon" ", Side Length:" << SideLength << " , Height:" << Height << " , Area:" << ((3 * sqrt(3)) / 2) * pow(SideLength, 2);
	pGUI->PrintMessage(msg.str());
}

bool CHexagon::isInside(int x, int y) {
	double a = SideLength / 2;
	double b = Height / 2;
	double x0 = TopLeft.x + a;
	double y0 = TopLeft.y + b;
	return ((pow((x - x0) / a, 2) + pow((y - y0) / b, 2)) <= 1) && (y >= TopLeft.y) && (y <= TopLeft.y + Height) && (x >= TopLeft.x) && (x <= TopLeft.x + SideLength);
}

