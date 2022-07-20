#pragma once
#include <iostream>

class Base
{
public:
	// constructor
	Base() {}

	// function
	inline static float& GetAssemblygap() { return assemblygap; }
	inline static float& GetCoppergap() { return coppergap; }
	inline static float& GetSilkscreenlen() { return silkscreenlen; }

protected:
	static float assemblygap;
	static float coppergap;
	static float silkscreenlen;

private:

};