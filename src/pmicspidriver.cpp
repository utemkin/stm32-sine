
/*
 * This file is part of the stm32-sine project.
 *
 * Copyright (C) 2022 Bernd Ocklin <bernd@ocklin.de>
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

#include "pmicspidriver.h"

uint32_t PmicSpiDriver::m_base = 0;
bool     PmicSpiDriver::m_readAfterWrite = false;

void PmicSpiDriver::InitGPIO(uint16_t pin, uint32_t cfg)
{
//not needed as done in hwinit.cpp
}

/**
 * \brief Initialise the SPI port's GPIO lines
 */
void PmicSpiDriver::Init()
{
//not needed as done in hwinit.cpp

}

bool PmicSpiDriver::ReadDataAfterWrite()
{
    return m_readAfterWrite;
}

uint16_t PmicSpiDriver::TransferData(uint16_t data)
{
    //return SPI_pollingNonFIFOTransaction(m_base, 16U, data);
    DigIo::PSU_CS.Clear();
    return spi_xfer(SPI1,data);
    DigIo::PSU_CS.Set();
}
