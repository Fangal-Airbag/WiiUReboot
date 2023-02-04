#include <coreinit/launch.h>
#include <whb/proc.h>

int main(int argc, char** argv)
{
	WHBProcInit();
	
	OSLaunchTitlel(OS_TITLE_ID_REBOOT, 0);

	while (WHBProcIsRunning()) {}

	WHBProcShutdown();
	return 0;
}