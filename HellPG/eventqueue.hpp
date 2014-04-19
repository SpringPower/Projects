#ifndef EVENTQUEUE_HPP
#define EVENTQUEUE_HPP

#include "common.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class IEvent
{
public:
    IEvent(){}
    virtual~IEvent(){}

    virtual std::string GetName() const = 0;
};
typedef std::shared_ptr<IEvent> PIEvent;

class IEventListener
{
public:
    IEventListener(){}
    virtual~IEventListener(){}

    virtual void NotifyOfEvent(PIEvent ptEvent) = 0;
};
typedef std::shared_ptr<IEventListener> PIEventListener;

class EventQueue
{
public:
    EventQueue();
    virtual~EventQueue();

    void Register(const std::string &crtName, PIEventListener ptListener);
    void PostEvent(PIEvent ptEvent) const;

private:
    typedef std::unordered_multimap<std::string, PIEventListener> ListenerMap;
    ListenerMap m_aListeners;
};

#endif // EVENTQUEUE_HPP
