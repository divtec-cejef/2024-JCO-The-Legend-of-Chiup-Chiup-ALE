:: Ce script génère l'executable de gameframework en mode release pour le déploiement.
:: Auteur : Jérôme Conus
:: Date   : 23.01.2024

@ECHO OFF

::Avant de changer de dossier, on mémorise le dossier actuel
::set OLDDIR=%CD%

set PATH=%PATH%;C:\Qt\Tools\mingw1120_64\bin

set QTFOLDER=C:\Qt\6.3.0

%QTFOLDER%\mingw_64\bin\qmake.exe ..\src\GameFramework.pro

C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -f Makefile qmake_all

:: Compilation et link
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -j2

IF ERRORLEVEL 1 GOTO errorHandling
:: errorhandling, errorlevel >= 1

:no_error
:: Nettoyage
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe clean -j2

:: Création du dossier release qui contiendra les fichiers de déploiement
mkdir ..\release
copy .\release\GameFramework.exe ..\release\ /Y
xcopy ..\res ..\release\res\ /E /Y

%QTFOLDER%\mingw_64\bin\windeployqt.exe ..\release\GameFramework.exe
IF ERRORLEVEL 1 GOTO errorDeploy

:: Suppression du dossier inutiles créés par windeployqt
rmdir ..\release\translations /S /Q
rmdir ..\release\tls /S /Q
:: Rétablissement du dossier d'origine
::cd %OLDDIR%
exit

:errorHandling
echo Erreur de compilation !
pause
exit 1

:errorDeploy
echo Erreur de déploiement
pause
exit 1
