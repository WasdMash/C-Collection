:: set the path to your visual studio vcvars script, it is different for every version of Visual Studio.
set VS2017TOOLS="C:\Program Files(x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"

:: make sure we found them
if not exist %VS2017TOOLS% (
    echo VS 2017 Build Tools are missing!
    exit
)

:: call that script, which essentially sets up the VS Developer Command Prompt
call %VS2017TOOLS%

:: run the compiler with your arguments
cl.exe /EHsc /Zi /Fe: helloworld.exe test.c

exit