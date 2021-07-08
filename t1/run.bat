start /B /D CZ python cpymat.py >CZ\concoreout.txt
cd PZ
g++ pmcpymat.cpp
cd ..
start /B /D PZ cmd /c a >PZ\concoreout.txt
