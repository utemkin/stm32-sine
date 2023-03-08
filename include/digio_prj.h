#ifndef PinMode_PRJ_H_INCLUDED
#define PinMode_PRJ_H_INCLUDED

#include "hwdefs.h"

#define DIG_IO_LIST \
    DIG_IO_ENTRY(cruise_in,   GPIOB, GPIO5,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(start_in,    GPIOC, GPIO15, PinMode::INPUT_PD)   \
    DIG_IO_ENTRY(brake_in,    GPIOB, GPIO2,  PinMode::INPUT_PD)   \
    DIG_IO_ENTRY(mprot_in,    GPIOD, GPIO15,  PinMode::INPUT_PU)    \
    DIG_IO_ENTRY(fwd_in,      GPIOB, GPIO9,  PinMode::INPUT_PU)   \
    DIG_IO_ENTRY(rev_in,      GPIOB, GPIO8,  PinMode::INPUT_PD)   \
    DIG_IO_ENTRY(emcystop_in, GPIOC, GPIO15,  PinMode::INPUT_PD)   \
    DIG_IO_ENTRY(bk_in,       GPIOA, GPIO6, PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(bms_in,      GPIOB, GPIO8,  PinMode::INPUT_PD)    \
    DIG_IO_ENTRY(ocur_in,     GPIOA, GPIO6,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(desat_in,    GPIOA, GPIO6,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(dcsw_out,    GPIOD, GPIO3, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(vtg_out,     GPIOD, GPIO4, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(prec_out,    GPIOD, GPIO5,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(led_out,     GPIOC, GPIO13, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(led2_out,    GPIOC, GPIO14, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(err_out,     GPIOD, GPIO6, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(temp0_out,   GPIOD, GPIO7, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(speed_out,   GPIOD, GPIO8,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(brk_out,     GPIOD, GPIO9,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Gate_CS,     GPIOA, GPIO4,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(OE_245,      GPIOB, GPIO14,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Gate_SD,     GPIOC, GPIO5,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Gate_PWR,    GPIOB, GPIO15,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Mux_S2,      GPIOC, GPIO7,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Mux_S1,      GPIOC, GPIO8,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(Mux_S0,      GPIOC, GPIO9,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(PSU_CS,      GPIOA, GPIO15,  PinMode::OUTPUT)      \



#define DIG_IO_BLUEPILL \
    DIG_IO_ENTRY(brake_in,    GPIOB, GPIO9,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(rev_in,      GPIOB, GPIO8,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(fwd_in,      GPIOB, GPIO7,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(start_in,    GPIOB, GPIO6,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(cruise_in,   GPIOB, GPIO5,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(mprot_in,    GPIOB, GPIO1,  PinMode::INPUT_FLT)    \
    DIG_IO_ENTRY(emcystop_in, GPIOB, GPIO1,  PinMode::INPUT_FLT)   \
    DIG_IO_ENTRY(bk_in,       GPIOB, GPIO12, PinMode::INPUT_PU)   \
    DIG_IO_ENTRY(bms_in,      GPIOD, GPIO15, PinMode::INPUT_FLT) /* non-existant */  \
    DIG_IO_ENTRY(ocur_in,     GPIOD, GPIO15, PinMode::INPUT_FLT) /* non-existant */  \
    DIG_IO_ENTRY(desat_in,    GPIOD, GPIO15, PinMode::INPUT_FLT) /* non-existant */  \
    DIG_IO_ENTRY(dcsw_out,    GPIOC, GPIO15, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(vtg_out,     GPIOD, GPIO14, PinMode::OUTPUT) /* non-existant */     \
    DIG_IO_ENTRY(prec_out,    GPIOB, GPIO4,  PinMode::OUTPUT)      \
    DIG_IO_ENTRY(led_out,     GPIOC, GPIO13, PinMode::OUTPUT)      \
    DIG_IO_ENTRY(err_out,     GPIOD, GPIO14, PinMode::OUTPUT) /* non-existant */     \
    DIG_IO_ENTRY(temp0_out,   GPIOD, GPIO14, PinMode::OUTPUT) /* non-existant */     \
    DIG_IO_ENTRY(speed_out,   GPIOD, GPIO14, PinMode::OUTPUT) /* non-existant */     \
    DIG_IO_ENTRY(brk_out,     GPIOD, GPIO14, PinMode::OUTPUT) /* non-existant */     \


/*    DIG_IO_ENTRY(test1_out,   GPIOB, GPIO3,  PinMode::OUTPUT)     \
    DIG_IO_ENTRY(test2_out,   GPIOA, GPIO13, PinMode::OUTPUT)     \
    DIG_IO_ENTRY(test3_out,   GPIOA, GPIO14, PinMode::OUTPUT)     \
    DIG_IO_ENTRY(test4_out,   GPIOA, GPIO15, PinMode::OUTPUT)     \*/

#define temp1_out bms_in  //is configured to output dynamically on Tesla hardware
#define spi_cs_out vtg_out

#endif // PinMode_PRJ_H_INCLUDED
