#ifndef CRTRIG_H
#define CTRIG_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point P1;
	Point P2;
	Point P3;
	Point C;
public:
	CTriangle();
	CTriangle(Point , Point, Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	double CalcArea(Point,Point,Point);
	virtual CFigure * SelectFigure (int , int );
	virtual void PrintInfo(Output* pOut);
	virtual CFigure* Paste (Point);
	virtual CFigure* NewOb();
	virtual string Getstring ();
	virtual void Save(ofstream &OutFile);
    virtual CTriangle* Load(ifstream &Infile);
};

#endif

