#pragma once

#include <mutex>
#include <thread>

class Clock;

class ClockListener
{
public:
                            ClockListener();
    virtual                ~ClockListener();

public:
                            //ClockListener( const ClockListener& )   = delete;
                            //ClockListener( ClockListener&& )        = delete;
                //ClockListener&  operator = ( const ClockListener& )     = delete;
            //ClockListener&  operator = ( ClockListener&& )          = delete;


public:
    virtual void            onClockTick( volatile unsigned );

public:
    virtual void            singleAction( volatile unsigned ) = 0;

private:
    virtual void            action();
    virtual void            waitForSignal();

    virtual bool            proceed();

    virtual void            setDoProcess( bool value );

private:
    Clock                  &m_cOwner;
    std::thread             m_cThread;
    bool                    m_bDoProcess;
    unsigned                m_nTime;

    std::mutex              m_cDoProcessMutex;
    std::condition_variable m_cConditionVariable;
};

