mkdir CZ
copy .\src\cpymat.py .\CZ\cpymat.py
copy .\src\concore.py .\CZ\concore.py
copy .\src\cpymat.iport .\CZ\concore.iport
copy .\src\cpymat.oport .\CZ\concore.oport
mkdir PZ
copy .\src\pmcpymat.cpp .\PZ\pmcpymat.cpp
copy .\src\concore.hpp .\PZ\concore.hpp
copy .\src\pmcpymat.iport .\PZ\concore.iport
copy .\src\pmcpymat.oport .\PZ\concore.oport
copy  .\src\pmcpymat.dir\*.* .\PZ
mkdir VCZ
mkdir VPZ
cd CZ
mklink /J out1 ..\VCZ
cd ..
cd PZ
mklink /J out1 ..\VPZ
cd ..
cd CZ
mklink /J in1 ..\VPZ
cd ..
cd PZ
mklink /J in1 ..\VCZ
cd ..
