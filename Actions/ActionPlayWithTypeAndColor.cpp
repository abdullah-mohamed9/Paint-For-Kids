#include "ActionPlayWithTypeAndColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
ActionPlayWithTypeAndColor::ActionPlayWithTypeAndColor(ApplicationManager* pApp) :Action(pApp)
{
	correct = 0;
	wrong = 0;
}
void ActionPlayWithTypeAndColor::Execute() {
	GUI* pGUI = pManager->GetGUI();
	int Count = 0;

	Fig = pManager->GetRandomColorType(Count, Fig_Type_color);
	if (Fig != "Empty") {
		stringstream print;
		print << pManager->colorToString(Fig_Type_color);
		pGUI->PrintMessage("Select all " + print.str() + " " + Fig);

		while (Count > 0)
		{
			pGUI->GetPointClicked(p.x, p.y);
			CFigure* r = pManager->GetFigure(p.x, p.y);
			if (r != NULL)
			{
				if (r->GetFigColor() == Fig_Type_color && r->GetFigName() == Fig)
				{
					if (!r->getHiddenValue()) {
						correct++;
						Count--;
					}
				}
				else {
					if (!r->getHiddenValue())
						wrong++;
				}
				r->show(false);
				pManager->UpdateInterface();
				pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              "
					+ "Wrong Ans = " + to_string(wrong) + "                                                 ..CONTINUE!");
			}
			else
			{
				pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              "
					+ "Wrong Ans = " + to_string(wrong) + "                  Select a Figure Please");

			}


		}
		pGUI->PrintMessage("your grade is " + to_string(correct) + "/" + to_string((correct + wrong)));
		//pGUI->CreateToolBar();
		pGUI->ClearDrawArea();
		//string Image = "images\\MenuItems\\finish.jpg";
		//pGUI->pWind->DrawImage(Image, 0, UI.ToolBarHeight + 1, UI.width, UI.height - UI.ToolBarHeight - UI.StatusBarHeight);
		pGUI->GetPointClicked(p.x, p.y);
		pManager->showAllFigure();
		pGUI->PrintMessage("Select any icon from toolbar please!");
		pGUI->CreatePlayToolBar();
	}
	else
	{
		pGUI->PrintMessage("There aren't any Colored Figures , Select another icon from toolbar");
		return;
	}
}
