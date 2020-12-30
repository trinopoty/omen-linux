#include "FourZoneModuleInstance.h"

OFourZoneModuleInstance::OFourZoneModuleInstance(std::shared_ptr<OModule> module, rapidjson::Value &configuration):
        OModuleInstance(), mModule(std::move(module)), mView(new FourZoneKbLightWidget(configuration)) {
    connect(mView.get(), &FourZoneKbLightWidget::ConfigurationChanged, this, &OFourZoneModuleInstance::HandleConfigurationChanged);
}

OFourZoneModuleInstance::~OFourZoneModuleInstance() noexcept = default;

std::shared_ptr<OModule> OFourZoneModuleInstance::GetModule() {
    return mModule;
}

std::shared_ptr<QWidget> OFourZoneModuleInstance::GetView() {
    return std::shared_ptr<QWidget>(mView);
}

rapidjson::Value OFourZoneModuleInstance::GetConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    return mView->SaveConfiguration(allocator);
}

void OFourZoneModuleInstance::HandleConfigurationChanged() {
    ConfigurationChanged();
}
