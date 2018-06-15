#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# 

if [ -z "$PATH" ]; then
  PATH=/home/justin/software/vivado/Xilinx/SDK/2018.1/bin:/home/justin/software/vivado/Xilinx/Vivado/2018.1/ids_lite/ISE/bin/lin64:/home/justin/software/vivado/Xilinx/Vivado/2018.1/bin
else
  PATH=/home/justin/software/vivado/Xilinx/SDK/2018.1/bin:/home/justin/software/vivado/Xilinx/Vivado/2018.1/ids_lite/ISE/bin/lin64:/home/justin/software/vivado/Xilinx/Vivado/2018.1/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=/home/justin/software/vivado/Xilinx/Vivado/2018.1/ids_lite/ISE/lib/lin64
else
  LD_LIBRARY_PATH=/home/justin/software/vivado/Xilinx/Vivado/2018.1/ids_lite/ISE/lib/lin64:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='/home/justin/vivado/driver_alert_system_zedboard/driver_alert_system_zedboard.runs/design_1_rst_ps7_0_50M_1_synth_1'
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

EAStep vivado -log design_1_rst_ps7_0_50M_1.vds -m64 -product Vivado -mode batch -messageDb vivado.pb -notrace -source design_1_rst_ps7_0_50M_1.tcl
