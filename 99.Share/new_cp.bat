@echo off
:: Kiểm tra có tham số truyền vào không
if "%~1"=="" (
    echo Vui long nhap ten bai vi du: new_cp A
    exit /b
)

:: Đường dẫn đến folder template
set TEMPLATE=D:\C++\CP\Share\cp-template

:: Tên thư mục đích = thư mục hiện tại + tên bài
set DEST=%cd%\%~1

:: Kiểm tra xem thư mục đích đã tồn tại chưa
if exist "%DEST%" (
    echo Thu muc %DEST% da ton tai!
    exit /b
)

:: Copy toàn bộ nội dung từ template sang thư mục đích
xcopy "%TEMPLATE%" "%DEST%" /E /I /H /Y

echo Da tao thu muc %DEST%