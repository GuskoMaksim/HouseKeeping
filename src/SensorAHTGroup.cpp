#include "SensorAHTGroup.h"

SensorAHTGroup::SensorAHTGroup(ValueType type, uint8_t module_address)
    : module_address_(module_address),
      temperature_(type, SensorDataType::Temperature),
      humidity_(type, SensorDataType::Humidity),
      aht_(){};

bool SensorAHTGroup::Init() {
    if (!aht_.begin()) {
        Serial.println("Error of INIT!");
        return false;
    } else {
        aht_.getEvent(&hum_, &temp_);
        Update();
        Serial.println("BME280 module added to the device!");
        return true;
    }
};

void SensorAHTGroup::Update() {
    temperature_.setValue(static_cast<float>(temp_.temperature));
    humidity_.setValue(static_cast<float>(hum_.relative_humidity));
};

Variant& SensorAHTGroup::getData(SensorDataType type) {
    switch (type) {
        case SensorDataType::Temperature:
            return temperature_;
            break;
        case SensorDataType::Humidity:
            return humidity_;
            break;
        default:
            static_assert("ERROR of getData from BME280");
            break;
    };
    static_assert("ERROR of getData from BME280");
    return temperature_;
};

const SensorAHTGroup::ModuleInfo& SensorAHTGroup::getModuleInfo() const { return moduleInfo_; };
