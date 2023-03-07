/*
 * This file is part of the tumanako_vc project.
 *
 * Copyright (C) 2018 Johannes Huebner <dev@johanneshuebner.com>
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
#ifndef TESLASPI_H
#define TESLASPI_H
#include <stdint.h>

class TeslaSpi
{
public:
   static void InitPmic();
   static void TlfErrChk();

private:
   /* TLF35584 register address space */
   typedef enum
   {
       ProtcfgRegAddr      = 0x03,                 /* Protection register                          */
       Syspcfg1RegAddr     = 0x05,                 /* Protected System configuration request 1     */
       Wdcfg0RegAddr       = 0x06,                 /* Protected Watchdog configuration request 0   */
       Rsyspcfg1RegAddr    = 0x0C,                 /* System configuration 1 status                */
       Rwdcfg0RegAddr      = 0x0D,                 /* Watchdog configuration 0 status              */
       DevctrlRegAddr      = 0x15,                 /* Device control request                       */
       DevctrlnRegAddr     = 0x16,                 /* Device control inverted request              */
       WwdscmdRegAddr      = 0x17,                 /* Window watchdog service command              */
       SyssfRegAddr        = 0x1D,                 /* System status flags                          */
       SpisfRegAddr        = 0x1F,                 /* SPI status flags                             */
       DevstatRegAddr      = 0x27,                 /* Device status                                */
   } tlf35584RegAddr;

   /* Protection key */
   typedef enum
   {
       UnlockKey1  = 0xAB,                         /* Key 1 to unlock protected registers          */
       UnlockKey2  = 0xEF,                         /* Key 2 to unlock protected registers          */
       UnlockKey3  = 0x56,                         /* Key 3 to unlock protected registers          */
       UnlockKey4  = 0x12,                         /* Key 4 to unlock protected registers          */
       LockKey1    = 0xDF,                         /* Key 1 to lock protected registers            */
       LockKey2    = 0x34,                         /* Key 2 to lock protected registers            */
       LockKey3    = 0xBE,                         /* Key 3 to lock protected registers            */
       LockKey4    = 0xCA,                         /* Key 4 to lock protected registers            */
   } keyType;

   /* TLF35584 SPI commands */
   typedef enum
   {
       SpiCommand_read  = 0,                       /* Read operation SPI command                   */
       SpiCommand_write = 1                        /* Write operation SPI command                  */
   } spiCommandType;

   typedef enum
   {
       DeviceStateTransition_none     = 0,         /* NONE     */
       DeviceStateTransition_init     = 1,         /* INIT     */
       DeviceStateTransition_normal   = 2,         /* NORMAL   */
       DeviceStateTransition_sleep    = 3,         /* SLEEP    */
       DeviceStateTransition_standby  = 4,         /* STANDBY  */
       DeviceStateTransition_wake     = 5,         /* WAKE     */
       DeviceStateTransition_reserved = 6,         /* RESERVED */
   } statereqType;

   static void unlockRegisterTLF35584();
   static void lockRegisterTLF35584();
   static void disableWindowWatchdogTLF35584();
   static void disableErrPinMonitorTLF35584();
   static void enableVoltageSupplyRails();
   static uint8_t getSystemStatusFlagsTFL35584();
   static void clearSystemStatusFlagsTFL35584();
   static void setStateTransitionTLF35584(statereqType requestedStateTransition);
   static uint8_t transferDataTLF35584(spiCommandType cmd, tlf35584RegAddr addr, uint8_t data);
};

#endif // TESLASPI_H
