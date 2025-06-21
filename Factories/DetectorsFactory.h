#include "FactoryInterface.h"
#include "DetectorInterface.h"

class DetectorsFactory : public FactoryInterface<DetectorInterface> {
protected:
    std::string getCreateSymbolName() const override { return "createDetector"; }
    std::string getDestroySymbolName() const override { return "destroyDetector"; }
};
