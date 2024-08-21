/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Device Tree binding constants for GS201 clock controller.
 *
 * Copyright (c) 2021 Samsung Electronics Co., Ltd.
 */

#ifndef _DT_BINDINGS_CLOCK_GS201_H
#define _DT_BINDINGS_CLOCK_GS201_H

#define NONE				(0 + 0)
#define OSCCLK				(0 + 1)


#define CLK_APM_BASE			(10)
#define MUX_APM_FUNCSRC			(CLK_APM_BASE + 0)
#define MUX_APM_FUNC			(CLK_APM_BASE + 1)
#define DOUT_CLK_APM_BOOST		(CLK_APM_BASE + 2)
#define DOUT_CLK_APM_USI0_UART		(CLK_APM_BASE + 3)
#define DOUT_CLK_APM_USI1_UART		(CLK_APM_BASE + 4)
#define DOUT_CLK_APM_USI0_USI		(CLK_APM_BASE + 5)


#define CLK_AUR_BASE			(20)
#define UMUX_CLKCMU_AUR_AURCTL		(CLK_AUR_BASE + 0)
#define UMUX_CLKCMU_AUR_NOC		(CLK_AUR_BASE + 1)
#define DOUT_CLK_AUR_NOCP		(CLK_AUR_BASE + 2)


#define CLK_TOP_BASE			(50)
#define GATE_DFTMUX_CMU_CIS_CLK0	(CLK_TOP_BASE + 0)
#define GATE_DFTMUX_CMU_CIS_CLK1	(CLK_TOP_BASE + 1)
#define GATE_DFTMUX_CMU_CIS_CLK2	(CLK_TOP_BASE + 2)
#define GATE_DFTMUX_CMU_CIS_CLK3	(CLK_TOP_BASE + 3)
#define GATE_DFTMUX_CMU_CIS_CLK4	(CLK_TOP_BASE + 4)
#define GATE_DFTMUX_CMU_CIS_CLK5	(CLK_TOP_BASE + 5)
#define GATE_DFTMUX_CMU_CIS_CLK6	(CLK_TOP_BASE + 6)
#define GATE_DFTMUX_CMU_CIS_CLK7	(CLK_TOP_BASE + 7)
#define VDOUT_CLK_TOP_HSI0_NOC		(CLK_TOP_BASE + 8)
#define CIS_CLK0			(CLK_TOP_BASE + 9)
#define CIS_CLK1			(CLK_TOP_BASE + 10)
#define CIS_CLK2			(CLK_TOP_BASE + 11)
#define CIS_CLK3			(CLK_TOP_BASE + 12)
#define CIS_CLK4			(CLK_TOP_BASE + 13)
#define CIS_CLK5			(CLK_TOP_BASE + 14)
#define CIS_CLK6			(CLK_TOP_BASE + 15)
#define CIS_CLK7			(CLK_TOP_BASE + 16)


#define CLK_NOCL0_BASE			(100)
#define UMUX_CLKCMU_NOCL0_NOC		(CLK_NOCL0_BASE + 0)
#define MUX_NOCL0_NOC_OPTION1		(CLK_NOCL0_BASE + 1)
#define DOUT_CLK_NOCL0_NOCP		(CLK_NOCL0_BASE + 2)


#define CLK_NOCL1A_BASE			(150)
#define UMUX_CLKCMU_NOCL1A_NOC		(CLK_NOCL1A_BASE + 0)
#define DOUT_CLK_NOCL1A_NOCP		(CLK_NOCL1A_BASE + 1)


#define CLK_NOCL1B_BASE			(200)
#define UMUX_CLKCMU_NOCL1B_NOC		(CLK_NOCL1B_BASE + 0)
#define DOUT_CLK_NOCL1B_NOCP		(CLK_NOCL1B_BASE + 1)


#define CLK_NOCL2A_BASE			(250)
#define UMUX_CLKCMU_NOCL2A_NOC		(CLK_NOCL2A_BASE + 0)
#define DOUT_CLK_NOCL2A_NOCP		(CLK_NOCL2A_BASE + 1)


#define CLK_EH_BASE			(300)
#define UMUX_CLKCMU_EH_NOC		(CLK_EH_BASE + 0)
#define UMUX_CLKCMU_EH_PLL_NOCL0	(CLK_EH_BASE + 1)
#define MUX_EH_NOC			(CLK_EH_BASE + 2)
#define DOUT_CLK_EH_NOCP		(CLK_EH_BASE + 3)


#define CLK_G3D_BASE			(350)
#define GATE_GPU			(CLK_G3D_BASE + 0)


