

class Boost : public Read
{ public:
    Boost() {
  
    
    //setup timer counter to create PWM
    TCCR0B |= _BV(CS00); // clock source F_CPU
    TCCR0A |= _BV(WGM01) | _BV(WGM00); // Fast PWM mode with no connections MAX count = OxFF (255)
    TIMSK0 |= _BV(0); // timer/counter 0 overflow interrupt enable
    TIMSK0 |= _BV(1); // enable interrupt with compare match OCR0A
    OCR0A = 127; // 50% duty cycle

    target_duty = 0.5; //initialize target duty cyle
    momentum = 0.9; //initialize momentum 0 = high friction, 1 = no friction
    momentum_vector = 0.1; //intialize momentum_vector for first learning cycle
    old_cost = 2.5;
    sei(); //enable global interrups in SREB
 
    }


    void set_duty(float x) {
        // max duty cyle = 0.95
        if (x > 0.95) {
            OCR0A = 243;
        }
        // minimum duty cycle = 0.05
        if (x < 0.05) {
            OCR0A = 12;
        }
        OCR0A = ceil(x * 255);
    }

 


    float read_boost() {
        select_channel(7); //select channel ADC7 on pin PA7
        float read = read_ADC();
        read = read * 5.6809; // reference voltage * 5.6809 = actual boost converter output
        return read;
    }


    void optimize() {
        // momentum optimization
        float current_volt = read_boost(); // boost output
        // derivative of linear cost function
        float delta_cost = (target_volt - current_volt) - old_cost;
        // Momentum Optimization
        momentum_vector = momentum * momentum_vector - LEARNING_RATE * delta_cost;
        target_duty = target_duty + momentum_vector;
        old_cost = (target_volt - current_volt); //reset current gradient for next round.
     }



    // Needs to be continuously called!!!
    void set_mains(float x) {
        target_volt = x; // set private member
        optimize(); //initiate learning cycle
        set_duty(target_duty); //set the new duty cycle
    }
    

    private:
        float target_volt;
        float target_duty;
        float old_cost;
        float momentum_vector;
        float momentum;

};




