// jobsystemtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <assert.h>

// jobsystem settings
#define JOBSYSTEM_ENABLE_PROFILING                  ///< Enables worker/job profiling, and an ascii profile dump on shutdown.
#define JOBSYSTEM_ASSERT(...) assert(__VA_ARGS__)   ///< Directs internal system asserts to app-specific assert mechanism.

// jobsystem include
#include <jobsystem.h>

int main()
{
    jobsystem::JobManagerDesciptor jobManagerDesc;
    jobManagerDesc.m_workers.emplace_back("Worker1");
    jobManagerDesc.m_workers.emplace_back("Worker2");

    jobsystem::JobManager jobManager;
    if (!jobManager.Create(jobManagerDesc))
    {
        return 1;
    }

    auto something = []()
    {
        OutputDebugStringA("something\n");
        Sleep(1);
    };

    auto somethingAfterThat = []()
    {
        OutputDebugStringA("somethingAfterThat\n");
        Sleep(1);
    };

    auto parallelThing1 = []()
    {
        OutputDebugStringA("parallelThing1\n");
        Sleep(1);
    };

    auto parallelThing2 = []()
    {
        OutputDebugStringA("parallelThing2\n");
        Sleep(1);
    };

    auto parallelThing3 = []()
    {
        OutputDebugStringA("parallelThing3\n");
        Sleep(1);
    };

    auto finalThing = []()
    {
        OutputDebugStringA("finalThing\n");
        Sleep(1);
    };

    jobsystem::JobChainBuilder<128>(jobManager)
        .Do(something, 'a')
        .Then()
        .Do(somethingAfterThat, 'b')
        .Then()
        .Together()
            .Do(parallelThing1, 'c')
            .Do(parallelThing2, 'd')
            .Do(parallelThing3, 'e')
        .Close()
        .Then()
        .Do(finalThing, 'F')
        .Go()
        .WaitForAll();

    return 0;
}

