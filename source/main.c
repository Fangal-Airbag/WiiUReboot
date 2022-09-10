#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <whb/proc.h>

int main(int argc, char** argv)
{
	WHBProcInit();
	
	OSForceFullRelaunch();
	SYSLaunchMenu();

	while (WHBProcIsRunning()) {}

	return 0;
}