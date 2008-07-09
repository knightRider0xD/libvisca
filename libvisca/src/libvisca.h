/*
 * VISCA(tm) Camera Control Library
 * Copyright (C) 2002 Damien Douxchamps 
 *
 * Written by Damien Douxchamps <ddouxchamps@users.sf.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _LIBVISCA_H_
#define _LIBVISCA_H_

#if defined(_WIN32)||defined(WIN32)||defined(__WIN32__)
#define WIN
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#ifdef WIN
#include "Windows.h"
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

typedef unsigned char       UInt8_t; 
typedef unsigned short int  UInt16_t; 

/**********************/
/* Message formatting */
/**********************/

#define VISCA_COMMAND                    0x01
#define VISCA_INQUIRY                    0x09
#define VISCA_TERMINATOR                 0xFF

#define VISCA_CATEGORY_INTERFACE         0x00
#define VISCA_CATEGORY_CAMERA1           0x04
#define VISCA_CATEGORY_PAN_TILTER        0x06
#define VISCA_CATEGORY_CAMERA2           0x07

/* Known Vendor IDs */
#define VISCA_VENDOR_SONY  0x20

/* Known Model IDs. The manual can be taken from 
 * http://www.sony.net/Products/ISP/docu_soft/index.html
 */
#define VISCA_MODEL_IX47x    0x0401          /* from FCB-IX47, FCB-IX470 instruction list */
#define VISCA_MODEL_EX47xL   0x0402          /* from FCB-EX47L, FCB-EX470L instruction list */
#define VISCA_MODEL_IX10     0x0404          /* FCB-IX10, FCB-IX10P instruction list */

#define VISCA_MODEL_EX780    0x0411          /* from EX780S(P) tech-manual */

#define VISCA_MODEL_EX480A   0x0412          /* from EX48A/EX480A tech-manual */
#define VISCA_MODEL_EX480AP  0x0413
#define VISCA_MODEL_EX48A    0x0414
#define VISCA_MODEL_EX48AP   0x0414
#define VISCA_MODEL_EX45M    0x041E
#define VISCA_MODEL_EX45MCE  0x041F

#define VISCA_MODEL_IX47A    0x0418          /* from IX47A tech-manual */
#define VISCA_MODEL_IX47AP   0x0419
#define VISCA_MODEL_IX45A    0x041A
#define VISCA_MODEL_IX45AP   0x041B

#define VISCA_MODEL_IX10A    0x041C          /* from IX10A tech-manual */
#define VISCA_MODEL_IX10AP   0x041D

#define VISCA_MODEL_EX780B   0x0420          /* from EX78/EX780 tech-manual */
#define VISCA_MODEL_EX780BP  0x0421
#define VISCA_MODEL_EX78B    0x0422
#define VISCA_MODEL_EX78BP   0x0423

#define VISCA_MODEL_EX480B   0x0424          /* from EX48/EX480 tech-manual */
#define VISCA_MODEL_EX480BP  0x0425
#define VISCA_MODEL_EX48B    0x0426
#define VISCA_MODEL_EX48BP   0x0427