#define CLK_DPU_BASE			(400)
#define UMUX_CLKCMU_DPU_NOC		(CLK_DPU_BASE + 0)
#define GATE_DPUF_DMA			(CLK_DPU_BASE + 1)
#define GATE_DPUF_DPP			(CLK_DPU_BASE + 2)
#define DOUT_CLK_DPU_NOCP		(CLK_DPU_BASE + 3)


#define CLK_DISP_BASE			(450)
#define UMUX_CLKCMU_DISP_NOC		(CLK_DISP_BASE + 0)
#define GATE_DPUB			(CLK_DISP_BASE + 1)
#define DOUT_CLK_DISP_NOCP		(CLK_DISP_BASE + 2)


#define CLK_G2D_BASE			(500)
#define UMUX_CLKCMU_G2D_G2D		(CLK_G2D_BASE + 0)
#define UMUX_CLKCMU_G2D_MSCL		(CLK_G2D_BASE + 1)
#define GATE_G2D			(CLK_G2D_BASE + 2)
#define GATE_JPEG			(CLK_G2D_BASE + 3)
#define DOUT_CLK_G2D_NOCP		(CLK_G2D_BASE + 4)


#define CLK_HSI0_BASE			(550)
#define UMUX_CLKCMU_HSI0_TCXO		(CLK_HSI0_BASE + 0)
#define MUX_HSI0_USB20_REF		(CLK_HSI0_BASE + 1)
#define UMUX_CLKCMU_HSI0_USB31DRD	(CLK_HSI0_BASE + 2)
#define UMUX_CLKCMU_HSI0_USB20		(CLK_HSI0_BASE + 3)
#define MUX_HSI0_USB31DRD		(CLK_HSI0_BASE + 4)
#define UMUX_CLKCMU_HSI0_NOC		(CLK_HSI0_BASE + 5)
#define UMUX_CLKCMU_HSI0_ALT		(CLK_HSI0_BASE + 6)
#define MUX_HSI0_NOC			(CLK_HSI0_BASE + 7)
#define UMUX_CLKCMU_HSI0_DPGTC		(CLK_HSI0_BASE + 8)
#define GATE_USB31DRD_SLV_LINK		(CLK_HSI0_BASE + 9)
#define DOUT_CLK_HSI0_USB31DRD		(CLK_HSI0_BASE + 10)


#define CLK_HSI1_BASE			(600)
#define UMUX_CLKCMU_HSI1_NOC		(CLK_HSI1_BASE + 0)
#define UMUX_CLKCMU_HSI1_PCIE		(CLK_HSI1_BASE + 1)
#define GATE_PCIE_GEN4_0_DBG_1		(CLK_HSI1_BASE + 2)
#define GATE_PCIE_GEN4_0_AXI_1		(CLK_HSI1_BASE + 3)
#define GATE_PCIE_GEN4_0_APB_1		(CLK_HSI1_BASE + 4)
#define GATE_PCIE_GEN4_0_SCLK_1		(CLK_HSI1_BASE + 5)
#define GATE_PCIE_GEN4_0_PCS_APB	(CLK_HSI1_BASE + 6)
#define GATE_PCIE_GEN4_0_PMA_APB	(CLK_HSI1_BASE + 7)
#define GATE_PCIE_GEN4_0_DBG_2		(CLK_HSI1_BASE + 8)
#define GATE_PCIE_GEN4_0_AXI_2		(CLK_HSI1_BASE + 9)
#define GATE_PCIE_GEN4_0_APB_2		(CLK_HSI1_BASE + 10)
#define GATE_PCIE_GEN4_0_UDBG		(CLK_HSI1_BASE + 11)


#define CLK_HSI2_BASE			(650)
#define UMUX_CLKCMU_HSI2_NOC		(CLK_HSI2_BASE + 0)
#define UMUX_CLKCMU_HSI2_PCIE		(CLK_HSI2_BASE + 1)
#define UMUX_CLKCMU_HSI2_UFS_EMBD	(CLK_HSI2_BASE + 2)
#define UMUX_CLKCMU_HSI2_MMC_CARD	(CLK_HSI2_BASE + 3)
#define GATE_MMC_CARD			(CLK_HSI2_BASE + 4)
#define GATE_PCIE_GEN4_1_AXI_1		(CLK_HSI2_BASE + 5)
#define GATE_PCIE_GEN4_1_APB_1		(CLK_HSI2_BASE + 6)
#define GATE_PCIE_GEN4_1_DBG_1		(CLK_HSI2_BASE + 7)
#define GATE_PCIE_GEN4_1_PCS_APB	(CLK_HSI2_BASE + 8)
#define GATE_PCIE_GEN4_1_SCLK_1		(CLK_HSI2_BASE + 9)
#define GATE_PCIE_GEN4_1_PMA_APB	(CLK_HSI2_BASE + 10)
#define GATE_PCIE_GEN4_1_AXI_2		(CLK_HSI2_BASE + 11)
#define GATE_PCIE_GEN4_1_DBG_2		(CLK_HSI2_BASE + 12)
#define GATE_PCIE_GEN4_1_APB_2		(CLK_HSI2_BASE + 13)
#define GATE_PCIE_GEN4_1_UDBG		(CLK_HSI2_BASE + 14)
#define GATE_UFS_EMBD			(CLK_HSI2_BASE + 15)
#define GATE_UFS_EMBD_FMP		(CLK_HSI2_BASE + 16)
#define DOUT_CLKCMU_HSI2_MMC_CARD	(CLK_HSI2_BASE + 17)
#define UFS_EMBD			(CLK_HSI2_BASE + 18)


