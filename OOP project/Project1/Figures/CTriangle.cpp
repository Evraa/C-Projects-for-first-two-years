#include "CTriangle.h"
#include <Cmath>

CTriangle::CTriangle()
{}


CTriangle::CTriangle(Point pt1, Point pt2, Point pt3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	P1 = pt1;
	P2 = pt2;
	P3 = pt3;
	C.x=(pt1.x+pt2.x+pt3.x)/3;
	C.y=(pt1.y+pt2.y+pt3.y)/3;
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTrig(P1, P2, P3, FigGfxInfo, Selected);
}
double CTriangle:: CalcArea(Point a,Point b,Point c)
{
	return (0.5*abs((a.x*b.y-b.x*a.y)-(a.x*c.y-a.y*c.x)+(b.x*c.y-b.y*c.x)));
}
CFigure * CTriangle::SelectFigure (int x, int y)
{
	Point s ;
	s.x = x ;
	s.y = y ;
	if (CalcArea(P1,P2,P3)==CalcArea(s,P1,P2)+CalcArea(s,P2,P3)+CalcArea(s,P1,P3))
			return this ;
	
	return NULL;
}
void CTriangle:: PrintInfo(Output* pOut)
{
	pOut -> PrintMessage( "Triangle ID : "+ to_string(ID)+" ,First Point :("+to_string(P1.x)+","+to_string(P1.y)+"), Second Point :("
		+to_string(P2.x)+","+to_string(P2.y)+") ,Third Point :("+to_string(P3.x)+","+to_string(P3.y)+")");
}
 CFigure* CTriangle :: Paste (Point p)
{
	Point diff;
	diff.x=p.x-C.x;
	diff.y=p.y-C.y;
	Point new_P1,new_P2,new_P3;
	new_P1=this->AddPoint(diff,P1);
	new_P2=this->AddPoint(diff,P2);
	new_P3=this->AddPoint(diff,P3);
	CTriangle *T = new CTriangle(new_P1,new_P2,new_P3,FigGfxInfo);
	return T;
}
 CFigure* CTriangle::NewOb()
{
	CTriangle *T = new CTriangle(P1,P2,P3,FigGfxInfo);
	return T;
}

string CTriangle ::Getstring()
{
	return " Triangle ";
}

void CTriangle:: Save(ofstream &OutFile)
{
   string DrawColorShape,FillColorShape;
  
     DrawColorShape = GetColor ( FigGfxInfo.DrawClr );

   if (FigGfxInfo.isFilled)
    {
	     FillColorShape = GetColor (FigGfxInfo.FillClr );  
	     OutFile<<"TRIANG"<<" "<<ID<<" "<<P1.x<<" "<<P1.y<<" "<<P2.x<<" "<<P2.y<<" "<<P3.x<<" "<<P3.y<<" "<<DrawColorShape<<" "<<FillColorShape<<endl;
    }
   else
   {
	      OutFile<<"TRIANG"<<" "<<ID<<" "<<P1.x<<" "<<P1.y<<" "<<P2.x<<" "<<P2.y<<" "<<P3.x<<" "<<P3.y<<" "<<DrawColorShape<<" NO_FILL"<<endl;
   }
}
CTriangle* CTriangle :: Load (ifstream& InFile)
{
	

	string DrawingColor,FillingColor;

	InFile>>ID>>P1.x>>P1.y>>P2.x>>P2.y>>P3.x>>P3.y>>DrawingColor>>FillingColor;
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
	if (FillingColor != "NO_FILL")
	{
		if (FillingColor == "WHITE")
			ChngFillClr( WHITE );
		if (FillingColor == "BLACK")
			ChngFillClr( BLACK );
		if (FillingColor == "RED")
			ChngFillClr( RED );
		if (FillingColor == "GREEN")
			ChngFillClr( GREEN );
		if (FillingColor == "BLUE")
			ChngFillClr( BLUE );
	}
	else
	{
		FigGfxInfo.isFilled = false;
	}
	
	CTriangle* Tri=new CTriangle(P1,P2,P3,FigGfxInfo);
	
	return Tri;
}
