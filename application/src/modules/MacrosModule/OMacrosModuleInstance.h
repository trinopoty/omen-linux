#ifndef OMENLINUX_OMACROSMODULEINSTANCE_H
#define OMENLINUX_OMACROSMODULEINSTANCE_H

#include <OmenModule.h>

class OMacrosModuleInstance: public OModuleInstance {
Q_OBJECT

public:
    OMacrosModuleInstance(std::shared_ptr<OModule> module, rapidjson::Value &configuration);
    ~OMacrosModuleInstance() noexcept override;

    std::shared_ptr<OModule> GetModule() override;
    std::shared_ptr<QWidget> GetView() override;
    rapidjson::Value GetConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) override;

public slots:
    void HandleConfigurationChanged();

private:
    std::shared_ptr<OModule> mModule;
    std::shared_ptr<QWidget> mView;
};


#endif //OMENLINUX_OMACROSMODULEINSTANCE_H
