#pragma once

#include <mutex>
#include <set>
#include <thread>

class ClockListener;

class Clock
{
private:
                                Clock();

private:
                                Clock( const Clock& )       = delete;
                                Clock( Clock&& )            = delete;
            Clock&              operator = ( const Clock& ) = delete;
            Clock&              operator = ( Clock&& )      = delete;

public:
    virtual                    ~Clock();

public:
    static Clock&               instance();
    virtual void 			    reset();

public:
    virtual void                addToClock( ClockListener& );
    virtual void                removeFromClock( ClockListener& );

public:
    virtual void                loop(unsigned);

public:
    virtual void                clockTickProcessed();
    virtual bool                isStopped();

private:
    virtual void                updateListeners();

    virtual void                clockTick( volatile unsigned );

    virtual void                waitUntilReady();

private:
    virtual void                setStopped();

private:
    virtual bool                proceed();

private:
    std::set<ClockListener*>    m_paListeners;
    std::set<ClockListener*>    m_paAddListeners;
    std::set<ClockListener*>    m_paRemoveListeners;
    volatile unsigned           m_nProcessed;
    bool                        m_bIsStopped;

    std::mutex                  m_cSetMutex,
                                m_cProcessedMutex,
                                m_cIsStoppedMutex;
    std::condition_variable     m_cConditionVariable;
};
