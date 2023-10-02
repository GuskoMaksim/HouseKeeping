#include "ManagerRX.h"

void ManagerRX::Update() {
    if (rx.tick()) {
        ReceivedData data;
        if (rx.readData(data)) {
            bool find = false;
            if (data.calcCRC(data) != data.CRC_) {
                Serial.print("Error");
            } else {
                StoredDate* sdNew = nullptr;
                for (int i = 0; i < storedDate_.getSize(); ++i) {
                    sdNew = storedDate_.getValue(i);
                    if (sdNew->idDevice == data.idDevice_ &&
                        sdNew->messageType == data.messageType_ &&
                        sdNew->data.typeOfSensorData == data.typeOfSensorData_) {
                        find = true;
                        break;
                    }
                }
                if (!find) {
                    sdNew = new StoredDate();
                    sdNew->idDevice = data.idDevice_;
                    sdNew->messageType = data.messageType_;
                    sdNew->data.setSensorDataType(data.typeOfSensorData_);
                    sdNew->data.setValueType(data.typeOfValue_);
                    sdNew->lastGet = millis();
                    storedDate_.add(sdNew);
                }
                ////////////////////////////////////////DELETE
                data.setVariantFromData(sdNew, data);
                Serial.print("data.pass: ");
                Serial.println(data.pass_);
                Serial.print("CRC: ");
                Serial.println(data.calcCRC(data));
                Serial.print("data.CRC: ");
                Serial.println(data.CRC_);
                Serial.print("sdNew.idDevice: ");
                Serial.println(sdNew->idDevice);
                Serial.print("sdNew->messageType: ");
                Serial.println((uint8_t)sdNew->messageType);
                Serial.print("sdNew->v.typeOfValue: ");
                Serial.println((uint8_t)sdNew->data.typeOfValue);
                Serial.print("sdNew->data.typeOfSensorData: ");
                Serial.println((uint8_t)sdNew->data.typeOfSensorData);
                Serial.print("sdNew->v.getValue: ");
                Serial.println(sdNew->data.getValue<float>());
                Serial.print("sdNew->lastGet: ");
                Serial.println(sdNew->lastGet);
                Serial.println("-------------------------------");
                Serial.println();
                ////////////////////////////////////////////
            }
        } else
            Serial.println("Data error");
    }
    // delete
    if (millis() - send_update_ms > refresh_send_ms) {
        send_update_ms = millis();
        Serial.print("Size: ");
        Serial.println(storedDate_.getSize());
        Serial.println("-----------------------");
        Serial.println();
    }
    //
};

void ManagerRX::setMaxTimeBetweenRetrieval(uint32_t mins) {
    maxTimeBetweenRetrieval_ = uint32_t(mins);
};
