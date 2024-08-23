#ifndef BULK_BULK_H
#define BULK_BULK_H
#include "IObserver.h"
#include <map>
#include <list>
#include <memory>
#include <optional>

class Bulk;

enum class StateType {Simple, Group};

class State
{
public:
    using Ptr = std::shared_ptr<State>;

public:
    explicit State(Bulk* bulk);
    virtual ~State() = default;

    virtual void execute(std::string line) = 0;
    void complete();
    void dispatch();
    virtual void clear();

    void setState(StateType type);

protected:
    Bulk* m_bulk;
    Data m_data;
};

/// Simple State

class SimpleState: public State
{
public:
    explicit SimpleState(Bulk* bulk);

    void execute(std::string line) override;
};

/// Group State

class GroupState: public State
{
public:
    explicit GroupState(Bulk* bulk);

    void execute(std::string line) override;
    void clear() override;

private:
    size_t m_depth;
};

class Bulk
{
public:
    explicit Bulk(size_t size);

    [[nodiscard]] size_t getSize() const;
    void setState(StateType type);
    void run();
    void applyCommand(const std::string &data);
    void dispatch(const Data& data);
    void complete();
    void setSize(std::optional<size_t> size);
    void subscribe(std::unique_ptr<IObserver> obj);
    void unsubscribeAll();

private:
    size_t m_size;
    std::map<StateType, State::Ptr> m_states;
    State::Ptr m_sm;
    bool m_isComplete;

    std::list<std::unique_ptr<IObserver>> m_listeners;
};

#endif //BULK_BULK_H
