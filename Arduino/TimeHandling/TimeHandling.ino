#include <Time.h>


/*******************************************************/
/*                                                     */
/*  TimeHandling - A Sketch to demonstrate the         */
/*  handling of Time needed in the Collecting Node     */
/*                                                     */
/*  Using Time Library by Michael Margolis             */
/*                                                     */
/*******************************************************/

// Time at which the Sketch starts
time_t startTime;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);

  // since there is no way to synchronize the time (in this Sketch),
  // The startTime gets set to some arbitrary Value.
  setTime(12, 0, 0, 24, 12, 1989);
  startTime = now();
}

void loop() {
  
  time_t time = now();  // Get the current Time
  
  // And Display it in seconds since the 1th january of 1970
  Serial.print("Current Time in Seconds (since 1970): ");
  Serial.println(time);
  
  // Now show all values of the current Time
  Serial.print("Hour: ");
  Serial.println(hour());
  Serial.print("Minute: ");
  Serial.println(minute());
  Serial.print("Second: ");
  Serial.println(second());
  Serial.print("Day: ");
  Serial.println(day());
  Serial.print("Month: ");
  Serial.println(month());
  Serial.print("Year: ");
  Serial.println(year());
  Serial.print("Week Day: ");
  Serial.println(weekday());
  
  // calculate difference time since startTime
  time_t diffTime = time - startTime;
  
  if(diffTime%60 == 0)  // If difference equals a just passing Minute
  {
    // Make a message about it
    Serial.print("A Minute Has passed. Minute No.: ");
    Serial.println(minute(diffTime));
  }
  
   // Wait 10 seconds before next looping
   delay(10000); 
}
