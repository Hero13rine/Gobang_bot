#include "TerminalMonitor.h"


int main()
{
	TerminalMonitor& DealMsg = TerminalMonitor::getinstance();
	DealMsg.ListenMassage();
}