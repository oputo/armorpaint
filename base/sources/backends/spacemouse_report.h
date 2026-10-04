#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// 3Dconnexion devices use either separate translation/rotation reports or
// a combined 13-byte report. Keep this decoder independent of Win32 so that
// both layouts can be checked without a connected device.
typedef struct spacemouse_report {
	float translation[3];
	float rotation[3];
	bool has_translation;
	bool has_rotation;
} spacemouse_report_t;

static float spacemouse_report_axis(const uint8_t *report, size_t offset) {
	int16_t value = (int16_t)((uint16_t)report[offset] | ((uint16_t)report[offset + 1] << 8));
	float axis = (float)value / 350.0f;
	return axis < -1.0f ? -1.0f : axis > 1.0f ? 1.0f : axis;
}

static bool spacemouse_report_decode(const uint8_t *report, size_t length, spacemouse_report_t *out) {
	*out = (spacemouse_report_t){0};
	if (length < 7) {
		return false;
	}
	if (report[0] == 1) {
		for (int i = 0; i < 3; ++i) {
			out->translation[i] = spacemouse_report_axis(report, 1 + i * 2);
		}
		out->has_translation = true;
		if (length >= 13) {
			for (int i = 0; i < 3; ++i) {
				out->rotation[i] = spacemouse_report_axis(report, 7 + i * 2);
			}
			out->has_rotation = true;
		}
		return true;
	}
	if (report[0] == 2) {
		for (int i = 0; i < 3; ++i) {
			out->rotation[i] = spacemouse_report_axis(report, 1 + i * 2);
		}
		out->has_rotation = true;
		return true;
	}
	return false;
}
