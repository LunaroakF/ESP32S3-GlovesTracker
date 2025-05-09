#include "defines.h"

bool grabGesture(int* flexion) {
	return (flexion[4] + flexion[3] + flexion[2] + flexion[1]) / 4 <= ANALOG_MAX / 2
			 ? 0
			 : 1;
}

bool pinchGesture(int* flexion) {
	return (flexion[1] + flexion[0]) / 2 <= ANALOG_MAX / 2 ? 0 : 1;
}

bool triggerGesture(int* flexion) { return flexion[1] <= (ANALOG_MAX / 2) ? 0 : 1; }
