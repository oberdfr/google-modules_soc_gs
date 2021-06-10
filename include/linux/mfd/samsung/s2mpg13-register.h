/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * s2mpg13-register.h
 *
 * Copyright (C) 2015 Samsung Electrnoics
 *
 * header file including register information of s2mpg13
 */

#ifndef __LINUX_MFD_S2MPG13_REGISTER_H
#define __LINUX_MFD_S2MPG13_REGISTER_H
#include <linux/i2c.h>
#include "s2mpg1x-register.h"

#define S2MPG13_REG_INVALID	(0xFF)
#define S2MPG13_EVT0	0

/*
 * Helper macros for creating bitmasks
 */
#define MASK(width, shift)	(((0x1 << (width)) - 1) << (shift))

/* Common(0x0) Registers */
enum S2MPG13_COMMON_REG {
	S2MPG13_COMMON_VGPIO0 = 0x0,
	S2MPG13_COMMON_VGPIO1 = 0x1,
	S2MPG13_COMMON_VGPIO2 = 0x2,
	S2MPG13_COMMON_VGPIO3 = 0x3,
	S2MPG13_COMMON_I3C_DAA = 0x4,
	S2MPG13_COMMON_IBI0 = 0x5,
	S2MPG13_COMMON_IBI1 = 0x6,
	S2MPG13_COMMON_IBI2 = 0x7,
	S2MPG13_COMMON_IBI3 = 0x8,
	S2MPG13_COMMON_CHIPID = 0xB,
	S2MPG13_COMMON_I3C_CFG1 = 0xC,
	S2MPG13_COMMON_I3C_STA = 0xE,
	S2MPG13_COMMON_IBIM1 = 0xF,
	S2MPG13_COMMON_IBIM2 = 0x10,
};