/* Commands/inquiries codes */
#define VISCA_POWER                      0x00
#define VISCA_DEVICE_INFO                0x02
#define VISCA_KEYLOCK                    0x17
#define VISCA_ID                         0x22
#define VISCA_ZOOM                       0x07
#define   VISCA_ZOOM_STOP                  0x00
#define   VISCA_ZOOM_TELE                  0x02
#define   VISCA_ZOOM_WIDE                  0x03
#define   VISCA_ZOOM_TELE_SPEED            0x20
#define   VISCA_ZOOM_WIDE_SPEED            0x30
#define VISCA_ZOOM_VALUE                 0x47
#define VISCA_ZOOM_FOCUS_VALUE           0x47
#define VISCA_DZOOM                      0x06
#define VISCA_FOCUS                      0x08
#define   VISCA_FOCUS_STOP                 0x00
#define   VISCA_FOCUS_FAR                  0x02
#define   VISCA_FOCUS_NEAR                 0x03
#define   VISCA_FOCUS_FAR_SPEED            0x20
#define   VISCA_FOCUS_NEAR_SPEED           0x30
#define VISCA_FOCUS_VALUE                0x48
#define VISCA_FOCUS_AUTO                 0x38
#define   VISCA_FOCUS_AUTO_MAN             0x10
#define VISCA_FOCUS_ONE_PUSH             0x18
#define   VISCA_FOCUS_ONE_PUSH_TRIG        0x01
#define   VISCA_FOCUS_ONE_PUSH_INF         0x02
#define VISCA_FOCUS_AUTO_SENSE           0x58
#define   VISCA_FOCUS_AUTO_SENSE_HIGH      0x02
#define   VISCA_FOCUS_AUTO_SENSE_LOW       0x03
#define VISCA_FOCUS_NEAR_LIMIT           0x28
#define VISCA_WB                         0x35
#define   VISCA_WB_AUTO                    0x00
#define   VISCA_WB_INDOOR                  0x01
#define   VISCA_WB_OUTDOOR                 0x02
#define   VISCA_WB_ONE_PUSH                0x03
#define   VISCA_WB_ATW                     0x04
#define   VISCA_WB_MANUAL                  0x05
#define   VISCA_WB_ONE_PUSH_TRIG           0x05
#define VISCA_RGAIN                      0x03
#define VISCA_RGAIN_VALUE                0x43
#define VISCA_BGAIN                      0x04
#define VISCA_BGAIN_VALUE                0x44
#define VISCA_AUTO_EXP                   0x39
#define   VISCA_AUTO_EXP_FULL_AUTO         0x00
#define   VISCA_AUTO_EXP_MANUAL            0x03
#define   VISCA_AUTO_EXP_SHUTTER_PRIORITY  0x0A
#define   VISCA_AUTO_EXP_IRIS_PRIORITY     0x0B
#define   VISCA_AUTO_EXP_GAIN_PRIORITY     0x0C
#define   VISCA_AUTO_EXP_BRIGHT            0x0D
#define   VISCA_AUTO_EXP_SHUTTER_AUTO      0x1A
#define   VISCA_AUTO_EXP_IRIS_AUTO         0x1B
#define   VISCA_AUTO_EXP_GAIN_AUTO         0x1C
#define VISCA_SLOW_SHUTTER               0x5A
#define   VISCA_SLOW_SHUTTER_AUTO          0x02
#define   VISCA_SLOW_SHUTTER_MANUAL        0x03
#define VISCA_SHUTTER                    0x0A
#define VISCA_SHUTTER_VALUE              0x4A
#define VISCA_IRIS                       0x0B
#define VISCA_IRIS_VALUE                 0x4B
#define VISCA_GAIN                       0x0C
#define VISCA_GAIN_VALUE                 0x4C
#define VISCA_BRIGHT                     0x0D
#define VISCA_BRIGHT_VALUE               0x4D
#define VISCA_EXP_COMP                   0x0E
#define VISCA_EXP_COMP_POWER             0x3E
#define VISCA_EXP_COMP_VALUE             0x4E
#define VISCA_BACKLIGHT_COMP             0x33
#define VISCA_APERTURE                   0x02
#define VISCA_APERTURE_VALUE             0x42
#define VISCA_ZERO_LUX                   0x01
#define VISCA_IR_LED                     0x31
#define VISCA_WIDE_MODE                  0x60
#define   VISCA_WIDE_MODE_OFF              0x00
#define   VISCA_WIDE_MODE_CINEMA           0x01
#define   VISCA_WIDE_MODE_16_9             0x02
#define VISCA_MIRROR                     0x61
#define VISCA_FREEZE                     0x62
#define VISCA_PICTURE_EFFECT             0x63
#define   VISCA_PICTURE_EFFECT_OFF         0x00
#define   VISCA_PICTURE_EFFECT_PASTEL      0x01
#define   VISCA_PICTURE_EFFECT_NEGATIVE    0x02
#define   VISCA_PICTURE_EFFECT_SEPIA       0x03
#define   VISCA_PICTURE_EFFECT_BW          0x04
#define   VISCA_PICTURE_EFFECT_SOLARIZE    0x05
#define   VISCA_PICTURE_EFFECT_MOSAIC      0x06
#define   VISCA_PICTURE_EFFECT_SLIM        0x07
#define   VISCA_PICTURE_EFFECT_STRETCH     0x08
#define VISCA_DIGITAL_EFFECT             0x64
#define   VISCA_DIGITAL_EFFECT_OFF         0x00
#define   VISCA_DIGITAL_EFFECT_STILL       0x01
#define   VISCA_DIGITAL_EFFECT_FLASH       0x02
#define   VISCA_DIGITAL_EFFECT_LUMI        0x03
#define   VISCA_DIGITAL_EFFECT_TRAIL       0x04
#define VISCA_DIGITAL_EFFECT_LEVEL       0x65
#define VISCA_MEMORY                     0x3F
#define   VISCA_MEMORY_RESET               0x00
#define   VISCA_MEMORY_SET                 0x01
#define   VISCA_MEMORY_RECALL              0x02
#define VISCA_DISPLAY                    0x15
#define   VISCA_DISPLAY_TOGGLE             0x10
#define VISCA_DATE_TIME_SET              0x70
#define VISCA_DATE_DISPLAY               0x71
#define VISCA_TIME_DISPLAY               0x72
#define VISCA_TITLE_DISPLAY              0x74
#define   VISCA_TITLE_DISPLAY_CLEAR        0x00
#define VISCA_TITLE_SET                  0x73
#define   VISCA_TITLE_SET_PARAMS           0x00
#define   VISCA_TITLE_SET_PART1            0x01
#define   VISCA_TITLE_SET_PART2            0x02
#define VISCA_IRRECEIVE                   0x08
#define   VISCA_IRRECEIVE_ON              0x02
#define   VISCA_IRRECEIVE_OFF             0x03
#define   VISCA_IRRECEIVE_ONOFF           0x10
#define VISCA_PT_DRIVE                     0x01
#define   VISCA_PT_DRIVE_HORIZ_LEFT        0x01
#define   VISCA_PT_DRIVE_HORIZ_RIGHT       0x02
#define   VISCA_PT_DRIVE_HORIZ_STOP        0x03
#define   VISCA_PT_DRIVE_VERT_UP           0x01
#define   VISCA_PT_DRIVE_VERT_DOWN         0x02
#define   VISCA_PT_DRIVE_VERT_STOP         0x03
#define VISCA_PT_ABSOLUTE_POSITION         0x02
#define VISCA_PT_RELATIVE_POSITION         0x03
#define VISCA_PT_HOME                      0x04
#define VISCA_PT_RESET                     0x05
#define VISCA_PT_LIMITSET                  0x07
#define   VISCA_PT_LIMITSET_SET            0x00
#define   VISCA_PT_LIMITSET_CLEAR          0x01
#define     VISCA_PT_LIMITSET_SET_UR       0x01
#define     VISCA_PT_LIMITSET_SET_DL       0x00
#define VISCA_PT_DATASCREEN                0x06
#define   VISCA_PT_DATASCREEN_ON           0x02
#define   VISCA_PT_DATASCREEN_OFF          0x03
#define   VISCA_PT_DATASCREEN_ONOFF        0x10

