@echo off
setlocal

REM	Use sub-module fasm2.
REM	(Alter for your local copy elsewhere, or if in environment.)

set "include=%~dp0fasm2\include;%include%"
"%~dp0fasm2\fasmg" -iInclude('fasm2.inc') %*
endlocal