/* PM(0x1) Registers */
enum S2MPG13_PM_REG {
	S2MPG13_PM_INT1 = 0x0,
	S2MPG13_PM_INT2 = 0x1,
	S2MPG13_PM_INT3 = 0x2,
	S2MPG13_PM_INT4 = 0x3,
	S2MPG13_PM_INT1M = 0x4,
	S2MPG13_PM_INT2M = 0x5,
	S2MPG13_PM_INT3M = 0x6,
	S2MPG13_PM_INT4M = 0x7,
	S2MPG13_PM_OFFSRC = 0xA,
	S2MPG13_PM_COMMON_CTRL1 = 0xC,
	S2MPG13_PM_COMMON_CTRL2 = 0xD,
	S2MPG13_PM_COMMON_CTRL3 = 0xE,
	S2MPG13_PM_B1S_CTRL = 0xF,
	S2MPG13_PM_B1S_OUT1 = 0x10,
	S2MPG13_PM_B2S_CTRL = 0x11,
	S2MPG13_PM_B2S_OUT1 = 0x12,
	S2MPG13_PM_B3S_CTRL = 0x13,
	S2MPG13_PM_B3S_OUT1 = 0x14,
	S2MPG13_PM_B4S_CTRL = 0x15,
	S2MPG13_PM_B4S_OUT = 0x16,
	S2MPG13_PM_B5S_CTRL = 0x17,
	S2MPG13_PM_B5S_OUT = 0x18,
	S2MPG13_PM_B6S_CTRL = 0x19,
	S2MPG13_PM_B6S_OUT1 = 0x1A,
	S2MPG13_PM_B7S_CTRL = 0x1B,
	S2MPG13_PM_B7S_OUT1 = 0x1C,
	S2MPG13_PM_B8S_CTRL = 0x1D,
	S2MPG13_PM_B8S_OUT1 = 0x1E,
	S2MPG13_PM_B9S_CTRL = 0x1F,
	S2MPG13_PM_B9S_OUT1 = 0x20,
	S2MPG13_PM_B9S_OUT2 = 0x21,
	S2MPG13_PM_B10S_CTRL = 0x22,
	S2MPG13_PM_B10S_OUT = 0x23,
	S2MPG13_PM_BUCKD_CTRL = 0x24,
	S2MPG13_PM_BUCKD_OUT = 0x25,
	S2MPG13_PM_BUCKA_CTRL = 0x26,
	S2MPG13_PM_BUCKA_OUT = 0x27,
	S2MPG13_PM_BUCKC_CTRL = 0x28,
	S2MPG13_PM_BUCKC_OUT = 0x29,
	S2MPG13_PM_BB_CTRL = 0x2A,
	S2MPG13_PM_BB_OUT1 = 0x2B,
	S2MPG13_PM_L1S_CTRL = 0x2C,
	S2MPG13_PM_L2S_CTRL = 0x2D,
	S2MPG13_PM_L3S_CTRL = 0x2E,
	S2MPG13_PM_L4S_CTRL = 0x2F,
	S2MPG13_PM_L5S_CTRL = 0x30,
	S2MPG13_PM_L6S_CTRL = 0x31,
	S2MPG13_PM_L7S_CTRL = 0x32,
	S2MPG13_PM_L8S_CTRL = 0x33,
	S2MPG13_PM_L9S_CTRL = 0x34,
	S2MPG13_PM_L10S_CTRL = 0x35,
	S2MPG13_PM_L11S_CTRL = 0x36,
	S2MPG13_PM_L12S_CTRL = 0x37,
	S2MPG13_PM_L13S_CTRL = 0x38,
	S2MPG13_PM_L14S_CTRL = 0x39,
	S2MPG13_PM_L15S_CTRL = 0x3A,
	S2MPG13_PM_L16S_CTRL = 0x3B,
	S2MPG13_PM_L17S_CTRL = 0x3C,
	S2MPG13_PM_L18S_CTRL = 0x3D,
	S2MPG13_PM_L19S_CTRL = 0x3E,
	S2MPG13_PM_L20S_CTRL = 0x3F,
	S2MPG13_PM_L21S_CTRL = 0x40,
	S2MPG13_PM_L22S_CTRL = 0x41,
	S2MPG13_PM_L23S_CTRL = 0x42,
	S2MPG13_PM_L24S_CTRL = 0x43,
	S2MPG13_PM_L25S_CTRL = 0x44,
	S2MPG13_PM_L26S_CTRL = 0x45,
	S2MPG13_PM_L27S_CTRL = 0x46,
	S2MPG13_PM_L28S_CTRL = 0x47,
	S2MPG13_PM_LDO_CTRL1 = 0x48,
	S2MPG13_PM_LDO_CTRL2 = 0x49,
	S2MPG13_PM_DSCH1 = 0x4A,
	S2MPG13_PM_DSCH2 = 0x4B,
	S2MPG13_PM_DSCH3 = 0x4C,
	S2MPG13_PM_DSCH4 = 0x4D,
	S2MPG13_PM_DVS_RAMP1 = 0x4E,
	S2MPG13_PM_DVS_RAMP2 = 0x4F,
	S2MPG13_PM_DVS_RAMP3 = 0x50,
	S2MPG13_PM_DVS_RAMP4 = 0x51,
	S2MPG13_PM_DVS_RAMP5 = 0x52,
	S2MPG13_PM_DVS_RAMP6 = 0x53,
	S2MPG13_PM_DVS_RAMP7 = 0x54,
	S2MPG13_PM_DVS_RAMP8 = 0x55,
	S2MPG13_PM_DVS_SYNC_CTRL1 = 0x56,
	S2MPG13_PM_PCTRLSEL1 = 0x97,
	S2MPG13_PM_PCTRLSEL2 = 0x98,
	S2MPG13_PM_PCTRLSEL3 = 0x99,
	S2MPG13_PM_PCTRLSEL4 = 0x9A,
	S2MPG13_PM_PCTRLSEL5 = 0x9B,
	S2MPG13_PM_PCTRLSEL6 = 0x9C,
	S2MPG13_PM_PCTRLSEL7 = 0x9D,
	S2MPG13_PM_PCTRLSEL8 = 0x9E,
	S2MPG13_PM_PCTRLSEL9 = 0x9F,
	S2MPG13_PM_PCTRLSEL10 = 0xA0,
	S2MPG13_PM_PCTRLSEL11 = 0xA1,
	S2MPG13_PM_DCTRLSEL1 = 0xA2,
	S2MPG13_PM_DCTRLSEL2 = 0xA3,
	S2MPG13_PM_DCTRLSEL3 = 0xA4,
	S2MPG13_PM_DCTRLSEL4 = 0xA5,
	S2MPG13_PM_DCTRLSEL5 = 0xA6,
	S2MPG13_PM_OCP_EN1 = 0xA7,
	S2MPG13_PM_OCP_EN2 = 0xA8,
	S2MPG13_PM_OCP_PD_EN1 = 0xA9,
	S2MPG13_PM_OCP_PD_EN2 = 0xAA,
	S2MPG13_PM_OCP_CTRL1 = 0xAB,
	S2MPG13_PM_OCP_CTRL2 = 0xAC,
	S2MPG13_PM_OCP_CTRL3 = 0xAD,
	S2MPG13_PM_OCP_CTRL4 = 0xAE,
	S2MPG13_PM_OCP_CTRL5 = 0xAF,
	S2MPG13_PM_OCP_CTRL6 = 0xB0,
	S2MPG13_PM_OCP_CTRL7 = 0xB1,
	S2MPG13_PM_B2S_OCP_WARN = 0xB8,
	S2MPG13_PM_B2S_SOFT_OCP_WARN = 0xB9,
	S2MPG13_PM_B1S_OUT2 = 0xBA,
	S2MPG13_PM_B2S_OUT2 = 0xBB,
	S2MPG13_PM_B6S_OUT2 = 0xBC,
	S2MPG13_PM_B8S_OUT2 = 0xBD,
	S2MPG13_PM_B10S_OUT2 = 0xBE,
	S2MPG13_PM_L1S_CTRL2 = 0xBF,
	S2MPG13_PM_L23S_CTRL2 = 0xC0,
	S2MPG13_PM_L26S_CTRL2 = 0xC1,
	/* TODO : ocp_warn * oi function */
};