#define CLK_CSIS_BASE			(700)
#define UMUX_CLKCMU_CSIS_NOC		(CLK_CSIS_BASE + 0)
#define DOUT_CLK_CSIS_NOCP		(CLK_CSIS_BASE + 1)


#define CLK_PDP_BASE			(750)
#define UMUX_CLKCMU_PDP_NOC		(CLK_PDP_BASE + 0)
#define UMUX_CLKCMU_PDP_VRA		(CLK_PDP_BASE + 1)
#define DOUT_CLK_PDP_NOCP		(CLK_PDP_BASE + 2)


#define CLK_IPP_BASE			(800)
#define UMUX_CLKCMU_IPP_NOC		(CLK_IPP_BASE + 0)
#define DOUT_CLK_IPP_NOCP		(CLK_IPP_BASE + 1)


#define CLK_G3AA_BASE			(850)
#define UMUX_CLKCMU_G3AA_G3AA		(CLK_G3AA_BASE + 0)
#define DOUT_CLK_G3AA_NOCP		(CLK_G3AA_BASE + 1)


#define CLK_ITP_BASE			(900)
#define UMUX_CLKCMU_ITP_NOC		(CLK_ITP_BASE + 0)
#define DOUT_CLK_ITP_NOCP		(CLK_ITP_BASE + 1)


#define CLK_DNS_BASE			(950)
#define UMUX_CLKCMU_DNS_NOC		(CLK_DNS_BASE + 0)
#define DOUT_CLK_DNS_NOCP		(CLK_DNS_BASE + 1)


#define CLK_TNR_BASE			(1000)
#define UMUX_CLKCMU_TNR_NOC		(CLK_TNR_BASE + 0)
#define DOUT_CLK_TNR_NOCP		(CLK_TNR_BASE + 1)


#define CLK_MCSC_BASE			(1050)
#define UMUX_CLKCMU_MCSC_ITSC		(CLK_MCSC_BASE + 0)
#define UMUX_CLKCMU_MCSC_MCSC		(CLK_MCSC_BASE + 1)
#define DOUT_CLK_MCSC_NOCP		(CLK_MCSC_BASE + 2)


#define CLK_GDC_BASE			(1100)
#define UMUX_CLKCMU_GDC_SCSC		(CLK_GDC_BASE + 0)
#define UMUX_CLKCMU_GDC_GDC0		(CLK_GDC_BASE + 1)
#define UMUX_CLKCMU_GDC_GDC1		(CLK_GDC_BASE + 2)
#define DOUT_CLK_GDC_NOCP		(CLK_GDC_BASE + 3)


#define CLK_MFC_BASE			(1150)
#define UMUX_CLKCMU_MFC_MFC		(CLK_MFC_BASE + 0)
#define DOUT_CLK_MFC_NOCP		(CLK_MFC_BASE + 1)
#define GATE_MFC			(CLK_MFC_BASE + 2)


#define CLK_MIF_BASE			(1200)
#define UMUX_MIF_DDRPHY2X		(CLK_MIF_BASE + 0)


#define CLK_MISC_BASE			(1250)
#define UMUX_CLKCMU_MISC_NOC		(CLK_MISC_BASE + 0)
#define UMUX_CLKCMU_MISC_SSS		(CLK_MISC_BASE + 1)
#define GATE_MCT			(CLK_MISC_BASE + 2)
#define DOUT_CLK_MISC_NOCP		(CLK_MISC_BASE + 3)
#define GATE_WDT_CL0			(CLK_MISC_BASE + 4)
#define GATE_WDT_CL1			(CLK_MISC_BASE + 5)
#define GATE_PDMA0			(CLK_MISC_BASE + 6)
#define GATE_PDMA1			(CLK_MISC_BASE + 7)
#define ATCLK				(CLK_MISC_BASE + 8)


