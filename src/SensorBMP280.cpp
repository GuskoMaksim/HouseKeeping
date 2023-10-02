#include "SensorBMP280.h"

SensorBMP280::SensorBMP280(ValueType type, uint8_t module_address)
    : module_address_(module_address),
      temperature_(type, SensorDataType::Temperature),
      pressure_(type, SensorDataType::Pressure),
      BME280_(){};

bool SensorBMP280::Init() {
    if (!BME280_.begin(module_address_)) {
        Serial.println("Error of INIT!");
        return false;
    } else {
        Update();
        Serial.println("BME280 module added to the device!");
        return true;
    }
};

void SensorBMP280::Update() {
    temperature_.setValue(static_cast<float>(BME280_.readTemperature()));
    pressure_.setValue(static_cast<float>(BME280_.readPressure() / mmColumn_));
};

Variant& SensorBMP280::getData(SensorDataType type) {
    switch (type) {
        case SensorDataType::Temperature:
            return temperature_;
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

const SensorBMP280::ModuleInfo& SensorBMP280::getModuleInfo() const { return moduleInfo_; };
