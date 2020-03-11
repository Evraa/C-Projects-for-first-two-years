#include "CLine.h"
#include <Cmath>

CLine :: CLine()
{
}

CLine::CLine(Point pt1, Point pt2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	P1 = pt1;
	P2 = pt2;
	C.x=(pt1.x+pt2.x)/2;
	C.y=(pt1.y+pt2.y)/2;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a line on the screen	
	pOut->DrawLine(P1, P2, FigGfxInfo, Selected);
}
CFigure * CLine::SelectFigure (int x, int y)
{
	if (CalcDis(x,y,P1.x,P1.y)+CalcDis(x,y,P2.x,P2.y)<=CalcDis(P1.x,P1.y,P2.x,P2.y)+.06)
			return this ;
		
	return NULL;
}
double CLine::CalcDis(int x1,int y1,int x2,int y2)
{
	return sqrt(pow (x1-x2,2)+pow(y1-y2,2));
}
void CLine ::PrintInfo(Output* pOut)
{
	pOut -> PrintMessage( "Line ID :"+ to_string(ID)+" ,First Point :("+to_string(P1.x)+","+to_string(P1.y)+"), Second Point :("
		+to_string(P2.x)+","+to_string(P2.y)+"), Lengh :"+to_string(CalcDis(P1.x,P1.y,P2.x,P2.y)));
}
CFigure* CLine::NewOb()
{
	CLine *L = new CLine(P1,P2,FigGfxInfo);
	return L;
}
CFigure* CLine:: Paste (Point p)
{
	Point diff;
	diff.x=p.x-C.x;
	diff.y=p.y-C.y;
	Point new_P1,new_P2;
	new_P1=AddPoint(diff,P1);
	new_P2=AddPoint(diff,P2);
	CLine *L = new CLine(new_P1,new_P2,FigGfxInfo);
	return L;
}

string CLine ::Getstring() 
{
	return " Line " ;
}

void CLine:: Save(ofstream &OutFile)
{
   string DrawColorShape;
   
   DrawColorShape = GetColor ( FigGfxInfo.DrawClr );
   OutFile <<"LINE"<<" "<<ID<<" "<<P1.x<<" "<<P1.y<<" "<<P2.x<<" "<<P2.y<<" "<<DrawColorShape<<endl;

} 

CLine* CLine :: Load (ifstream& InFile)
{

	string DrawingColor;
	
	InFile>>ID>>P1.x>>P1.y>>P2.x>>P2.y>>DrawingColor;

	if (DrawingColor == "WHITE")
		ChngDrawClr( WHITE );
	if (DrawingColor == "BLACK")
		ChngDrawClr( BLACK );
	if (DrawingColor == "RED")
		ChngDrawClr( RED );
	if (DrawingColor == "BLUE")
		ChngDrawClr( BLUE );
	if (DrawingColor == "GREEN")
		ChngDrawClr( GREEN );

	CLine* Line=new CLine (P1,P2,FigGfxInfo);
	return Line;
}
