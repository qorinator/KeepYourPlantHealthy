#ifndef MESSAGEDECODER_H
#define MESSAGEDECODER_H

#include <vector>

class MessageDecoder
{	
public:
	MessageDecoder();
	virtual ~MessageDecoder();

	typedef std::vector<unsigned int> buffer_t;

	void DecodeSerialPortMessage(const buffer_t& rxBuffer);
	
	int GetSoilMoistureValue();	
	int GetUVLevel();
	float GetTemperatureValue();
	float GetHumidityValue();
private:
	bool IsStartOfMessageFound(const buffer_t& rxBuffer, unsigned int index);
	bool IsCheckSumCorrect(const buffer_t& rxBuffer);
	void DecodedMessageToSensorsValue(const buffer_t& rxBuffer);
private:
	
	unsigned int m_soilMoistureValue;
	float m_temperature;
	float m_humidity;
	unsigned int m_UVLevel;
	int m_startIndex;
};

#endif // MESSAGEDECODER_H
