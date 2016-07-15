@echo off
REM SWIG utility for creating interface files.
REM By myd7349
REM 2016-04-22T15:25+08:00
REM Usage:
REM SWIGHelper.bat <namespace> <output wrapper code file> <source swig interface file>

cmd /c swig -help > nul
if not errorlevel 0 goto SWIGNotFound

echo Invoking SWIG...
:: Windows will not automatically append a .dll extension to library names that already have a period (.) 
:: in their name, such as libgtk-win32-2.0-0.dll. If you try to use libgtk-win32-2.0-0 as the library name, 
:: Windows won’t automatically append .dll, resulting in a DllNotFoundException. Consequently you should 
:: either avoid periods in library names or always use the full filename (including the .dll extension) and
:: rely on Mono’s <dllmap/> mechanism. [1]
::
:: In VS2015, this `DllNotFoundException` will be solved if the `.dll` extension is appended manually.
:: In VS2010, however, the problem is still there. What's worse, there is not a `dllmap` mechanism right
:: here for you in Visual Studio. So, consider about the `Dynamic-Link Library Redirection` technic.
swig -c++ -csharp -namespace %1 -dllimport %1.Native.dll -outdir "%~dp0%2" -outfile %3.cs "%4"
goto Finish

:SWIGNotFound
echo Command 'swig' not found.

:Finish
echo on

:: References:
:: http://www.mono-project.com/docs/advanced/pinvoke/