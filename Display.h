
#include "lcd_header.h"



// This Class contains the member functions 
// to control the display            
class Display: public Reading{

    //friend class Reading;



    public: 

        Display() {
        orientation first = West;
        set_orientation(first);
        init_lcd();
        

        TCCR1A  |= _BV(0) | _BV(1); //set Mode 3: 10 bit Fast PWM mode.
        TCCR1B |= _BV(2) | _BV(0); //set clock source to F_CPU/1024
        TIMSK1 |= _BV(0); //Enable interrupt on overflow
        sei(); // enable global interrupts 
        
        }




        void draw_axis() {
            
            uint16_t x1 = 10;
            uint16_t x2 = 15;
            uint16_t x3 = 230;

            uint16_t y1 = 310;
            uint16_t y2 = 305;
            uint16_t y3 = 190;

            uint16_t y4 = 50;
            uint16_t y5 = 170;
            uint16_t y6 = 175;

            // create the bottom rectangles to be drawn
            rectangle xrect_bottom = {x1, x3, y2, y1};
            rectangle yrect_bottom = {x1, x2, y3, y2};
            rectangle xrect_top = {x1, x3, y5, y6};
            rectangle yrect_top = {x1, x2, y4, y6};

            fill_rectangle(xrect_bottom, WHITE);
            fill_rectangle(yrect_bottom, WHITE);
            fill_rectangle(xrect_top, WHITE);
            fill_rectangle(yrect_top, WHITE);
        }


        void power_stats() {   
            //update_readings();
            float wind = (get_wind() * 240);
            float pv = (get_pv() * 240); 
            float mains = (get_busbar_current() - wind - pv) * 240;

            // for anomolies
           if(wind < 0) {
                wind = 0;
            } else if(pv < 0) {
                pv = 0;
            } else if(mains < 0) {
                mains = 0;
            }

            // create strings to fill
            char str_mains_power[120]; 
            char str_pv_power[120];
            char str_wind_power[120];
            char str_total_power[120];

            // fill the strings
            sprintf(str_mains_power, "          Mains Power:  %5.2fW                                 ", mains);
            sprintf(str_pv_power, "PV Power:  %fW                                    ", pv);
            sprintf(str_wind_power, " Wind Power:  %5.2fW                                                                                  ", wind);
            sprintf(str_total_power, "TOTAL POWER:  %5.2fW ", mains + pv + wind);

            // write the strings on the display
            display_string(str_mains_power);
            display_string(str_pv_power);
            display_string(str_wind_power);
            display_string(str_total_power);
        }




        void draw_power_consumption() {
            uint16_t max_amp = 10; // Watts 240V * 6A
            float pixel_per_amp = 120/max_amp;

            //update_readings();
            float wind = get_wind();
            float pv = get_pv(); 
            float mains = get_busbar_current() - wind - pv;

            // for anomolies
            if(wind < 0) {
                wind = 0.0001;
            } else if(pv < 0) {
                pv = 0.0001;
            } else if(mains < 0) {
                mains = 0.0001;
            }

            //heights 
            int wind_height = ceil(wind * pixel_per_amp); 
            int pv_height = ceil(pv * pixel_per_amp);
            int mains_height = ceil(mains * pixel_per_amp);
            int graph_height = 120;

            //create reference points 
            uint16_t x1 = 20;
            uint16_t y1 = 50;
            uint16_t x2 = 170; 
            uint16_t y2 = 155;

            rectangle wind_rect = {x1, x2, y2 - wind_height, y1 + graph_height};
            rectangle pv_rect = {x1, x2, y2 - wind_height - pv_height, y1 + graph_height - wind_height};
            rectangle mains_rect = {x1, x2, y2 - wind_height - pv_height - mains_height, (y2 - wind_height - pv_height)} ;                          
            rectangle the_rest = {x1, x2, y1, y2 - wind_height - pv_height - mains_height};
        

            fill_rectangle(wind_rect, BLUE); 
            fill_rectangle(pv_rect, GREEN);
            fill_rectangle(mains_rect, RED); 
            fill_rectangle(the_rest, BLACK);

        }



        
        void draw_graph_consumption(uint16_t daily_data[128]) {
            //reference point for drawing
            uint16_t xpos = 10; 
            uint16_t y = 305;

            uint16_t max_power = 6; //amps 
            float pixel_per_amp = 115/max_power;
            uint16_t daily_data_height[128] = {0}; //initialise the full day to zero consumption

            for(uint16_t i=0;i<128;i++) // the height = current * pixel_per_amp
                daily_data_height[i] = daily_data[i] * pixel_per_amp;

            //draw the graph
            uint16_t index = 0;
            for(xpos = 20; xpos < 148; xpos++) {
                if(daily_data_height[index] > 110) {
                    daily_data_height[index] = 110;
                }
                rectangle rect = {xpos, xpos+1, y - daily_data_height[index], y};
                fill_rectangle(rect, YELLOW);
                index++;
            }
            

        }

    

};



//globals for Display ISR (data for daily consumption)
// to be accessibly by the ISR has to be global
uint16_t  disp_isr_count = 0; 
uint16_t daily_consum_data[128] = {};



















