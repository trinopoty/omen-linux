#ifndef OMENLINUX_FOURZONEMODULEINSTANCE_H
#define OMENLINUX_FOURZONEMODULEINSTANCE_H

#include <OmenModule.h>
#include "FourZoneKbLightWidget.h"

class OFourZoneModuleInstance: public OModuleInstance {
    Q_OBJECT

public:
    OFourZoneModuleInstance(std::shared_ptr<OModule> module, rapidjson::Value &configuration);
    ~OFourZoneModuleInstance() noexcept override;

    std::shared_ptr<OModule> GetModule() override;
    std::shared_ptr<QWidget> GetView() override;
    rapidjson::Value GetConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) override;

public slots:
    void HandleConfigurationChanged();

private:
    std::shared_ptr<OModule> mModule;
    std::shared_ptr<FourZoneKbLightWidget> mView;
};

#endif //OMENLINUX_FOURZONEMODULEINSTANCE_H
