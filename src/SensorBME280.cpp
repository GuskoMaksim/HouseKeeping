#include "SensorBME280.h"

SensorBME280::SensorBME280(ValueType type, uint8_t module_address)
    : module_address_(module_address),
      temperature_(type, SensorDataType::Temperature),
      pressure_(type, SensorDataType::Pressure),
      humidity_(type, SensorDataType::Humidity),
      BME280_(){};

bool SensorBME280::Init() {
    if (!BME280_.begin(module_address_)) {
        Serial.println("Error of INIT!");
        return false;
    } else {
        Update();
        Serial.println("BME280 module added to the device!");
        return true;
    }
};

void SensorBME280::Update() {
    temperature_.setValue(static_cast<float>(BME280_.readTemperature()));
    pressure_.setValue(static_cast<float>(BME280_.readPressure() / mmColumn_));
    humidity_.setValue(static_cast<float>(BME280_.readHumidity()));
};

Variant& SensorBME280::getData(SensorDataType type) {
    switch (type) {
        case SensorDataType::Temperature:
            return temperature_;
            break;
        case SensorDataType::Humidity:
            return humidity_;
            break;
        case SensorDataType::Pressure:
            return pressure_;
            break;
        default:
            static_assert("ERROR of getData from BME280");
            break;
    };
    static_assert("ERROR of getData from BME280");
    return temperature_;
};

const SensorBME280::ModuleInfo& SensorBME280::getModuleInfo() const { return moduleInfo_; };
