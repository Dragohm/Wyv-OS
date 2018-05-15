/****************************************************************************
 * config/imxrt1050-evk/src/imxrt_flexspi_nor_flash.c
 *
 *   Copyright (C) 2018 Gregory Nutt. All rights reserved.
 *   Author: Ivan Ucherdzhiev <ivanucherdjiev@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*******************************************************************************
 * Included Files
 ******************************************************************************/

#include "imxrt_flexspi_nor_flash.h"

/*******************************************************************************
 * Public Data
 ******************************************************************************/

__attribute__((section(".boot_hdr.conf")))
const struct flexspi_nor_config_s hyperflash_config =
{
  .mem_config =
  {
    .tag                    = FLEXSPI_CFG_BLK_TAG,
    .version                = FLEXSPI_CFG_BLK_VERSION,
    .read_sample_clksrc     = FLASH_READ_SAMPLE_CLK_EXTERNALINPUT_FROM_DQSPAD,
    .cs_hold_time           = 3u,
    .cs_setup_time          = 3u,
    .column_address_width   = 3u,

    /* Enable DDR mode, Wordaddassable, Safe configuration, Differential clock */

    .controller_misc_option = (1u << FLEXSPIMISC_OFFSET_DDR_MODE_EN) |
                              (1u << FLEXSPIMISC_OFFSET_WORD_ADDRESSABLE_EN) |
                              (1u << FLEXSPIMISC_OFFSET_SAFECONFIG_FREQ_EN) |
                              (1u << FLEXSPIMISC_OFFSET_DIFFCLKEN),
    .sflash_pad_type        = SERIAL_FLASH_8PADS,
    .serial_clk_freq        = FLEXSPI_SERIAL_CLKFREQ_133MHz,
    .sflash_a1size          = 64u * 1024u * 1024u,
    .data_valid_time        = {16u, 16u},
    .lookup_table           =
    {
      /* Read LUTs */

      FLEXSPI_LUT_SEQ(CMD_DDR, FLEXSPI_8PAD, 0xA0, RADDR_DDR, FLEXSPI_8PAD, 0x18),
      FLEXSPI_LUT_SEQ(CADDR_DDR, FLEXSPI_8PAD, 0x10, DUMMY_DDR, FLEXSPI_8PAD, 0x06),
      FLEXSPI_LUT_SEQ(READ_DDR, FLEXSPI_8PAD, 0x04, STOP, FLEXSPI_1PAD, 0x0),
    },
  },
  .page_size                = 512u,
  .sector_size              = 256u * 1024u,
  .blocksize                = 256u * 1024u,
  .is_uniform_blocksize     = 1,
};
