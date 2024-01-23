#include "Clock.h"

#include "ClockListener.h"

#include <assert.h>
#include <chrono>

Clock::Clock()
{
    m_nProcessed    = 0;
    m_bIsStopped    = false;
}

Clock::~Clock()
{
    assert( m_paRemoveListeners.size() == m_paListeners.size() );
}

Clock& Clock::instance()
{
    static Clock clock;

    return clock;
}

void
Clock::addToClock(ClockListener& cListener)
{
    std::lock_guard<std::mutex> cLockGuard( m_cSetMutex );

    m_paAddListeners.insert( &cListener );
}

void
Clock::removeFromClock(ClockListener& cListener)
{
    std::lock_guard<std::mutex> cLockGuard( m_cSetMutex );

    m_paRemoveListeners.insert( &cListener );
}

void
Clock::loop(unsigned nMax)
{
    updateListeners();

    m_nProcessed    = unsigned( m_paListeners.size() );

    for ( unsigned count = 1; count <= nMax + 1; count++ )
    {
        volatile unsigned time  = count;

        if ( time == nMax + 1 )
            setStopped();

        clockTick( time );

        if ( time <= nMax )
            waitUntilReady();
    }
}

void
Clock::clockTickProcessed()
{
    std::lock_guard<std::mutex> cLockguard( m_cProcessedMutex );

    m_nProcessed    = m_nProcessed + 1;

    if ( m_nProcessed == m_paListeners.size() )
        m_cConditionVariable.notify_one();
}

bool
Clock::isStopped()
{
    std::lock_guard<std::mutex> cLockguard( m_cIsStoppedMutex );

    return m_bIsStopped;
}

void
Clock::updateListeners()
{
    m_paListeners.insert( m_paAddListeners.begin(), m_paAddListeners.end() );
    m_paAddListeners.clear();

    for (auto it = m_paRemoveListeners.begin(); it != m_paRemoveListeners.end(); ++it) {
        m_paListeners.erase(*it);
    }
    m_paRemoveListeners.clear();
}

void
Clock::clockTick( volatile unsigned nTime )
{
    std::lock_guard<std::mutex> cLockGuard( m_cSetMutex );

    {
        std::lock_guard<std::mutex> cLockguard( m_cProcessedMutex );

        assert( m_nProcessed == m_paListeners.size() );

        m_nProcessed    = 0;
    }

    updateListeners();

    std::this_thread::sleep_for( std::chrono::microseconds(1) );

    for ( ClockListener* pListener : m_paListeners )
        pListener->onClockTick( nTime );
}

void
Clock::waitUntilReady()
{
    std::unique_lock<std::mutex>    lock( m_cProcessedMutex );

    m_cConditionVariable.wait( lock, [&] { return proceed(); } );
}

void
Clock::setStopped()
{
    std::lock_guard<std::mutex> cLockguard( m_cIsStoppedMutex );

    m_bIsStopped    = true;
}


bool
Clock::proceed()
{
    return m_nProcessed == m_paListeners.size();
}

void Clock::reset()
{
    updateListeners();

    m_nProcessed = 0;
    m_bIsStopped = false;
}

