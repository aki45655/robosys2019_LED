LED Project
====

Create a device driver to operate the Raspberry Pi GPIO.  
Use it to turn on the LED.

## Requirement
* Rasbery Pi 3 B+
* Jump wire (x2)
* LED
* Resistor(200~300Ω)
### Electoric circuit
Pins use GPIO25 and Ground.
## Usage
```
$make  
$sudo rmmod myled  
$sudo insmod myled.ko  
$sudo chmod 666 /dev/myled0  
```  
```
$echo H > /dev/myled0    //turn on LED  
$echo L > /dev/myled0    //turn off LED  
$echo 1 > /dev/myled0    //blink LED  
```
## Demo

## Licence

[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)


