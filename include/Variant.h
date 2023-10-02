#pragma once
#include <Arduino.h>

enum class SensorDataType : uint8_t {
    Temperature = 0,
    Pressure = 1,
    Humidity = 2,
    Co2 = 3,
    LPG = 4,
    Methane = 5,
    Smoke = 6,
    Hydrogen = 7,
    Light = 8
};

enum class ValueType : uint8_t {
    BOOL = 0,
    FLOAT = 1,
    INT8_T = 2,
    INT16_T = 3,
    INT32_T = 4,
    UINT8_T = 5,
    UINT16_T = 6,
    UINT32_T = 7
};

enum class MessageType : uint8_t { DATA = 1, SIGNAL = 2 };

union Value {
    bool bool_value;
    float float_value;
    int8_t int8_value;
    int16_t int16_value;
    int32_t int32_value;
    uint8_t uint8_value;
    uint16_t uint16_value;
    uint32_t uint32_value;
};

struct Variant {
    Variant(){};
    Variant(ValueType vType, SensorDataType vTypeOfSensorData)
        : typeOfValue(vType), typeOfSensorData(vTypeOfSensorData){};

    void setValue(bool value_new) {
        value.bool_value = value_new;
        typeOfValue = ValueType::BOOL;
    };
    void setValue(float value_new) {
        value.float_value = value_new;
        typeOfValue = ValueType::FLOAT;
    }
    void setValue(int8_t value_new) {
        value.int8_value = value_new;
        typeOfValue = ValueType::INT32_T;
    }
    void setValue(int16_t value_new) {
        value.int16_value = value_new;
        typeOfValue = ValueType::INT16_T;
    }
    void setValue(int32_t value_new) {
        value.int32_value = value_new;
        typeOfValue = ValueType::INT32_T;
    }
    void setValue(uint8_t value_new) {
        value.uint8_value = value_new;
        typeOfValue = ValueType::UINT8_T;
    }
    void setValue(uint16_t value_new) {
        value.uint16_value = value_new;
        typeOfValue = ValueType::UINT16_T;
    }
    void setValue(uint32_t value_new) {
        value.uint32_value = value_new;
        typeOfValue = ValueType::UINT32_T;
    }
    void setValue(Value& value_new, ValueType& value_type) {
        switch (value_type) {
            case ValueType::BOOL:
                value.bool_value = value_new.bool_value;
                break;
            case ValueType::FLOAT:
                value.float_value = value_new.float_value;
                break;
            case ValueType::INT8_T:
                value.int8_value = value_new.int8_value;
                break;
            case ValueType::INT16_T:
                value.int16_value = value_new.int16_value;
                break;
            case ValueType::INT32_T:
                value.int32_value = value_new.int32_value;
                break;
            case ValueType::UINT8_T:
                value.uint8_value = value_new.uint8_value;
                break;
            case ValueType::UINT16_T:
                value.uint16_value = value_new.uint16_value;
                break;
            case ValueType::UINT32_T:
                value.uint32_value = value_new.uint32_value;
                break;
            default:
                static_assert("ERROR get value from Variant");
                break;
        }
    }
    void setValue(Variant& value_new) {
        typeOfValue = value_new.typeOfValue;
        typeOfSensorData = value_new.typeOfSensorData;
        setValue(value_new.value, value_new.typeOfValue);
    }
    void setValueType(ValueType typeOfValue_new) { typeOfValue = typeOfValue_new; }

    void setSensorDataType(SensorDataType typeOfSensorData_new) {
        typeOfSensorData = typeOfSensorData_new;
    }
    template <typename T>
    const T getValue() const {
        switch (typeOfValue) {
            case ValueType::BOOL:
                return value.bool_value;
                break;
            case ValueType::FLOAT:
                return value.float_value;
                break;
            case ValueType::INT8_T:
                return value.int8_value;
                break;
            case ValueType::INT16_T:
                return value.int16_value;
                break;
            case ValueType::INT32_T:
                return value.int32_value;
                break;
            case ValueType::UINT8_T:
                return value.uint8_value;
                break;
            case ValueType::UINT16_T:
                return value.uint16_value;
                break;
            case ValueType::UINT32_T:
                return value.uint32_value;
                break;
            default:
                static_assert("ERROR get value from Variant");
                break;
        }
        static_assert("ERROR get value from Variant");
        return 0;
    };
    ValueType typeOfValue;
    SensorDataType typeOfSensorData;

   private:
    Value value;
};
