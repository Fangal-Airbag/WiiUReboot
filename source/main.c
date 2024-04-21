#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <vpad/input.h>
#include <padscore/kpad.h>
#include <whb/proc.h>
#include <coreinit/time.h>
#include <coreinit/thread.h>

VPADStatus vStatus;
VPADReadError vErr;
KPADStatus kStatus;
KPADError kErr;

#define BUTTON_B (WPAD_BUTTON_B | WPAD_CLASSIC_BUTTON_B | WPAD_PRO_BUTTON_B)

uint32_t buttonHeld() {
	return kStatus.hold | kStatus.classic.hold | kStatus.pro.hold;
}

int main(int argc, char **argv)
{	
	WHBProcInit();
	KPADInit();
	WPADEnableURCC(1);

	OSTick start = OSGetTick();

	while (WHBProcIsRunning()) 
	{
		OSTick end = OSGetTick();
		for (int i = 0; i < 4; i++) {
			VPADRead(VPAD_CHAN_0, &vStatus, 1, &vErr);
            KPADReadEx((KPADChan)i, &kStatus, 1, &kErr);

			// To fully reboot the system the user needs to hold B
			if ((buttonHeld() & BUTTON_B) | (vStatus.hold & VPAD_BUTTON_B)) 
				OSLaunchTitlel(OS_TITLE_ID_REBOOT, 0);
		}

		// Yes I do indeed go by mister hacky mchackson
		if ((end - start) >= OSMillisecondsToTicks(2500)) {
			OSForceFullRelaunch();
			SYSLaunchMenu();
		}
	}

	WHBProcShutdown();
	return 0;
}