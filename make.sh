#！/bin/bash
g++ -o ../C/ChessOffice vcx.cpp minimax.cpp evaState.cpp TerminalMonitor.cpp Open.cpp Game.cpp main.cpp
cd ..
cd C
chmod +777 ChessOffice