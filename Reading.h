
class Reading : public Read {
    public: 
        Reading () {
        select_channel(0);
           
    DDRC &= ~_BV(PINC6) & ~_BV(PINC7);
    //leave floating grounds should be connected
    // load calls are active high 
        }

        
    // checks for a load call on channel 0
        int  get_call_l1(void) {
            float ret;
            select_channel(0);
            float read = read_ADC();
            if(read > 2.5) {
                    ret = 1;
                } else {
                    ret = 0;
                }
            return ret;
        }

        int get_call_l2(void) {
            if(PINC & _BV(PINC6)) {
                return 1;
            } else {return 0;}
        }

        int get_call_l3(void) {
            if(PINC & _BV(PINC7)) {
                return 1;
            } else {return 0;}
        }

    
    float get_pv(void) {
        float gnd = get_ground();
        select_channel(4);
        float read = read_ADC();
        read = read * (5/3.3);
        return read - gnd;//relative to analogue ground
    }
    
    float get_wind(void) {
        float gnd = get_ground();
        select_channel(3);
        float read = read_ADC();
        read = read * (5/3.3);
        return read - gnd; //relative to analogue ground
    }
    
    
    
    float get_busbar_voltage(void) {
        float gnd = get_ground();
        select_channel(1);
        float peak = get_peak();
        peak = peak + 0.7; //add the Vth of diode To get actual peak
        float rms = peak/0.7071; //get rms value from peak
        return 100 * (rms - gnd); // relative to analogue ground
    }
    
    float get_busbar_current(void) {
        float gnd = get_ground();
        select_channel(2);
        float peak = get_peak();
        peak = (peak * 2.943) + 0.7; // calculate input from output using the schematic voltage divider
        float rms = peak/0.7071;// get rms value from peak
        return rms - gnd; //relative to analogue ground
    }
};
    

    