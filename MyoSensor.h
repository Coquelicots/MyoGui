#pragma once
#include <array>
#include <myo/myo.hpp>
#include <iostream>
#include <thread>
using namespace myo;
using namespace std;

class MyoSensor : public myo::DeviceListener {
public:
	MyoSensor();
	~MyoSensor();
	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp);

	// onEmgData() is called whenever a paired Myo has provided new EMG data, and EMG streaming is enabled.
	void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);

	void connectOnThread();
	void connect();
	array<int8_t, 8> getEmg();
	void stopRecord();
	void refreshEmg();
private:
	array<int8_t, 8> emgSamples;
	thread sensorThread;
	bool isRecord;
	Hub hub;
};
