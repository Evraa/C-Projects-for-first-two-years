#ifndef CFIGURE_H
#define CFIGURE_H
#include <fstream>
#include "..\defs.h"
#include "..\GUI\Output.h"
string GetColor( color );
//Base class for all figures
class CFigure
{
protected:
	 int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
		bool seen;
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	void SetID(int);
	int GetID ()const;
	bool IsFilled ();
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//Save and Load functions , at first it needs  a pointer to the opened file to im/export to/from the file
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//the return type is dependant to the type of the calling object, it returns pointer to the created object
	//so it could be put(passed) in the addfigure func
    virtual CFigure* Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	virtual CFigure* NewOb() = 0;                   // creats a new object with the same members of the calling obj
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	virtual CFigure* SelectFigure(int, int) = 0; // returns a pointer to the calling object if the point sent(int x,int y)belong to the figure otherwise it returns NULL
	virtual CFigure* Paste(Point) = 0;         // creats a new object of the same type of the calling object and its center is the point sent to the function
											   // the new figure created by paste has the same area and diameter (lengh and slope in the case of a line),but with different points 
											   // around the center that the user choses
	Point AddPoint(Point, Point);              // returns a point whose x and y are the sum of the x and y of two points respictively
	virtual bool Isavilable () const ;
	void setVisiable ( bool );
	virtual string Getstring () =0;
	virtual color GetColour () const;
};

#endif