#define VISCA_PT_VIDEOSYSTEM_INQ           0x23
#define VISCA_PT_MODE_INQ                  0x10
#define VISCA_PT_MAXSPEED_INQ              0x11
#define VISCA_PT_POSITION_INQ              0x12
#define VISCA_PT_DATASCREEN_INQ            0x06

/*****************/
/* D30/D31 CODES */
/*****************/
#define VISCA_WIDE_CON_LENS		   0x26
#define   VISCA_WIDE_CON_LENS_SET          0x00

#define VISCA_AT_MODE                      0x01
#define   VISCA_AT_ONOFF                   0x10
#define VISCA_AT_AE                        0x02
#define VISCA_AT_AUTOZOOM                  0x03
#define VISCA_ATMD_FRAMEDISPLAY            0x04
#define VISCA_AT_FRAMEOFFSET               0x05
#define VISCA_ATMD_STARTSTOP               0x06
#define VISCA_AT_CHASE                     0x07
#define   VISCA_AT_CHASE_NEXT              0x10

#define VISCA_MD_MODE                      0x08
#define   VISCA_MD_ONOFF                   0x10
#define VISCA_MD_FRAME                     0x09
#define VISCA_MD_DETECT                    0x0A

#define VISCA_MD_ADJUST                    0x00
#define   VISCA_MD_ADJUST_YLEVEL           0x0B
#define   VISCA_MD_ADJUST_HUELEVEL         0x0C
#define   VISCA_MD_ADJUST_SIZE             0x0D
#define   VISCA_MD_ADJUST_DISPTIME         0x0F
#define   VISCA_MD_ADJUST_REFTIME          0x0B
#define   VISCA_MD_ADJUST_REFMODE          0x10

