void move_disc (int n) // n is how many discs you want to move up or down by
{
  if (n > 0) // positive n makes platform  move up, negative n makes the platform move down
  {
    digitalWrite (dirPin, LOW); // this makes the motor move up
  }
  else 
    {
    digitalWrite (dirPin, HIGH); // this makes the motor move down
    }
  for(int x = 0; x < abs(n) * disc_steps ; x++) 
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(20000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(20000); 
  }

}