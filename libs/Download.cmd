
rem %WGET% http://xmlsoft.org/sources/win32/libxmlsec-1.2.18.win32.zip

set WGET=wget
mkdir bin include lib
for %%f in (iconv-1.9.2.win32 libxml2-2.7.8.win32 libxslt-1.1.26.win32 zlib-1.2.5.win32) do (
	echo === %%f ===
	%WGET% http://xmlsoft.org/sources/win32/%%f.zip
	unzip -o %%f.zip
)
for %%f in (iconv-1.9.2.win32 libxml2-2.7.8.win32 libxslt-1.1.26.win32 zlib-1.2.5) do (
	xcopy /e %%f\bin\* bin\
	xcopy /e %%f\include\* include\
	xcopy /e %%f\lib\* lib\
	rmdir /S /Q %%f
)
