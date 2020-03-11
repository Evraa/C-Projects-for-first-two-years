#include "CCircle.h"
#include <Cmath>


CCircle::CCircle()
{
}

CCircle::CCircle(Point pt1, Point pt2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	 R = 0.5*sqrt((pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y));
	 C.x = (pt1.x + pt2.x)/2;
	 C.y = (pt1.y + pt2.y)/2;
	 P1 = pt1; 
	 P2 = pt2;
}
	

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCirc to draw a circle on the screen	
	pOut->DrawCirc(C, R, FigGfxInfo, Selected);
}
CFigure * CCircle::SelectFigure (int x, int y)
{
	if (pow((C.x-x),2)+pow((C.y-y),2)<=pow(R,2))
			return this ;
	
	return NULL;
}
 void CCircle :: PrintInfo(Output* pOut)
{
	pOut -> PrintMessage( "Circle ID :"+ to_string(ID)+" ,Centre :("+to_string(C.x)+","+to_string(C.y)+") ,Radius :"+to_string(R));
}
 CFigure * CCircle::NewOb()
{
	 CCircle *C = new CCircle(P1,P2,FigGfxInfo);	
	 return C;
}
 CFigure* CCircle:: Paste (Point p)
 {
	 Point diff;
	 diff.x=p.x-C.x;
	 diff.y=p.y-C.y;
	 Point new_P1,new_P2;
	 new_P1=this->AddPoint(diff,P1);
	 new_P2=this->AddPoint(diff,P2);
	 CCircle *C = new CCircle(new_P1,new_P2,FigGfxInfo);	
	 return C;
 }

 string CCircle ::Getstring ()
{
	return " Circle ";
}

void CCircle:: Save(ofstream &OutFile)
{
   string DrawColorShape,FillColorShape;
   
   DrawColorShape = GetColor ( FigGfxInfo.DrawClr );

   if (FigGfxInfo.isFilled)
   {
	  FillColorShape = GetColor (FigGfxInfo.FillClr );
	  OutFile << "CIRCLE"<<" "<<ID<<" "<<C.x<<" "<<C.y<<" "<<R<<" "<<DrawColorShape<<" "<<FillColorShape<<endl;
   }
   else
   {
	   OutFile << "CIRCLE"<<" "<<ID<<" "<<C.x<<" "<<C.y<<" "<<R<<" "<<DrawColorShape<<" NO_FILL"<<endl;
   }
}

CCircle* CCircle :: Load (ifstream& InFile)
{
	

	string DrawingColor,FillingColor;
	
	InFile>>ID>>C.x>>C.y>>R>>DrawingColor>>FillingColor;

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
	
	Point PCirc1,PCirc2;
	PCirc1.x=(C.x+R);
	PCirc1.y=C.y;
	PCirc2.x=abs(R-C.x);
	PCirc2.y=C.y;

    CCircle* Circ=new CCircle (PCirc1,PCirc2,FigGfxInfo);

	return Circ;
	
}


 