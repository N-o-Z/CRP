"C:\Program Files\gs\gs9.15\bin\gswin64c.exe" -q -dNOPAUSE -r600 -sCompression=pack -sDEVICE=tiffgray -sOutputFile=%2f %1 -c quit
rem "C:\Program Files\gs\gs9.15\bin\gswin64c.exe" -q -dNOPAUSE -g5000x7072 -sDEVICE=tiff24nc -sOutputFile=%2 %2f -c quit

echo %ERRORLEVEL%