#define CLK_PERIC0_BASE			(1300)
#define UMUX_CLKCMU_PERIC0_NOC		(CLK_PERIC0_BASE + 0)
#define UMUX_CLKCMU_PERIC0_USI0_UART	(CLK_PERIC0_BASE + 1)
#define GATE_PERIC0_TOP0_USI1_USI	(CLK_PERIC0_BASE + 2)
#define GATE_PERIC0_TOP0_USI2_USI	(CLK_PERIC0_BASE + 3)
#define GATE_PERIC0_TOP0_USI3_USI	(CLK_PERIC0_BASE + 4)
#define GATE_PERIC0_TOP0_USI4_USI	(CLK_PERIC0_BASE + 5)
#define GATE_PERIC0_TOP0_USI5_USI	(CLK_PERIC0_BASE + 6)
#define GATE_PERIC0_TOP0_USI6_USI	(CLK_PERIC0_BASE + 7)
#define GATE_PERIC0_TOP0_USI7_USI	(CLK_PERIC0_BASE + 8)
#define GATE_PERIC0_TOP0_USI8_USI	(CLK_PERIC0_BASE + 9)
#define GATE_PERIC0_TOP0_I3C1		(CLK_PERIC0_BASE + 10)
#define GATE_PERIC0_TOP0_I3C2		(CLK_PERIC0_BASE + 11)
#define GATE_PERIC0_TOP0_I3C3		(CLK_PERIC0_BASE + 12)
#define GATE_PERIC0_TOP0_I3C4		(CLK_PERIC0_BASE + 13)
#define GATE_PERIC0_TOP0_I3C5		(CLK_PERIC0_BASE + 14)
#define GATE_PERIC0_TOP0_I3C6		(CLK_PERIC0_BASE + 15)
#define GATE_PERIC0_TOP0_I3C7		(CLK_PERIC0_BASE + 16)
#define GATE_PERIC0_TOP0_I3C8		(CLK_PERIC0_BASE + 17)
#define GATE_PERIC0_TOP0_S1		(CLK_PERIC0_BASE + 18)
#define GATE_PERIC0_TOP0_S2		(CLK_PERIC0_BASE + 19)
#define GATE_PERIC0_TOP0_S3		(CLK_PERIC0_BASE + 20)
#define GATE_PERIC0_TOP0_S4		(CLK_PERIC0_BASE + 21)
#define GATE_PERIC0_TOP0_S5		(CLK_PERIC0_BASE + 22)
#define GATE_PERIC0_TOP0_S6		(CLK_PERIC0_BASE + 23)
#define GATE_PERIC0_TOP0_S7		(CLK_PERIC0_BASE + 24)
#define GATE_PERIC0_TOP0_S8		(CLK_PERIC0_BASE + 25)
#define GATE_PERIC0_TOP1_USI0_UART	(CLK_PERIC0_BASE + 26)
#define GATE_PERIC0_TOP1_USI14_USI	(CLK_PERIC0_BASE + 27)
#define VDOUT_CLK_PERIC0_USI0_UART	(CLK_PERIC0_BASE + 28)
#define VDOUT_CLK_PERIC0_USI1_USI	(CLK_PERIC0_BASE + 29)
#define VDOUT_CLK_PERIC0_USI2_USI	(CLK_PERIC0_BASE + 30)
#define VDOUT_CLK_PERIC0_USI3_USI	(CLK_PERIC0_BASE + 31)
#define VDOUT_CLK_PERIC0_USI4_USI	(CLK_PERIC0_BASE + 32)
#define VDOUT_CLK_PERIC0_USI5_USI	(CLK_PERIC0_BASE + 33)
#define VDOUT_CLK_PERIC0_USI6_USI	(CLK_PERIC0_BASE + 34)
#define VDOUT_CLK_PERIC0_USI7_USI	(CLK_PERIC0_BASE + 35)
#define VDOUT_CLK_PERIC0_USI8_USI	(CLK_PERIC0_BASE + 36)
#define VDOUT_CLK_PERIC0_USI14_USI	(CLK_PERIC0_BASE + 37)
#define VDOUT_CLK_PERIC0_I3C		(CLK_PERIC0_BASE + 38)


