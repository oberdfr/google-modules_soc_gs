/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 Google, LLC.
 *
 * Device Tree binding constants for ZUMA BCL
 */

#ifndef _DT_BINDINGS_ZUMA_BCL_H
#define _DT_BINDINGS_ZUMA_BCL_H

/* Current Limit */
#define CPU1_UPPER_LIMIT	8000
#define CPU1_LOWER_LIMIT	2688
#define CPU1_STEP	166
#define CPU2_UPPER_LIMIT	12000
#define CPU2_LOWER_LIMIT	4000
#define CPU2_STEP	250
#define TPU_UPPER_LIMIT	12000
#define TPU_LOWER_LIMIT	4000
#define TPU_STEP	250
#define GPU_UPPER_LIMIT	12000
#define GPU_LOWER_LIMIT	4000
#define GPU_STEP	250
#define BO_LIMIT	5000
#define BO_UPPER_LIMIT	6800
#define BO_LOWER_LIMIT	3800
#define BO_STEP	200
#define BO_BAT_OPEN_TO_DEFAULT	1
#define BO_INT_REL_DEFAULT	3
#define BO_INT_DET_DEFAULT	3
#define UV_INT_REL_DEFAULT	2
#define UV_INT_DET_DEFAULT	1

/* Thermal Limit */
#define PMIC_OVERHEAT_UPPER_LIMIT	2000
#define PMIC_120C_UPPER_LIMIT	1200
#define PMIC_140C_UPPER_LIMIT	1400
#define THERMAL_DELAY_INIT_MS	1000

/* Voltage Limit */
#define SMPL_BATTERY_VOLTAGE	4200
#define SMPL_UPPER_LIMIT	3300
#define SMPL_LOWER_LIMIT	2600
#define SMPL_STEP	100
#define SMPL_NUM_LVL	32
#define VD_BATTERY_VOLTAGE	4200
#define VD_UPPER_LIMIT	3350
#define VD_LOWER_LIMIT	2600
#define VD_STEP	50
#define VD_DELAY	300
#define UVLO1_LIMIT	1000
#define UVLO2_LIMIT	1200
#define SMPL_LIMIT	1100
#define SOC_LIMIT	80
#define THERMAL_HYST_LEVEL	100

/* Indexing */
#define SMPL_WARN	0
#define OCP_WARN_CPUCL1	1
#define OCP_WARN_CPUCL2	2
#define SOFT_OCP_WARN_CPUCL1	3
#define SOFT_OCP_WARN_CPUCL2	4
#define OCP_WARN_TPU	5
#define SOFT_OCP_WARN_TPU	6
#define OCP_WARN_GPU	7
#define SOFT_OCP_WARN_GPU	8
#define PMIC_SOC	9
#define UVLO1	10
#define UVLO2	11
#define BATOILO1	12
#define BATOILO2	13
#define PMIC_120C	14
#define PMIC_140C	15
#define PMIC_OVERHEAT	16
#define BATOILO BATOILO1
#define TRIGGERED_SOURCE_MAX	17

#define SMPL_WARN_CTRL		S2MPG14_PM_SMPL_WARN_CTRL
#define SMPL_WARN_SHIFT		S2MPG14_SMPL_WARN_LVL_SHIFT
#define OCP_WARN_LVL_SHIFT	S2MPG14_OCP_WARN_LVL_SHIFT
#define CPU1_OCP_WARN		S2MPG14_PM_B3M_OCP_WARN
#define SOFT_CPU1_OCP_WARN	S2MPG14_PM_B3M_SOFT_OCP_WARN
#define CPU2_OCP_WARN		S2MPG14_PM_B2M_OCP_WARN
#define SOFT_CPU2_OCP_WARN	S2MPG14_PM_B2M_SOFT_OCP_WARN
#define TPU_OCP_WARN		S2MPG14_PM_B7M_OCP_WARN
#define SOFT_TPU_OCP_WARN	S2MPG14_PM_B7M_SOFT_OCP_WARN
#define GPU_OCP_WARN		S2MPG15_PM_B2S_OCP_WARN
#define SOFT_GPU_OCP_WARN	S2MPG15_PM_B2S_SOFT_OCP_WARN
#define MAIN_CHIPID		S2MPG14_COMMON_CHIPID
#define SUB_CHIPID		S2MPG15_COMMON_CHIPID
#define INT3_120C		S2MPG14_IRQ_120C_INT3
#define INT3_140C		S2MPG14_IRQ_140C_INT3
#define INT3_TSD		S2MPG14_IRQ_TSD_INT3
#define GPIO_ALIVE_BASE		(0x154d0000)
#define GPA9_CON		(0x100)

