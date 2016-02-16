/**
 * Copyright (c) 2016 Ross Cairns <ross@electricglen.com>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _LIB_PIDEE_H
#define _LIB_PIDEE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <string.h>

#include <wiringPi.h>

/* Version */
#define LIB_PIDEE_VERSION "0.0.1"

/* Feature Type */

typedef enum {
    PIDEE_FEATURE_DIP,
    PIDEE_FEATURE_BUTTON,
    PIDEE_FEATURE_LED
} pidee_feature_t;

/* Features */

typedef struct pidee_feature {
    const char *name;
    pidee_feature_t feature_type;
    int bcm_pin;
    void(*interupt_handler)(pidee_feature);
} pidee_feature;


// Pin mapping source: http://pinout.xyz/pinout/
pidee_feature pidee_feature_button     = { "button",     PIDEE_FEATURE_BUTTON, 18 /* physical pin: 12 */ };
pidee_feature pidee_feature_dip_1      = { "dip.1",      PIDEE_FEATURE_DIP,    6  /* physical pin: 31 */ };
pidee_feature pidee_feature_dip_2      = { "dip.2",      PIDEE_FEATURE_DIP,    5  /* physical pin: 29 */ };
pidee_feature pidee_feature_dip_3      = { "dip.3",      PIDEE_FEATURE_DIP,    25 /* physical pin: 22 */ };
pidee_feature pidee_feature_dip_4      = { "dip.4",      PIDEE_FEATURE_DIP,    24 /* physical pin: 18 */ };
pidee_feature pidee_feature_dip_5      = { "dip.5",      PIDEE_FEATURE_DIP,    23 /* physical pin: 16 */ };
pidee_feature pidee_feature_dip_8      = { "dip.6",      PIDEE_FEATURE_DIP,    17 /* physical pin: 11 */ };
pidee_feature pidee_feature_dip_7      = { "dip.7",      PIDEE_FEATURE_DIP,    27 /* 21 on pi rev 1. physical pin: 13 */ };
pidee_feature pidee_feature_dip_6      = { "dip.8",      PIDEE_FEATURE_DIP,    22 /* physical pin: 15 */ };
pidee_feature pidee_feature_led_red    = { "led.red",    PIDEE_FEATURE_LED,    13 /* physical pin: 33 */ };
pidee_feature pidee_feature_led_green  = { "led.green",  PIDEE_FEATURE_LED,    12 /* physical pin: 32 */ };
pidee_feature pidee_feature_led_yellow = { "led.yellow", PIDEE_FEATURE_LED,    19 /* physical pin: 35 */ };

/* Interupts */

void pidee_button_interupt() { if ( pidee_feature_button.interupt_handler != NULL ) { pidee_feature_button.interupt_handler( pidee_feature_button ); } };
void pidee_dip_1_interupt()  { if ( pidee_feature_dip_1.interupt_handler  != NULL ) { pidee_feature_dip_1.interupt_handler( pidee_feature_dip_1 ); } };
void pidee_dip_2_interupt()  { if ( pidee_feature_dip_2.interupt_handler  != NULL ) { pidee_feature_dip_2.interupt_handler( pidee_feature_dip_2 ); }};
void pidee_dip_3_interupt()  { if ( pidee_feature_dip_3.interupt_handler  != NULL ) { pidee_feature_dip_3.interupt_handler( pidee_feature_dip_3 ); }};
void pidee_dip_4_interupt()  { if ( pidee_feature_dip_4.interupt_handler  != NULL ) { pidee_feature_dip_4.interupt_handler( pidee_feature_dip_4 ); }};
void pidee_dip_5_interupt()  { if ( pidee_feature_dip_5.interupt_handler  != NULL ) { pidee_feature_dip_5.interupt_handler( pidee_feature_dip_5 ); }};
void pidee_dip_6_interupt()  { if ( pidee_feature_dip_6.interupt_handler  != NULL ) { pidee_feature_dip_6.interupt_handler( pidee_feature_dip_6 ); }};
void pidee_dip_7_interupt()  { if ( pidee_feature_dip_7.interupt_handler  != NULL ) { pidee_feature_dip_7.interupt_handler( pidee_feature_dip_7 ); }};
void pidee_dip_8_interupt()  { if ( pidee_feature_dip_8.interupt_handler  != NULL ) { pidee_feature_dip_8.interupt_handler( pidee_feature_dip_8 ); }};

/* Setup/Read/Write  */

void pidee_system_command( const char *head, int pin, const char *tail ) {
    char str[100];
    sprintf( str, "%s %d %s", head, pin, tail );
    system( str );
}

void pidee_feature_setup( pidee_feature *feature ) {
    if ( feature->feature_type == PIDEE_FEATURE_BUTTON || feature->feature_type == PIDEE_FEATURE_DIP ) {
        pidee_system_command( "gpio export ", feature->bcm_pin, " in" );
        pidee_system_command( "gpio -g mode ", feature->bcm_pin, " up" );
    } else {
        pidee_system_command( "gpio export ", feature->bcm_pin, " out" );
    }
}

int pidee_feature_read( pidee_feature *feature ) {
    return digitalRead( feature->bcm_pin ) ? 0 : 1;
}

void pidee_feature_write( pidee_feature *feature, int value ) {
   digitalWrite( feature->bcm_pin, value );
}

/* Interupts */

void pidee_feature_enable_interupt( pidee_feature *feature ) {
    int pin = feature->bcm_pin;
    if      ( pidee_feature_button.bcm_pin == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_button_interupt ); }
    else if ( pidee_feature_dip_1.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_1_interupt ); }
    else if ( pidee_feature_dip_2.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_2_interupt ); }
    else if ( pidee_feature_dip_3.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_3_interupt ); }
    else if ( pidee_feature_dip_4.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_4_interupt ); }
    else if ( pidee_feature_dip_5.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_5_interupt ); }
    else if ( pidee_feature_dip_6.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_6_interupt ); }
    else if ( pidee_feature_dip_7.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_7_interupt ); }
    else if ( pidee_feature_dip_8.bcm_pin  == pin ) { wiringPiISR( pin, INT_EDGE_BOTH, &pidee_dip_8_interupt ); }
}

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* defined _PIDEE_H */
