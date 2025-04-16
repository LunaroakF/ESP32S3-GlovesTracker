#include "Alpha.h"

// alphabetic LucidGloves正式编码
char* AlphaEncoder::encode(
	int* flexion,
	int joyX,
	int joyY,
	bool joyClick,
	bool triggerButton,
	bool aButton,
	bool bButton,
	bool grab,
	bool pinch,
	bool calib,
	bool menu
) {
	static char stringToEncode[75];
	int trigger = (flexion[1] > ANALOG_MAX / 2) ? (flexion[1] - ANALOG_MAX / 2) * 2 : 0;
	sprintf(
		stringToEncode,
		"A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s\n",
		flexion[0],
		flexion[1],
		flexion[2],
		flexion[3],
		flexion[4],
		joyX,
		joyY,
		trigger,
		joyClick ? "H" : "",
		triggerButton ? "I" : "",
		aButton ? "J" : "",
		bButton ? "K" : "",
		grab ? "L" : "",
		pinch ? "M" : "",
		menu ? "N" : "",
		calib ? "O" : ""
	);
	return stringToEncode;
}

void AlphaEncoder::decodeData(char* stringToDecode, int* hapticLimits) {
	hapticLimits[0] = AlphaEncoder::getArgument(stringToDecode, 'A');  // 大拇指
	hapticLimits[1] = AlphaEncoder::getArgument(stringToDecode, 'B');  // 食指
	hapticLimits[2] = AlphaEncoder::getArgument(stringToDecode, 'C');  // 中指
	hapticLimits[3] = AlphaEncoder::getArgument(stringToDecode, 'D');  // 无名指
	hapticLimits[4] = AlphaEncoder::getArgument(stringToDecode, 'E');  // 小拇指
	// Serial.println("Haptic: "+ (String)hapticLimits[0] + " " +
	// (String)hapticLimits[1] + " " + (String)hapticLimits[2] + " " +
	// (String)hapticLimits[3] + " " + (String)hapticLimits[4] + " ");
}

int AlphaEncoder::getArgument(char* stringToDecode, char command) {
	char* start = strchr(stringToDecode, command);
	if (start == NULL) {
		return -1;
	} else {
		return atoi(start + 1);
	}
}
