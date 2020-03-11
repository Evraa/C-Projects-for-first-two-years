#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point C ;
public:
	CRectangle();
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual CFigure * SelectFigure (int , int );
	virtual void PrintInfo(Output* pOut);
	virtual CFigure* Paste (Point);
	virtual CFigure* NewOb();
	virtual string Getstring () ;
	virtual void Save(ofstream &OutFile);
	virtual CRectangle* Load (ifstream& Infile);
};

#endif