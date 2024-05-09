# Software part of my Weather station  

- Code based on the Raspberry Pi pico sdk
- Rpi pi sdk getting started tutotarial : https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html    
  
  ## Getting started in brief 

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



    
     

