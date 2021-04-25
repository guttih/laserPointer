
#### Wiring diagram from Laser Part pointer

This project will be about driving 2 servos and 1 laser using a esp32 and a power supply to to point to parts or tools, I own around my garage. This project will be connected to another project called GParts which is also located on this github space.

[Project on github](https://github.com/guttih/laserPointer)

How to connect trigger a 6V laser with esp32
 - 100Ω resistor to esp32 pin and base on BC547 (middle pin)
 - 10kΩ resistor from base on BC547 to GND
 - BC547 Collector to GND
 - Laser GND to BC547 Emitter
 - Laser VCC wire to 6V
 - [View image about it here](https://electronics.stackexchange.com/questions/56093/how-to-use-a-3v-output-to-control-a-5v-relay)

 
Parts I plan to use in the project
 - [Laser 650nm 5mW Red Cross](https://www.aliexpress.com/item/32870666247.html?spm=a2g0s.12269583.0.0.7be313f4OIyWvS)
 - Two pieces [Servo motor RDS3225](https://www.aliexpress.com/item/4000943153775.html?spm=a2g0s.12269583.0.0.701745b71zAQGI)
 - [ESP32 Development Board ](https://www.aliexpress.com/item/32839311668.html?spm=a2g0s.9042311.0.0.27424c4dYD8HnK)
 - [Power supply 6V - 6A](https://www.aliexpress.com/item/4000102102421.html?spm=a2g0s.12269583.0.0.4f644eccTkOI4c)
 - [HLK-PM01 5V](https://www.aliexpress.com/item/32504127465.html?spm=a2g0s.9042311.0.0.27424c4dOggB1n)
 - [BC547B Transistor](https://www.aliexpress.com/item/32853901405.html?spm=a2g0s.12269583.0.0.4eb45072Gat93G)

### Wiring diagram
```
GND                                     +6V
 ├──────────────────────┐                │
 | ╔════╗ ╔═══════════╗ |                │
 ├─╢ R2 ║ ║  -BC547-  ║ |    ╔═════════╗ |
 | ║10kΩ║ ║           ║ |    ║ -Laser- ║ │
 | ╚═╤══╝ ║ Collector ╟─┘    ║         ║ │
 |   ├────╢ Base      ║      ║     VCC ╟─┤
 |   │    ║ Emitter   ╟──────╢ GND     ║ │
 | ╔═╧══╗ ╚═══════════╝      ╚═════════╝ │
 | ║ R1 ║ ╔═══════════╗     ╔══════════╗ │
 │ ║100Ω║ ║  -ESP32-  ║     ║-HLK-PM01-║ │
 | ╚═╤══╝ ║           ║     ║          ║ │
 │   │GND ║ 3V3   VIN ╟─────╢ +Vo (+5V)║ │
 │   │ ╧ ─╢ GND   GND ╟─────╢ -Vo      ║ │
 │   └────╢ D4        ║     ╚══════════╝ │
 |      ┌─╢ D13   D12 ╟─┐ ┌──── GND      │
 |      │ ║           ║ | |      ╧       │
 |      │ ╚═══════════╝ | | ╔══════════╗ │
 |      │ ╔══════════╗  | | ║ -Servo2- ║ │
 |      │ ║ -Servo1- ║  | | ║          ║ │
 |      │ ║          ║  | └─╢ GND      ║ │
 |      └─╢ Signal   ║  └───╢ Signal   ║ │
 |        ║      VCC ╟──┐   ║      VCC ╟─┤
 └────────╢ GND      ║  |   ╚══════════╝ │
          ╚══════════╝  └────────────────┘
```
 - __R1__ 100 ohm resistor
 - __R2__ 10**k** ohm resistor

[Ascii codes](https://www.rapidtables.com/code/text/alt-codes.html)