/* Meter(0xA) Registers */
enum S2MPG13_METER_REG {
	S2MPG13_METER_INT1 = 0x0,
	S2MPG13_METER_INT2 = 0x1,
	S2MPG13_METER_INT3 = 0x2,
	S2MPG13_METER_INT4 = 0x3,
	S2MPG13_METER_INT1M = 0x4,
	S2MPG13_METER_INT2M = 0x5,
	S2MPG13_METER_INT3M = 0x6,
	S2MPG13_METER_INT4M = 0x7,
	S2MPG13_METER_CTRL1 = 0x8,
	S2MPG13_METER_CTRL2 = 0x9,
	S2MPG13_METER_CTRL3 = 0xA,
	S2MPG13_METER_CTRL4 = 0xB,
	S2MPG13_METER_CTRL5 = 0xC,
	S2MPG13_METER_CTRL6 = 0xD,
	S2MPG13_METER_CTRL7 = 0xE,
	S2MPG13_METER_BUCKEN1 = 0xF,
	S2MPG13_METER_BUCKEN2 = 0x10,
	S2MPG13_METER_MUXSEL0 = 0x11,
	S2MPG13_METER_MUXSEL1 = 0x12,
	S2MPG13_METER_MUXSEL2 = 0x13,
	S2MPG13_METER_MUXSEL3 = 0x14,
	S2MPG13_METER_MUXSEL4 = 0x15,
	S2MPG13_METER_MUXSEL5 = 0x16,
	S2MPG13_METER_MUXSEL6 = 0x17,
	S2MPG13_METER_MUXSEL7 = 0x18,
	S2MPG13_METER_MUXSEL8 = 0x19,
	S2MPG13_METER_MUXSEL9 = 0x1A,
	S2MPG13_METER_MUXSEL10 = 0x1B,
	S2MPG13_METER_MUXSEL11 = 0x1C,
	S2MPG13_METER_PWR_WARN0 = 0x31,
	S2MPG13_METER_PWR_WARN1 = 0x32,
	S2MPG13_METER_PWR_WARN2 = 0x33,
	S2MPG13_METER_PWR_WARN3 = 0x34,
	S2MPG13_METER_PWR_WARN4 = 0x35,
	S2MPG13_METER_PWR_WARN5 = 0x36,
	S2MPG13_METER_PWR_WARN6 = 0x37,
	S2MPG13_METER_PWR_WARN7 = 0x38,
	S2MPG13_METER_PWR_WARN8 = 0x39,
	S2MPG13_METER_PWR_WARN9 = 0x3A,
	S2MPG13_METER_PWR_WARN10 = 0x3B,
	S2MPG13_METER_PWR_WARN11 = 0x3C,
	S2MPG13_METER_NTC_OT_WARN0 = 0x3D,
	S2MPG13_METER_NTC_OT_WARN1 = 0x3E,
	S2MPG13_METER_NTC_OT_WARN2 = 0x3F,
	S2MPG13_METER_NTC_OT_WARN3 = 0x40,
	S2MPG13_METER_NTC_OT_WARN4 = 0x41,
	S2MPG13_METER_NTC_OT_WARN5 = 0x42,
	S2MPG13_METER_NTC_OT_WARN6 = 0x43,
	S2MPG13_METER_NTC_OT_WARN7 = 0x44,
	S2MPG13_METER_NTC_OT_FAULT0 = 0x45,
	S2MPG13_METER_NTC_OT_FAULT1 = 0x46,
	S2MPG13_METER_NTC_OT_FAULT2 = 0x47,
	S2MPG13_METER_NTC_OT_FAULT3 = 0x48,
	S2MPG13_METER_NTC_OT_FAULT4 = 0x49,
	S2MPG13_METER_NTC_OT_FAULT5 = 0x4A,
	S2MPG13_METER_NTC_OT_FAULT6 = 0x4B,
	S2MPG13_METER_NTC_OT_FAULT7 = 0x4C,
	S2MPG13_METER_NTC_UT_WARN0 = 0x4D,
	S2MPG13_METER_NTC_UT_WARN1 = 0x4E,
	S2MPG13_METER_NTC_UT_WARN2 = 0x4F,
	S2MPG13_METER_NTC_UT_WARN3 = 0x50,
	S2MPG13_METER_NTC_UT_WARN4 = 0x51,
	S2MPG13_METER_NTC_UT_WARN5 = 0x52,
	S2MPG13_METER_NTC_UT_WARN6 = 0x53,
	S2MPG13_METER_NTC_UT_WARN7 = 0x54,
	S2MPG13_METER_ACC_DATA_CH0_1 = 0x63,
	S2MPG13_METER_ACC_DATA_CH0_2 = 0x64,
	S2MPG13_METER_ACC_DATA_CH0_3 = 0x65,
	S2MPG13_METER_ACC_DATA_CH0_4 = 0x66,
	S2MPG13_METER_ACC_DATA_CH0_5 = 0x67,
	S2MPG13_METER_ACC_DATA_CH0_6 = 0x68,
	S2MPG13_METER_ACC_DATA_CH1_1 = 0x69,
	S2MPG13_METER_ACC_DATA_CH1_2 = 0x6A,
	S2MPG13_METER_ACC_DATA_CH1_3 = 0x6B,
	S2MPG13_METER_ACC_DATA_CH1_4 = 0x6C,
	S2MPG13_METER_ACC_DATA_CH1_5 = 0x6D,
	S2MPG13_METER_ACC_DATA_CH1_6 = 0x6E,
	S2MPG13_METER_ACC_DATA_CH2_1 = 0x6F,
	S2MPG13_METER_ACC_DATA_CH2_2 = 0x70,
	S2MPG13_METER_ACC_DATA_CH2_3 = 0x71,
	S2MPG13_METER_ACC_DATA_CH2_4 = 0x72,
	S2MPG13_METER_ACC_DATA_CH2_5 = 0x73,
	S2MPG13_METER_ACC_DATA_CH2_6 = 0x74,
	S2MPG13_METER_ACC_DATA_CH3_1 = 0x75,
	S2MPG13_METER_ACC_DATA_CH3_2 = 0x76,
	S2MPG13_METER_ACC_DATA_CH3_3 = 0x77,
	S2MPG13_METER_ACC_DATA_CH3_4 = 0x78,
	S2MPG13_METER_ACC_DATA_CH3_5 = 0x79,
	S2MPG13_METER_ACC_DATA_CH3_6 = 0x7A,
	S2MPG13_METER_ACC_DATA_CH4_1 = 0x7B,
	S2MPG13_METER_ACC_DATA_CH4_2 = 0x7C,
	S2MPG13_METER_ACC_DATA_CH4_3 = 0x7D,
	S2MPG13_METER_ACC_DATA_CH4_4 = 0x7E,
	S2MPG13_METER_ACC_DATA_CH4_5 = 0x7F,
	S2MPG13_METER_ACC_DATA_CH4_6 = 0x80,
	S2MPG13_METER_ACC_DATA_CH5_1 = 0x81,
	S2MPG13_METER_ACC_DATA_CH5_2 = 0x82,
	S2MPG13_METER_ACC_DATA_CH5_3 = 0x83,
	S2MPG13_METER_ACC_DATA_CH5_4 = 0x84,
	S2MPG13_METER_ACC_DATA_CH5_5 = 0x85,
	S2MPG13_METER_ACC_DATA_CH5_6 = 0x86,
	S2MPG13_METER_ACC_DATA_CH6_1 = 0x87,
	S2MPG13_METER_ACC_DATA_CH6_2 = 0x88,
	S2MPG13_METER_ACC_DATA_CH6_3 = 0x89,
	S2MPG13_METER_ACC_DATA_CH6_4 = 0x8A,
	S2MPG13_METER_ACC_DATA_CH6_5 = 0x8B,
	S2MPG13_METER_ACC_DATA_CH6_6 = 0x8C,
	S2MPG13_METER_ACC_DATA_CH7_1 = 0x8D,
	S2MPG13_METER_ACC_DATA_CH7_2 = 0x8E,
	S2MPG13_METER_ACC_DATA_CH7_3 = 0x8F,
	S2MPG13_METER_ACC_DATA_CH7_4 = 0x90,
	S2MPG13_METER_ACC_DATA_CH7_5 = 0x91,
	S2MPG13_METER_ACC_DATA_CH7_6 = 0x92,
	S2MPG13_METER_ACC_DATA_CH8_1 = 0x93,
	S2MPG13_METER_ACC_DATA_CH8_2 = 0x94,
	S2MPG13_METER_ACC_DATA_CH8_3 = 0x95,
	S2MPG13_METER_ACC_DATA_CH8_4 = 0x96,
	S2MPG13_METER_ACC_DATA_CH8_5 = 0x97,
	S2MPG13_METER_ACC_DATA_CH8_6 = 0x98,
	S2MPG13_METER_ACC_DATA_CH9_1 = 0x99,
	S2MPG13_METER_ACC_DATA_CH9_2 = 0x9A,
	S2MPG13_METER_ACC_DATA_CH9_3 = 0x9B,
	S2MPG13_METER_ACC_DATA_CH9_4 = 0x9C,
	S2MPG13_METER_ACC_DATA_CH9_5 = 0x9D,
	S2MPG13_METER_ACC_DATA_CH9_6 = 0x9E,
	S2MPG13_METER_ACC_DATA_CH10_1 = 0x9F,
	S2MPG13_METER_ACC_DATA_CH10_2 = 0xA0,
	S2MPG13_METER_ACC_DATA_CH10_3 = 0xA1,
	S2MPG13_METER_ACC_DATA_CH10_4 = 0xA2,
	S2MPG13_METER_ACC_DATA_CH10_5 = 0xA3,
	S2MPG13_METER_ACC_DATA_CH10_6 = 0xA4,
	S2MPG13_METER_ACC_DATA_CH11_1 = 0xA5,
	S2MPG13_METER_ACC_DATA_CH11_2 = 0xA6,
	S2MPG13_METER_ACC_DATA_CH11_3 = 0xA7,
	S2MPG13_METER_ACC_DATA_CH11_4 = 0xA8,
	S2MPG13_METER_ACC_DATA_CH11_5 = 0xA9,
	S2MPG13_METER_ACC_DATA_CH11_6 = 0xAA,
	S2MPG13_METER_ACC_COUNT_1 = 0xAB,
	S2MPG13_METER_ACC_COUNT_2 = 0xAC,
	S2MPG13_METER_ACC_COUNT_3 = 0xAD,
	S2MPG13_METER_LPF_DATA_CH0_1 = 0xAE,
	S2MPG13_METER_LPF_DATA_CH0_2 = 0xAF,
	S2MPG13_METER_LPF_DATA_CH0_3 = 0xB0,
	S2MPG13_METER_LPF_DATA_CH1_1 = 0xB1,
	S2MPG13_METER_LPF_DATA_CH1_2 = 0xB2,
	S2MPG13_METER_LPF_DATA_CH1_3 = 0xB3,
	S2MPG13_METER_LPF_DATA_CH2_1 = 0xB4,
	S2MPG13_METER_LPF_DATA_CH2_2 = 0xB5,
	S2MPG13_METER_LPF_DATA_CH2_3 = 0xB6,
	S2MPG13_METER_LPF_DATA_CH3_1 = 0xB7,
	S2MPG13_METER_LPF_DATA_CH3_2 = 0xB8,
	S2MPG13_METER_LPF_DATA_CH3_3 = 0xB9,
	S2MPG13_METER_LPF_DATA_CH4_1 = 0xBA,
	S2MPG13_METER_LPF_DATA_CH4_2 = 0xBB,
	S2MPG13_METER_LPF_DATA_CH4_3 = 0xBC,
	S2MPG13_METER_LPF_DATA_CH5_1 = 0xBD,
	S2MPG13_METER_LPF_DATA_CH5_2 = 0xBE,
	S2MPG13_METER_LPF_DATA_CH5_3 = 0xBF,
	S2MPG13_METER_LPF_DATA_CH6_1 = 0xC0,
	S2MPG13_METER_LPF_DATA_CH6_2 = 0xC1,
	S2MPG13_METER_LPF_DATA_CH6_3 = 0xC2,
	S2MPG13_METER_LPF_DATA_CH7_1 = 0xC3,
	S2MPG13_METER_LPF_DATA_CH7_2 = 0xC4,
	S2MPG13_METER_LPF_DATA_CH7_3 = 0xC5,
	S2MPG13_METER_LPF_DATA_CH8_1 = 0xC6,
	S2MPG13_METER_LPF_DATA_CH8_2 = 0xC7,
	S2MPG13_METER_LPF_DATA_CH8_3 = 0xC8,
	S2MPG13_METER_LPF_DATA_CH9_1 = 0xC9,
	S2MPG13_METER_LPF_DATA_CH9_2 = 0xCA,
	S2MPG13_METER_LPF_DATA_CH9_3 = 0xCB,
	S2MPG13_METER_LPF_DATA_CH10_1 = 0xCC,
	S2MPG13_METER_LPF_DATA_CH10_2 = 0xCD,
	S2MPG13_METER_LPF_DATA_CH10_3 = 0xCE,
	S2MPG13_METER_LPF_DATA_CH11_1 = 0xCF,
	S2MPG13_METER_LPF_DATA_CH11_2 = 0xD0,
	S2MPG13_METER_LPF_DATA_CH11_3 = 0xD1,
	S2MPG13_METER_VBAT_DATA1 = 0xD2,
	S2MPG13_METER_VBAT_DATA2 = 0xD3,
	S2MPG13_METER_LPF_DATA_NTC0_1 = 0xD4,
	S2MPG13_METER_LPF_DATA_NTC0_2 = 0xD5,
	S2MPG13_METER_LPF_DATA_NTC1_1 = 0xD6,
	S2MPG13_METER_LPF_DATA_NTC1_2 = 0xD7,
	S2MPG13_METER_LPF_DATA_NTC2_1 = 0xD8,
	S2MPG13_METER_LPF_DATA_NTC2_2 = 0xD9,
	S2MPG13_METER_LPF_DATA_NTC3_1 = 0xDA,
	S2MPG13_METER_LPF_DATA_NTC3_2 = 0xDB,
	S2MPG13_METER_LPF_DATA_NTC4_1 = 0xDC,
	S2MPG13_METER_LPF_DATA_NTC4_2 = 0xDD,
	S2MPG13_METER_LPF_DATA_NTC5_1 = 0xDE,
	S2MPG13_METER_LPF_DATA_NTC5_2 = 0xDF,
	S2MPG13_METER_LPF_DATA_NTC6_1 = 0xE0,
	S2MPG13_METER_LPF_DATA_NTC6_2 = 0xE1,
	S2MPG13_METER_LPF_DATA_NTC7_1 = 0xE2,
	S2MPG13_METER_LPF_DATA_NTC7_2 = 0xE3,
	S2MPG13_METER_EXT_SIGNED_DATA1 = 0xE4,
	S2MPG13_METER_EXT_SIGNED_DATA2 = 0xE5,
};

