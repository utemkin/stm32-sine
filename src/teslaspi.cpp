/*
 * This file is part of the stm32-... project.
 *
 * Copyright (C) 2021 Johannes Huebner <dev@johanneshuebner.com>
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
#include "teslaspi.h"
#include "digio.h"
#include "params.h"
#include <libopencm3/stm32/spi.h>

#define PMIC_SPI SPI1
#define GATE_SPI SPI2
#define CLEAR_STATUS_FLAGS          0x3F        /* Mask used to clear system status flags given in SYSSF register    */
/** SPI Parity Bit Mask */
#define TLF35584_SPI_PARITY_MASK    0x0001

#define FLASH_DELAY 9000
static void delay(void)
{
   int i;
   for (i = 0; i < FLASH_DELAY; i++)       /* Wait a bit. */
      __asm__("nop");
}

void TeslaSpi::TlfErrChk()
{
   uint8_t TLFStatus=getSystemStatusFlagsTFL35584();
   Param::SetInt(Param::TLFStat,TLFStatus);
}



void TeslaSpi::InitPmic()
{
   unlockRegisterTLF35584();
   disableWindowWatchdogTLF35584();
   disableErrPinMonitorTLF35584();
   lockRegisterTLF35584();
   enableVoltageSupplyRails();

   /* If any error flag has been raised, clear that flag */
   if (getSystemStatusFlagsTFL35584() != 0)
   {
      clearSystemStatusFlagsTFL35584();
   }
   //In the example there is a wait time, needed?
   delay();
   setStateTransitionTLF35584(DeviceStateTransition_normal);
}

void TeslaSpi::unlockRegisterTLF35584()
{
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, UnlockKey1);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, UnlockKey2);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, UnlockKey3);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, UnlockKey4);
}

void TeslaSpi::lockRegisterTLF35584()
{
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, LockKey1);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, LockKey2);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, LockKey3);
   transferDataTLF35584(SpiCommand_write, ProtcfgRegAddr, LockKey4);
}

void TeslaSpi::disableWindowWatchdogTLF35584()
{
   /* Get the value of RWDCFG0 to check the current window watchdog setting */
   uint16_t u = transferDataTLF35584(SpiCommand_read, Rwdcfg0RegAddr, 0);

   transferDataTLF35584(SpiCommand_write, Wdcfg0RegAddr, u);
}

void TeslaSpi::disableErrPinMonitorTLF35584()
{
   /* Get the value of RSYSPCFG1 to check the current error pin monitoring setting */
   uint16_t u = transferDataTLF35584(SpiCommand_read, Rsyspcfg1RegAddr, 0);

   transferDataTLF35584(SpiCommand_write, Syspcfg1RegAddr, u);
}

void TeslaSpi::enableVoltageSupplyRails()
{
   uint8_t u = transferDataTLF35584(SpiCommand_read, DevctrlRegAddr, 0);

   u |= 1 << 3; //VoltageReferenceQVR_enabled
   u |= 1 << 5; //VoltageReferenceQVR_enabled

   /* Update device register values */
   transferDataTLF35584(SpiCommand_write, DevctrlRegAddr, u);
   transferDataTLF35584(SpiCommand_write, DevctrlnRegAddr, ~u);
}

uint8_t TeslaSpi::getSystemStatusFlagsTFL35584()
{
   return transferDataTLF35584(SpiCommand_read, SyssfRegAddr, 0);
}

void TeslaSpi::clearSystemStatusFlagsTFL35584()
{
   transferDataTLF35584(SpiCommand_write, SyssfRegAddr, CLEAR_STATUS_FLAGS);
}

void TeslaSpi::setStateTransitionTLF35584(statereqType requestedStateTransition)
{
    uint8_t u = transferDataTLF35584(SpiCommand_read, DevctrlRegAddr, 0);

    u |= requestedStateTransition;

    /* Update device register values */
    transferDataTLF35584(SpiCommand_write, DevctrlRegAddr, u);
    transferDataTLF35584(SpiCommand_write, DevctrlnRegAddr, ~u);
}

uint8_t TeslaSpi::transferDataTLF35584(spiCommandType cmd, tlf35584RegAddr addr, uint8_t data)
{
   uint8_t result = 0;

   DigIo::PSU_CS.Clear();

   if (cmd == SpiCommand_write)
      spi_send(PMIC_SPI, (1 << 14) | (addr << 8) | data);
   else
      result = spi_xfer(PMIC_SPI, (addr << 8) | data); //discards the upper byte

   DigIo::PSU_CS.Set();

   return result;
}
