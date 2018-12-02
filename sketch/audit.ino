void manageAudit(){
  
  // chose speed using audit phase
  if (auditPhase == 1){
    int sensorState = lineFinder.readSensors();
    if (sensorState != previousSensorState) {
      switch(sensorState) {
        case S1_IN_S2_IN:
          motor1Target = EIGHTY_MMS_LIMIT;
          motor2Target = -EIGHTY_MMS_LIMIT;
          break;
        case S1_IN_S2_OUT:
          motor1Target = EIGHTY_MMS_LIMIT;
          motor2Target = FIFTEEN_MMS_LIMIT;
          break;
        case S1_OUT_S2_IN:
          motor1Target = -FIFTEEN_MMS_LIMIT;
          motor2Target = -EIGHTY_MMS_LIMIT;
          break;
        case S1_OUT_S2_OUT:
          motor1Target = -EIGHTY_MMS_LIMIT/3;
          motor2Target = EIGHTY_MMS_LIMIT/3;
          break;
        default:
          break;
      }
      
      previousSensorState = sensorState;
    }
    led.setColor(255, 0, 0);
    led.show();
    float redValue = lightSensor.read();

    led.setColor(0, 255, 255);
    led.show();
    float cyanValue = lightSensor.read();

    updateQueue(redDetection, redSum, redValue / cyanValue);
    bool redDetected = (redDetection.size() == bufferSize) && (getValue(redDetection, redSum) < redThreshold);

    if(redDetected){
      auditPhase = 2;
      motor1.run(FIFTEEN_MMS_LIMIT);
      motor2.run(-FIFTEEN_MMS_LIMIT);
      waitedTime = millis() + 3500;
      restartMotorsAfterDelay = true;
      led.setColor(0, 0, 0);
      led.show();
    }
  } else if(auditPhase = 2){
    int sensorState = lineFinder.readSensors();
    if (sensorState != previousSensorState) {
      switch(sensorState) {
        case S1_IN_S2_IN:
          motor1Target = FIFTEEN_MMS_LIMIT;
          motor2Target = -FIFTEEN_MMS_LIMIT;
          break;
        case S1_IN_S2_OUT:
          motor1Target = FIFTEEN_MMS_LIMIT;
          motor2Target = 0;
          break;
        case S1_OUT_S2_IN:
          motor1Target = 0;
          motor2Target = -FIFTEEN_MMS_LIMIT;
          break;
        case S1_OUT_S2_OUT:
          motor1Target = -FIFTEEN_MMS_LIMIT;
          motor2Target = FIFTEEN_MMS_LIMIT;
          break;
        default:
          break;
      }
      
      previousSensorState = sensorState;
    }
  }

  // disable audit if "autopilot" button is pressed.
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    String text = String("Data recieved (" + String(data.size()) + ") : ");
    for (int i = 0 ; i < data.size() ; i++){
      if (data[i].substring(0,2) == String("A")){
        audit = false;
        motor1.stop();
        motor2.stop();
        autoPilotStop();
      }
    }
  }
}
