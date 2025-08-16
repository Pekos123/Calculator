#ifndef EVENT_H
#define EVENT_H
#pragma once

#include <vector>
#include <functional>

class Event
{
private:
    std::vector<std::function<void()>> listeners;
public:
    void AddListener(std::function<void()> callback);
    void Invoke();
};

#endif
