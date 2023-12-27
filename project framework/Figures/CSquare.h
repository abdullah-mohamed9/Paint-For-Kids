#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;
	int length;
public:
	CSquare(Point, int, GfxInfo FigureGfxInfo);
	virtual bool isInside(int x, int y);
	virtual void DrawMe(GUI* pOut) const;
	void printInfo(GUI* pGUI, int);
};

#endif