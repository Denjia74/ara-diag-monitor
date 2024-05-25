#include <gtest/gtest.h>
#include "../src/monitor.h"
#include "../include/instance_specifier.h"

// Unit test for Monitor class with CounterBased debouncer, testing the Offer and StopOffer methods
TEST(MonitorTest, CounterBasedOfferScenario)
{
    ara::core::InstanceSpecifier _specifier("Instance0");
    ara::diag::InitMonitorReason _currentReason{InitMonitorReason::kClear};
    auto _initMonitor = [&](InitMonitorReason newReason)
    {
        _currentReason = newReason;
    };
    ara::diag::CounterBased _defaultValues;

    ara::diag::Monitor _monitor(_specifier, _initMonitor, _defaultValues);

    ara::core::Result<void> _result{_monitor.Offer()};
    EXPECT_TRUE(_result.HasValue());
    EXPECT_EQ(InitMonitorReason::kReenabled, _currentReason);

    ara::core::Result<void> _newResult{_monitor.Offer()};
    EXPECT_FALSE(_newResult.HasValue());

    _monitor.StopOffer();
    EXPECT_EQ(InitMonitorReason::kDisabled, _currentReason);
}
// Unit test for Monitor class with TimerBased debouncer, testing the Offer and StopOffer methods
TEST(MonitorTest, TimerBasedOfferScenario)
{
    core::InstanceSpecifier _specifier("Instance0");
    InitMonitorReason _currentReason{InitMonitorReason::kClear};
    auto _initMonitor = [&](InitMonitorReason newReason)
    {
        _currentReason = newReason;
    };
    TimeBased _defaultValues;

    Monitor _monitor(_specifier, _initMonitor, _defaultValues);

    core::Result<void> _result{_monitor.Offer()};
    EXPECT_TRUE(_result.HasValue());
    EXPECT_EQ(InitMonitorReason::kReenabled, _currentReason);

    core::Result<void> _newResult{_monitor.Offer()};
    EXPECT_FALSE(_newResult.HasValue());

    _monitor.StopOffer();
    EXPECT_EQ(InitMonitorReason::kDisabled, _currentReason);
}
// Unit test for verifying the AttachEvent method in Monitor class
TEST(MonitorTest, AttachEvent)
{
    core::InstanceSpecifier specifier("Instance0");
    auto initMonitor = [&](InitMonitorReason newReason){};

    Monitor monitor(specifier, initMonitor);

    Event event;
    monitor.AttachEvent(&event);

    EXPECT_EQ(&event, monitor.GetEvent());
}
// Unit test for verifying the ReportMonitorAction method in Monitor class
TEST(MonitorTest, ReportMonitorAction)
{
    core::InstanceSpecifier specifier("Instance0");
    auto initMonitor = [&](InitMonitorReason newReason){};

    Monitor monitor(specifier, initMonitor);

    Event event;
    monitor.AttachEvent(&event);
    monitor.ReportMonitorAction(MonitorAction::kResetTestFailed);
    EXPECT_FALSE(event.GetEventStatusBit(EventStatusBit::kTestFailed));

    EXPECT_THROW(monitor.ReportMonitorAction(static_cast<MonitorAction>(100)), std::invalid_argument);
}
// Unit test for Offer and StopOffer methods without an InitMonitor callback
TEST(MonitorTest, OfferAndStopOfferWithoutInitMonitorCallback)
{
    core::InstanceSpecifier specifier("Instance0");
    Monitor monitor(specifier, nullptr);

    EXPECT_TRUE(monitor.Offer().HasValue());

    monitor.StopOffer();
}
// Unit test for verifying Offer method after StopOffer method
TEST(MonitorTest, OfferAfterStopOffer)
{
    core::InstanceSpecifier specifier("Instance0");
    auto initMonitor = [&](InitMonitorReason newReason){};

    Monitor monitor(specifier, initMonitor);

    monitor.StopOffer();

    EXPECT_TRUE(monitor.Offer().HasValue());
}
// Unit test for verifying different debouncer actions in Monitor class
TEST(MonitorTest, DebouncerActions)
{
    core::InstanceSpecifier specifier("Instance0");
    auto initMonitor = [&](InitMonitorReason newReason){};
    CounterBased defaultValues;

    Monitor monitor(specifier, initMonitor, defaultValues);

    monitor.ReportMonitorAction(MonitorAction::kPassed);

    monitor.ReportMonitorAction(MonitorAction::kFailed);

    monitor.ReportMonitorAction(MonitorAction::kPrepassed);

    monitor.ReportMonitorAction(MonitorAction::kPrefailed);

    monitor.ReportMonitorAction(MonitorAction::kFreezeDebouncing);

    monitor.ReportMonitorAction(MonitorAction::kResetDebouncing);
}
