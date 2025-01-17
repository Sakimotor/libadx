/* LibADX for KallistiOS ##version##
 *
 * Direct Access to Sound Driver
 *
 * Copyright (C) 2011-2013 Josh 'PH3NOM' Pearson
 * Copyright (C) 2024 The KOS Team and contributors
 *
 * This code was contributed to KallistiOS (KOS) by Mickaël Cardoso (SiZiOUS).
 * It was originally made by Josh Pearson (PH3NOM). Some portions of code were
 * made by BERO. Sightly improved by Headshotnoby and Ian Micheal.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*    
    To anyone looking at this code:

    This driver runs in its own thread on the SH4.

    When the AICA driver requests more samples,
    it will signal sndbuf_status=SNDDRV_STATUS_NEEDBUF 
    and assign the number of requested samples to snddrv.pcm_needed.

    The decoders need to check sndbuf_status,
    when more samples are requested by the driver the decoders will loop
    decoding into pcm_buffer untill pcm_bytes==snddrv.pcm_needed
    at that point the decoder signals sndbuf_status=SNDDRV_STATUS_HAVEBUF.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <kos/thread.h>
#include <dc/sound/stream.h>

#include "snddrv.h"

snd_stream_hnd_t shnd;
kthread_t * snddrv_thd;
static int snddrv_vol = 255;

struct snddrv snddrv;
struct snddrv_song_info snd_sinfo;

/* Increase the Sound Driver volume */
int snddrv_volume_up() {
    
    if( snddrv_vol <= 245 ) {
        snddrv_vol += 10;
  	    snd_stream_volume(shnd, snddrv_vol);
    }
    return snddrv_vol;
}

/* Decrease the Sound Driver volume */
int snddrv_volume_down() {
    
    if( snddrv_vol >= 10 ) {
        snddrv_vol -= 10;
  	    snd_stream_volume(shnd, snddrv_vol);
    }
    return snddrv_vol;
}

/* Exit the Sound Driver */
int snddrv_exit() {
    
    if( snddrv.drv_status != SNDDRV_STATUS_NULL ) {  
        snddrv.drv_status = SNDDRV_STATUS_DONE;
        snddrv.buf_status = SNDDRV_STATUS_BUFEND;
       
        while( snddrv.drv_status != SNDDRV_STATUS_NULL ) 
          thd_pass();
          
          
        printf("SNDDRV: Exited\n");   
    }
          
    memset( snddrv.pcm_buffer, 0, 65536+16384);
    snddrv.pcm_bytes = 0;
    snddrv.pcm_needed = 0;
    
    SNDDRV_FREE_STRUCT();
    
    return snddrv.drv_status;
}   

/* Signal how many samples the AICA needs, then wait for the deocder to produce them */
static void *snddrv_callback(snd_stream_hnd_t hnd, int len, int * actual) {
       
    /* Signal the Decoder thread how many more samples are needed */
    snddrv.pcm_needed = len;       
    snddrv.buf_status = SNDDRV_STATUS_NEEDBUF;

    /* Wait for the samples to be ready */
    while( snddrv.buf_status != SNDDRV_STATUS_HAVEBUF && snddrv.buf_status != SNDDRV_STATUS_BUFEND )  
           thd_pass();

    snddrv.pcm_ptr = snddrv.pcm_buffer;    
    snddrv.pcm_bytes = 0;
    *actual = len;
	
    return snddrv.pcm_ptr;

}

static void* snddrv_thread(void*) {

    printf("SNDDRV: Rate - %i, Channels - %i\n", snddrv.rate, snddrv.channels);
    
	shnd = snd_stream_alloc(snddrv_callback, SND_STREAM_BUFFER_MAX/4);
	
    snd_stream_start(shnd, snddrv.rate, snddrv.channels-1);
    snddrv.drv_status = SNDDRV_STATUS_STREAMING;

	while( snddrv.drv_status != SNDDRV_STATUS_DONE && snddrv.drv_status != SNDDRV_STATUS_ERROR ) {
           
		snd_stream_poll(shnd);		
		thd_sleep(20);
		
	}
    snddrv.drv_status = SNDDRV_STATUS_NULL;

    snd_stream_destroy(shnd);
	snd_stream_shutdown();

    printf("SNDDRV: Finished\n");
	return NULL;

}

/* Start the AICA Sound Stream Thread */
int snddrv_start( int rate, int chans ) {
    
    snddrv.rate = rate;
    snddrv.channels = chans;
    if( snddrv.channels > 2) {
        printf("SNDDRV: ERROR - Exceeds maximum channels\n");
        return -1;
    }

    printf("SNDDRV: Creating Driver Thread\n");

    snddrv.drv_status = SNDDRV_STATUS_INITIALIZING;

    snd_stream_init();
        
    snddrv_thd = thd_create( true, snddrv_thread, NULL );
    
    return snddrv.drv_status;

}