/* gpio(0xC) Registers */
enum S2MPG13_GPIO_REG {
	S2MPG13_GPIO_INT1 = 0x0,
	S2MPG13_GPIO_INT2 = 0x1,
	S2MPG13_GPIO_INT1M = 0x2,
	S2MPG13_GPIO_INT2M = 0x3,
	S2MPG13_GPIO_STATUS = 0x4,
	S2MPG13_GPIO_0_SET = 0x5,
	S2MPG13_GPIO_1_SET = 0x6,
	S2MPG13_GPIO_2_SET = 0x7,
	S2MPG13_GPIO_3_SET = 0x8,
	S2MPG13_GPIO_4_SET = 0x9,
	S2MPG13_GPIO_5_SET = 0xA,
	S2MPG13_GPIO_6_SET = 0xB,
	S2MPG13_GPIO_7_SET = 0xC,
	S2MPG13_GPIO_0_MONSEL = 0xD,
	S2MPG13_GPIO_1_MONSEL = 0xE,
	S2MPG13_GPIO_2_MONSEL = 0xF,
	S2MPG13_GPIO_3_MONSEL = 0x10,
	S2MPG13_GPIO_4_MONSEL = 0x11,
	S2MPG13_GPIO_5_MONSEL = 0x12,
	S2MPG13_GPIO_6_MONSEL = 0x13,
	S2MPG13_GPIO_7_MONSEL = 0x14,
};

