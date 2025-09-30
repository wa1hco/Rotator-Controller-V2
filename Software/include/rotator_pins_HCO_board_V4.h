/* Arduino Rotator Controller "wa1hco Edition"
 *
   Jeff Millar, WA1HCO
   wa1hco@gmail.com
   
   Anthony Good, K3NG
   anthony.good@gmail.com

   Contributions from John Eigenbode, W3SA
   w3sa@arrl.net
   Contributions: AZ/EL testing and debugging, AZ/EL LCD Enhancements, original North center code, Az/El Rotator Control Connector Pins

   Contributions from Jim Balls, M0CKE
   makidoja@gmail.com
   Contributions: Rotary Encoder Preset Support
   
   Contributions from Gord, VO1GPK
   Contribution: FEATURE_ADAFRUIT_BUTTONS code

   ***************************************************************************************************************

    This program is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
    
                              http://creativecommons.org/licenses/by-nc-sa/3.0/

                          http://creativecommons.org/licenses/by-nc-sa/3.0/legalcode
 */

// ------------------------------------- Teensy 4.0Pin Definitions ------------------------------------------

#ifndef ROTATOR_PINS_H_
#define ROTATOR_PINS_H_

#include "rotator_features.h"
#include "dependencies.h"


// You need to look at these and set them appropriately !
// Most pins can be disabled by setting them to 0 (zero).  If you're not using a pin or function, set it to 0.

// STM32F405 LQFP64, Hardware Pin Definitions, lower case means secondary pin location
//-----|--------|----------|------|-------|--------|---------|-----|--------|--------|
// Pin | Name   | Function | Free | Power | Serial |   ADC   | DAC |  SPI   |  TWI   |
//-----|--------|----------|------|-------|--------|---------|-----|--------|--------|
//  1  | VBAT   |          |      | VBAT  |        |         |     |        |        |
//  2  | PC13   |          |      |       |        |         |     |        |        |
//  3  | PC14   |          |      |       |        |         |     |        |        |
//  4  | PC15   |          |      |       |        |         |     |        |        |
//  5  | PH0    |          |      |       |        |         |     |        |        |
//  6  | PH1    |          |      |       |        |         |     |        |        |
//  7  | NRST   |          |      |       |        |         |     |        |        |
//  8  | PC0    |          |      |       |        |A123_IN10|     |        |        |
//  9  | PC1    |          |      |       |        |A123_IN11|     |        |        |
// 10  | PC2    |          |      |       |        |A123_IN12|     |        |        |
// 11  | PC3    |          |      |       |        |A123_IN13|     |        |        |
// 12  | VSSA   |          |      | GND   |        |         |     |        |        |
// 13  | VDDA   |          |      | 3V3   |        |         |     |        |        |
// 14  | PA0    |          |      |       |        |A123_IN0 |     |        |        |
// 15  | PA1    |          |      |       |        |A123_IN1 |     |        |        |
// 16  | PA2    |          |      |       |        |A123_IN2 |     |        |        |
//-----|--------|----------|------|-------|--------|---------|-----|--------|--------|
// 17  | PA3    |          |      |       |        |         |     |        |        |
// 18  | VSS1   |          |      |       |        |         |     |        |        |
// 19  | VDD    |          |      | 3V3   |        |         |     |        |        |
// 20  | PA4    |          |      |       |        |A12_IN4  |     |        |        |
// 21  | PA5    |          |      |       |        |A12_IN5  |     |        |        |
// 22  | PA6    |          |      |       |        |A12_IN6  |     |        |
// 23  | PA7    |          |      |       |        |A12_IN7  |     |        |        |
// 24  | PC4    |          |      |       |        |A12_IN14 |     |        |        |
// 25  | PC5    |          |      |       |        |A12_IN15 |     |        |        |
// 26  | PB0    |          |      |       |        |A12_IN8  |     |        |        |
// 27  | PB1    |          |      |       |        |A12_IN9  |     |        |        |
// 28  | PB2    |          |      | 5V    |        |         |     |        |        |
// 29  | PB10   |          |      | GND   |        |         |     |        |        |
// 30  | PB11   |          |      |       |        | AIN8    |     | 0,mosi |        |
// 31  | VCAP1  |          |      | VCAP1 |        | AIN9    |     | 0,miso |        |
// 32  | VDD    |          |      | 3V3   |        | AIN10   |     | 0,sck  |        |
//-----|--------|----------|------|--=----|--------|---------|-----|--------|--------|
// 33  | PB12   |          |      |       |        | AIN11   |     | 0,ss\  |        |
// 34  | PB13   |          |      |       |        |         |     |        |        |
// 35  | PB14   |          |      |       |        |         |     |        |        |
// 36  | PB15   |          |      |       |        |         |     |        | 1,SDA  |
// 37  | PC6    |          |      |       |        |         |     |        | 1,SCL  |
// 38  | PC7    |          |      |       |        |         |     |        |        |
// 39  | PC8    |          |      |       |        |         |     |        |        |
// 40  | PC9    |          |      |       |        |         |     |        |        |
// 41  | PA8    |          |      |       |        |         |     |        |        |
// 42  | PA9    |          |      |       |        |         |     |        |        |
// 43  | PA10   |          |      |       |        |         |     |        |        |
// 44  | PA11   | USB_D-   |      |       |        |         |     |        |        |
// 45  | PA12   | USB_D+          |       |        |         |     |        |        |
// 46  | PA13   |          |      |       |        |         |     |        |        |
// 47  | VCAP2  |          |      | VCAP2 |        |         |     |        |        |
// 48  | VDD    |          |      | 3V3   |        |         |     |        |        |
//-----|--------|----------|------|-------|--------|---------|-----|--------|--------|
// 49  | PA14   |          |      |       |        |         |     |        |        |
// 50  | PA15   |          |      |       |        |         |     |        |        |
// 51  | PC10   |          |      |       |        |         |     |        |        |
// 52  | PC11   |          |      |       |        |         |     |        |        |
// 53  | PC12   |          |      |       |        |         |     |        |        |
// 54  | PD2    |          |      |       |        |         |     |        |        |
// 55  | PB3    |          |      |       |        |         |     |        |        |
// 56  | PB4    |          |      |       |        |         |     |        |        |
// 57  | PB5    |          |      |       |        |         |     |        |        |
// 58  | PB6    |          |      |       |        |         |     |        |        |
// 59  | PB7    |          |      |       |        |         |     |        |        |
// 60  | BOOT0  |          |      |       |        |         |     |        |        |
// 61  | PB8    |          |      |       |        |         |     |        |        |
// 62  | PB9    |          |      |       |        |         |     |        |        |
// 63  | VSS2   |          |      | GND   |        |         |     |        |        |
// 64  | VDD    |          |      | 3V3   |        |         |     |        |        |
//-----|--------|----------|------|-------|--------|---------|-----|--------|--------|


