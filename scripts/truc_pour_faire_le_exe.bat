:: Ce script génère l'executable de gameframework en mode release pour le déploiement.
:: Auteur : Jérôme Conus
:: Date   : 23.01.2024

@ECHO OFF

cd C:\Users\MEYNALE\Documents\2024-JCO-The-Legend-of-Chiup-Chiup-ALE\scripts

::Avant de changer de dossier, on mémorise le dossier actuel
::set OLDDIR=%CD%
set MINGW_FOLDER=C:\QtCreator\Tools\mingw1310_64

del ..\release.zip
rmdir /S/Q ..\release

set QTFOLDER=C:\QtCreator\6.8.0
set PATH=%MINGW_FOLDER%\bin;%QTFOLDER%\mingw_64\bin;%PATH%

:: CMake
C:\QtCreator\Tools\CMake_64\bin\cmake.exe ^
    -G "MinGW Makefiles" ^
    -DCMAKE_PREFIX_PATH="%QTFOLDER%\mingw_64\lib\cmake" ^
    -DCMAKE_BUILD_TYPE=Release ^
    ..\src

:: Compilation et link
mingw32-make.exe -j2

:: Nettoyage
:: mingw32-make.exe clean -j2
:: IF ERRORLEVEL 1 GOTO errorHandling
:: errorhandling, errorlevel >= 1

:: no_error
:: Nettoyage
:: C:\Qt-SDK\Tools\mingw1310_64\bin\mingw32-make.exe clean -j2

:: Création du dossier release qui contiendra les fichiers de déploiement
mkdir ..\release
copy .\2024-JCO-The-Legend-of-Chiup-Chiup-ALE.exe ..\release\ /Y
xcopy ..\res ..\release\res\ /E /Y

%QTFOLDER%\mingw_64\bin\windeployqt.exe ..\release\2024-JCO-The-Legend-of-Chiup-Chiup-ALE.exe
IF ERRORLEVEL 1 GOTO errorDeploy

:: Suppression du dossier inutiles créés par windeployqt
rmdir ..\release\translations /S /Q
rmdir ..\release\tls /S /Q

rmdir /S/Q .qt 2024-JCO-The-Legend-of-Chiup-Chiup-ALE_autogen CMakeFiles
del Makefile CMakeCache.txt 2024-JCO-The-Legend-of-Chiup-Chiup-ALE.exe cmake_install.cmake

::ResourceHacker.exe -open ../release/2024-JCO-The-Legend-of-Chiup-Chiup-ALE.exe -save ../release/2024-JCO-The-Legend-of-Chiup-Chiup-ALE.exe -action addoverwrite -res ../res/images/brawlhalla/icon.ico -mask ICONGROUP,MAINICON,

:: Génération d'une release zip
7z a ..\release.zip ..\release\*

:: Rétablissement du dossier d'origine
exit
:errorHandling
echo Erreur de compilation !
pause
exit 1

:errorDeploy
echo Erreur de déploiement
pause
exit 1
