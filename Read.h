







/********************** BASE CLASS *******************************/
/****************************************************************/

class Read
{   public:

    Read() {
    ADMUX &= ~_BV(MUX0) & ~_BV(MUX1) & ~_BV(MUX2) & ~_BV(MUX3) & ~_BV(MUX4); // initially set channel 0
    ADMUX |= _BV(MUX2);// select the voltage reference
    ADMUX = ADMUX | 0x20;        // set for Left Justified
        
    ADCSRA &=  ~_BV(ADPS2) & ~_BV(ADPS1);
    ADCSRA |= _BV(ADPS0);// select the ADC clock frequency 2 division
    ADCSRA = ADCSRA | 0x80;        // enable the ADC
    }

 


    void select_channel(uint16_t channel) {
        if(channel == 0) {
            ADMUX &= ~_BV(MUX0) & ~_BV(MUX1) & ~_BV(MUX2) & ~_BV(MUX3) & ~_BV(MUX4);
        }
        if(channel == 1) {
            ADMUX &= ~_BV(MUX0) & ~_BV(MUX1) & ~_BV(MUX2) & ~_BV(MUX3);
            ADMUX |= _BV(MUX0);
        }
        if(channel == 2) {
            ADMUX &= ~_BV(MUX0)  & ~_BV(MUX2) & ~_BV(MUX3) & ~_BV(MUX4);
            ADMUX |= _BV(MUX1);
        }
        if (channel == 3) {
            ADMUX &= ~_BV(MUX2) & ~_BV(MUX3) & ~_BV(MUX4);
            ADMUX |= _BV(MUX0) | _BV(MUX1);
        }
        if (channel == 4) {
            ADMUX &= ~_BV(MUX0) & ~_BV(MUX1) & ~_BV(MUX3) & ~_BV(MUX4);
            ADMUX |= _BV(MUX2);
        }
        if (channel == 5) {
            ADMUX &= ~_BV(MUX1) & ~_BV(MUX3) & ~_BV(MUX4);
            ADMUX |= _BV(MUX2) | _BV(MUX0);
        }
        if (channel ==6) {
            ADMUX &= ~_BV(MUX0) & ~_BV(MUX3) & ~_BV(MUX4);
            ADMUX |= _BV(MUX2) | _BV(MUX1);
        }
        if (channel == 7) {
            ADMUX &= ~_BV(MUX4) & ~_BV(MUX3);
            ADMUX |= _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
        }
    }



float read_ADC()
    {
    unsigned char value;
    ADCSRA = ADCSRA | 0x40;            // start a conversion
    while( (ADCSRA & 0x10) == 0 );        // wait for conversion to be completed
    value = ADCH;                // get the upper 8-bits
    ADCSRA = ADCSRA | 0x10;// clear the flag
    int q = (int)(value);
    float f = (float)q * (3.3/255);
    return f;
    }



float get_peak() {
    float max_read = 0;
    float read;
    //577 is the number of conversions per 2pi period of the
    // input signal calculated using the clock prescaler
    // ADC cycles per conversions and the 50Hz input
    for(int i = 1; i<577; i++) {
        //  _delay_ms(1);
        read = read_ADC();
        if(max_read<read) {
            max_read = read;
        }
    }
    return max_read;
}


    
    float get_ground() {
        select_channel(5);
        float read = read_ADC();
        return read;
    }

};