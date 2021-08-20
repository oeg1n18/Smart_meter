//
//  main.cpp
//  
//
//  Created by Oliver Grainge on 15/03/2021.
//
//*
//* Author: Oliver Grainge
//*
//*
//*       
//*
//*
///


#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <ctype.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>



using namespace std;

 



class Read;
class Reading;
class Boost;
class Display;
class Outputs;


#include "Read.h"
#include "Reading.h"
#include "Boost.h"
#include "Display.h"
#include "Outputs.h"

//learning rate for boost converter 
//control algorithm
#define LEARNING_RATE 0.01



  // GLOBAL OBJECTS
  Display disp;
  Outputs outs;
  Reading reads;


//=========================== ALGORITHM ==================================
 int main() {
    //turn on the LED on light
    outs.on_light();
    
   // initially draw display
    disp.power_stats();
    disp.draw_power_consumption();
    disp.draw_graph_consumption(daily_consum_data);
    disp.draw_axis();
    
   







// initialize data for algorithms first cycle
int SSavedLS1 = 0; 
int SSavedLS2 = 0;; 
int SSavedLS3 = 0; 
int SSavedCB = 0;
int SSavedDB = 0;
float SSavedBusV = 0; 
float SSavedBusI = 0;

int SavedLS1 = 0; 
int SavedLS2 = 0;; 
int SavedLS3 = 0; 
int SavedLC1 = 0; 
int SavedLC2 = 0; 
int SavedLC3 = 0;
int SavedCB = 0;
int SavedDB = 0;
float SavedBusV = 0; 
float SavedBusI = 0;
float SavedWind = 0;
float SavedPV = 0;


float DischargeTime = 0;
float ChargeTime = 0;

float SavedMains = 0;
//================================ Algorithm ================================//
while(1) {


float MainsReq;
float Maincap = 3;
//The maximum mains capacity
float BCCurrent = 1;
//The battery charging current
float BDCurrent = 1;
//The battery discharging current
float Load1Dem = 0.8;
//The current demand from load1
float Load2Dem = 1.8;
//The current demand from load2
float Load3Dem = 1.4;
//The current demand from load3
float WandPV;
//The current available from wind and pv
float CurrentDem;
//The total current demand from all of three loads
float ChargingParameter = 4.7;
//The battery charging parameter
float DischargingParameter = 7;
//The battery discharging parameter
int Dis;




//The variable to decide whether the battery can be discharged
int LoadSw1; 
int LoadSw2; 
int LoadSw3; 
int DBattery;
int CBattery;


// ============= Readings ==================
float Wind = reads.get_wind();
float PV = reads.get_pv();
int LoadCall1 = reads.get_call_l1();
int LoadCall2 = reads.get_call_l2();
int LoadCall3 = reads.get_call_l3();
float BusV = reads.get_busbar_voltage();
float BusI = reads.get_busbar_current();

WandPV = Wind + PV;

//This statement decides whether the battery is available. If Dis is 1 it means that the battery can be used.
if(ChargeTime>DischargeTime)
   Dis = 1;
else Dis = 0;


//If the busbar voltage is lower than 2
//and the difference between the total demand and the busbar current is greater than 0.4 for two continuous loop iterations,
//We think that there is a problem and set MainsReq = 10.
//This MainsReq=10 is used as an error signal since normally the mains request will not be 10.
//If the mains request is set to 10 it means that the mains power is not available and the error case statement will be executed.
//Normally when it works correctly we should not access to this part. 
//If we let MainsReq=10 when it works correctly, we will have a great waste of mains power so I set very strict condidtions for this statement.
//The only two execeptions are when all three loads are on and there is not any wind and PV available,
//and when all three loads are on, no battery available and WandPV=1.
//Since in these cases we cannot actually tell the difference between the normal MainsReq=10 and the MainsReq=10 as error signal.
//We have to make a choose between them and I decide to switch on all the loads.
if((SavedBusV<2)&&(BusV<2)&&(((SavedLS1*0.8+SavedLS2*1.8+SavedLS3*1.4+SavedCB)-BusI)>0.4)&&(((SSavedLS1*0.8+SSavedLS2*1.8+SSavedLS3*1.4+SSavedCB)-SavedBusI)>0.4))
   MainsReq = 10;


//Error-case statement for battery available.
//Here are seven load cases and I list all of them in detail.
//It will depend on the availability of wind and PV whether loads should be switched on or off.
//In this statement the MainsReq will be set to 10 again to make sure it will not jump out until there is a change in load demand or availability of renewable energy.
if((((SavedMains==10)&&Dis)||((MainsReq==10)&&Dis))&&((!(LoadCall1&&LoadCall2&&LoadCall3&&(WandPV==0)))||(!(LoadCall1&&LoadCall2&&LoadCall3&&(!Dis)&&(WandPV==1))))){
 //Only load1 is required
   if(LoadCall1&&(!LoadCall2)&&(!LoadCall3)){
      LoadSw1 = 1;
      if(WandPV<0.8){
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<0.8))&&(WandPV<1.8)){
         DBattery = 0;
         CBattery = 0;}
      if(!(WandPV<1.8)){
         DBattery = 0;
         CBattery = 1;}}
//Only load2 is required
   if(LoadCall2&&(!LoadCall1)&&(!LoadCall3)){
      LoadSw2 = 1;
      if(WandPV<0.8){
         DBattery = 0;
         CBattery = 0;}
      if((!(WandPV<0.8))&&(WandPV<1.8)){
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<1.8))&&(WandPV<2.8)){
         DBattery = 0;
         CBattery = 0;}
      if(!(WandPV<2.8)){
         DBattery = 0;
         CBattery = 1;}}
