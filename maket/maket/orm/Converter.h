#pragma once
#include "KeplerianElements.h"
#include "TLE.h"
#include "State.h"
#include "Satellite.h"
class Converter
{
public:
	Converter();
	~Converter();

	//static methods
	static State tleToState(TLE);
	static KeplerianElements stateToKep(State);
	static Satellite satFromTle(TLE);
	static Satellite satFromState(State);

};

