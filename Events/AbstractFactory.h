#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include <stdexcept>

template <typename T>
class AbstractFactory {
protected:
    //  map between name of event and creator
    typedef std::function<std::unique_ptr<T>()> ItemCreator;
    std::unordered_map<std::string, ItemCreator> itemCreators;

public:
    AbstractFactory() = default;
    virtual ~AbstractFactory() = default;

    virtual std::unique_ptr<T> create(const std::string &itemType) const;

    void registerItem(const std::string &itemName, const ItemCreator &creator);
};

template <typename T>
std::unique_ptr<T> AbstractFactory<T>::create(const std::string &itemType) const {
    const auto it = itemCreators.find(itemType);
    if (it != itemCreators.end())
    {
        return it->second();
    }
    throw std::invalid_argument("Item not found");
}

template <typename T>
void AbstractFactory<T>::registerItem(const std::string &itemName, const ItemCreator &creator)
{
    itemCreators[itemName] = creator;
}