/* MT_TRIM(0xE) Registers */
enum S2MPG13_MT_TRIM_REG {
	S2MPG13_MT_TRIM_COMMON2 = 0x34,
};

/* S2MPG13 regulator ids */
enum S2MPG13_REGULATOR {
	S2MPG13_LDO1,
	S2MPG13_LDO2,
	S2MPG13_LDO3,
	S2MPG13_LDO4,
	S2MPG13_LDO5,
	S2MPG13_LDO6,
	S2MPG13_LDO7,
	S2MPG13_LDO8,
	S2MPG13_LDO9,
	S2MPG13_LDO10,
	S2MPG13_LDO11,
	S2MPG13_LDO12,
	S2MPG13_LDO13,
	S2MPG13_LDO14,
	S2MPG13_LDO15,
	S2MPG13_LDO16,
	S2MPG13_LDO17,
	S2MPG13_LDO18,
	S2MPG13_LDO19,
	S2MPG13_LDO20,
	S2MPG13_LDO21,
	S2MPG13_LDO22,
	S2MPG13_LDO23,
	S2MPG13_LDO24,
	S2MPG13_LDO25,
	S2MPG13_LDO26,
	S2MPG13_LDO27,
	S2MPG13_LDO28,
	S2MPG13_BUCK1,
	S2MPG13_BUCK2,
	S2MPG13_BUCK3,
	S2MPG13_BUCK4,
	S2MPG13_BUCK5,
	S2MPG13_BUCK6,
	S2MPG13_BUCK7,
	S2MPG13_BUCK8,
	S2MPG13_BUCK9,
	S2MPG13_BUCK10,
	S2MPG13_BUCKD,
	S2MPG13_BUCKA,
	S2MPG13_BUCKC,
	S2MPG13_BUCKBOOST,
	S2MPG13_REGULATOR_MAX,
};

