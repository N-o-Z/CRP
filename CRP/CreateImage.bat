@echo off

IF %1==-d (

	echo Iterating on all PDFs in folder

	pushd %cd%
	chdir "./%2"
	for %%i in (*.pdf) do (
		echo %%~ni
		"C:\Program Files\gs\gs9.15\bin\gswin64c.exe" -q -dNOPAUSE -r120 -sCompression=pack -sDEVICE=tiffgray -sOutputFile=%%~ni.tif %%i -c quit
	)

	popd
	
	goto END

) 

"C:\Program Files\gs\gs9.15\bin\gswin64c.exe" -q -dNOPAUSE -r600 -sCompression=pack -sDEVICE=tiffgray -sOutputFile=%2f %1 -c quit

:END

echo %ERRORLEVEL%