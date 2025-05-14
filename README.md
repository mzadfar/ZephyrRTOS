# FreeRTOS Programming

The purpose of this repository is to start from practicing RTOS programming on Zephyr, and provide a base for embedded code development using Hardware Abstraction Layer (HAL) of STM32F439ZI developed by ST.

## Description

The following topics will be practiced here on a NUCLEO-F439ZI board:
* Empty project
* Virtual Com port
* LED blinking
* GPIO as output 
* Interrupt Service Routine (ISR)
* GPIO as input/output
* Pulse Width Modulation (PWM)
* Fading LEDs
* ktimer
* Custom DTS binding
* Threads
* System heap memory
* Hash map
* Servo motor

## Getting Started

### Dependencies

* Host can be any OS like Fedora 42 Linux in this case or Ubuntu, Windows etc.  
* Follow instruction in the link"[Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)" to set up a Zephyr development environment

### Installing

* After following the link"[Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)", please check "cmake --version", "python3 --version", "dtc –version", and "ninja --version".
* After "west zephyr-export" command, one of the 2 below lines should be run on the command line: "west packages pip --install" or "pip install -r /home/your_user_name/Documents/Workspace/STM32/ZephyrProject/zephyr/scripts/requirements.txt"; whichever works 
* After running the last command to set up Zephyr development environment "west sdk install -b /home/your_user_name/Documents/Workspace/STM32/ZephyrProject/zephyr", you may receive error regarding "cannot install toolchain" which seems not a deal breaker.
* Create a file named ~/.zephyrrc if it doesn’t exist, then open it by "vim ~/.zephyrrc", and add these lines or whatever your toolchains are to it: 
export GNUARMEMB_TOOLCHAIN_PATH="/usr", 
export CROSS_COMPILE="/usr/bin/arm-none-eabi-", 
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb.
* To get this value back into your current terminal environment, you must run source zephyr-env.sh from the main zephyr repository. Among other things, this script "sources ~/.zephyrrc".

### Executing program

#### Empty project

* This is a Zephyr empty example project to initiate practicing Zephyr RTOS. First run "west build -p always -b nucleo_f429zi --build-dir /home/your_user_name/Documents/Workspace/STM32/ZephyrProject/Zephyr/blinky/build", and then run "west flash --runner jlink" to execute the code. 

#### Virtual Com Port

* This is a Zephyr RTOS example equipped with virtual COM port to communicate with PC. Follow corresponding order for Zephyr RTOS "Empty project" above.

#### LED blinking
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### GPIO as output 
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Interrupt Service Routine (ISR)
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### GPIO as input/output
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Pulse Width Modulation (PWM)
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Fading LEDs
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### ktimer
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Custom DTS binding
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Threads
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### System heap memory
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Hash map
* Follow corresponding order for Zephyr RTOS "Empty project" above.

#### Servo motor
* Follow corresponding order for Zephyr RTOS "Empty project" above.

## Help

TBD

## Authors

Contributor names and contact info

TBD

## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the FREE License - see the LICENSE.md file for details

## Acknowledgments

Inspiration, code snippets, etc.
* [mz](https://github.com/mzadfar/)