#include "../sources/backends/spacemouse_report.h"
#include <assert.h>

int main(void) {
	spacemouse_report_t decoded;
	const uint8_t translation[] = {1, 0x5e, 0x01, 0xa2, 0xfe, 0x00, 0x00};
	assert(spacemouse_report_decode(translation, sizeof(translation), &decoded));
	assert(decoded.has_translation && !decoded.has_rotation);
	assert(decoded.translation[0] == 1.0f && decoded.translation[1] == -1.0f);
	const uint8_t rotation[] = {2, 0x5e, 0x01, 0x00, 0x00, 0xa2, 0xfe};
	assert(spacemouse_report_decode(rotation, sizeof(rotation), &decoded));
	assert(!decoded.has_translation && decoded.has_rotation);
	assert(decoded.rotation[0] == 1.0f && decoded.rotation[2] == -1.0f);
	const uint8_t combined[] = {1, 0x5e, 0x01, 0x00, 0x00, 0xa2, 0xfe, 0x00, 0x00, 0x5e, 0x01, 0x00, 0x00};
	assert(spacemouse_report_decode(combined, sizeof(combined), &decoded));
	assert(decoded.has_translation && decoded.has_rotation);
	assert(decoded.translation[0] == 1.0f && decoded.translation[2] == -1.0f);
	assert(decoded.rotation[1] == 1.0f);
	const uint8_t invalid[] = {3, 1};
	assert(!spacemouse_report_decode(invalid, sizeof(invalid), &decoded));
	return 0;
}
