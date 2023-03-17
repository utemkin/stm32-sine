
/*
 * This file is part of the stm32-sine project.
 *
 * Copyright (C) 2022 David J. Fiddes <D.J@fiddes.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gatedriverinterface.h"
#include "hw/stgap1as_gate_driver.h"

namespace c2000 {

/**
 * \brief Set up the SPI bus connected to the STGAP1AS gate drivers
 */
void GateDriverInterface::Init()
{
//not needed as done in hwinit.cpp
}

/**
 * \brief Initiate an SPI transaction with the gate drivers
 *
 * Encapsulates all of the hardware dependent work required to communicate with
 * an array of daisy-chained STGAP1AS gate driver chips. Inter-message timing
 * delays are not included.
 *
 * \param writeData Data to be sent to the STGAP1AS driver chips
 * \param readData Data buffer for data read from the chips. May be NULL if the
 * received data is not required
 */
 /*
 void GateDriverInterface::SendData(DataBuffer writeData, DataBuffer readData)
{
    // Manually assert the ~CS pin and add a delay to allow it to settle and
    // match the required set-up time for the STGAP1AS
   // GPIO_writePin(m_gateCsPin, 0);
    DigIo::Gate_CS.Clear();
    DEVICE_DELAY_US(2);

    // Run the SPI transaction with a 2 cycle delay between 16-bit words
   // SPI_pollingFIFOTransaction(
   //     m_gateSpiBase, 16U, writeData, readData, NumDriverChips, 2U);
    if (readData)
    {
        for (int i = 0; i < NumDriverChips; i++)
        {
            readData[i] = spi_xfer(SPI3, writeData[i]);
            DEVICE_DELAY_US(1);
        }
    }
    else
    {
        for (int i = 0; i < NumDriverChips; i++)
        {
            spi_xfer(SPI3, writeData[i]);
            DEVICE_DELAY_US(1);
        }
    }

    // Manually de-assert the ~CS pin and ensure that we have waited sufficient
    // time for the data being sent byt the chips to arrive
    DEVICE_DELAY_US(20);
    //GPIO_writePin(m_gateCsPin, 1);
    DigIo::Gate_CS.Set();
}
*/

void GateDriverInterface::SendData(DataBuffer writeData, DataBuffer readData)
{
    // Manually assert the ~CS pin and add a delay to allow it to settle and
    // match the required set-up time for the STGAP1AS
   // GPIO_writePin(m_gateCsPin, 0);
    DigIo::Gate_CS.Clear();
    DEVICE_DELAY_US(2);

    // Run the SPI transaction with a 2 cycle delay between 16-bit words
   // SPI_pollingFIFOTransaction(
   //     m_gateSpiBase, 16U, writeData, readData, NumDriverChips, 2U);
    for (int i = 0; i < NumDriverChips; i++)
    {
        readData[i] = spi_xfer(SPI3, writeData[i]);
        DEVICE_DELAY_US(1);
        Param::SetInt(Param::SPI3Rx,readData[i]);
    }


    // Manually de-assert the ~CS pin and ensure that we have waited sufficient
    // time for the data being sent byt the chips to arrive
    DEVICE_DELAY_US(20);
    //GPIO_writePin(m_gateCsPin, 1);
    DigIo::Gate_CS.Set();
}

/**
 * \brief Assert the ~SD line on the STGAP1AS gate drivers allowing them to be
 * configured
 */
void GateDriverInterface::Shutdown()
{
    //GPIO_writePin(m_gateShutdownPin, 0);
    DigIo::Gate_SD.Clear();
}

/**
 * \brief De-assert the ~SD line on the STGAP1AS gate drivers to allow them to
 * run normally
 */
void GateDriverInterface::Resume()
{
    //GPIO_writePin(m_gateShutdownPin, 1);
    DigIo::Gate_SD.Set();
}

/**
 * \brief Return whether the STGAP1AS gate drivers are enabled
 */
bool GateDriverInterface::IsShutdown()
{
    //return GPIO_readPin(m_gateShutdownPin) == 0;
    return DigIo::Gate_SD.Get() == 0;
}

} // namespace c2000
