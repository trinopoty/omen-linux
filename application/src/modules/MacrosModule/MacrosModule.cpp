#include "MacrosModule.h"
#include "OMacrosModuleInstance.h"

/* OMacrosModule */

class OMacrosModule: public OModule {
public:
    OMacrosModule() = default;
    ~OMacrosModule() = default;

    std::string GetName() const override {
        return std::string("Macros");
    }

    std::string GetDisplayName() const override {
        return std::string("Macros");
    }

    bool ShouldEnable() const override {
        return true;
    }

    std::unique_ptr<OModuleInstance> MakeInstance(rapidjson::Value &configuration) override {
        return std::unique_ptr<OModuleInstance>(new OMacrosModuleInstance(mModule, configuration));
    }

    void SetSelfPtr(std::shared_ptr<OMacrosModule> &module) {
        mModule = module;
    }

private:
    std::shared_ptr<OMacrosModule> mModule;
};

/* GetMacrosModule */

std::shared_ptr<OModule> GetMacrosModule() {
    auto result = std::make_shared<OMacrosModule>();
    result->SetSelfPtr(result);
    return result;
}
