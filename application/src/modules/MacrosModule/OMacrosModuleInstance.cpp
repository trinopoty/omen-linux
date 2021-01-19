#include "OMacrosModuleInstance.h"
#include "MacrosWidget.h"

OMacrosModuleInstance::OMacrosModuleInstance(std::shared_ptr<OModule> module, rapidjson::Value &configuration):
        OModuleInstance(), mModule(std::move(module)), mView(new MacrosWidget()) {
}

OMacrosModuleInstance::~OMacrosModuleInstance() noexcept = default;

std::shared_ptr<OModule> OMacrosModuleInstance::GetModule() {
    return mModule;
}

std::shared_ptr<QWidget> OMacrosModuleInstance::GetView() {
    return std::shared_ptr<QWidget>(mView);
}

rapidjson::Value OMacrosModuleInstance::GetConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    return rapidjson::Value(rapidjson::kObjectType);
}

void OMacrosModuleInstance::HandleConfigurationChanged() {
    ConfigurationChanged();
}
