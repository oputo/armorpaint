# SpaceMouse support (Windows)

This local ArmorPaint 1.0 build reads 3Dconnexion motion through Windows Raw Input.
It accepts Multi-axis Controller HID devices from vendor IDs 0x256f and 0x046d,
including SpaceMouse Compact and Wireless. Older separate translation (report 1)
and rotation (report 2) packets and newer combined report 1 packets are supported.

In Preferences > Camera, enable **SpaceMouse Navigation**. Use **SpaceMouse
Sensitivity** for overall speed. The six axis rows each have an On switch, a
Speed slider (0.1-4.0), and a Reverse switch. Existing settings default to all
axes on, speed 1.0, and no reversal, preserving the previous behavior. The
control applies in the 3D Paint workspace when camera controls are enabled.
Device X slides the view sideways; device Y pans vertically; device Z dollies.
Rx/Rz orbit
around the current camera pivot and Ry rolls the camera. Existing camera pan, zoom,
and rotation speed preferences also apply. Painting, UI dragging, menus, and other
workspaces do not receive SpaceMouse navigation. Buttons are not mapped.

This implementation does not require a 3Dconnexion SDK. The Windows HID report
format can vary by device and firmware, so verify directions and speed on the
actual hardware. The decoder has synthetic tests in base/tests/spacemouse_report.c.
