#include "YoloDetector.h"
#include "DetectorInterface.h"

extern "C" DetectorInterface* createDetector() {
    return new YoloDetector();
}

extern "C" void destroyDetector(DetectorInterface* detector) {
    delete detector;
}