//Only load3 is required
   if(LoadCall3&&(!LoadCall1)&&(!LoadCall2)){
      LoadSw3 = 1;
      if(WandPV<0.4){
         DBattery = 0;
         CBattery = 0;}
      if((!(WandPV<0.4))&&(WandPV<1.4)){
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<1.4))&&(WandPV<2.4)){
         DBattery = 0;
         CBattery = 0;}
      if(!(WandPV<2.4)){
         DBattery = 0;
         CBattery = 1;}}
//Both load1 and load2 are required
   if(LoadCall1&&LoadCall2&&(!LoadCall3)){
      if(WandPV<0.8){
         LoadSw1 = 1;
         LoadSw2 = 0;
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<0.8))&&(WandPV<0.9)){
         LoadSw1 = 1;
         LoadSw2 = 0;
         DBattery = 0;
         CBattery = 0;}
      if((!(WandPV<0.9))&&(WandPV<2.6)){
         LoadSw1 = 1;
         LoadSw2 = 1;
         DBattery = 1;
         CBattery = 0;}
      if(!(WandPV<2.6)){
         LoadSw1 = 1;
         LoadSw2 = 1;
         DBattery = 0;
         CBattery = 0;}}
//Both load1 and load3 are required
   if(LoadCall1&&LoadCall3&&(!LoadCall2)){
      if(WandPV<0.8){
         LoadSw1 = 1;
         LoadSw3 = 0;
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<0.8))&&(WandPV<1.2)){
         LoadSw1 = 1;
         LoadSw3 = 0;
         DBattery = 0;
         CBattery = 0;}
      if((!(WandPV<1.2))&&(WandPV<2.2)){
         LoadSw1 = 1;
         LoadSw3 = 1;
         DBattery = 1;
         CBattery = 0;}
      if(!(WandPV<2.2)){
         LoadSw1 = 1;
         LoadSw3 = 1;
         DBattery = 0;
         CBattery = 0;}}
//Both load2 and load3 are required
   if(LoadCall2&&LoadCall3&&(!LoadCall1)){
      if(WandPV<1.8){
         LoadSw2 = 1;
         LoadSw3 = 0;
         DBattery = 1;
         CBattery = 0;}
      if(!(WandPV<1.8)){
         LoadSw2 = 1;
         LoadSw3 = 1;
         DBattery = 1;
         CBattery = 0;}}
