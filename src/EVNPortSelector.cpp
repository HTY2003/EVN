#include "EVNPortSelector.h"
#include <Arduino.h>
#include <Wire.h>

EVNPortSelector::EVNPortSelector()
{
}

void EVNPortSelector::begin()
{
	Wire.setSDA(WIRE0_SDA);
	Wire.setSCL(WIRE0_SCL);
	Wire1.setSDA(WIRE1_SDA);
	Wire1.setSCL(WIRE1_SCL);

	Serial1.setRX(SERIAL1_RX);
	Serial1.setTX(SERIAL1_TX);
	Serial2.setRX(SERIAL2_RX);
	Serial2.setTX(SERIAL2_TX);

	Wire.begin();
	Wire1.begin();
	Serial.begin();
}

void EVNPortSelector::printPorts()
{
	for (uint8_t t = 1; t < 9; t++)
	{
		this->setPort(t);
		Serial.print("---Port ");
		Serial.print(t);
		Serial.println("---");

		for (uint8_t addr = 0; addr <= 127; addr++)
		{
			if (addr == TCAADDR)
				continue;
			Wire.beginTransmission(addr);
			if (!Wire.endTransmission())
			{
				Serial.print("Address 0x");
				Serial.print(addr, HEX);
				Serial.println(" found");
			}
		}
	}

	for (uint8_t t = 9; t < 17; t++)
	{
		this->setPort(t);
		Serial.print("---Port ");
		Serial.print(t);
		Serial.println("---");

		for (uint8_t addr = 0; addr <= 127; addr++)
		{
			if (addr == TCAADDR)
				continue;
			Wire1.beginTransmission(addr);
			if (!Wire1.endTransmission())
			{
				Serial.print("Address 0x");
				Serial.print(addr, HEX);
				Serial.println(" found");
			}
		}
	}
}

void EVNPortSelector::setPort(uint8_t port)
{
	uint8_t portc = constrain(port, 1, 16);

	if (portc <= 8)
	{
		Wire.beginTransmission(TCAADDR);
		Wire.write(1 << (portc - 1));
		Wire.endTransmission();
		_wire0SensorPort = portc;
		_port = portc;
	}
	else
	{
		Wire1.beginTransmission(TCAADDR);
		Wire1.write(1 << (portc - 9));
		Wire1.endTransmission();
		_wire1SensorPort = portc;
		_port = portc;
	}
}

uint8_t EVNPortSelector::getPort()
{
	return _port;
}