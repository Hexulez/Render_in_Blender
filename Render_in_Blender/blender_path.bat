@echo off
set /p blender_path=Enter the path to the folder that contains the Blender executable:
setx PATH "%PATH%;%blender_path%" /M
echo.
echo The Blender executable has been added to the system's path.
