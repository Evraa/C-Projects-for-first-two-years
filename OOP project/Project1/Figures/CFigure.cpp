#include "CFigure.h"

CFigure::CFigure()
{
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	seen = true;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
void CFigure::SetID(int i)
{
	ID = i ;
}
int CFigure ::GetID()const
{
	return ID ;
}

bool CFigure :: IsFilled()
{ 
	return FigGfxInfo.isFilled ; 
}
bool CFigure :: Isavilable() const
{
	return seen;
}
 void CFigure :: setVisiable( bool show )
{
	seen = show;
} 
color CFigure :: GetColour() const
{
	return FigGfxInfo.FillClr ;
}

Point CFigure:: AddPoint (Point P1,Point P2)
{
	Point P;
	P.x=P1.x+P2.x;
	P.y=P1.y+P2.y;
	return P;
}