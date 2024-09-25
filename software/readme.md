# Software part of my Weather station  

- Code based on the Raspberry Pi pico sdk
- Rpi pi sdk getting started tutorial : https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html    
  
  ## Getting started in brief 

  - Be sure to have installed the cross-compiler and other essential software :  
```shell  
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential    
```  

  - __Clone pico-sdk git :__
```shell
$ git clone https://github.com/raspberrypi/pico-sdk.git 
```  

  - Set PICO_SDK_PATH :  
```shell  
$ export PICO_SDK_PATH="/home/gael/git/pico-sdk"
```

  - Copy `external/pico_sdk_inport.cmake` in my project directory  
  - Compilation :  
```shell  
$ mkdir build  
$ cd build
$ cmake ..  
$ make <target_name>  
```  



    
     

