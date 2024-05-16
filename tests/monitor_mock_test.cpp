#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "monitor.h"

using namespace testing;

class MockEvent : public Event {
public:
    MOCK_METHOD(void, SetFaultDetectionCounter, (int8_t));
    MOCK_METHOD(void, SetEventStatusBits, (std::map<EventStatusBit, bool>));
};

// Test fixture for Monitor tests with mock Event
class MonitorTest : public Test {
protected:
    void SetUp() override {
        mockEvent = std::make_shared<MockEvent>();
    }

    std::shared_ptr<MockEvent> mockEvent;
};
// Test that verifies the AttachEvent function in Monitor class
TEST_F(MonitorTest, AttachEventTest) {
    Monitor monitor;
    monitor.AttachEvent(mockEvent.get());

    EXPECT_EQ(mockEvent.get(), monitor.GetEvent());
}
// Test that verifies ReportMonitorAction function calls the expected methods on the mock Event
TEST_F(MonitorTest, ReportMonitorActionTest) {
    Monitor monitor;

    EXPECT_CALL(*mockEvent, SetFaultDetectionCounter(_)).Times(1);
    EXPECT_CALL(*mockEvent, SetEventStatusBits(_)).Times(1);

    monitor.ReportMonitorAction(MonitorAction::kPassed);
}
