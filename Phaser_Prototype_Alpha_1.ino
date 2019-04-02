int BUTTON = 3;
int RLED = 7;
int INFR = 13;
bool INFRON = false;
bool RLEDON = false;
int HEAT = 0;
int HTSK = 10000;
int CLDNTRG = 500; //Rate of cooldown
long DSBDCNTD = 0; // disabled countdown
long CLDN = 0;
bool FIRED = false;
bool DISABLED = false;

  void setup(){
    pinMode(BUTTON,INPUT); // Read for button, write for others
    pinMode(RLED,OUTPUT);
    pinMode(INFR,OUTPUT);
    Serial.begin(9600);
  }
  
  void loop(){
    Serial.println(HEAT);
    //IF HEAT IS AT 100 THEN DISABLE GUN
    if(HEAT == 100 || DISABLED){
      DISABLED = true;
  
      //IF THE RED LED IS OFF THEN TURN ON
      if(!RLEDON){
        digitalWrite(RLED,HIGH);
        RLEDON = true;
      }
  
      //IF THE DISABLED COUNT DOWN IS NOT SET THEN SAVE CURRENT TIME
      if(DSBDCNTD == 0){
        DSBDCNTD = millis();
      }else{
  
        //IF CURRENT TIME MINUS THE TIME THE GUN WAS DISABLED IS GREATER THAN OR EQUAL TO COOL DOWN TIME THEN RESET GUN
        if(  millis() - DSBDCNTD >= HTSK ){
          HEAT = 0;
          DISABLED = false;
          DSBDCNTD = 0;
          if(RLEDON){
            digitalWrite(RLED,LOW);
            RLEDON = false;
          }
        }
      }
    }
    if(digitalRead(BUTTON) == HIGH && !DISABLED){
      FIRED = true;
  
      /* TURNS ON INFR WHITE LIGHT */
      if(!INFRON){
        INFRON = true;
        digitalWrite(INFR,HIGH);
      }
      
    }else{
      if(FIRED){
        HEAT = HEAT + 10;
        CLDN = millis();
      }
      FIRED = false;
  
      /* TURNS OFF INFR WHITE LIGHT */
      if(INFRON){
        INFRON = false;
        digitalWrite(INFR,LOW);
      }
    }

    //LOWER HEAT EVERY TICK
    if(CLDN == 0){
      CLDN = millis();
    }else{
      if(  millis() - CLDN >= CLDNTRG ){
        CLDN = 0;
        if(HEAT > 0){
          HEAT = HEAT - 10;
        }else{
          HEAT = 0;
        }
      } 
     } 
        if(HEAT >= 40 && HEAT <= 60){
           CLDNTRG = 1500;
        }     
        else if(HEAT > 60){
           CLDNTRG = 2200;
        }else{
          CLDNTRG = 750;   
        }
      } 
