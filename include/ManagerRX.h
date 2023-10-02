#pragma once
#include <Gyver433.h>

#include <List.hpp>

#include "Variant.h"

class ManagerRX {
   private:
    struct StoredDate {
        uint32_t lastGet;
        uint8_t idDevice;
        MessageType messageType;
        Variant data;
    };
    struct ReceivedData {
        uint8_t idDevice_;
        MessageType messageType_;
        ValueType typeOfValue_;
        SensorDataType typeOfSensorData_;
        Value value_;
        uint16_t CRC_;
        uint16_t pass_;
        uint16_t getHash(uint16_t data, int length) {
            uint16_t hash = 0;
            int i = 0;
            while (length--) {
                hash += data + i;
                i++;
            }
            return hash;
        }
        uint16_t calcCRC(ReceivedData& receivedData) {
            uint16_t CRC = 0;
            CRC += getHash(static_cast<uint16_t>(idDevice_), sizeof(idDevice_));
            CRC += getHash(static_cast<uint16_t>(messageType_), sizeof(messageType_));
            CRC += getHash(static_cast<uint16_t>(typeOfSensorData_), sizeof(typeOfSensorData_));
            CRC += getHash(static_cast<uint16_t>(typeOfValue_), sizeof(typeOfValue_));
            CRC += getHash(static_cast<uint16_t>(pass_), sizeof(pass_));
            switch (receivedData.typeOfValue_) {
                case ValueType::BOOL:
                    CRC +=
                        getHash(static_cast<uint16_t>(receivedData.value_.bool_value), sizeof(bool));
                    break;
                case ValueType::FLOAT:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.float_value),
                                   sizeof(float));
                    break;
                case ValueType::INT8_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.int8_value),
                                   sizeof(uint16_t));
                    break;
                case ValueType::INT16_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.int16_value),
                                   sizeof(uint16_t));
                    break;
                case ValueType::INT32_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.int32_value),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT8_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.uint8_value),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT16_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.uint16_value),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT32_T:
                    CRC += getHash(static_cast<uint16_t>(receivedData.value_.uint32_value),
                                   sizeof(uint16_t));
                    break;
                default:
                    static_assert("ERROR get value_ from Variant");
                    break;
            }
            return CRC;
        }
        void setVariantFromData(StoredDate* data, ReceivedData& receivedData) {
            switch (receivedData.typeOfValue_) {
                case ValueType::BOOL:
                    data->data.setValue(receivedData.value_.bool_value);
                    break;
                case ValueType::FLOAT:
                    data->data.setValue(receivedData.value_.float_value);
                    break;
                case ValueType::INT8_T:
                    data->data.setValue(receivedData.value_.int8_value);
                    break;
                case ValueType::INT16_T:
                    data->data.setValue(receivedData.value_.int16_value);
                    break;
                case ValueType::INT32_T:
                    data->data.setValue(receivedData.value_.int32_value);
                    break;
                case ValueType::UINT8_T:
                    data->data.setValue(receivedData.value_.uint8_value);
                    break;
                case ValueType::UINT16_T:
                    data->data.setValue(receivedData.value_.uint16_value);
                    break;
                case ValueType::UINT32_T:
                    data->data.setValue(receivedData.value_.uint32_value);
                    break;
                default:
                    static_assert("ERROR get value_ from Variant");
                    break;
            }
        }
    };
    List<StoredDate*> storedDate_;
    uint32_t maxTimeBetweenRetrieval_ = 3600000;
    Gyver433_RX<4, 12> rx;
    // delete
    const uint32_t refresh_send_ms = 10000;
    uint32_t send_update_ms = refresh_send_ms + 1;
    //
    uint16_t getHash(uint16_t data, int length) {
        uint16_t hash = 0;
        int i = 0;
        while (length--) {
            hash += data + i;
            i++;
        }
        return hash;
    }

   public:
    void Update();
    void setMaxTimeBetweenRetrieval(uint32_t hour);
    ~ManagerRX() = default;
};
