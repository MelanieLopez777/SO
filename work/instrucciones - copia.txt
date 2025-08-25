@echo off
title LIMPIADOR DE CAPTURAS DE PANTALLA

echo Fecha actual: %date%

echo Hora actual: %time%

echo Usuario actual: %username%

echo Nombre de la PC: %computername%

ver

echo.
pause

echo Ejecutando Liberador de espacio en disco...
cleanmgr /autoclean
echo.

cd %UserProfile%\Downloads\Capturas de pantalla

echo Archivos encontrados en la carpeta:
dir *.png
echo.

:: Menu de opciones
echo Elige una opcion:
echo [1] Eliminar TODAS las capturas sin confirmacion
echo [2] Eliminar con confirmacion (una por una)
echo [3] Cancelar
set /p opcion=Opcion: 

if "%opcion%"=="1" goto borrar_todo
if "%opcion%"=="2" goto borrar_confirmar
if "%opcion%"=="3" goto fin

:borrar_todo
echo Eliminando todas las capturas sin confirmacion...
del /q *.png
goto fin

:borrar_confirmar
echo Eliminando con confirmacion por archivo...
del /p *.png
goto fin

:fin
echo.
echo Proceso terminado.
pause

