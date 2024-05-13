#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "monitor.h"

using namespace testing;

class MockEvent : public Event {
public:
    MOCK_METHOD(void, SetFaultDetectionCounter, (int8_t));
    MOCK_METHOD(void, SetEventStatusBits, (std::map<EventStatusBit, bool>));
};

class MonitorTest : public Test {
protected:
    void SetUp() override {
        mockEvent = std::make_shared<MockEvent>();
    }

    std::shared_ptr<MockEvent> mockEvent;
};

TEST_F(MonitorTest, AttachEventTest) {
    Monitor monitor;
    monitor.AttachEvent(mockEvent.get());

    EXPECT_EQ(mockEvent.get(), monitor.GetEvent());
}

TEST_F(MonitorTest, ReportMonitorActionTest) {
    Monitor monitor;

    EXPECT_CALL(*mockEvent, SetFaultDetectionCounter(_)).Times(1);
    EXPECT_CALL(*mockEvent, SetEventStatusBits(_)).Times(1);

    monitor.ReportMonitorAction(MonitorAction::kPassed);
}