enum s2mpg13_irq {
	/* PMIC */
	S2MPG13_IRQ_PWRONF_INT1,
	S2MPG13_IRQ_PWRONR_INT1,
	S2MPG13_IRQ_INT120C_INT1,
	S2MPG13_IRQ_INT140C_INT1,
	S2MPG13_IRQ_TSD_INT1,
	S2MPG13_IRQ_WRST_INT1,
	S2MPG13_IRQ_WTSR_INT1,

	S2MPG13_IRQ_SCL_SOFTRST_INT2,
	S2MPG13_IRQ_WLWP_ACC_INT2,

	S2MPG13_IRQ_OCP_B1S_INT3,
	S2MPG13_IRQ_OCP_B2S_INT3,
	S2MPG13_IRQ_OCP_B3S_INT3,
	S2MPG13_IRQ_OCP_B4S_INT3,
	S2MPG13_IRQ_OCP_B5S_INT3,
	S2MPG13_IRQ_OCP_B6S_INT3,
	S2MPG13_IRQ_OCP_B7S_INT3,
	S2MPG13_IRQ_OCP_B8S_INT3,

	S2MPG13_IRQ_OCP_B9S_INT4,
	S2MPG13_IRQ_OCP_B10S_INT4,
	S2MPG13_IRQ_OCP_BDS_INT4,
	S2MPG13_IRQ_OCP_BAS_INT4,
	S2MPG13_IRQ_OCP_BCS_INT4,
	S2MPG13_IRQ_OCP_BBS_INT4,

