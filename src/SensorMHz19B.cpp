#include "SensorMHz19B.h"

SensorMHz19B::SensorMHz19B(ValueType type, int8_t RX_MHZ, int8_t TX_MHZ)
    : Co2_(type, SensorDataType::Co2), RX_MHZ_(RX_MHZ), TX_MHZ_(TX_MHZ){};

bool SensorMHz19B::Init() {
    mhz19_.begin(TX_MHZ_, RX_MHZ_);
    mhz19_.setAutoCalibration(false);
    mhz19_.getStatus();
    delay(2000);
    if (!(mhz19_.getStatus() == 0)) {
        Serial.println("Error of INIT!");
        return false;
    } else {
        Update();
        Serial.println("MH-Z19B module added to the device!");
        return true;
    }
};

void SensorMHz19B::Update() { Co2_.setValue(static_cast<int16_t>(mhz19_.getPPM())); };

Variant& SensorMHz19B::getData(SensorDataType type) {
    switch (type) {
        case SensorDataType::Co2:
            return Co2_;
            break;
        default:
            static_assert("ERROR of getData from MH-Z19B");
            break;
    };
    static_assert("ERROR of getData from MH-Z19B");
    return Co2_;
};

const SensorMHz19B::ModuleInfo& SensorMHz19B::getModuleInfo() const { return moduleInfo_; };
