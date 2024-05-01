# Mines-Detector-Robot

###### An AVR project

<br/>

## Introduction 

Detecting robots are designed to cover the maximum possible area of a landmine field for the detection of landmines.
The robot should give an alarm in case of mine detected and stop moving for a while then continue detection .

I built my project using ATmega32 , as ATmega32 is easy to program AVR controller. With appreciable program memory it can satisfy most EMBEDDED SYSTEMS.
and writing code using C and Embedded C Programming.

#### Objective
The primary goal of a Mine detection robot is to identify and locate buried landmines. Detecting landmines is crucial for the safety of army personnel and civilians living in war-prone areas.


#### Detection Mechanism
Metal detectors are commonly used as sensors to detect landmines since most landmines have metal components. The robot travels over the landmine field, scanning the ground using metal detectors to identify buried mines

#### Modes of Operation
###### The robot operates in different modes:

- Auto mode: Fully autonomous operation.

- Manual mode: Direct control by the operator

#### Full description of the module

[![Project Video](https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/2b97a48e-230d-44b2-8d7a-a25ce10acc72)](https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/6773b7ae-28ed-4d2e-bc0a-ac24cba79cb3
)


<br />
<br />

## Table of contents

- ##### Requirements
- ##### Recommended modules
- ##### Features
- ##### Installation
- ##### Configuration
- ##### Road Map
- ##### Analysis
- ##### Simulation
- ##### Hardware interface

<br />
<br />

## Requirements

##### This module requires the following modules:

[ROBOT](https://electra.store/product/robot-chassis-4-gear-motors-4-wheels-random-color-chassis/)

[ATMEGA32](https://www.ram-e-shop.com/shop/atmega32a-pu-atmega32a-u-6528)

[ULTRA-Sonic](https://store.fut-electronics.com/products/ultrasonic-sensor-module?_pos=1&_sid=e22a018fa&_ss=r)

[MOTOR-Drive](https://www.ram-e-shop.com/shop/kit-l298-red-l298-module-red-board-dual-h-bridge-motor-driver-using-l298n-7084)

[METAL-Detector](https://store.fut-electronics.com/products/inductive-proximity-sensor-metal-object-detection?_pos=1&_sid=ec5f7ae0a&_ss=r)

[BUZZER](https://store.fut-electronics.com/products/buzzer-5v?_pos=1&_sid=a37711764&_ss=r)

[BLUETOOTH-Module](https://www.ram-e-shop.com/shop/kit-bluetooth-hc05-normal-hc-05-bluetooth-module-normal-6674)

[USBASP](https://www.ram-e-shop.com/shop/prog-avr-serial-atmel-avr-usbasp-programmer-china-6290)

- 12v battery for Motor Drive and Metal-Detector sensor
  
- optocoupler for controlling Metal-Detector Signal
  ![image](https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/5710f879-f841-4fe8-8842-b73551b567b0)

<br />
<br />

## Recommended modules


- [SERVO-Motor](https://www.ram-e-shop.com/shop/servo-sg90-sg90-micro-servo-motor-180deg-1-8-kg-cm-plastic-gears-7222) : for making radar scan by ultrasonic

- [Metal-Detector](https://www.ram-e-shop.com/shop/kit-diy-metal-detector-diy-kit-simple-metal-detector-locator-7984) : for more detection range

- AVR Development Board


<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/40c4151e-739f-4d89-8f8d-7124775af552" width="200" >

<br />
<br />

## Features

- Robot has two modes of operation         : auto mode & manual mode
- Robot has three levels of movement speed : High & Medium & Low
- Obstacle avoidness
- Mine detection
- Remote access "Bluetooth"

<br />
<br />

## Installation

- Installing a text editor : For writting and editing code like Notepad++ & Visual studio code

- Installing Eclipse : (C/C++ Development Tools) plug-ins allow to create, build, debug ,burn  and have many features

- Installing Proteus : For simulation and test inputs & outputs

###### Step one :

Writing a C Project using text editor or eclipse 

###### Step two :

Making C Project  in eclipse , then choose C project type AVR Cross target application , then choose ATmega32 and finaly adjust freq 8000000 

###### step three :
<div>
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/7947e4de-b96e-47d7-ab24-59ef68977947" width="400" >
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/ff4ededc-b297-4760-add1-4b6672840b27" width="400" >
</div>

###### Step four :

Closing unrelated project ,then writing Or copy Code to C project ,then save code and finaly build 

###### Step five :

Making simulation in proteus to test project

###### step six :

Burn code To Atmega32 using USBASP 

<br />
<br />

## Configuration

###### ALL HAL Drivers Have Configurations

- ##### ULTRA-Sonic Driver (HUS) :
  Minimum Distance , checking time , port and pin of trigger , timer1 prescaler


  <img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/6de45d70-813f-4993-9c7f-aa11b84733ee" width="400" height ="200" >

###### Ex Configuration of minimum distance  :

```
#define HUS_MIN_DISTANCE			40

```

- ##### The other drivers :
  
<div>
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/9e807c25-4335-4108-a596-dffafa61ab12" width="400" height ="200" >
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/3eaf47e2-386b-4f5a-ada1-c13aee71c9dd" width="400" height ="200" >
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/341ec64b-5e8a-4252-b560-9802529164ec" width="400" height ="200" >
<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/e9afa9bd-a623-4409-b621-fbde376007ad" width="400" height ="200" >
</div>

- ##### Application Configuration :

<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/718ec6d1-7f1e-4ebb-aa9e-fde941853d16" width="400" height ="200" >

###### Ex Configuration of Application mode  :

```
//#define APP_MODE			APP_MANUAL_MODE
#define APP_MODE			APP_AUTO_MODE

```

<br />
<br />
  
## Road Map


###### Software road map
<br />

<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/f481772b-ffb5-4d88-af99-84fc54ea2b33" >

<br />
<br />
<br />
<br />

## Analysis

<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/3d962cbf-6c9c-4b84-a148-c9ba63d83c0b" >

<br />
<br />

## Simulation

###### My simulation using proteus
[Simulation](https://drive.google.com/drive/u/0/folders/1aevleRuMcT-sCoZyqtTnewIL26lUJ_Ju)

<br />
<br />



## Hardware Interface

<img src="https://github.com/MuhamedAmr10/Mines-Detector-Robot/assets/168368256/6ecb4f08-2a7a-47c3-b4b6-aae2e207d031" >












  














