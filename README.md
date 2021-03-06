LED Project
====

Create a device driver to operate the Raspberry Pi GPIO.  
Use it to turn on the LED.
Blink LED at 0.1-0.9 second intervals.

## Requirement
* Rasbery Pi 3 B+
* Jump wire (x2)
* LED
* Resistor(200~300Ω)
### Electoric circuit
Pins use GPIO25 and Ground.
![circuit](electric_circuit.png)  
## Usage
Preparation command
```
$make  
$sudo rmmod myled  
$sudo insmod myled.ko  
$sudo chmod 666 /dev/myled0  
```  
Turn on and turn off LED
```
$echo H > /dev/myled0    //turn on LED  
$echo L > /dev/myled0    //turn off LED  
```  
Blink LED 10 times at 0.1-0.9 second intervals
```
$echo 1 > /dev/myled0    //blink LED 10 times at 0.1 second intervals  
$echo 2 > /dev/myled0    //blink LED 10 times at 0.2 second intervals  
      ･  
      ･　
      ･　
$echo 9 > /dev/myled0    //blink LED 10 times at 0.9 second intervals       
```
## Demo
https://youtu.be/hpsKJ90Ckdg 
## Licence

[GNU General Public License](https://github.com/aki45655/robosys2019_LED/blob/master/LICENSE)


