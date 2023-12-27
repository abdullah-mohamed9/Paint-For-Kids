#include "CFigure.h"

class CHexagon : public CFigure
{
    int SideLength;
    int Height;
    Point TopLeft;

public:
    CHexagon(Point, int, int, GfxInfo FigureGfxInfo);
    void DrawMe(GUI*) const;
    virtual bool isInside(int x, int y);
    void printInfo(GUI* pGUI, int);
};
