/*-----------------------------------------------------------------------------
 * Hardware-dependent code for usb_jtag
 *-----------------------------------------------------------------------------
 * Copyright (C) 2007 Kolja Waschk, ixo.de
 *-----------------------------------------------------------------------------
 * This code is part of usbjtag. usbjtag is free software; you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version. usbjtag is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.  You should have received a
 * copy of the GNU General Public License along with this program in the file
 * COPYING; if not, write to the Free Software Foundation, Inc., 51 Franklin
 * St, Fifth Floor, Boston, MA  02110-1301  USA
 *-----------------------------------------------------------------------------
 */

#include "hw_basic.h"

void HW_Init(void)
{
   /* The following code depends on your actual circuit design.
      Make required changes _before_ you try the code! */

   // set the CPU clock to 48MHz, enable clock output to FPGA
   CPUCS = bmCLKOE | bmCLKSPD1;

   // Use internal 48 MHz, enable output, use "Port" mode for all pins
   IFCONFIG = bmIFCLKSRC | bm3048MHZ | bmIFCLKOE;

   // power on the onboard FPGA and all other VCCs, de-assert RESETN
   IOE = 0x1F;
   OEE = 0x1F;
   mdelay(500); // wait for supply to come up
}

void ShiftOut(unsigned char c)
{
  (void)c;
  _asm
        MOV  A,DPL
        ;; Bit0
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        ;; Bit1
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit2
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit3
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit4
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit5
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit6
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        ;; Bit7
        RRC  A
        CLR  _TCK
        MOV  _TDI,C
        SETB _TCK
        NOP 
        CLR  _TCK
        ret
  _endasm;
}

/*
;; For ShiftInOut, the timing is a little more
;; critical because we have to read _TDO/shift/set _TDI
;; when _TCK is low. But 20% duty cycle at 48/4/5 MHz
;; is just like 50% at 6 Mhz, and that's still acceptable
*/

unsigned char ShiftInOut(unsigned char c)
{
  _asm
        MOV  A,DPL

        ;; Bit0
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit1
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit2
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit3
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit4
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit5
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit6
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit7
        MOV  C,_TDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK

        MOV  DPL,A
        ret
  _endasm;
  return c;
}

#ifdef HAVE_AS_MODE

unsigned char ShiftInOut_AS(unsigned char c)
{
  _asm
        MOV  A,DPL

        ;; Bit0
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit1
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit2
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit3
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit4
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit5
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit6
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK
        ;; Bit7
        MOV  C,_ASDO
        RRC  A
        MOV  _TDI,C
        SETB _TCK
        CLR  _TCK

        MOV  DPL,A
        ret
  _endasm;
  return c;
}

#endif /* HAVE_ASMODE */



