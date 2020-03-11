#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	int R ;
	Point C ;
	Point P1;
	Point P2;
public:
	CCircle ();
	CCircle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual CFigure * SelectFigure (int , int );
	virtual void PrintInfo(Output* pOut);
	virtual CFigure* Paste (Point);
	virtual string Getstring () ;
	virtual CFigure* NewOb ();
	virtual void Save(ofstream &OutFile);
	virtual CCircle* Load (ifstream &Infile);

};

#endif
