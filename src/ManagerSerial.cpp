#include "ManagerSerial.h"

ManagerSerial::ManagerSerial() {
    Serial.begin(9600);
    Serial.println("Start");
}

void ManagerSerial::SendDebugDataToSerialPort() {
    if (timer_) {
        Serial.print(timer_->Get_data_time_().date_);
        Serial.print(".");
        Serial.print(timer_->Get_data_time_().month_);
        Serial.print(".");
        Serial.print(timer_->Get_data_time_().year_);
        Serial.println("");
        Serial.print(timer_->Get_data_time_().hour_);
        Serial.print(":");
        Serial.print(timer_->Get_data_time_().minute_);
        Serial.print(":");
        Serial.print(timer_->Get_data_time_().second_);
        Serial.println("");
    }
    if (data_) {
        for (int i = 0; i < data_->GetDataFromSensors().getSize(); ++i) {
            Serial.print(
                static_cast<uint8_t>(data_->GetDataFromSensors().getValue(i).typeOfSensorData));
            Serial.print(" - ");
            Serial.print(data_->GetDataFromSensors().getValue(i).getValue<float>());
            Serial.println("   ");
        }
    }
    Serial.println("");
}

void ManagerSerial::Update(bool debug) {
    if (debug) {
        SendDebugDataToSerialPort();
    }
};