#ifdef FEATURE_MAX7221_DISPLAY
#define MAX7221_CS_PIN 10 // MAX7221 SPI bus chip select pin
#endif

#ifdef FEATURE_HCO_BUTTONS
#define BUTTON_CCW_PIN   8
#define BUTTON_CW_PIN    9
#endif

// when using a quad relay board
#define BrakeAzPin       16         // high to release brake
#define DirectionPin     17         // high to rotate left
#define MotorPin         20         // high to run motor

#define AzPositionTopPin 14         // A0, top pin of pot with grounded wiper
#define AzPositionBotPin 15         // A1, bottom pin of pot with grounded wiper
#define AzPresetPin      21         // A7, 10K pot, 3V3 to GND

#define TeensyLED        13

// when using motor and direction relays or...
// when using an L298N H-bridge PWM motor controller
#define ENAPin           20         // ENA on L298n, Motor control pin
#define IN1Pin           17         // IN1 on L298n, Direction controlpin
#define IN2Pin           0          // IN2 on L298n


// azimuth pins --------------------- (use just the azimuth pins for an azimuth-only rotator)
// if change made here, also change initialize_pins()
#define serial_led              TeensyLED       // LED blinks when command is received on serial port (set to 0 to disable)
#define overlap_led             0               // line goes high when azimuth rotator is in overlap (> 360 rotators)
#define brake_az                BrakeAzPin      // goes high to disengage azimuth brake (set to 0 to disable)
#define az_speed_pot            0               // connect to wiper of 1K to 10K potentiometer for speed control (set to 0 to disable)
#define az_preset_pot           AzPresetPin     // connect to wiper of 1K to 10K potentiometer for preset control (set to 0 to disable)
#define preset_start_button     0               // connect to momentary switch (ground on button press) for preset start (set to 0 to disable or for preset automatic start)
#define button_stop             0               // connect to momentary switch (ground on button press) for preset stop (set to 0 to disable or for preset automatic start)

#define rotate_cw               0               // asserted to activate rotator R ( CW) rotation - pin 1 on Yaesu connector
#define rotate_ccw              0               // asserted to activate rotator L (CCW) rotation - pin 2 on Yaesu connector
#define rotate_cw_pwm           0               // optional - PWM CW output  - set to 0 to disable (must be PWM capable pin)
#define rotate_ccw_pwm          0               // optional - PWM CCW output - set to 0 to disable (must be PWM capable pin)
#define rotate_cw_ccw_pwm       0               // optional - PWM on CW and CCW output - set to 0 to disable (must be PWM capable pin)
#define rotate_motor            ENAPin          // optional - motor control pin
#define rotate_cw_freq          0               // optional - CW variable frequency output
#define rotate_ccw_freq         0               // optional - CCW variable frequency output

