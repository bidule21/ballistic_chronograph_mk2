void disableInterrupts(){
  editInterrupts(0);
}

void enableInterrupts(){
  editInterrupts(1);
}

void enableSerial(){
  editInterrupts(2);
}

void editInterrupts(byte _s){
  //0 = All interrupts OFF
  //1 = All interrupts ON
  //2 = Turn on Serial
  static byte _tccr0b;
  static byte _tccr2b;
  static byte _spcr;
  static byte _ucsr0b;
  static byte _adcsra;
  static byte _adcsrb;
  static byte _acsr;
  static byte _eimsk;
  static byte _intState = 1;
  if (!_s){
    if (_intState){
      _intState = 0;
      _tccr0b = TCCR0B;
      _tccr2b = TCCR2B;
      _spcr = SPCR;
      _adcsra = ADCSRA;
      _adcsrb = ADCSRB;
      _acsr = ACSR;
      _eimsk = EIMSK;
      TCCR0B = 0;
      TCCR2B = 0;
      SPCR = 0;
      ADCSRA = 0;
      ADCSRB = 0;
      ACSR = 0b10000000;
      EIMSK = 0b00000000;
    }
    if (UCSR0B){
      _ucsr0b = UCSR0B;
      UCSR0B = 0; //Need to reset this for the interrupt serial
    }
  }
  else if (_s == 1 && !_intState) {
    _intState = 1;
    TCCR0B = _tccr0b;
    TCCR2B = _tccr2b;
    SPCR = _spcr;
    UCSR0B = _ucsr0b;
    ADCSRA = _adcsra;
    ADCSRB = _adcsrb;
    ACSR = _acsr;
    EIMSK = _eimsk;
  }
  else if (_s == 2 && !_intState){
    if (!_intState) UCSR0B = _ucsr0b;
  }
}
