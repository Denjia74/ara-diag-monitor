#include <gtest/gtest.h>
#include "monitor.h"
#include "event.h"

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

TEST_F(MonitorEventIntegrationTest, MonitorEventInteractionTest) {
    monitor.ReportMonitorAction(MonitorAction::kPassed);

    EXPECT_EQ(1, event.GetFaultDetectionCounter());
}

TEST_F(MonitorEventIntegrationTest, AnotherIntegrationTest) {
    monitor.ReportMonitorAction(MonitorAction::kFailed);
    EXPECT_TRUE(event.HasEventStatusBit(EventStatusBit::kTestFailed));
}