//All three loads are required
   if(LoadCall1&&LoadCall2&&LoadCall3){
      if((WandPV>0)&&(WandPV<0.8)){
         LoadSw1 = 1;
         LoadSw2 = 0;
         LoadSw3 = 0;
         DBattery = 1;
         CBattery = 0;}
      if((!(WandPV<0.8))&&(WandPV<0.9)){
         LoadSw1 = 1;
         LoadSw2 = 0;
         LoadSw3 = 0;
         DBattery = 0;
         CBattery = 0;}
      if((!(WandPV<0.9))&&(WandPV<2.7)){
         LoadSw1 = 1;
         LoadSw2 = 1;
         LoadSw3 = 0;
         DBattery = 1;
         CBattery = 0;}
      if(!(WandPV<2.7)){
         LoadSw1 = 1;
         LoadSw2 = 1;
         LoadSw3 = 1;
         DBattery = 1;
         CBattery = 0;}}
   MainsReq = 10;
}


//Error-case statement for battery unavailable.
//In this statement the MainsReq will be set to 10 again to make sure it will not jump out until there is a change in load demand or availability of renewable energy.
if((((SavedMains==10)&&(!Dis))||((MainsReq==10)&&(!Dis)))&&((!(LoadCall1&&LoadCall2&&LoadCall3&&(WandPV==0)))||(!(LoadCall1&&LoadCall2&&LoadCall3&&(!Dis)&&(WandPV==1))))){
    if(!(WandPV<0.8)){
      if(LoadCall1)
         LoadSw1 = 1;
      else LoadSw1 = 0;
    }

    if(!(WandPV<1.8)){
      if(LoadCall2&&(!(LoadCall1)))
         LoadSw2 = 1;
    } else LoadSw2 = 0;

   if(!(WandPV<2.6)){
      if(LoadCall1)
         LoadSw1 = 1;
      else LoadSw1 = 0;

      if(LoadCall2)
         LoadSw2 = 1;
      else LoadSw2 = 0;
   } 
   LoadSw3 = 0;
   MainsReq = 10;
}


//When one of the load demand or the values of renewable energy is changed, the mains request will be set to 0 and the algorithm will break out of the error case statement.
if((LoadCall1!=SavedLC1)||(LoadCall2!=SavedLC2)||(LoadCall3!=SavedLC3)||(Wind!=SavedWind)||(PV!=SavedPV))
   MainsReq = 0;


//When the mains request is not 10 the code below will be executed since normally the MainsReq=10 is considered as an error signal.
if((MainsReq!=10)||(LoadCall1&&LoadCall2&&LoadCall3&&(WandPV==0))||(LoadCall1&&LoadCall2&&LoadCall3&&(!Dis)&&(WandPV==1))){

//The MainsReq calculation statement. 
//It calculates the initial mains request based on the availability of renewable energy and the demands from loads.
//Sometimes the MainsReq can be lower than 0. We should avoid this.
   if(LoadCall1)
      LoadSw1 = 1;
   else LoadSw1 = 0;

   if(LoadCall2)
      LoadSw2 = 1;
   else LoadSw2 = 0;

   if(LoadCall3)
      LoadSw3 = 1;
   else LoadSw3 = 0;

   CurrentDem = LoadSw1*Load1Dem+LoadSw2*Load2Dem+LoadSw3*Load3Dem;

   MainsReq = 10*(CurrentDem-WandPV)/Maincap;
   if(MainsReq<0)
      MainsReq = 0;


//The battery charging statement. 
//The battery will be charged when the MainsReq is lower than the battery charging parameter.
//If the battery charging parameter is 5, the battery will be charged when the use of mains current is lower than 50% (including the battery charging current).
   if(!(WandPV<(CurrentDem-3*((ChargingParameter-(10/3))/10)))){
      DBattery = 0;
      CBattery = 1;
      MainsReq = 10*(CurrentDem - WandPV - DBattery*BDCurrent + CBattery*BCCurrent)/Maincap ;
      if(MainsReq<0)
         MainsReq = 0;
   }else CBattery = 0;


//The battery discharging statement. 
//The battery will discharge when the MainsReq is greater than the battery discharging parameter.
   if(MainsReq>DischargingParameter){
      DBattery = 1;      
      MainsReq = 10*(CurrentDem - WandPV - DBattery*BDCurrent + CBattery*BCCurrent)/Maincap ;
   }else DBattery = 0;


//This statement will be executed when there is no charge available but we still make DBattery=1 in the above statement.
//In this case, the battery will not be allowed to discharge.
//If the calculated MainsReq without battery available is not smaller than 10, we have to turn off the load3 which has the lowest priority until the battery is charged again.
//One exception is when all three loads are needed and WandPV=1.
//In this case we will let MainsReq=10 to provide to all three loads.
if(!Dis){
   if(DBattery){
      DBattery = 0;

      float DMainsReq = 10*(CurrentDem-WandPV)/Maincap;
   
      if(DMainsReq<10)
         MainsReq = DMainsReq;

      if(!(DMainsReq<10)){
         LoadSw3 = 0;
         CurrentDem = LoadSw1*Load1Dem+LoadSw2*Load2Dem+LoadSw3*Load3Dem;
         MainsReq = 10*(CurrentDem-WandPV-DBattery*BDCurrent+CBattery*BCCurrent)/Maincap;
      }
   }
   if(LoadCall1&&LoadCall2&&LoadCall3&&(WandPV==1)){
      LoadSw3 = 1;
      MainsReq = 10;
   }
}






//================================ Output the determined parameters =======================

}

