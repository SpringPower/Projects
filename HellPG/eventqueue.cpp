#include "eventqueue.hpp"
#include <algorithm>

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{

}

void EventQueue::Register(const std::string &crtName, PIEventListener ptListener)
{
    m_aListeners.insert(ListenerMap::value_type(crtName, ptListener));
}

void EventQueue::PostEvent(PIEvent ptEvent) const
{
    auto range = m_aListeners.equal_range(ptEvent->GetName());
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        iter->second->NotifyOfEvent(ptEvent);
    }
}
