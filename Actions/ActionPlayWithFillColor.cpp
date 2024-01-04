#include "ActionPlayWithFillColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <sstream>
ActionPlayWithFillColor::ActionPlayWithFillColor(ApplicationManager* pApp) : Action(pApp)
{
	correct = 0;
	wrong = 0;
}
void ActionPlayWithFillColor::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int Count = 0;
	Fig_Color = pManager->GetRandomColor(Count);

	// FigColor << Fig_Color;
	if (Fig_Color != UI.BkGrndColor)
	{
		stringstream print;
		print << pManager->colorToString(Fig_Color);
		pGUI->PrintMessage("Select all " + print.str() + " Figures");
		while (Count>0)
		{
			pGUI->GetPointClicked(p.x, p.y);
			if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				CFigure* r = pManager->GetFigure(p.x, p.y);
				if (r != NULL)
				{
					if (r->GetFigColor() == Fig_Color)
					{
						if (!r->getHiddenValue())
						{
							correct++;
							Count--;
						}
					}
					else
					{
						if (!r->getHiddenValue())
							wrong++;
					}

					r->show(false);
					pManager->UpdateInterface();

					pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              " + "Wrong Ans = " + to_string(wrong) + "                                                 ..CONTINUE!");
				}

				else
				{
					pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              " + "Wrong Ans = " + to_string(wrong) + "                  Select a Figure Please");
				}
			}
			else
			{
				pGUI->PrintMessage("Toolbar clicked, game aborted.");
				Count = -1;
			}
			
		}
		pGUI->PrintMessage("your grade is " + to_string(correct) + "/" + to_string((correct + wrong)));

		pGUI->ClearDrawArea();
		
		//pGUI->GetPointClicked(p.x, p.y);
		pManager->showAllFigure();
		pGUI->PrintMessage("Select any icon from toolbar please!");
		pGUI->CreatePlayToolBar();
	}
	else
	{
		pGUI->PrintMessage("There aren't any Colored Figures , Select another icon from toolbar ");
		return;
	}
}
