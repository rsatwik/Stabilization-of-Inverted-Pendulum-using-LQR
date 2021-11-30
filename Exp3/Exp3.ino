#define sel1 38
#define sel2 39
#define rst_ 40
#define clk 12
#define m1 9
#define m2 8
#define pi 3.14159
int alpha,theta;
byte alpha1, alpha2;
byte theta1, theta2;
float alpha_n1,theta_n1,dalpha,dtheta;
float prev_theta =0;
float prev_alpha =0;
float u1 =0;
float u =0;
unsigned long time_now,prev_time;
void setup()
 {
  pinMode(sel1, OUTPUT);
  pinMode(sel2, OUTPUT);
  pinMode(rst_, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  TCCR1B=0x01;
  analogWrite(clk, 127);

  digitalWrite(rst_, LOW);
  delay(1000);
  digitalWrite(rst_, HIGH);

 alpha = 0;
 DDRC=0b00000000;

  Serial.begin(9600);
time_now =millis();
}

void loop()
 {
    float  k1=-6.3246;float k2=78.9678;float k3=-3.1025;float k4=10.4448;

    prev_time = time_now;  
    Serial.print(time_now);Serial.print('\t');
//      Serial.print(prev_theta);Serial.print('\t');
//      Serial.print(prev_alpha);Serial.print('\t');
//  while(1){
    digitalWrite(sel1, HIGH);
  digitalWrite(sel2, LOW);
  alpha1=PINC;
    digitalWrite(sel1, LOW);
  digitalWrite(sel2, LOW);
  alpha2=PINC;
  alpha=word(alpha2, alpha1);
  
  alpha_n1 = alpha*(pi/1000);
 
  Serial.print(180*(alpha_n1/pi));Serial.print('\t');
  
  digitalWrite(sel1, HIGH);
  digitalWrite(sel2, LOW);
  theta1=PINA;
  digitalWrite(sel1, LOW);
  digitalWrite(sel2, LOW);
  theta2=PINA;
  theta=word(theta2, theta1);
  
  theta_n1 = theta*(pi/1000); 
  
  Serial.println(180*(theta_n1/pi));
//  Serial.print('\t');
  time_now = millis();

dtheta = ((theta_n1-prev_theta)*1000)/(time_now-prev_time);
dalpha = ((alpha_n1-prev_alpha)*1000)/(time_now-prev_time);
//dtheta = theta_n1-prev_theta;
//dalpha = alpha_n1-prev_alpha;
  
  u = (k1*theta_n1)+(k2*alpha_n1)+(k3*dtheta)+(k4*dalpha);
  u1=255*u/12;
  if(u1>256){
    u1 =255;
  }
  else if (u1<-256){
    u1 =-255;
  }

   
   if (u1<0){
    analogWrite(m2,-u1);
    analogWrite(m1,0);
   }
   else{
    analogWrite(m1,u1);
    analogWrite(m2,0);
   }
    prev_theta = theta_n1; 
      prev_alpha = alpha_n1;
//      Serial.print(u);Serial.print('\t');
//      Serial.println(u1);
  }
    
//}
