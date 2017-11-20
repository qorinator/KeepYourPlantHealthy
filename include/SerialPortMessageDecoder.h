#ifndef SERIALPORTMESSAGEDECODER_H
#define SERIALPORTMESSAGEDECODER_H

#include <queue>

class SerialPortMessageDecoder
{
public:
	SerialPortMessageDecoder();
	~SerialPortMessageDecoder();
	void DecodeSerialPortMessage(const std::vector<unsigned int>& rxBuffer);
private:
	bool IsStartOfMessageFound(unsigned int firstByte, unsigned int secondByte);
	bool IsCheckSumCorrect(const std::vector<unsigned int>& rxBuffer);
	void DecodedMessageToSensorsValue(const std::vector<unsigned int>& rxBuffer);
	int GetSoilMoistureValue(const std::vector<unsigned int>& rxBuffer);
	float GetTemperatureValue(const std::vector<unsigned int>& rxBuffer);
	float GetHumidityValue(const std::vector<unsigned int>& rxBuffer);
	int GetUVLevel(const std::vector<unsigned int>& rxBuffer);
private:
	unsigned int m_soilMoistureValue;
	float m_temperature;
	float m_humidity;
	unsigned int m_UVLevel;
	int m_startIndex;
};

#endif // SERIALPORTMESSAGEDECODER_H