#define VISCA_AT_ENTRY                     0x15
#define VISCA_AT_LOSTINFO                  0x20
#define VISCA_MD_LOSTINFO                  0x21
#define VISCA_ATMD_LOSTINFO1               0x20
#define VISCA_ATMD_LOSTINFO2               0x07

#define VISCA_MD_MEASURE_MODE_1            0x27
#define VISCA_MD_MEASURE_MODE_2            0x28

#define VISCA_ATMD_MODE                    0x22
#define VISCA_AT_MODE_QUERY                0x23
#define VISCA_MD_MODE_QUERY                0x24
#define VISCA_MD_REFTIME_QUERY             0x11
#define VISCA_AT_POSITION                  0x20
#define VISCA_MD_POSITION                  0x21

/***************/
/* ERROR CODES */
/***************/

/* these two are defined by me, not by the specs. */
#define VISCA_SUCCESS                    0x00
#define VISCA_FAILURE                    0xFF

/* specs errors: */
#define VISCA_ERROR_MESSAGE_LENGTH       0x01
#define VISCA_ERROR_SYNTAX               0x02
#define VISCA_ERROR_CMD_BUFFER_FULL      0x03
#define VISCA_ERROR_CMD_CANCELLED        0x04
#define VISCA_ERROR_NO_SOCKET            0x05
#define VISCA_ERROR_CMD_NOT_EXECUTABLE   0x41

/* Generic definitions */
#define VISCA_ON                         0x02
#define VISCA_OFF                        0x03
#define VISCA_RESET                      0x00
#define VISCA_UP                         0x02
#define VISCA_DOWN                       0x03

/* serial wait (us)*/
#define SERIAL_WAIT                    100000 
#define VISCA_INPUT_BUFFER_SIZE          1024

/* response types */
#define VISCA_RESPONSE_CLEAR             0x40
#define VISCA_RESPONSE_ADDRESS           0x30
#define VISCA_RESPONSE_ACK               0x40
#define VISCA_RESPONSE_COMPLETED         0x50
#define VISCA_RESPONSE_ERROR             0x60

