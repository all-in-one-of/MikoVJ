#ifndef FLUID_UTILS
#define FLUID_UTILS

/*
 * Holfd mostly inlined defined quick utility functions
 */

inline void iClamp(const int minValue, const int maxValue, int& ioValue)
{
	if(ioValue > maxValue) {
		ioValue = maxValue; }
	else if (ioValue < minValue) {
		ioValue = minValue; }
}

inline void fClamp(const float minValue, const float maxValue, float& ioValue)
{
	if(ioValue > maxValue) {
		ioValue = maxValue;
	}
	else if (ioValue < minValue) {
		ioValue = minValue;
	}
}

#endif