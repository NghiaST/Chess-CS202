@ECHO OFF

REM Check if "make" exists
where make > nul 2>&1
IF %ERRORLEVEL% EQU 0 (
    ECHO Running "make"...
    make
) ELSE (
    REM Check if "mingw32-make" exists
    where mingw32-make > nul 2>&1
    IF %ERRORLEVEL% EQU 0 (
        ECHO Running "mingw32-make"...
        mingw32-make
    ) ELSE (
        ECHO Error: Neither "make" nor "mingw32-make" found in PATH.
    )
)

REM Optional: Pause to keep the command prompt window open
PAUSE