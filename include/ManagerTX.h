#pragma once
#include <Gyver433.h>

#include "ManagerSensor.h"
#include "Variant.h"

class ManagerTX {
   private:
    struct SendingData {
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
        uint16_t calcCRC(Variant& variantData) {
            uint16_t CRC = 0;
            CRC += getHash(static_cast<uint16_t>(idDevice_), sizeof(idDevice_));
            CRC += getHash(static_cast<uint16_t>(messageType_), sizeof(messageType_));
            CRC += getHash(static_cast<uint16_t>(typeOfSensorData_), sizeof(typeOfSensorData_));
            CRC += getHash(static_cast<uint16_t>(typeOfValue_), sizeof(typeOfValue_));
            CRC += getHash(static_cast<uint16_t>(pass_), sizeof(pass_));
            switch (variantData.typeOfValue) {
                case ValueType::BOOL:
                    CRC +=
                        getHash(static_cast<uint16_t>(variantData.getValue<bool>()), sizeof(bool));
                    break;
                case ValueType::FLOAT:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<float>()),
                                   sizeof(float));
                    break;
                case ValueType::INT8_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<int8_t>()),
                                   sizeof(uint16_t));
                    break;
                case ValueType::INT16_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<int16_t>()),
                                   sizeof(uint16_t));
                    break;
                case ValueType::INT32_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<int32_t>()),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT8_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<uint8_t>()),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT16_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<uint16_t>()),
                                   sizeof(uint16_t));
                    break;
                case ValueType::UINT32_T:
                    CRC += getHash(static_cast<uint16_t>(variantData.getValue<uint32_t>()),
                                   sizeof(uint16_t));
                    break;
                default:
                    static_assert("ERROR get value_ from Variant");
                    break;
            }
            return CRC;
        }
        void setDataFromVariant(SendingData& data, Variant& variantData) {
            switch (variantData.typeOfValue) {
                case ValueType::BOOL:
                    data.value_.bool_value = variantData.getValue<bool>();
                    break;
                case ValueType::FLOAT:
                    data.value_.float_value = variantData.getValue<float>();
                    break;
                case ValueType::INT8_T:
                    data.value_.int8_value = variantData.getValue<int8_t>();
                    break;
                case ValueType::INT16_T:
                    data.value_.int16_value = variantData.getValue<int16_t>();
                    break;
                case ValueType::INT32_T:
                    data.value_.int32_value = variantData.getValue<int32_t>();
                    break;
                case ValueType::UINT8_T:
                    data.value_.uint8_value = variantData.getValue<uint8_t>();
                    break;
                case ValueType::UINT16_T:
                    data.value_.uint16_value = variantData.getValue<uint16_t>();
                    break;
                case ValueType::UINT32_T:
                    data.value_.uint32_value = variantData.getValue<uint32_t>();
                    break;
                default:
                    static_assert("ERROR get value_ from Variant");
                    break;
            }
        }
    };
    Gyver433_TX<2> tx_;
    ManagerSensor* dataSensor_ = nullptr;
    uint8_t idDevice_ = 1;
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
    void Init();
    void AddManagerSensor(ManagerSensor* data);
};
