:: Ce script génère l'executable de gameframework en mode release pour le déploiement.
:: Auteur : Jérôme Conus
:: Date   : 23.01.2024

@ECHO OFF

::Avant de changer de dossier, on mémorise le dossier actuel
::set OLDDIR=%CD%
set MINGW_FOLDER=C:\Qt-SDK\Tools\mingw1310_64

set QTFOLDER=C:\Qt-SDK\6.8.0
set PATH=%MINGW_FOLDER%\bin;%QTFOLDER%\mingw_64\bin;%PATH%

:: CMake
C:\Qt-SDK\Tools\CMake_64\bin\cmake.exe ^
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
copy .\2024-JCO-Brawlhalla-LMO.exe ..\release\ /Y
xcopy ..\res ..\release\res\ /E /Y

%QTFOLDER%\mingw_64\bin\windeployqt.exe ..\release\2024-JCO-Brawlhalla-LMO.exe
IF ERRORLEVEL 1 GOTO errorDeploy

:: Suppression du dossier inutiles créés par windeployqt
rmdir ..\release\translations /S /Q
rmdir ..\release\tls /S /Q
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
