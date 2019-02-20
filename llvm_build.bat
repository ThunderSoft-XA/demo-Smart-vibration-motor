@echo off
setlocal enabledelayedexpansion

set DAM_RO_BASE=0x43000000
set TOOLCHAIN_DIR=D:\4.0.3
set PYTHON_DIR=C:\Python27
set SDK_DIR=sdk

set TOOLCHAIN_PATH=%TOOLCHAIN_DIR%\bin
set TOOLCHAIN_PATH_STANDARdS=%TOOLCHAIN_DIR%\armv7m-none-eabi\libc\include
set LLVMLIB=%TOOLCHAIN_DIR%\lib\clang\4.0.11\lib
set LLVMLINK_PATH=%TOOLCHAIN_DIR%\tools\bin
set BIN_OUTPUT_PATH=target

set DAM_INC_BASE=%SDK_DIR%\include
set DAM_LIB_PATH=%SDK_DIR%\libs
set DAM_SRC_PATH=.
set PYTHON_PATH=%PYTHON_DIR%\python.exe

set DEMO_APP_SRC_PATH=%GATGENT_IOF%\iofbg96
set DAM_LD_PATH=%SDK_DIR%\ld

set DAM_LIBNAME=txm_lib.lib
set TIMER_LIBNAME=timer_dam_lib.lib
set DIAG_LIB_NAME=diag_dam_lib.lib
set QMI_LIB_NAME=qcci_dam_lib.lib
set QMI_QCCLI_LIB_NAME=IDL_DAM_LIB.lib

set DAM_ELF_NAME=gizwits_app.elf
set DAM_TARGET_BIN=gizwits_app.bin
set DAM_GAGENT_LIB=libgagent.a

set COMPILER=%TOOLCHAIN_PATH%\clang.exe
set LINKER=%TOOLCHAIN_PATH%\clang++.exe
set LLVMAR=%TOOLCHAIN_PATH%\llvm-ar.exe


set RM=del
set RMD=rd /s /q
set MV=move
set LS=dir


rem ###################### modify by Alex start #####################
rem # configer data for gagent
rem # if it's soc project, it shoult be "N"

set PRJ_PATH=%~dp0
set PROJECT_PATH=%PRJ_PATH:~,-1%
set TARGET=%PROJECT_PATH%\target
set OBJS_OUTPUT_PATH=%PROJECT_PATH%\objs
set GAGENT_LIB_PATH=%PROJECT_PATH%\gagent

set MAIN_DIR=%PROJECT_PATH%\main
set SOC_GIZWITS=%PROJECT_PATH%\Gizwits
set SOC_UTILS=%PROJECT_PATH%\Utils
set SOC_DRIVER_GPIO=%PROJECT_PATH%\driver\gpio
rem #set SOC_DRIVER_HEARTBEAT=%PROJECT_PATH%\driver\heartbeat
rem #set SOC_DRIVER_ACTIVITY=%PROJECT_PATH%\driver\activity
rem #set SOC_DRIVER_IIC=%PROJECT_PATH%\driver\I2c
rem #set SOC_DRIVER_ADC=%PROJECT_PATH%\driver\adc
rem #set SOC_DRIVER_TEMPERATURE=%PROJECT_PATH%\driver\temperature


del *.o /s

if not exist %BIN_OUTPUT_PATH% (
  mkdir %BIN_OUTPUT_PATH%
)

if not exist "%OBJS_OUTPUT_PATH%" (
  mkdir "%OBJS_OUTPUT_PATH%"
)

if "%1%"=="-c" (
  echo "Cleaning...%BIN_OUTPUT_PATH%"
  rd /s /q %BIN_OUTPUT_PATH%
  echo "Cleaning...%OBJS_OUTPUT_PATH%"
  rd /s /q %OBJS_OUTPUT_PATH%
  
  echo "Done."
  exit /b
)


echo "Application RO base selected = %DAM_RO_BASE%"

set DAM_CPPFLAGS=-DUSE_LLVM -DQAPI_TXM_MODULE -DTXM_MODULE -DTX_DAM_QC_CUSTOMIZATIONS -DTX_ENABLE_PROFILING -DTX_ENABLE_EVENT_TRACE -DTX_DISABLE_NOTIFY_CALLBACKS -DFX_FILEX_PRESENT -DTX_ENABLE_IRQ_NESTING -DTX3_CHANGES