#ifdef __cplusplus
extern "C" {
#endif

/* INTERFACE STRUCTURE */
typedef struct _interface
{
  // RS232 data:
#ifdef WIN
  HANDLE port_fd;
#else
  int port_fd;
  struct termios options;
#endif
  int baud;

  // VISCA data:
  int address;
  int broadcast;

  // RS232 input buffer
  unsigned char ibuf[VISCA_INPUT_BUFFER_SIZE];
  int bytes;
  int type;

} VISCAInterface_t;


/* CAMERA STRUCTURE */
typedef struct _camera
{
  // VISCA data:
  int address;
  
  // camera info:
  unsigned int vendor;
  unsigned int model;
  unsigned int rom_version;
  unsigned int socket_num;

} VISCACamera_t;


/* TITLE STRUCTURE */
typedef struct _title
{
  unsigned int vposition;
  unsigned int hposition;
  unsigned int color;
  unsigned int blink;
  unsigned char title[20];

} VISCATitleData_t;

typedef struct _packet
{
  unsigned char bytes[32];
  unsigned int length;
} VISCAPacket_t;

/* GENERAL FUNCTIONS */

unsigned int
VISCA_open_serial(VISCAInterface_t *interface, char *device_name);

unsigned int
VISCA_close_serial(VISCAInterface_t *interface);

unsigned int
VISCA_set_address(VISCAInterface_t *interface, int *camera_num);

unsigned int
VISCA_clear(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_get_camera_info(VISCAInterface_t *interface, VISCACamera_t *camera);

/* COMMANDS */

unsigned int
VISCA_set_power(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_get_info(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_keylock(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_camera_id(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t id);

unsigned int
VISCA_set_zoom_tele(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_zoom_wide(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_zoom_stop(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_zoom_tele_speed(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int speed);

unsigned int
VISCA_set_zoom_wide_speed(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int speed);

unsigned int
VISCA_set_zoom_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int zoom);

unsigned int
VISCA_set_zoom_and_focus_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int zoom, unsigned int focus);

unsigned int
VISCA_set_dzoom(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int power);

unsigned int
VISCA_set_focus_far(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_near(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_stop(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_far_speed(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int speed);

unsigned int
VISCA_set_focus_near_speed(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int speed);

unsigned int
VISCA_set_focus_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int focus);

unsigned int
VISCA_set_focus_auto(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_focus_one_push(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_infinity(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_autosense_high(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_autosense_low(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_focus_near_limit(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int limit);

unsigned int
VISCA_set_whitebal_mode(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int mode);

unsigned int
VISCA_set_whitebal_one_push(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_rgain_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_rgain_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_rgain_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_rgain_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_bgain_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bgain_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bgain_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bgain_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_shutter_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_shutter_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_shutter_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_shutter_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_iris_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_iris_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_iris_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_iris_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_gain_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_gain_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_gain_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_gain_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_bright_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bright_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bright_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_bright_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_aperture_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_aperture_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_aperture_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_aperture_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_exp_comp_up(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_exp_comp_down(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_exp_comp_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_exp_comp_value(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int value);

unsigned int
VISCA_set_exp_comp_power(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_auto_exp_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t mode);

unsigned int
VISCA_set_slow_shutter_auto(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_backlight_comp(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_zero_lux_shot(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_ir_led(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_wide_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t mode);

unsigned int
VISCA_set_mirror(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_freeze(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_picture_effect(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t mode);

unsigned int
VISCA_set_digital_effect(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t mode);

unsigned int
VISCA_set_digital_effect_level(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t level);

unsigned int
VISCA_memory_set(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t channel);

unsigned int
VISCA_memory_recall(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t channel);

unsigned int
VISCA_memory_reset(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t channel);

unsigned int
VISCA_set_display(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_date_time(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute);

unsigned int
VISCA_set_date_display(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_time_display(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_title_display(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_title_clear(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_title_params(VISCAInterface_t *interface, VISCACamera_t *camera, VISCATitleData_t *title);

unsigned int
VISCA_set_title(VISCAInterface_t *interface, VISCACamera_t *camera, VISCATitleData_t *title);
unsigned int
VISCA_set_irreceive_on(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_irreceive_off(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_irreceive_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

/*  pan_speed should be in the range 01 - 18.
    tilt_speed should be in the range 01 - 14 */

unsigned int
VISCA_set_pantilt_up(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_down(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_left(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_right(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_upleft(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_upright(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_downleft(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_downright(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

unsigned int
VISCA_set_pantilt_stop(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed);

/*  pan_speed should be in the range 01 - 18.
    tilt_speed should be in the range 01 - 14
    pan_position should be in the range -880 - 880 (0xFC90 - 0x370) 
    tilt_position should be in range -300 - 300 (0xFED4 - 0x12C)  */
unsigned int
VISCA_set_pantilt_absolute_position(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed, int pan_position, int tilt_position);

unsigned int
VISCA_set_pantilt_relative_position(VISCAInterface_t *interface, VISCACamera_t *camera, unsigned int pan_speed, unsigned int tilt_speed, int pan_position, int tilt_position);

unsigned int
VISCA_set_pantilt_home(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_pantilt_reset(VISCAInterface_t *interface, VISCACamera_t *camera);

/*  pan_limit should be in the range -880 - 880 (0xFC90 - 0x370) 
    tilt_limit should be in range -300 - 300 (0xFED4 - 0x12C)  */
unsigned int
VISCA_set_pantilt_limit_upright(VISCAInterface_t *interface, VISCACamera_t *camera, int pan_limit, int tilt_limit);

unsigned int
VISCA_set_pantilt_limit_downleft(VISCAInterface_t *interface, VISCACamera_t *camera, int pan_limit, int tilt_limit);

unsigned int
VISCA_set_pantilt_limit_downleft_clear(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_pantilt_limit_upright_clear(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_datascreen_on(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_datascreen_off(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_datascreen_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

/* INQUIRIES */

unsigned int
VISCA_get_power(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_dzoom(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_zoom_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_focus_auto(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_focus_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_focus_auto_sense(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_focus_near_limit(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_whitebal_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_rgain_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_bgain_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_auto_exp_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_slow_shutter_auto(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_shutter_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_iris_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_gain_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_bright_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_exp_comp_power(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_exp_comp_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_backlight_comp(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_aperture_value(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_zero_lux_shot(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_ir_led(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_wide_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_mirror(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_freeze(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_picture_effect(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_digital_effect(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *mode);

unsigned int
VISCA_get_digital_effect_level(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_memory(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *channel);

unsigned int
VISCA_get_display(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_id(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *id);

unsigned int
VISCA_get_videosystem(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *system);

unsigned int
VISCA_get_pantilt_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *status);

unsigned int
VISCA_get_pantilt_maxspeed(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *max_pan_speed, UInt8_t *max_tilt_speed);

unsigned int
VISCA_get_pantilt_position(VISCAInterface_t *interface, VISCACamera_t *camera, int *pan_position, int *tilt_position);

unsigned int
VISCA_get_datascreen(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *status);

/* SPECIAL FUNCTIONS FOR D30/31 */
unsigned int
VISCA_set_wide_con_lens(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_mode_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_ae_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_ae(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_autozoom_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_autozoom(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_atmd_framedisplay_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_atmd_framedisplay(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_frameoffset_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_frameoffset(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_atmd_startstop(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_chase(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_chase_next(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_mode_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_frame(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_detect(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_at_entry(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_at_lostinfo(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_lostinfo(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_adjust_ylevel(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_adjust_huelevel(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_adjust_size(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_adjust_disptime(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_adjust_refmode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_adjust_reftime(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_measure_mode1_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_measure_mode1(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_set_md_measure_mode2_onoff(VISCAInterface_t *interface, VISCACamera_t *camera);

unsigned int
VISCA_set_md_measure_mode2(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t power);

unsigned int
VISCA_get_keylock(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_wide_con_lens(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_atmd_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_at_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_at_entry(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_mode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt16_t *value);

unsigned int
VISCA_get_md_ylevel(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_huelevel(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_size(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_disptime(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_refmode(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_md_reftime(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *power);

unsigned int
VISCA_get_at_obj_pos(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *xpos, UInt8_t *ypos, UInt8_t *status);

unsigned int
VISCA_get_md_obj_pos(VISCAInterface_t *interface, VISCACamera_t *camera, UInt8_t *xpos, UInt8_t *ypos, UInt8_t *status);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif
