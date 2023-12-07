# BackflushController
 Controller for automating backflushing of LWC filters

![Backflush Controller](/CAD/PXL_20231116_032817253.jpg)

The `Backflush Controller` uses an Arduino Uno microcontroller to operate a bank of eight relays to control the backflush procedure in an automated fashion. The backflush procedure consists of the following steps:

1. Bypass power for the sand filter valve relays. This ensures that the `Backflush Controller` activity will not be interfered with if the `main relay switch` is in the on position.
2. Open `sand filter valve #1` which supplies clean water to the secondary backflush plumbing.
3. Open the `zeolite backflush supply valve` which routes water from the secondary backflush plumbing to the `zeolite filter` on the effluent side.
4. Open the `middle zeolite bypass valve` which routes the backflush water from the influent side of the `zeolite filter` to the drain.
5. In this configuration, clean water is running backward through the `zeolite filter` and out through the drain. This configuration is maintained for 10 minutes.
6. After 10 minutes, close the `middle zeolite bypass valve`.
7. Close the `zeolite backflush supply valve`.
8. Open `sand filter valve #2` and `sand filter valve #4` which together supply clean water to the influent side of the `zeolite filter` for pack down.
9. Open the `lower zeolite bypass valve` which routes water from the effluent side of the `zeolite filter` to the drain.
10. After 2 minutes in this configuration, close the `lower zeolite bypass valve`.
11. Un-bypass power for the sand filter valve relays.
12. Energize the sand filter valve relays. This will reset the sand filter valves that were opened before.
13. Momentarily short the `sand filter backflush button`, which starts the sand filter backwash process, which is controlled by the PLC in the front room.
14. The sand filter backwash takes about an hour or so, so the `Backflush Controller` maintains this configuration for two hours to be safe. Then...
15. Deenergize the sand filter valve relays.

This repository contains the Arduino sketch for the controller as well as the `TinyCAD` schematic and .stl file for the 3D printed base. 