// set the outputs
outs.mains_request(MainsReq);
outs.sw_load1(LoadSw1);
outs.sw_load2(LoadSw2);
outs.sw_load3(LoadSw3);
outs.charge_bat(CBattery);
outs.discharge_bat(DBattery);

//save data for new algorithm cycles
SavedLS1 = LoadSw1; 
SavedLS2 = LoadSw2; 
SavedLS3 = LoadSw3; 
SavedLC1 = LoadCall1; 
SavedLC2 = LoadCall2; 
SavedLC3 = LoadCall3;
SavedCB = CBattery;
SavedDB = DBattery;
SavedBusV = BusV; 
SavedBusI = BusI;
SavedWind = Wind;
SavedPV = PV;
SavedMains = MainsReq;

SSavedLS1 = SavedLS1; 
SSavedLS2 = SavedLS2; 
SSavedLS3 = SavedLS3; 
SSavedCB = SavedCB;
SSavedDB = SavedDB;
SSavedBusV = SavedBusV; 
SSavedBusI = SavedBusI;
SavedWind = SavedWind;
SavedPV = SavedPV;





}
    return 0;
   
}













  //================ PWM signal for boost converter =================================
//overflow ISR
ISR(TIMER0_OVF_vect) {
  PORTA |= _BV(6); //turn pin on 


}

//compare match ISR
ISR(TIMER0_COMPA_vect) {
    PORTA &= ~_BV(6); //turn pin of.
}



// ============================ Display ISR ===================================== //
// ---------------------------- ISR FREQ = 11.44Hz -------------------------------//

ISR(TIMER1_OVF_vect) {

      // Increment timer
      disp_isr_count++;
      disp.draw_power_consumption();
      disp.draw_axis();
      
      // Executes every 7.5 seconds. Updating displayed text
      if(disp_isr_count % 86 == 0) {
        uint16_t power_consump =  reads.get_busbar_current();
        daily_consum_data[disp_isr_count/86] = power_consump; // update consumption data for this time
        clear_screen();
        disp.power_stats();
        disp.draw_axis();
        disp.draw_power_consumption();
        disp.draw_graph_consumption(daily_consum_data);
      }


      

      // reset data at end of day 
      if(disp_isr_count == 16464) {
          disp_isr_count=0;
          for(uint16_t i = 0; i < 128; i++) {
              daily_consum_data[i] = 0;}
          clear_screen();
          disp.power_stats();
          disp.draw_axis();
          disp.draw_power_consumption();
          disp.draw_graph_consumption(daily_consum_data);
          
          } 


} 
