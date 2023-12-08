"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" gameoverlay.sln /t:build /p:Configuration=Release /p:Platform=Win32
"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" gameoverlay.sln /t:build /p:Configuration=Release /p:Platform=x64

echo "copy binary"
copy /y .\bin\release\n_overlay.dll ..\prebuilt
copy /y .\bin\release\n_overlay.x64.dll ..\prebuilt
copy /y .\bin\release\n_ovhelper.exe ..\prebuilt\injector_helper.exe
copy /y .\bin\release\n_ovhelper.x64.exe ..\prebuilt\injector_helper.x64.exe
