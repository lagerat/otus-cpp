#include "Bulk.h"

#include <iostream>

State::State(Bulk* bulk): m_bulk(bulk) {}
//-----------------------------------------------------------
void State::complete()
{
    m_bulk->complete();
    clear();
}
//-----------------------------------------------------------
void State::dispatch()
{
    if (!m_data.empty())
    {
        m_bulk->dispatch(m_data);
    }
    clear();
}
//-----------------------------------------------------------
void State::clear()
{
    m_data.clear();
}
//-----------------------------------------------------------
void State::setState(StateType type)
{
    m_bulk->setState(type);
}
//-----------------------------------------------------------
SimpleState::SimpleState(Bulk* bulk): State(bulk)
{
    m_data.reserve(m_bulk->getSize());
}
//-----------------------------------------------------------
void SimpleState::execute(std::string line)
{
    if (line.empty())
    {
        dispatch();
        complete();
        return;
    }

    if (line == "{")
    {
        dispatch();
        setState(StateType::Group);
        return;
    }

    if (line == "}")
    {
        return;
    }

    m_data.emplace_back(line);

    if (m_data.size() >= m_bulk->getSize())
    {
        dispatch();
    }
}
//-----------------------------------------------------------
GroupState::GroupState(Bulk* bulk): State(bulk) {}
//-----------------------------------------------------------
void GroupState::execute(std::string line)
{
    if (line.empty())
    {
        complete();
        return;
    }

    if (line == "{")
    {
        ++ m_depth;
        return;
    }

    if (line == "}")
    {
        if (m_depth > 0)
        {
            -- m_depth;
            return;
        }

        dispatch();
        setState(StateType::Simple);
        return;
    }

    m_data.emplace_back(line);
}
//-----------------------------------------------------------
void GroupState::clear()
{
    State::clear();
    m_depth = 0;
}
//-----------------------------------------------------------
Bulk::Bulk(size_t size): m_size(size)
{
    m_states.emplace(StateType::Simple, new SimpleState(this));
    m_states.emplace(StateType::Group, new GroupState(this));

    setState(StateType::Simple);
}
//-----------------------------------------------------------
void Bulk::setState(StateType type)
{
    m_sm = m_states[type];
}
//-----------------------------------------------------------
void Bulk::run()
{
    std::string line;

    while (!m_isComplete)
    {
        std::getline(std::cin, line);
        m_sm->execute(std::move(line));
    }
}
//-----------------------------------------------------------
size_t Bulk::getSize() const
{
    return m_size;
}
//-----------------------------------------------------------
void Bulk::complete()
{
    m_isComplete = true;
    unsubscribeAll();
}
//-----------------------------------------------------------
void Bulk::dispatch(const Data& data)
{
    for (const auto& listener : m_listeners)
    {
        listener->update(data);
    }
}
//-----------------------------------------------------------
void Bulk::subscribe(IObserver* listener)
{
    m_listeners.push_back(listener);
}
//-----------------------------------------------------------
void Bulk::unsubscribeAll()
{
    m_listeners.clear();
}
//-----------------------------------------------------------
