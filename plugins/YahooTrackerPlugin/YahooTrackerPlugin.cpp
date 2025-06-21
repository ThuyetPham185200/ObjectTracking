#include "YahooTracker.h"
#include "TrackerInterface.h"

extern "C" TrackerInterface* createTracker() {
    return new YahooTracker();
}

extern "C" void destroyTracker(TrackerInterface* tracker) {
    delete tracker;
}
