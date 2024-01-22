#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer {
public:
  Potentiometer(int pin);
  /* restituisce il valore del potenziometro,
    ovvero quanto è stato aperto il rubinetto
    usato perl'apertura manuale delle valvole*/
  int getShaftValue();
  int getShaftValue();
private:
  int pin;
  int last;
};


#endif