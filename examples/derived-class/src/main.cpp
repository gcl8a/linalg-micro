#include <Arduino.h>
#include <matrix_uC.h>

#include "../include/derived.h"

SampleMatrix samples;

void setup() 
{
  Serial.begin(9600);
  while(!Serial) {}
  
  SampleMatrix samplesCopy = samples;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      Serial.print(samplesCopy[i][j]);
      Serial.print(',');
    }
    Serial.println();
  }

  TMatrix<double> matrixCopy = samples;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      Serial.print(matrixCopy[i][j]);
      Serial.print(',');
    }
    Serial.println();
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
}