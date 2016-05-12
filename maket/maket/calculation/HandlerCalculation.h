#pragma once
#include "..\orm\Satellite.h"
#include "..\handlers\FileWriter.h"
class HandlerCalculation
{
private:
	MySQL * sql;
	FileWriter fw;
	Satellite* sat;
	vector<Satellite*> selected;

	void firstSelection();
	void secondSelectionR();
	void secondSelectionL();
	void calculation(State, double, double);

	//static fields
	static const string FIRST_SELECTION_1;
	static const string FIRST_SELECTION_2;
	static const string FIRST_SELECTION_3;
public:
	HandlerCalculation(Satellite*);
	~HandlerCalculation();

	void calculat(double,double,string);
};

