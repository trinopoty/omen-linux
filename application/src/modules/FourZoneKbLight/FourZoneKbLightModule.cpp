#include "FourZoneKbLightModule.h"

#include <memory>

#include "FourZoneModuleInstance.h"
#include "FourZoneKbLightDriver.h"

/* OFourZoneModule */

class OFourZoneModule: public OModule {
public:
    OFourZoneModule() = default;
    ~OFourZoneModule() = default;

    std::string GetName() const override {
        return std::string("FourZoneKeyboardLight");
    }

    std::string GetDisplayName() const override {
        return std::string("4 Zone Keyboard Light");
    }

    bool ShouldEnable() const override {
        return FourZoneKbLightDriver::DriverDetect();
    }

    std::unique_ptr<OModuleInstance> MakeInstance(rapidjson::Value &configuration) override {
        return std::unique_ptr<OModuleInstance>(new OFourZoneModuleInstance(mModule, configuration));
    }

    void SetSelfPtr(std::shared_ptr<OFourZoneModule> &module) {
        mModule = module;
    }

private:
    std::shared_ptr<OFourZoneModule> mModule;
};

/* GetFourZoneModule */

std::shared_ptr<OModule> GetFourZoneModule() {
    auto result = std::make_shared<OFourZoneModule>();
    result->SetSelfPtr(result);
    return result;
}