#define CLK_PERIC1_BASE			(1400)
#define UMUX_CLKCMU_PERIC1_NOC		(CLK_PERIC1_BASE + 0)
#define GATE_PERIC1_TOP0_USI0_USI	(CLK_PERIC1_BASE + 1)
#define GATE_PERIC1_TOP0_USI9_USI	(CLK_PERIC1_BASE + 2)
#define GATE_PERIC1_TOP0_USI10_USI	(CLK_PERIC1_BASE + 3)
#define GATE_PERIC1_TOP0_USI11_USI	(CLK_PERIC1_BASE + 4)
#define GATE_PERIC1_TOP0_USI12_USI	(CLK_PERIC1_BASE + 5)
#define GATE_PERIC1_TOP0_USI13_USI	(CLK_PERIC1_BASE + 6)
#define GATE_PERIC1_TOP0_USI15_USI	(CLK_PERIC1_BASE + 7)
#define GATE_PERIC1_TOP0_USI16_USI	(CLK_PERIC1_BASE + 8)
#define GATE_PERIC1_TOP0_I3C0		(CLK_PERIC1_BASE + 9)
#define GATE_PERIC1_TOP0_PWM		(CLK_PERIC1_BASE + 10)
#define GATE_PERIC1_TOP0_S		(CLK_PERIC1_BASE + 11)
#define VDOUT_CLK_PERIC1_USI0_USI	(CLK_PERIC1_BASE + 12)
#define VDOUT_CLK_PERIC1_USI9_USI	(CLK_PERIC1_BASE + 13)
#define VDOUT_CLK_PERIC1_USI10_USI	(CLK_PERIC1_BASE + 14)
#define VDOUT_CLK_PERIC1_USI11_USI	(CLK_PERIC1_BASE + 15)
#define VDOUT_CLK_PERIC1_USI12_USI	(CLK_PERIC1_BASE + 16)
#define VDOUT_CLK_PERIC1_USI13_USI	(CLK_PERIC1_BASE + 17)
#define VDOUT_CLK_PERIC1_USI15_USI	(CLK_PERIC1_BASE + 18)
#define VDOUT_CLK_PERIC1_USI16_USI	(CLK_PERIC1_BASE + 19)
#define VDOUT_CLK_PERIC1_I3C		(CLK_PERIC1_BASE + 20)


#define CLK_TPU_BASE			(1450)
#define UMUX_CLKCMU_TPU_TPU		(CLK_TPU_BASE + 0)
#define UMUX_CLKCMU_TPU_TPUCTL		(CLK_TPU_BASE + 1)
#define UMUX_CLKCMU_TPU_NOC		(CLK_TPU_BASE + 2)
#define UMUX_CLKCMU_TPU_UART		(CLK_TPU_BASE + 3)
#define MUX_TPU_TPU			(CLK_TPU_BASE + 4)
#define MUX_TPU_TPUCTL			(CLK_TPU_BASE + 5)
#define DOUT_CLK_TPU_TPU		(CLK_TPU_BASE + 6)
#define DOUT_CLK_TPU_TPUCTL		(CLK_TPU_BASE + 7)
#define DOUT_CLK_TPU_NOCP		(CLK_TPU_BASE + 8)


#define CLK_BO_BASE			(1500)
#define UMUX_CLKCMU_BO_NOC		(CLK_BO_BASE + 0)
#define DOUT_CLK_BO_NOCP		(CLK_BO_BASE + 1)


#define CLK_CLKOUT_BASE			(1550)
#define CLKOUT1				(CLK_CLKOUT_BASE + 0)
#define CLKOUT0				(CLK_CLKOUT_BASE + 1)

#define CLK_NR_CLKS			(1700)

#define ACPM_DVFS_MIF			(0x0B040000)
#define ACPM_DVFS_INT			(0x0B040001)
#define ACPM_DVFS_CPUCL0		(0x0B040002)
#define ACPM_DVFS_CPUCL1		(0x0B040003)
#define ACPM_DVFS_CPUCL2		(0x0B040004)
#define ACPM_DVFS_G3D			(0x0B040005)
#define ACPM_DVFS_G3DL2			(0x0B040006)
#define ACPM_DVFS_TPU			(0x0B040007)
#define ACPM_DVFS_INTCAM		(0x0B040008)
#define ACPM_DVFS_TNR			(0x0B040009)
#define ACPM_DVFS_CAM			(0x0B04000A)
#define ACPM_DVFS_MFC			(0x0B04000B)
#define ACPM_DVFS_DISP			(0x0B04000C)
#define ACPM_DVFS_BW			(0x0B04000D)

#define CAMERA_CLOCK_FAMILY_CAM		0
#define CAMERA_CLOCK_FAMILY_INTCAM	1
#define CAMERA_CLOCK_FAMILY_TNR		2

#endif /* _DT_BINDINGS_CLOCK_GS201_H */