#define rotate_h1               IN1Pin          // L298 H Bridge In 1 Pin, High means rotate cw
#define rotate_h2               0               // L298 H Bridge In 2 Pin, High means rotate ccw
#define button_cw_pin           BUTTON_CW_PIN      // normally open button to ground for manual CW rotation (schematic pin: A1)
#define button_ccw_pin          BUTTON_CCW_PIN      // normally open button to ground for manual CCW rotation (schematic pin: A2)
#define azimuth_speed_voltage   0               // optional - PWM output for speed control voltage feed into rotator (on continually unlike rotate_cw_pwm and rotate_ccw_pwm)
#define blink_led               0

#define rotator_Raz             0               // reads analog azimuth voltage from rotator - pin 4 on Yaesu connector
#define rotation_indication_pin 0


/*----------- elevation pins --------------*/
#ifdef FEATURE_ELEVATION_CONTROL
#define rotate_up               0           // goes high to activate rotator elevation up
#define rotate_down             0           // goes high to activate rotator elevation down
#define rotate_up_or_down       0           // goes high when elevation up or down is activated
#define rotate_up_pwm           0           // optional - PWM UP output - set to 0 to disable (must be PWM capable pin)
#define rotate_down_pwm         0           // optional - PWM DOWN output - set to 0 to disable (must be PWM capable pin)
#define rotate_up_down_pwm      0           // optional - PWM on both UP and DOWN (must be PWM capable pin)
#define rotate_up_freq          0           // optional - UP variable frequency output
#define rotate_down_freq        0           // optional - UP variable frequency output
#define rotator_analog_el       0           // reads analog elevation voltage from rotator
#define button_up               0           // normally open button to ground for manual up elevation
#define button_down             0           // normally open button to ground for manual down rotation
#define brake_el                0           // goes high to disengage elevation brake (set to 0 to disable)
#define elevation_speed_voltage 0           // optional - PWM output for speed control voltage feed into rotator (on continually unlike rotate_up_pwm and rotate_down_pwm)
#endif //FEATURE_ELEVATION_CONTROL

// rotary encoder pins and options
#ifdef FEATURE_AZ_PRESET_ENCODER 
#define az_rotary_preset_pin1           0   // CW Encoder Pin
#define az_rotary_preset_pin2           0   // CCW Encoder Pin
#endif //FEATURE_AZ_PRESET_ENCODER

#ifdef FEATURE_EL_PRESET_ENCODER 
#define el_rotary_preset_pin1           0  // UP Encoder Pin
#define el_rotary_preset_pin2           0  // DOWN Encoder Pin
#endif //FEATURE_EL_PRESET_ENCODER

#ifdef FEATURE_AZ_POSITION_ROTARY_ENCODER
#define az_rotary_position_pin1         0  // CW Encoder Pin
#define az_rotary_position_pin2         0  // CCW Encoder Pin
#endif //FEATURE_AZ_POSITION_ROTARY_ENCODER

#ifdef FEATURE_EL_POSITION_ROTARY_ENCODER
#define el_rotary_position_pin1         0   // CW Encoder Pin
#define el_rotary_position_pin2         0   // CCW Encoder Pin
#endif //FEATURE_EL_POSITION_ROTARY_ENCODER

#ifdef FEATURE_AZ_POSITION_PULSE_INPUT
#define az_position_pulse_pin           0   // must be an interrupt capable pin!
#define AZ_POSITION_PULSE_PIN_INTERRUPT 0   // Uno: pin 2 = interrupt 0, pin 3 = interrupt 1
#endif                                      // read http://arduino.cc/en/Reference/AttachInterrupt for details on hardware and interrupts

#ifdef FEATURE_EL_POSITION_PULSE_INPUT
#define el_position_pulse_pin           0   // must be an interrupt capable pin!
#define EL_POSITION_PULSE_PIN_INTERRUPT 0   // Uno: pin 2 = interrupt 0, pin 3 = interrupt 1
#endif                                      // read http://arduino.cc/en/Reference/AttachInterrupt for details on hardware and interrupts

#ifdef FEATURE_PARK
#define button_park 0
#endif

#define    LCDRsPin   99
#define    LCDEnPin   99
#define    LCDD7Pin   99
#define    LCDD6Pin   99
#define    LCDD5Pin   99
#define    LCDD4Pin   99
#define   LCDDimPin   99

#define    KeyInPin   99

//classic 4 bit LCD pins
#define lcd_4_bit_rs_pin                LCDRsPin
#define lcd_4_bit_enable_pin            LCDEnPin
#define lcd_4_bit_d4_pin                LCDD4Pin 
#define lcd_4_bit_d5_pin                LCDD5Pin
#define lcd_4_bit_d6_pin                LCDD6Pin
#define lcd_4_bit_d7_pin                LCDD7Pin


#ifdef FEATURE_JOYSTICK_CONTROL
#define pin_joystick_x 0
#define pin_joystick_y 0
#endif //FEATURE_JOYSTICK_CONTROL

#endif // ifndef ROTATOR_PINS_H_


