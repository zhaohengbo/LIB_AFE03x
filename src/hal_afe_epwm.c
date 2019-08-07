#include "F28x_Project.h"
#include "hal_afe_epwm.h"

void HAL_afe_epwmCfg()
{
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EPwm5Regs.ETSEL.bit.SOCAEN = 0;
	EPwm5Regs.ETSEL.bit.SOCBEN = 0;
	EPwm6Regs.ETSEL.bit.SOCAEN = 0;
	EPwm6Regs.ETSEL.bit.SOCBEN = 0;
	EPwm5Regs.ETSEL.bit.SOCASEL = 1;
	EPwm5Regs.ETSEL.bit.SOCBSEL = 2;
	EPwm6Regs.ETSEL.bit.SOCASEL = 2;
	EPwm6Regs.ETSEL.bit.SOCBSEL = 1;
	EPwm5Regs.ETPS.bit.SOCAPRD = 1;
	EPwm5Regs.ETPS.bit.SOCBPRD = 1;
	EPwm6Regs.ETPS.bit.SOCAPRD = 1;
	EPwm6Regs.ETPS.bit.SOCBPRD = 1;
	EPwm5Regs.TBPRD = HAL_afe_epwm_handle_s.socPrd;
	EPwm6Regs.TBPRD = HAL_afe_epwm_handle_s.socPrd;
	EPwm5Regs.TBCTL.bit.CTRMODE = 2;
	EPwm6Regs.TBCTL.bit.CTRMODE = 2;
	EPwm5Regs.TBPHS.bit.TBPHS = 0;
	EPwm5Regs.TBPHS.bit.TBPHSHR = 0;
	EPwm5Regs.TBCTL.bit.PHSEN = 0;
	EPwm5Regs.TBCTL.bit.SYNCOSEL = 1;
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;
	EPwm6Regs.TBPHS.bit.TBPHS = 0xF0;
	EPwm6Regs.TBPHS.bit.TBPHSHR = 0;
	EPwm6Regs.TBCTL.bit.PHSEN = 1;
	EPwm6Regs.TBCTL.bit.PHSDIR = 1;
	EPwm5Regs.TBCTL.bit.SYNCOSEL = 1;
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
}