#define CPUCL0_BASE (0x29c00000)
#define CPUCL1_BASE (0x29d00000)
#define CPUCL2_BASE (0x29d80000)
#define G3D_BASE (0x1EE00000)
#define TPU_BASE (0x1A300000)
#define AUR_BASE (0x20A00000)
#define SYSREG_CPUCL0_BASE (0x29c20000)
#define CLUSTER0_GENERAL_CTRL_64 (0x1404)
#define CLKDIVSTEP (0x830)
#define VDROOP_FLT (0x838)
#define CPUCL0_CLKDIVSTEP_STAT (0x83c)
#define CPUCL0_CLKDIVSTEP_CON (0x838)
#define CLKDIVSTEP_STAT (0x848)
#define CLKDIVSTEP_CON_HEAVY (0x840)
#define CLKDIVSTEP_CON_LIGHT (0x844)
#define CLKOUT (0x810)
#define G3D_CLKDIVSTEP_STAT (0x854)
#define TPU_CLKDIVSTEP_STAT (0x850)
#define AUR_CLKDIVSTEP_STAT (0x838)
#define CLUSTER0_MPMM (0x1408)
#define CLUSTER0_LIT_MPMM (0x1408)
#define CLUSTER0_MID_MPMM (0x140C)
#define CLUSTER0_BIG_MPMM (0x1410)
#define CLUSTER0_MPMMEN (0x1414)
#define CLUSTER0_PPM (0x140c)
#define CLUSTER0_MID_DISPBLOCK (0x158c)
#define CLUSTER0_BIG_DISPBLOCK (0x1588)
#define MPMMEN_MASK (0xF << 21)
#define PPMEN_MASK (0x3 << 8)
#define PPMCTL_MASK (0xFF)
#define OCP_WARN_MASK (0x1F)
#define SMPL_WARN_MASK (0xE0)
#define ACTIVE_HIGH (0x1)
#define ACTIVE_LOW (0x0)
#define PMU_ALIVE_CPU0_STATES (0x1908)
#define PMU_ALIVE_CPU1_STATES (0x1988)
#define PMU_ALIVE_CPU2_STATES (0x1A08)
#define PMU_ALIVE_TPU_STATES (0x2508)
#define PMU_ALIVE_GPU_STATES (0x1A88)
#define PMU_ALIVE_AUR_STATES (0x2308)
#define PMU_CLK_OUT (0x3E80)
#define XCLKOUT_SOURCE_CPU0 (0x3001)
#define XCLKOUT_SOURCE_CPU1 (0x1101)
#define XCLKOUT_SOURCE_CPU2 (0x1201)
#define XCLKOUT_SOURCE_TPU (0x2E01)
#define XCLKOUT_SOURCE_GPU (0x1A01)
#define THRESHOLD_DELAY_MS 10
#define PWRWARN_DELAY_MS 50
#define LPF_CURRENT_SHIFT 4
#define ADD_CPUCL0 (0x29ce0000)
#define ADD_CPUCL1 (0x29d10000)
#define ADD_CPUCL2 (0x29d90000)
#define ADD_G3D (0x1EE60000)
#define ADD_TPU (0x1A3A0000)
#define ADD_AUR (0x20AF0000)
#define CLUSTER1_NONCPU_STATES (0x1508)
#define CLUSTER2_NONCPU_STATES (0x1708)

#define CORE_PMIC_MAIN 0
#define CORE_PMIC_SUB 1

#define CPU0_CLUSTER_MIN 0
#define CPU1_CLUSTER_MIN 4
#define CPU2_CLUSTER_MIN 8

/* Event Counter */
#define EVT_CNT_ENABLE_DEFAULT	1
#define EVT_CNT_RATE_DEFAULT	0

#endif /* _DT_BINDINGS_ZUMA_BCL_H */

