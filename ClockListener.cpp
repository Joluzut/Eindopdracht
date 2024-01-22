#include "ClockListener.h"

#include "Clock.h"

#include <chrono>

#include <assert.h>

ClockListener::ClockListener()
    : m_cOwner( Clock::instance() )
{
    m_cOwner.addToClock( *this );

    m_bDoProcess    = false;

    m_nTime         = 0;
    m_cThread       = std::thread( &ClockListener::action, this );
}

ClockListener::~ClockListener()
{
    m_cThread.join();

    m_cOwner.removeFromClock( *this );
}

void
ClockListener::onClockTick( volatile unsigned nTime )
{
    m_nTime         = nTime;

    setDoProcess( true );

    m_cConditionVariable.notify_one();
}

void
ClockListener::action()
{
    while ( !m_cOwner.isStopped() )
    {
        waitForSignal();

        if ( !m_cOwner.isStopped() )
        {
            try
            {
                singleAction( m_nTime );
            }
            catch (...)
            {
            }
        }

        m_cOwner.clockTickProcessed();
    }
}

void
ClockListener::waitForSignal()
{
    std::unique_lock<std::mutex>    lock( m_cDoProcessMutex );

    m_cConditionVariable.wait( lock, [&] { return proceed(); } );

    m_bDoProcess    = false;
}

bool
ClockListener::proceed()
{
    return m_bDoProcess;
}

void
ClockListener::setDoProcess( bool value )
{
    std::lock_guard<std::mutex> cLockguard( m_cDoProcessMutex );

    assert( m_bDoProcess != value );

    m_bDoProcess    = value;
}

ClockListener::ClockListener(const ClockListener& listener)
    : m_cOwner(Clock::instance())
{
    m_cOwner.addToClock(*this);

    m_bDoProcess = false;

    m_nTime = 0;
    m_cThread = std::thread(&ClockListener::action, this);
}