	S2MPG13_IRQ_NR,
};

typedef enum {
	BUCK1S = 0x1,
	BUCK2S = 0x2,
	BUCK3S = 0x3,
	BUCK4S = 0x4,
	BUCK5S = 0x5,
	BUCK6S = 0x6,
	BUCK7S = 0x7,
	BUCK8S = 0x8,
	BUCK9S = 0x9,
	BUCK10S = 0xA,
	BUCKD = 0xB,
	BUCKA = 0xC,
	BUCKC = 0xD,
	BUCKBOOST = 0x10,
	VSEN_P4 = 0x1C,
	VSEN_P5 = 0x1D,
	VSEN_P6 = 0x1E,
	VBAT = 0x1F,
	LDO1S = 0x21,
	LDO2S = 0x22,
	LDO3S = 0x23,
	LDO4S = 0x24,
	LDO5S = 0x25,
	LDO6S = 0x26,
	LDO7S = 0x27,
	LDO8S = 0x28,
	LDO9S = 0x29,
	LDO10S = 0x2A,
	LDO11S = 0x2B,
	LDO12S = 0x2C,
	LDO13S = 0x2D,
	LDO14S = 0x2E,
	LDO15S = 0x2F,
	LDO16S = 0x30,
	LDO17S = 0x31,
	LDO18S = 0x32,
	LDO19S = 0x33,
	LDO20S = 0x34,
	LDO21S = 0x35,
	LDO22S = 0x36,
	LDO23S = 0x37,
	LDO24S = 0x38,
	LDO25S = 0x39,
	LDO26S = 0x3A,
	LDO27S = 0x3B,
	LDO28S = 0x3C,
	VSEN_C4 = 0x5C,
	VSEN_C5 = 0x5D,
	VSEN_C6 = 0x5E,
} s2mpg13_meter_muxsel;

typedef enum {
	NTC_0P078125HZ = 1,
	NTC_0P15625HZ,
	NTC_0P3125HZ,
	NTC_0P625HZ,
	NTC_1P25HZ,
	NTC_2P5HZ,
	NTC_5HZ,
	NTC_10HZ,
} s2mpg13_ntc_samp_rate;

/* Common(0x0) MASK */
/* S2MPG13_COMMON_IBIM1 */
#define S2MPG13_IRQSRC_MASK	BIT(0)

/* PM(0x1) MASK */
#define S2MPG13_BUCK_MAX		13
#define S2MPG13_LDO_MAX			28
#define S2MPG13_BB_MAX			1
#define S2MPG13_VGPIO_NUM		11
#define S2MPG13_VGPIO_MAX_VAL	(0xFF)

/* S2MPG13_PM_INT3M */
#define S2MPG13_IRQ_INT3M_SHIFT		0
#define S2MPG13_IRQ_INT3M_WIDTH		8
#define S2MPG13_IRQ_INT3M_MASK		MASK(S2MPG13_IRQ_INT3M_WIDTH, S2MPG13_IRQ_INT3M_SHIFT)

#define S2MPG13_IRQ_OCP_B1S_MASK	BIT(0)
#define S2MPG13_IRQ_OCP_B2S_MASK	BIT(1)
#define S2MPG13_IRQ_OCP_B3S_MASK	BIT(2)
#define S2MPG13_IRQ_OCP_B4S_MASK	BIT(3)
#define S2MPG13_IRQ_OCP_B5S_MASK	BIT(4)
#define S2MPG13_IRQ_OCP_B6S_MASK	BIT(5)
#define S2MPG13_IRQ_OCP_B7S_MASK	BIT(6)
#define S2MPG13_IRQ_OCP_B8S_MASK	BIT(7)

/* S2MPG13_PM_INT4M */
#define S2MPG13_IRQ_INT4M_SHIFT		0
#define S2MPG13_IRQ_INT4M_WIDTH		5
#define S2MPG13_IRQ_INT4M_MASK		MASK(S2MPG13_IRQ_INT4M_WIDTH, S2MPG13_IRQ_INT4M_SHIFT)

