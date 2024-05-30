// ALIGNMENT PSEUDOCODE
// * THE ALIGNERS START AWAY *
// 1. bring the aligners flat
// 2. wait a little bit 
// 3. pull the aligners away so that the platform can move again
void flat()
{
  servoL.write (servoL_flat);
  servoR.write (servoR_flat);
}

void away()
{ servoL.write(servoL_away);
  servoR.write(servoR_away);
}

void align() 
{ flat();
  delay(1000);
  away();

}