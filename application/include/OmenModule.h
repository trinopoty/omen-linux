#ifndef OMENLINUX_OMENMODULE_H
#define OMENLINUX_OMENMODULE_H

#include <string>

#include <QObject>
#include <QWidget>

#include <rapidjson/document.h>

class OModule;
class OModuleInstance;

typedef std::shared_ptr<OModule> (*GetModule)();

class OModule {
public:
    ~OModule() = default;
    OModule() = default;

    virtual std::string GetName() const = 0;
    virtual std::string GetDisplayName() const = 0;
    virtual bool ShouldEnable() const = 0;

    /**
     * Create a new instance of the module.
     *
     * @param configuration Configuration document for this module. Ownership resides with caller.
     * @return Pointer to instance of module.
     */
    virtual std::unique_ptr<OModuleInstance> MakeInstance(rapidjson::Value &configuration) = 0;
};

class OModuleInstance: public QObject {
    Q_OBJECT

public:
    OModuleInstance();
    ~OModuleInstance() noexcept override;

    virtual std::shared_ptr<OModule> GetModule() = 0;
    virtual std::shared_ptr<QWidget> GetView() = 0;
    virtual rapidjson::Value GetConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) = 0;

signals:
    void ConfigurationChanged();
};

#endif //OMENLINUX_OMENMODULE_H
