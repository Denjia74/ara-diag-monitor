#include <gtest/gtest.h>
#include "../src/monitor.h"
#include "../include/instance_specifier.h"

// Unit test for Monitor class with CounterBased debouncer, testing the Offer and StopOffer methods
TEST(MonitorTest, CounterBasedOfferScenario)
{
    ara::core::InstanceSpecifier _specifier("Instance0");
    ara::diag::InitMonitorReason _currentReason{ara::diag::InitMonitorReason::kClear};
    auto _initMonitor = [&](ara::diag::InitMonitorReason newReason)
    {
        _currentReason = newReason;
    };
    ara::diag::CounterBased _defaultValues;

    ara::diag::Monitor _monitor(_specifier, _initMonitor, _defaultValues);

    ara::core::Result<void> _result{_monitor.Offer()};
    EXPECT_TRUE(_result.HasValue());
    EXPECT_EQ(ara::diag::InitMonitorReason::kReenabled, _currentReason);

    ara::core::Result<void> _newResult{_monitor.Offer()};
    EXPECT_FALSE(_newResult.HasValue());

    _monitor.StopOffer();
    EXPECT_EQ(ara::diag::InitMonitorReason::kDisabled, _currentReason);
}
// Unit test for Monitor class with TimerBased debouncer, testing the Offer and StopOffer methods
TEST(MonitorTest, TimerBasedOfferScenario)
{
    ara::core::InstanceSpecifier _specifier("Instance0");
    ara::diag::InitMonitorReason _currentReason{ara::diag::InitMonitorReason::kClear};
    auto _initMonitor = [&](ara::diag::InitMonitorReason newReason)
    {
        _currentReason = newReason;
    };
    ara::diag::TimeBased _defaultValues;

    ara::diag::Monitor _monitor(_specifier, _initMonitor, _defaultValues);

    ara::core::Result<void> _result{_monitor.Offer()};
    EXPECT_TRUE(_result.HasValue());
    EXPECT_EQ(ara::diag::InitMonitorReason::kReenabled, _currentReason);

    ara::core::Result<void> _newResult{_monitor.Offer()};
    EXPECT_FALSE(_newResult.HasValue());

    _monitor.StopOffer();
    EXPECT_EQ(ara::diag::InitMonitorReason::kDisabled, _currentReason);
}
// Unit test for verifying different debouncer actions in Monitor class
TEST(MonitorTest, DebouncerActions)
{
    ara::core::InstanceSpecifier specifier("Instance0");
    auto initMonitor = [&](ara::diag::InitMonitorReason newReason){};
    ara::diag::CounterBased defaultValues;

    ara::diag::Monitor monitor(specifier, initMonitor, defaultValues);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kPassed);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kFailed);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kPrepassed);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kPrefailed);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kFreezeDebouncing);

    monitor.ReportMonitorAction(ara::diag::MonitorAction::kResetDebouncing);
}