set DAM_CFLAGS=-marm -target armv7m-none-musleabi -mfloat-abi=softfp -mfpu=none -mcpu=cortex-a7 -mno-unaligned-access  -fms-extensions -Osize -fshort-enums -Wbuiltin-macro-redefined


set DAM_INCPATHS=-I %DAM_INC_BASE% -I %DAM_INC_BASE%\threadx_api -I %DAM_INC_BASE%\qmi -I %DAM_INC_BASE%\qapi -I %DEMO_APP_SRC_PATH% -I %TOOLCHAIN_PATH_STANDARdS% -I %DAM_CPPFLAGS% -I %LLVMLIB%

set APP_CFLAGS=-DTARGET_THREADX
REM -D__SIMCOM_DAM__

echo "Compiling application"

@echo on

REM ################################ GAgent END ########################################

for %%x in (%MAIN_DIR%\*.c) do (
 %COMPILER%  -c  %DAM_CPPFLAGS% %GAGENT_CPPFLAGS% %DAM_CFLAGS% %APP_CFLAGS% %DAM_INCPATHS% %GAGENT_INC%  %%x
 if errorlevel 1 (goto :eof)
)
for %%x in (%SOC_GIZWITS%\*.c) do (
%COMPILER%  -c  %DAM_CPPFLAGS% %GAGENT_CPPFLAGS% %DAM_CFLAGS% %APP_CFLAGS% %DAM_INCPATHS% %GAGENT_INC% %SOC_GIZWITS% %%x
 if errorlevel 1 (goto :eof)
)
for %%x in (%SOC_UTILS%\*.c) do (
%COMPILER%  -c  %DAM_CPPFLAGS% %GAGENT_CPPFLAGS% %DAM_CFLAGS% %APP_CFLAGS% %DAM_INCPATHS% %GAGENT_INC% %SOC_UTILS% %%x 
 if errorlevel 1 (goto :eof)
)
for %%x in (%SOC_DRIVER_GPIO%\*.c) do (
%COMPILER%  -c  %DAM_CPPFLAGS% %GAGENT_CPPFLAGS% %DAM_CFLAGS% %APP_CFLAGS% %DAM_INCPATHS% %GAGENT_INC% %SOC_DRIVER_GPIO% %%x 
 if errorlevel 1 (goto :eof)
)
move *.o %OBJS_OUTPUT_PATH%

%COMPILER% -E  %DAM_CPPFLAGS% %DAM_CFLAGS% %SDK_DIR%\preamble\txm_module_preamble_llvm.S > %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm_pp.S

%COMPILER%  -c %DAM_CPPFLAGS% %DAM_CFLAGS% %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm_pp.S -o %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm.o

del %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm_pp.S

echo "Linking application"

%LINKER% -d -o %BIN_OUTPUT_PATH%\%DAM_ELF_NAME% -target armv7m-none-musleabi -fuse-ld=qcld -lc++ -Wl,-mno-unaligned-access -fuse-baremetal-sysroot -fno-use-baremetal-crt -Wl,-entry=%DAM_RO_BASE% %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm.o -Wl,-T%DAM_LD_PATH%\quectel_dam_demo.ld -Wl,-Map,-Wl,-gc-sections %OBJS_OUTPUT_PATH%\*.o %GAGENT_LIB_PATH%\%DAM_GAGENT_LIB% %DAM_LIB_PATH%\*.lib

REM %LINKER% -d -o %BIN_OUTPUT_PATH%\%DAM_ELF_NAME% -target armv7m-none-musleabi -fuse-ld=qcld -lc++ -Wl,-mno-unaligned-access -fuse-baremetal-sysroot -fno-use-baremetal-crt -Wl,-entry=%DAM_RO_BASE% %OBJS_OUTPUT_PATH%\txm_module_preamble_llvm.o -Wl,-T%DAM_LD_PATH%\quectel_dam_demo.ld -Wl,-Map,-Wl,-gc-sections %OBJS_OUTPUT_PATH%\*.o %DAM_LIB_PATH%\*.lib


%PYTHON_PATH% %LLVMLINK_PATH%\llvm-elf-to-hex.py --bin %BIN_OUTPUT_PATH%\%DAM_ELF_NAME% --output %BIN_OUTPUT_PATH%\%DAM_TARGET_BIN%

echo "Application is built at" %BIN_OUTPUT_PATH%\%DAM_TARGET_BIN%
echo "Application is built at" %date% %time%

set /p =/datatx/%DAM_TARGET_BIN%<nul > %BIN_OUTPUT_PATH%\oem_app_path.ini

endlocal
pause

