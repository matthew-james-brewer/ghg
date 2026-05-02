
/*

vol.h: portable volume manipulation (works on windows and linux)

To get the volume, run `*((long*)vol(-1))`.
To set the volume, run `(void)vol(volume)` (replace volume with the new volume to set).

*/

void* vol(long volume);
