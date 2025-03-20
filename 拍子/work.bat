:loop
    data.exe
    std.exe
    my.exe
    fc std.out my.out
    if %errorlevel%==0 goto loop
pause