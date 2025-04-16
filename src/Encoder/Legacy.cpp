#include "Legacy.h"

// legacy LucidGloves传统编码 已弃用
char* LegacyEncoder::encode(
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

	sprintf(
		stringToEncode,
		"%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n",
		flexion[0],
		flexion[1],
		flexion[2],
		flexion[3],
		flexion[4],
		joyX,
		joyY,
		joyClick,
		triggerButton,
		aButton,
		bButton,
		grab,
		pinch
	);
	return stringToEncode;
}

void LegacyEncoder::decodeData(char* stringToDecode, int* hapticLimits) {
	byte index = 0;
	char* ptr = strtok(stringToDecode, "&");  // 分隔符
	while (ptr != NULL) {
		hapticLimits[index] = atoi(ptr);
		index++;
		ptr = strtok(NULL, "&");
	}
}