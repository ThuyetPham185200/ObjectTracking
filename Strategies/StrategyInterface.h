#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

template <typename BaseType>
class StrategyInterface {
public:
    virtual ~StrategyInterface() = default;

    // Register a strategy by name
    void registerStrategy(const std::string& name, std::shared_ptr<BaseType> strategy) {
        strategies[name] = strategy;
    }

    // Select active strategy
    bool selectStrategy(const std::string& name) {
        auto it = strategies.find(name);
        if (it != strategies.end()) {
            current = it->second;
            return true;
        }
        std::cerr << "Strategy '" << name << "' not found.\n";
        return false;
    }

    std::shared_ptr<BaseType> currentStrategy() const {
        return current;
    }

protected:
    std::unordered_map<std::string, std::shared_ptr<BaseType>> strategies;
    std::shared_ptr<BaseType> current;
};
