#include "ActionPlayWithType.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionPlayWithType::ActionPlayWithType(ApplicationManager* pApp) :Action(pApp)
{
	correct = 0;
	wrong = 0;
}
void ActionPlayWithType::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int Count = 0; //Number of shape(TRi|squ|circ) must be selected
	Fig = pManager->GetRandomFigure(Count);
	if (Fig != "Empty")
	{
		pGUI->PrintMessage("SELECT ALL " + Fig);
		while (Count > 0)
		{
			pGUI->GetPointClicked(p.x, p.y);
			CFigure* r = pManager->GetFigure(p.x, p.y);
			if (r != NULL)
			{
				if (r->GetFigName() == Fig)
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

				pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              "
					+ "Wrong Ans = " + to_string(wrong) + "                        ..CONTINUE!");
				pManager->UpdateInterface();
			}
			else
			{
				pGUI->PrintMessage("Correct Ans = " + to_string(correct) + "                                              "
					+ "Wrong Ans = " + to_string(wrong) + "                  Select a Figure Please");
			}
		}
		pGUI->PrintMessage("your grade is " + to_string(correct) + "/" + to_string(correct + wrong));
		pGUI->CreateToolBar();
		pGUI->ClearDrawArea();
		//string Image = "images\\MenuItems\\finish.jpg";
		//pGUI->pWind->DrawImage(Image, 0, UI.ToolBarHeight + 1, UI.width, UI.height - UI.ToolBarHeight - UI.StatusBarHeight);

		pGUI->GetPointClicked(p.x, p.y);
		pManager->showAllFigure();
		pGUI->PrintMessage("");
		pGUI->CreatePlayToolBar();
		//pGUI->CreateDrawToolBar();

	}
	else
	{
		pGUI->PrintMessage("Empty Drawing Area , You can back to \"Draw Mode\" by selecting Draw Icon ");
		return;
	}

}
