@echo off
REM Build and test script for Asio Echo Demo on Windows
REM This script initializes MSVC environment, builds, and runs tests

cd /d "%~dp0"

echo ========================================
echo Initializing MSVC Environment...
echo ========================================

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to initialize MSVC environment
    exit /b 1
)

echo.
echo ========================================
echo Building Asio Echo Demo...
echo ========================================

call build_win.bat

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo You can now run:
echo   - asio_echo_server.exe [port]
echo   - asio_echo_client.exe [host] [port] [message]
echo.