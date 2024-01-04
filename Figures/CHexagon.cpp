#include "CHexagon.h"


CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	TopLeft = P1;
	BottomRight = P2;
	Height = abs(P1.y - P2.y);
	SideLen = abs(P1.x - P2.x);
}

void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeft, BottomRight, FigGfxInfo, Selected);
}

bool CHexagon::isInside(int x, int y)
{
    // Divide the hexagon into triangles
    //Point vertices[6] = { /* insert vertices here */ };
    Point vertices[6];
    vertices[0] = TopLeft; // top-left corner
    vertices[1] = Point((int)(TopLeft.x + 0.25 * (BottomRight.x - TopLeft.x)), (int)(TopLeft.y)); // top-middle point
    vertices[2] = Point(static_cast<int>(BottomRight.x - 0.25 * (BottomRight.x - TopLeft.x)), static_cast<int>(TopLeft.y)); // top-right point
    vertices[3] = BottomRight; // bottom-right corner
    vertices[4] = Point(static_cast<int>(BottomRight.x - 0.25 * (BottomRight.x - TopLeft.x)), static_cast<int>(BottomRight.y)); // bottom-middle point
    vertices[5] = Point(static_cast<int>(TopLeft.x + 0.25 * (BottomRight.x - TopLeft.x)), static_cast<int>(BottomRight.y)); // bottom-left point

    Point triangles[4][3] = { { vertices[0], vertices[1], vertices[2] },
                              { vertices[0], vertices[2], vertices[3] },
                              { vertices[0], vertices[3], vertices[4] },
                              { vertices[0], vertices[4], vertices[5] } };
    // Check if the point is inside any of the triangles
    for (int i = 0; i < 4; i++)
    {
        int x1 = triangles[i][0].x;
        int y1 = triangles[i][0].y;
        int x2 = triangles[i][1].x;
        int y2 = triangles[i][1].y;
        int x3 = triangles[i][2].x;
        int y3 = triangles[i][2].y;
        bool isInsideTriangle = ((x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y) >= 0) &&
            ((x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y) >= 0) &&
            ((x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y) >= 0);
        if (isInsideTriangle)
        {
            return true;
        }
    }
    return false;
}


void CHexagon::Save(ofstream& OutFile)	//Save the figure parameters to the file
{
	OutFile << endl << ITM_HEX << "\t" << ID << "\t" << TopLeft.x << "\t" << TopLeft.y << "\t" << BottomRight.x << "\t" << BottomRight.y << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << "(" << (int)FigGfxInfo.FillClr.ucRed << "," << (int)FigGfxInfo.FillClr.ucGreen << "," << (int)FigGfxInfo.FillClr.ucBlue << ")" << endl;
	else
		OutFile << "NO_FILL";
}
void CHexagon::printInfo(GUI* pGUI, int x)
{
	pGUI->ClearStatusBar();

	stringstream msg;
	msg << "ID:" << x + 1 << " Hexagon" ", Side Length:" << SideLen << " , Height:" << Height << " , Area:" << ((3 * sqrt(3)) / 2) * pow(SideLen, 2);
	pGUI->PrintMessage(msg.str());
}
void CHexagon::Load(ifstream& Infile)	//Load the figure parameters to the file
{
    // Declare variables for x, y, len, drawColorString, and fill
    string drawColorString, fill;
    // Read values from the file into object data members
    Infile >> ID;
    Infile >> TopLeft.x;
    Infile >> TopLeft.y;
    Infile >> BottomRight.x;
    Infile >> BottomRight.y;
    Infile >> drawColorString >> fill;//read colors from file into strings first to convert to color later

    setDrawandFillClr(drawColorString, fill); //set the draw and fill colors
}
CHexagon* CHexagon::Clone() const
{
    return new CHexagon(*this); // Assuming you have a copy constructor for CEllipse
}



int CHexagon::resize(float resizeFactor)
{
	/*
	//check size of shape
	if (SideLength < 80 && resizeFactor < 1)
	{
		return -2;
	}

	//Calculate the center of the hexagon
	Point center;
	int horiaontalDiff = SideLength / 2;
	int verticalDiff = Height / 2;
	center.x = TopLeft.x + horiaontalDiff;
	center.y = TopLeft.y + verticalDiff;
	if (resizeFactor > 1) {
		//Check if resizing would go beyond the specified vertical boundaries
		if ((center.y - (verticalDiff * resizeFactor) > UI.height - UI.StatusBarHeight) || (center.y - (verticalDiff * resizeFactor) < UI.ToolBarHeight)) {
			return -1;
		}
		if ((center.y + (verticalDiff * resizeFactor) > UI.height - UI.StatusBarHeight) || (center.y + (verticalDiff * resizeFactor) < UI.ToolBarHeight)) {
			return -1;
		}
	}

		//Perform the resizing
		TopLeft.x = center.x - horiaontalDiff * resizeFactor;
		TopLeft.y = center.y - verticalDiff * resizeFactor;
		Height *= resizeFactor;
		SideLength *= resizeFactor;
		return 1;
	*/
	Point center;
	int horiaontalDiff = SideLen / 2;
	int verticalDiff = Height / 2;
	center.x = TopLeft.x + horiaontalDiff;
	center.y = TopLeft.y + verticalDiff;

	if ((center.y - (verticalDiff * resizeFactor) > UI.height - UI.StatusBarHeight) || (center.y - (verticalDiff * resizeFactor) < UI.ToolBarHeight)) {
		return -1;
	}
	if ((center.y + (verticalDiff * resizeFactor) > UI.height - UI.StatusBarHeight) || (center.y + (verticalDiff * resizeFactor) < UI.ToolBarHeight)) {
		return -1;
	}

	TopLeft.x = center.x - horiaontalDiff * resizeFactor;
	TopLeft.y = center.y - verticalDiff * resizeFactor;
	Height *= resizeFactor;
	SideLen *= resizeFactor;
	return 1;
}

string CHexagon::GetFigName() {
    return "Hexagon";
}