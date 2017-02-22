#include "MyoSensor.h"


void MyoSensor::onUnpair(myo::Myo * myo, uint64_t timestamp){
	// We've lost a Myo.
	// Let's clean up some leftover state.
	emgSamples.fill(0);
}

MyoSensor::MyoSensor() : emgSamples(), hub("com.example.emg-data-sample")
{
}

MyoSensor::~MyoSensor()
{
	if(sensorThread.joinable())
		sensorThread.join();
}

void MyoSensor::onEmgData(myo::Myo * myo, uint64_t timestamp, const int8_t * emg){
	for (int i = 0; i < 8; i++) {
		emgSamples[i] = emg[i];
	}
}
void MyoSensor::connectOnThread()
{
	sensorThread = thread(&MyoSensor::connect,this);
}
void MyoSensor::connect(){
	try {
		isRecord  = true;
		// First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
		// publishing your application. The Hub provides access to one or more Myos.
		//Hub hub("com.example.emg-data-sample");

        //cout << "Attempting to find a Myo..." << endl;

		// Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
		// immediately.
		// waitForMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
		// if that fails, the function will return a null pointer.
		Myo* myo = hub.waitForMyo(10000);

		// If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
		if (!myo) {
			throw std::runtime_error("Unable to find a Myo!");
		}

		// We've found a Myo.
        //cout << "Connected to a Myo armband!" << std::endl << std::endl;

		// Next we enable EMG streaming on the found Myo.
		myo->setStreamEmg(Myo::streamEmgEnabled);

		// Next we construct an instance of our DeviceListener, so that we can register it with the Hub.

		// Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
		// Hub::run() to send events to all registered device listeners.
		hub.addListener(this);
	}
	catch (const std::exception& e) {
		/*
		cerr << "Error: " << e.what() << std::endl;
		cerr << "Press enter to continue.";
		cin.ignore();*/
	}
}
array<int8_t, 8> MyoSensor::getEmg()
{
	return emgSamples;
}

void MyoSensor::stopRecord()
{
	isRecord = false;
}

void MyoSensor::refreshEmg()
{
	hub.run(20);
}
