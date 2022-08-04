# MySweeper
An implementation of minesweeper using Qt

The release build should run in visual studio as it includes all the necessary DLLs to run the binary. 

If it does not, the steps to make it run in visual studio are:

1. remove the pre-existing directory
2. run cmake and set the relevant paths (i've only tested this on Qt5 but Qt6 should be compatible) and open the project file in VS2019
3. follow these instructions: https://doc.qt.io/qt-5/windows-deployment.html to deploy the necessary DLLs and folders for Qt. 
4. Try running the executable again. 
