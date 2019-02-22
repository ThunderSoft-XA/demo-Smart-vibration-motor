# demo-Smart-vibration-motor
A Demo of Qualcomm MDM9206

Basic Information:

Maintainer: Kou Zhiwu,JiangYuan,Wang Jie,Yan Shaohui,YangRong.

Start date: February 12th, 2019

Function description:

Mainly to use the APP installed in mobile phone to send commands to control the vibrator provided by Gokit4 development kit to start/stop the vibration.

Document introduction:

===> Gizwits: it mainly include Gizwits cloud protocol related files.

===> Utils: It mainly includes some common data processing algorithms.

===> demo-Smart-Motion-detector-picture: include some pictures about this demo.

===> driver: mainly include some driver code, about gpio, adxl345, spi etc.

===> gagent: file containing the Gizwits Cloud Device Connection Protocol Library.

===> main: code start runing from this directory.

===> objs: Store some link files.

===> sdk: Store head files.

===> target: Store image file.

===> demo-Smart-Motion-detector.doc: detailed description of the demo;

===> llvm_build.bat: Script to compile source code.

Usage Instructions:
1. Download code from github according to the repository in ”https://github.com/ThunderSoft-XA/demo-Smart-vibrator"sheet.
2. Compile the code and flash the image to Gokit4 development kit.
3. USB data cable to connect PC and Gokit development board.
4. Open the serial debugging assistant.
5. Click on "Device log" in Gizwits cloud to check if device is online.
6. When device online, you can click "view" button, and you'll see data from local was sent to Gizwits cloud.
7. Download app from "https://download.gizwits.com/zh-cn/p/98/99", and install it to your phone.
8. Open the apk, and you'll see "my device", here you can find your device by scanning QR code.
9. Next, generate the QR code.
	a. open "gizwits debugging assistant_v2.3.9/GIZ_SerialTool.exe"
	b. choose "small tools", 	click "QR code generation", input "product key" and "MAC/IMEI"
	c. click "get QR code", and wait for a moment,you can see a QR code.
10. Click "my device" , and scan the generated QR code,  you can find your device.
11. Then you can control the device and view the data.
