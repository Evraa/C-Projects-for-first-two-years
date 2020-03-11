#include "CRectangle.h"


CRectangle ::CRectangle()
{
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	C.x=(P1.x+P2.x)/2;
	C.y=(P1.y+P2.y)/2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
CFigure * CRectangle::SelectFigure (int x, int y)
{
if ((x>= Corner1.x && x<=Corner2.x)||(x>=Corner2.x && x<=Corner1.x))
	if((y>=Corner1.y&&y<=Corner2.y)||(y>=Corner2.y&&y<=Corner1.y))
			return this ;
	
	return NULL;
}
void CRectangle:: PrintInfo(Output* pOut)
{
	pOut -> PrintMessage( "Rectangle ID :"+ to_string(ID)+" ,First Corner :("+to_string(Corner1.x)+","+to_string(Corner1.y)+
		") ,Second Corner :("+to_string(Corner2.x)+","+to_string(Corner2.y)+") ,Width :"+to_string(abs(Corner1.x-Corner2.x))
		+" ,Lengh :"+to_string(abs(Corner1.y-Corner2.y)));
}
CFigure* CRectangle::NewOb()
{
	CRectangle *R = new CRectangle(Corner1,Corner2,FigGfxInfo);
	return R; 
}
CFigure* CRectangle:: Paste (Point p)
{
	Point diff;
	diff.x=p.x-C.x;
	diff.y=p.y-C.y;
	Point new_P1,new_P2;
	 new_P1=AddPoint(diff,Corner1);
	 new_P2=AddPoint(diff,Corner2);
	 CRectangle *R = new CRectangle( new_P1, new_P2,FigGfxInfo);
	return R; 
}

string CRectangle :: Getstring() 
{
	return " Rectangle ";
}

void CRectangle:: Save(ofstream &OutFile)
{
   string DrawColorShape,FillColorShape;
  
    DrawColorShape = GetColor ( FigGfxInfo.DrawClr );

   if (FigGfxInfo.isFilled)
   {
	   FillColorShape = GetColor (FigGfxInfo.FillClr );
	   OutFile << "RECT"<<" "<<ID<<" "<<Corner1.x<<" "<<Corner1.y<<" "<<Corner2.x<<" "<<Corner2.y<<" "<<DrawColorShape<<" "<< FillColorShape<<endl;
   }
   else
   {
	   OutFile << "RECT"<<" "<<ID<<" "<<Corner1.x<<" "<<Corner1.y<<" "<<Corner2.x<<" "<<Corner2.y<<" "<<DrawColorShape<<" NO_FILL"<<endl;
   }
}

CRectangle* CRectangle :: Load (ifstream& InFile)
{
	

	string DrawingColor,FillingColor;
	
	
	InFile>>ID>>Corner1.x>>Corner1.y>>Corner2.x>>Corner2.y>>DrawingColor>>FillingColor;
	

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



  CRectangle* Rect= new CRectangle (Corner1,Corner2,FigGfxInfo);
	return Rect;

	
}
