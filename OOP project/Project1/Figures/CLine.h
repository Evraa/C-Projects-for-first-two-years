#ifndef CLINE_H
#define CLINE_H
#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point P1;
	Point P2;
	Point C;
public:
	CLine();
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	CFigure *SelectFigure (int x, int y);
	double CalcDis (int,int,int,int);
	virtual void PrintInfo(Output* pOut);
	virtual CFigure* Paste (Point);
	virtual CFigure* NewOb ();
	virtual string Getstring () ;
	virtual void Save(ofstream &OutFile);
	virtual CLine* Load(ifstream &Infile);
};

#endif