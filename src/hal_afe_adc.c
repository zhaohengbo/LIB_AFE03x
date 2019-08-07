#include "F28x_Project.h"
#include "hal_afe_adc.h"

void HAL_afe_adcCfg()
{
	InitAdc();
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;//ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;//Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 1;//Enabled ADCINT1 Continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL	= 3;
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;
	AdcRegs.ADCSOC1CTL.bit.CHSEL = 0;
	AdcRegs.ADCSOC2CTL.bit.CHSEL = 0;
	AdcRegs.ADCSOC3CTL.bit.CHSEL = 0;
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 13;
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 15;
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL = 14;
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL = 16;
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC1CTL.bit.ACQPS = 6;//set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC2CTL.bit.ACQPS = 6;//set SOC2 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC3CTL.bit.ACQPS = 6;//set SOC3 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	EDIS;
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;// Enable INT 1.1 in the PIE
}

void HAL_afe_adcStart()
{
	EPwm5Regs.ETSEL.bit.SOCAEN = 1;
	EPwm5Regs.ETSEL.bit.SOCBEN = 1;
	EPwm6Regs.ETSEL.bit.SOCAEN = 1;
	EPwm6Regs.ETSEL.bit.SOCBEN = 1;
}

void HAL_afe_adcStop()
{
	EPwm5Regs.ETSEL.bit.SOCAEN = 0;
	EPwm5Regs.ETSEL.bit.SOCBEN = 0;
	EPwm6Regs.ETSEL.bit.SOCAEN = 0;
	EPwm6Regs.ETSEL.bit.SOCBEN = 0;
}
