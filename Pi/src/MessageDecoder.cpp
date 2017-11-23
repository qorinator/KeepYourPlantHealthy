#include "MessageDecoder.h"
#include <iostream>


MessageDecoder::MessageDecoder()
	: m_soilMoistureValue(0)
	, m_temperature(0)
	, m_humidity(0)
	, m_UVLevel(0)
	, m_startIndex(0)
{}

MessageDecoder::~MessageDecoder()
{}

void MessageDecoder::DecodeSerialPortMessage(const buffer_t& rxBuffer) {
	for (size_t i = 0; i < rxBuffer.size(); i++) {	
		if(IsStartOfMessageFound(rxBuffer, i)) {
			m_startIndex = i;
			std::cout << "start index " << i << std::endl;
			if (IsCheckSumCorrect(rxBuffer) && rxBuffer.size() >= 16) {
				DecodedMessageToSensorsValue(rxBuffer);
				break;
			}	
		}	
	}
}

int MessageDecoder::GetSoilMoistureValue() {
	return m_soilMoistureValue;
}
float MessageDecoder::GetTemperatureValue() {
	return m_temperature;
}
float MessageDecoder::GetHumidityValue() {
	return m_humidity;
}
int MessageDecoder::GetUVLevel() {
	return m_UVLevel;
}

bool MessageDecoder::IsStartOfMessageFound(const buffer_t& rxBuffer, 
							size_t index) {
	return ((rxBuffer[index] == 0) 
		&& (rxBuffer[index+1] == 240)
		&& (rxBuffer[index+2] == 15));
}
bool MessageDecoder::IsCheckSumCorrect(const buffer_t& rxBuffer) {
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

void MessageDecoder::DecodedMessageToSensorsValue(const buffer_t& rxBuffer) {
	m_soilMoistureValue = (rxBuffer[m_startIndex + 3] << 8) + rxBuffer[m_startIndex + 4];
	m_temperature = rxBuffer[m_startIndex + 6] + rxBuffer[m_startIndex + 7] / 10.0;
	m_humidity = rxBuffer[m_startIndex + 9] + rxBuffer[m_startIndex + 10] / 10.0;
	m_UVLevel = rxBuffer[m_startIndex + 12];	
	// std::cout << "soil moisture " << m_soilMoistureValue  << std::endl;
	// std::cout << "temperature " << m_temperature  << std::endl;
	// std::cout << "humidity " << m_humidity  << std::endl;
	// std::cout << "UV level " << m_UVLevel  << std::endl;	
}

