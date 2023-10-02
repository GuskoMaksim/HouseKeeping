#include "SensorMQ2.h"

SensorMQ2::SensorMQ2(uint8_t pinA)
    : type(ValueType::UINT16_T),
      pinA_(pinA),
      mq2(pinA_),
      LPG_(type, SensorDataType::LPG),
      Methane_(type, SensorDataType::Methane),
      Smoke_(type, SensorDataType::Smoke),
      Hydrogen_(type, SensorDataType::Hydrogen){};

bool SensorMQ2::Init() {
    mq2.calibrate();
    return true;
};

Variant& SensorMQ2::getData(SensorDataType type) {
    switch (type) {
        case SensorDataType::LPG:
            return LPG_;
            break;
        case SensorDataType::Methane:
            return Methane_;
            break;
        case SensorDataType::Smoke:
            return Smoke_;
            break;
        case SensorDataType::Hydrogen:
            return Hydrogen_;
            break;
        default:
            static_assert("ERROR of getData from MH-Z19B");
            break;
    };
    static_assert("ERROR of getData from MH-Z19B");
    return LPG_;
};

void SensorMQ2::Update() {
    LPG_.setValue(static_cast<uint16_t>(mq2.readLPG()));
    Methane_.setValue(static_cast<uint16_t>(mq2.readMethane()));
    Smoke_.setValue(static_cast<uint16_t>(mq2.readSmoke()));
    Hydrogen_.setValue(static_cast<uint16_t>(mq2.readHydrogen()));
};

const SensorMQ2::ModuleInfo& SensorMQ2::getModuleInfo() const { return moduleInfo_; };
