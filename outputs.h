class Outputs : public Boost
{ public:
    

    Outputs() {
    
    DDRC |= _BV(0)
            | _BV(1)
            | _BV(2)
            | _BV(3)
            | _BV(4)
            | _BV(5); // set PORTC 0-5 as output
  
    
   
    }



    // this function needs to be continuously called!!!
    // would be better to put in a thread time allows 
    void mains_request(float x) {
        if(x > 10) {
            x = 10;
        } else if (x < 1.5) {
            x = 1.5;
        } else {
            x = x;
        }
    
        //voltage output is 10 * mains request
        set_mains(x);
         
    }


    //set on pc0 to Charge battery status
    void charge_bat(uint8_t x) {
        if(x==1) {
            PORTC |= _BV(0);
        } else {
            PORTC &= ~_BV(0);
        }
        
    }



    //set on PC1 to discharge batter status
    void discharge_bat(uint8_t x) {
        if(x == 1) {    
            PORTC |= _BV(1);}
        else {
            PORTC &= ~_BV(1);
        }
    }

    // if val is tru set PC2 otherwise set 0
    void sw_load1(int val) {
        
        if(val == 1) {
            PORTC |= _BV(2);
        } else {
            PORTC &= ~_BV(2);
        }
    }

    // if val is tru set PC2 otherwise set 0
    void sw_load2(int val) {
        
        if(val == 1) {
            PORTC |= _BV(3);
        } else {
            PORTC &= ~_BV(3);
        }
    }

    // if val is tru set PC2 otherwise set 0
    void sw_load3(int val) {
        if(val == 1) {
            PORTC |= _BV(4);
        } else {
            PORTC &= ~_BV(4);
        }
    }
    
    void on_light() {
        PORTC |= _BV(PINC5);
    }
    };



