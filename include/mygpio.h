/*
Copyright (c) 2016 Kazuki Yamamoto <k.yamamoto.08136891@gmail.com>
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/** mygpio.h
*/

#ifndef _MY_GPIO_H_  // NOLINT
#define _MY_GPIO_H_
#include "pin_names.h"  //NOLINT

class DigitalIn {
 public:
  DigitalIn(PinName pin);
  DigitalIn(PinName pin, PinMode mode);
  ~DigitalIn();

  int read();
  operator int() { return read(); }
  void mode(PinMode pull);

 private:
  GPIO_PORT _port;
  GPIO_PIN _pin;
  GPIO_PUPD _mode;
};

class DigitalOut {
 public:
  DigitalOut(PinName pin);
  DigitalOut(PinName pin, int state);
  ~DigitalOut();
  void write(int value);
  int read();
  //  int is_connected ();
  DigitalOut& operator=(int value) {
    write(value);
    return *this;
  }
  operator int() { return read(); }

 private:
  GPIO_PORT _port;
  GPIO_PIN _pin;
};

/** A digital input/output, used for setting or reading a bi-directional pin
 */
class DigitalInOut {
 public:
  /** Create a DigitalInOut connected to the specified pin
   *
   *  @param pin DigitalInOut pin to connect to
   */
  DigitalInOut(PinName pin);

  /** Create a DigitalInOut connected to the specified pin
   *
   *  @param pin DigitalInOut pin to connect to
   *  @param direction the initial direction of the pin
   *  @param mode the initial mode of the pin
   *  @param value the initial value of the pin if is an output
   */
  DigitalInOut(PinName pin, PinDirection direction, PinMode mode, int value);
  /** Set the output, specified as 0 or 1 (int)
   *
   *  @param value An integer specifying the pin output value,
   *      0 for logical 0, 1 (or any other non-zero value) for logical 1
   */
  void write(int value);

  /** Return the output setting, represented as 0 or 1 (int)
   *
   *  @returns
   *    an integer representing the output setting of the pin if it is an
   * output,
   *    or read the input if set as an input
   */
  int read();

  /** Set as an output
   */
  void output();

  /** Set as an input
   */
  void input();

  /** Set the input pin mode
   *
   *  @param mode PullUp, PullDown, PullNone, OpenDrain
   */
  void mode(PinMode pull);

  /** Return the output setting, represented as 0 or 1 (int)
   *
   *  @returns
   *    Non zero value if pin is connected to uc GPIO
   *    0 if gpio object was initialized with NC
   */
  // int is_connected();

  /** A shorthand for write()
   */
  DigitalInOut& operator=(int value) {
    write(value);
    return *this;
  }

  DigitalInOut& operator=(DigitalInOut& rhs) {
    write(rhs.read());
    return *this;
  }

  /** A shorthand for read()
   */
  operator int() { return read(); }

  // protected:
  //     gpio_t gpio;
 private:
  GPIO_PORT _port;
  GPIO_PIN _pin;
  GPIO_PUPD _mode;
  GPIO_PUPD _direction;
};

#endif  //_MY_GPIO_H_