#define S2MPG13_IRQ_OCP_B9S_MASK	BIT(0)
#define S2MPG13_IRQ_OCP_B10S_MASK	BIT(1)
#define S2MPG13_IRQ_OCP_BDS_MASK	BIT(2)
#define S2MPG13_IRQ_OCP_BAS_MASK	BIT(3)
#define S2MPG13_IRQ_OCP_BCS_MASK	BIT(4)
#define S2MPG13_IRQ_OCP_BBS_MASK	BIT(5)

/*
 * _MIN(group) S2MPG13_REG_MIN##group
 * _STEP(group) S2MPG13_REG_STEP##group
 */

/* BUCK1S~6S, BUCK8S~10S, BUCKC ## group: 1 */
#define S2MPG13_REG_MIN1	200000
#define S2MPG13_REG_STEP1	6250
/* BUCK7S,D,A ## group: 2 */
#define S2MPG13_REG_MIN2	600000
#define S2MPG13_REG_STEP2	12500
/* BUCKBOOST ## group: 3 */
#define S2MPG13_REG_MIN3	2600000
#define S2MPG13_REG_STEP3	12500
/* LDO1S,23S~26S ## group: 4 */
#define S2MPG13_REG_MIN4	300000
#define S2MPG13_REG_STEP4	12500
/* LDO2S,3S,8S,9S,21S ## group: 5 */
#define S2MPG13_REG_MIN5	725000
#define S2MPG13_REG_STEP5	12500
/* LDO4S,7S,10S~12S,14S,17S~20S,22S,27S ## group: 6 */
#define S2MPG13_REG_MIN6	700000
#define S2MPG13_REG_STEP6	25000
/* LDO5S,6S,13S,15S,16S,28S ## group: 7 */
#define S2MPG13_REG_MIN7	1800000
#define S2MPG13_REG_STEP7	25000

/* _N_VOLTAGES(num) S2MPG13_REG_N_VOLTAGES_##num */
#define S2MPG13_REG_N_VOLTAGES_64	0x40
#define S2MPG13_REG_N_VOLTAGES_128	0x80
#define S2MPG13_REG_N_VOLTAGES_256	0x100

#define S2MPG13_REG_ENABLE_WIDTH		2
#define S2MPG13_REG_ENABLE_MASK_1_0		MASK(S2MPG13_REG_ENABLE_WIDTH, 0)
#define S2MPG13_REG_ENABLE_MASK_3_2		MASK(S2MPG13_REG_ENABLE_WIDTH, 2)
#define S2MPG13_REG_ENABLE_MASK_4_3		MASK(S2MPG13_REG_ENABLE_WIDTH, 3)
#define S2MPG13_REG_ENABLE_MASK_5_4		MASK(S2MPG13_REG_ENABLE_WIDTH, 4)
#define S2MPG13_REG_ENABLE_MASK_7_6		MASK(S2MPG13_REG_ENABLE_WIDTH, 6)
#define S2MPG13_REG_ENABLE_MASK_7		BIT(7)

/* _TIME(macro) S2MPG13_ENABLE_TIME##macro */
#define S2MPG13_ENABLE_TIME_LDO 128
#define S2MPG13_ENABLE_TIME_BUCK 130

/* S2MPG13_PM_DCTRLSEL1 ~ 5 */
#define DCTRLSEL_VOUT					0x0
#define DCTRLSEL_PWREN					0x1
#define DCTRLSEL_PWREN_TRG				0x2
#define DCTRLSEL_PWREN_MIF				0x3
#define DCTRLSEL_PWREN_MIF_TRG			0x4
#define DCTRLSEL_AP_ACTIVE_N			0x5
#define DCTRLSEL_AP_ACTIVE_N_TRG		0x6
#define DCTRLSEL_PWREN_MIF_AP_ACTIVE_N	0x7
#define DCTRLSEL_AOC_VDD				0x8

/* S2MPG13_PM_OCP_WARN */
#define S2MPG13_OCP_WARN_EN_SHIFT		7
#define S2MPG13_OCP_WARN_CNT_SHIFT		6
#define S2MPG13_OCP_WARN_DVS_MASK_SHIFT	5
#define S2MPG13_OCP_WARN_LVL_SHIFT		0

/* Meter(0xA) MASK */
/* S2MPG13_METER_CTRL1 */
#define NTC_SAMP_RATE_SHIFT		5
#define NTC_SAMP_RATE_WIDTH		3
#define NTC_SAMP_RATE_MASK		MASK(NTC_SAMP_RATE_WIDTH, NTC_SAMP_RATE_SHIFT)

#define S2MPG13_METER_NTC_BUF 2 /* 12-bit */

#define S2MPG13_METER_EN_MASK		BIT(0)

/* MT_TRIM(0xE) MASK */
/* S2MPG13_MT_TRIM_COMMON2 */
#define S2MPG13_PMETER_MRST_MASK	BIT(7)

#endif /* __LINUX_MFD_S2MPG13_REGISTER_H */
