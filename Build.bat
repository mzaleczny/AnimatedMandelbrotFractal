@echo off

WHERE /Q cl.exe
IF %ERRORLEVEL% NEQ 0 (
    ECHO Ten skrypt powinien byc uruchamiany z konsoli "x64 Native Tools Command Prompt for Visual Studio"
    BREAK
) ELSE (
    cl /EHsc Main.cpp Desktop.cpp

    del *.ilk
    del *.obj
    del *.idb
    del *.pdb
)
