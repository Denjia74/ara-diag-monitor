#include <gtest/gtest.h>
#include "monitor.h"
#include "event.h"

// Integration test fixture for Monitor and Event classes
class MonitorEventIntegrationTest : public testing::Test {
protected:
    void SetUp() override {
        monitor = Monitor();
        event = Event();
        monitor.AttachEvent(&event);
    }

    Monitor monitor;
    Event event;
};
// Test that verifies Monitor reports a 'kPassed' action and checks Event's fault detection counter
TEST_F(MonitorEventIntegrationTest, MonitorEventInteractionTest) {
    monitor.ReportMonitorAction(MonitorAction::kPassed);

    EXPECT_EQ(1, event.GetFaultDetectionCounter());
}
// Test that verifies Monitor reports a 'kFailed' action and checks if Event status bit is set correctly
TEST_F(MonitorEventIntegrationTest, AnotherIntegrationTest) {
    monitor.ReportMonitorAction(MonitorAction::kFailed);
    EXPECT_TRUE(event.HasEventStatusBit(EventStatusBit::kTestFailed));
}
