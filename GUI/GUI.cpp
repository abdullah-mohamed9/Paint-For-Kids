#include "GUI.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	UI.isFilled = false;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	// array of colors to convert it form rgb to string and vice versa
	/*colors[0] = "Red";
	colors[1] = "Green";
	colors[2] = "Blue";
	colors[3] = "Yellow";
	colors[4] = "Orange";
	colors[5] = "Purple";
	colors[6] = "Pink";
	colors[7] = "Cyan";
	colors[8] = "Magenta";
	colors[9] = "Brown";*/

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//======================================================================================//
//								Dealing with colors										//
//======================================================================================//
color GUI::getBackgroundColor() const	//get current filling color
{
	return UI.BkGrndColor;
}
color GUI::getFillColor() const	//get current filling color
{
	return UI.FillColor;
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		
			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX: return DRAW_HEX;
			case DRAW_CLR: return CHNG_DRAW_CLR;
			case FILL_CLR: return CHNG_FILL_CLR;
			case BK_CLR: return CHNG_BK_CLR;
			case ITM_QUARTER: return RESIZE_QUARTER;
			case ITM_HALF: return RESIZE_HALF;
			case ITM_DOUBLE: return RESIZE_DOUBLE;
			case ITM_QUADRUPLE: return RESIZE_QUADRUPLE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_EXIT: return EXIT;
			case TO_PLAY_MODE: return TO_PLAY;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case FIGURE_TYPE: return PLAYWITHTYPE;
				case FIGURE_FILLCOLOR: return PLAYWITHCOLOR;
				case FIGURETYPE_AND_FILLCOLOR: return PLAYWITHTYPECOLOR;

				case TO_DRAW_MODE: return TO_DRAW;

				default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Menu_Hexagon.jpg";
	MenuItemImages[DRAW_CLR] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[FILL_CLR] = "images\\MenuItems\\Menu_FillColor.jpg";
	MenuItemImages[BK_CLR] = "images\\MenuItems\\Menu_PickColor.jpg";
	MenuItemImages[COLORS_PIC] = "images\\MenuItems\\OIP.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\Quarter.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\Half.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\Two.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\Four.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Delete.jpg";
	MenuItemImages[TO_PLAY_MODE] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.height - UI.ToolBarHeight);

	string MenuItemImages2[PLAY_ITM_COUNT];
	MenuItemImages2[FIGURE_TYPE] = "images\\MenuItems\\Fig_Type.jpeg";
	MenuItemImages2[FIGURE_FILLCOLOR] = "images\\MenuItems\\Fig_Color.jpg";
	MenuItemImages2[FIGURETYPE_AND_FILLCOLOR] = "images\\MenuItems\\Fill_Color.jpg";
	MenuItemImages2[TO_DRAW_MODE] = "images\\MenuItems\\draw.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages2[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(BLUE, 5);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setFillColor(color c) {
	UI.FillColor = c;
	UI.isFilled = true;
	pWind->SetBrush(UI.FillColor);
}
color GUI::getDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;	
}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
}
void GUI::DrawElipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);

}
void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int lengthx = abs(P1.x - P2.x);
	int lengthy = abs(P1.y - P2.y);

	int arrx[6] = { P1.x,P1.x + lengthx, P1.x + 1.5 * lengthx,P1.x + lengthx,P1.x,P1.x - 0.5 * lengthx };
	int arry[6] = { P1.y,P1.y,P1.y + 0.5 * lengthy,P1.y + lengthy,P1.y + lengthy,P1.y + 0.5 * lengthy };

	pWind->DrawPolygon(arrx, arry, 6, style);

}
Point GUI::ValidatePoint(Point P1) const {
	if (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight)
	{
		bool flag = false;
		PrintMessage("Can't choose here!; please choose a point in the drawing area");
		while (!flag)
		{
			GetPointClicked(P1.x, P1.y);
			if (!(P1.y < UI.StatusBarHeight || P1.y > UI.height - UI.StatusBarHeight))
				flag = 1;
		}
	}
	return P1;
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

