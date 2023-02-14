#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <vpad/input.h>
#include <whb/proc.h>

int main(int argc, char **argv)
{
	VPADStatus status;
	VPADReadError err;
	
	WHBProcInit();
	
	VPADRead(VPAD_CHAN_0, &status, 1, &err);

	// To fully reboot the system the user needs to hold B
	if (status.hold & VPAD_BUTTON_B) 
		OSLaunchTitlel(OS_TITLE_ID_REBOOT, 0);
	else {
		OSForceFullRelaunch();
		SYSLaunchMenu();
	}

	while (WHBProcIsRunning()) {}

	WHBProcShutdown();
	return 0;
}