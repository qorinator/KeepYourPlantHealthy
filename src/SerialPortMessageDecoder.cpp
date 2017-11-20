#include "SerialPortMessageDecoder.h"
#include <iostream>


SerialPortMessageDecoder::SerialPortMessageDecoder()
	: m_soilMoistureValue(0)
	, m_temperature(0)
	, m_humidity(0)
	, m_UVLevel(0)
	, m_startIndex(0)
{
}

SerialPortMessageDecoder::~SerialPortMessageDecoder()
{
}

void SerialPortMessageDecoder::DecodeSerialPortMessage(const std::vector<unsigned int>& rxBuffer)
{
	for (size_t i = 0; i < rxBuffer.size(); i++)
	{		
		if (IsStartOfMessageFound(rxBuffer[i], rxBuffer[i + 1]))
		{
			m_startIndex = i;
			if (IsCheckSumCorrect(rxBuffer) && rxBuffer.size() >= 16)
			{
				DecodedMessageToSensorsValue(rxBuffer);
				break;
			}	
		}	
	}
}

bool SerialPortMessageDecoder::IsStartOfMessageFound(unsigned int firstByte, unsigned int secondByte)
{
	return ((firstByte == 240) && (secondByte == 15));
}
bool SerialPortMessageDecoder::IsCheckSumCorrect(const std::vector<unsigned int>& rxBuffer)
{
	unsigned int retrievedChecksum = rxBuffer[m_startIndex + 14];
	unsigned int calculatedChecksum = rxBuffer[m_startIndex + 3] 
									+ rxBuffer[m_startIndex + 4] 
									+ rxBuffer[m_startIndex + 6]
									+ rxBuffer[m_startIndex + 7]
									+ rxBuffer[m_startIndex + 9]
									+ rxBuffer[m_startIndex + 10]
									+ rxBuffer[m_startIndex + 12];		
	return ((retrievedChecksum && 0x00FF) == (calculatedChecksum  && 0x00FF));
}
void SerialPortMessageDecoder::DecodedMessageToSensorsValue(const std::vector<unsigned int>& rxBuffer)
{
	m_soilMoistureValue = (rxBuffer[m_startIndex + 3] << 8) + rxBuffer[m_startIndex + 4];
	m_temperature = rxBuffer[m_startIndex + 6] + rxBuffer[m_startIndex + 7] / 10.0;
	m_humidity = rxBuffer[m_startIndex + 9] + rxBuffer[m_startIndex + 10] / 10.0;
	m_UVLevel = rxBuffer[m_startIndex + 12];	
	std::cout << "soil moisture " << m_soilMoistureValue  << std::endl;
	std::cout << "temperature " << m_temperature  << std::endl;
	std::cout << "humidity " << m_humidity  << std::endl;
	std::cout << "UV level " << m_UVLevel  << std::endl;	
}

