/****************************************************************
 * this example demonstrates streaming synthensized audio
 ****************************************************************/
 
#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>
#include "libintdsp.h"

agraph_t gg;
node_t* osc;
node_t* adr;
node_t* lpf;
int16_t spl_a, spl_b;

//-----------------------------------------------------------------------------
enum {
//-----------------------------------------------------------------------------
	// blue backdrop
	bg_colour = 13 << 10,
	
	// red cpu usage
	cpu_colour = 31,

	srate = 32000
};

int16_t sint_init(int16_t p){
	return sinLerp((p<<8)-32768);
}
/***********************************************************************************
 * on_stream_request
 *
 * Audio stream data request handler.
 ***********************************************************************************/
mm_word on_stream_request( mm_word length, mm_addr dest, mm_stream_formats format ) {
//----------------------------------------------------------------------------------
	
	s16 *target = dest;
	
	int len = length;

	for( ; len; len-- )
	{
		proc_graph(&gg);
		*target++ = spl_a;
		*target++ = spl_b;
	}
	
	
	return length;
}

/**********************************************************************************
 * main
 *
 * Program Entry Point
 **********************************************************************************/
int main( void ) {
//---------------------------------------------------------------------------------

	//----------------------------------------------------------------
	// print out some stuff
	//----------------------------------------------------------------
	consoleDemoInit();
	iprintf( "\n YoYo libintdsp \n");
	
	libintdsp_init(&gg,sint_init);
	node_t* daca = new_dac(&gg, "left", &spl_a);
	node_t* dacb = new_dac(&gg, "right", &spl_b);
	
	osc = new_osc(&gg,"lol");
	set_osc_freq((osc_t*)osc->processor, 10000, srate);
	
	node_t* lfo = new_osc(&gg,"lfo");
	set_osc_freq((osc_t*)lfo->processor, 10, srate);
	((osc_t*)lfo->processor)->gain = 3;
	((osc_t*)lfo->processor)-> bias = ((osc_t*)osc->processor)->acc;
	
	node_t* osc2 = new_osc(&gg,"lol");
	set_osc_freq((osc_t*)osc2->processor, 4000, srate);
	node_t* osc3 = new_osc(&gg,"lol");
	set_osc_freq((osc_t*)osc3->processor, 2500, srate);
	
	((osc_t*)osc2->processor)->table = sawt;
	((osc_t*)osc3->processor)->table = sawt;
	((osc_t*)osc2->processor)->gain = 50;
	((osc_t*)osc3->processor)->gain = 50;

	adr = new_adr(&gg, "adr");
	lpf = new_lpf(&gg, "lpf");

	set_lpf_freq((lpf_t*)(lpf->processor), 1000, srate);
	set_adr_attack_ms((adr_t*)(adr->processor), 1000, srate);
	set_adr_release_ms((adr_t*)(adr->processor), 1000, srate);
	
	connect(&gg,lfo,osc);
	connect(&gg,osc,dacb);
	
	connect(&gg,osc2,adr);
	connect(&gg,adr,dacb);
	connect(&gg,osc3,lpf);
	connect(&gg,lpf,daca);
	
	//----------------------------------------------------------------
	// initialize maxmod without any soundbank (unusual setup)
	//----------------------------------------------------------------
	mm_ds_system sys;
	sys.mod_count 			= 0;
	sys.samp_count			= 0;
	sys.mem_bank			= 0;
	sys.fifo_channel		= FIFO_MAXMOD;
	mmInit( &sys );
	
	//----------------------------------------------------------------
	// open stream
	//----------------------------------------------------------------
	mm_stream mystream;
	mystream.sampling_rate	= srate;					// sampling rate = 25khz
	mystream.buffer_length	= 2048;						// buffer length = 1200 samples
	mystream.callback		= on_stream_request;		// set callback function
	mystream.format			= MM_STREAM_16BIT_STEREO;	// format = stereo 16-bit
	mystream.timer			= MM_TIMER0;				// use hardware timer 0
	mystream.manual			= true;						// use manual filling
	mmStreamOpen( &mystream );
		
	//----------------------------------------------------------------
	// when using 'automatic' filling, your callback will be triggered
	// every time half of the wave buffer is processed.
	//
	// so: 
	// 25000 (rate)
	// ----- = ~21 Hz for a full pass, and ~42hz for half pass
	// 1200  (length)
	//----------------------------------------------------------------
	// with 'manual' filling, you must call mmStreamUpdate
	// periodically (and often enough to avoid buffer underruns)
	//----------------------------------------------------------------
	
	SetYtrigger( 0 );
	irqEnable( IRQ_VCOUNT );
	
	int cc = 0;
	int pp = 0;
	
	while( 1 )
	{
		iprintf( "\x1b[2;0HFPS counter: %d\n", cc++);
		iprintf( "\x1b[3;0HPP counter: %d\n", pp);

		// update stream
		mmStreamUpdate();
		
		// restore backdrop (some lines were drawn with another colour to show cpu usage)
		//BG_PALETTE_SUB[0] = bg_colour;
		
		// wait until next frame
		swiWaitForVBlank();
		//-----------------------------------------------------
		// get new keypad input
		//-----------------------------------------------------
		
		BG_PALETTE_SUB[0] = bg_colour;

		scanKeys();
		int keysD = keysDown();
		int keysU = keysUp();
		int keysC = keysCurrent();

		if( keysD & KEY_X) {
			pp++;
			set_osc_freq((osc_t*)lfo->processor, 30, 24000);
		}
		if( keysU & KEY_X) {
			set_osc_freq((osc_t*)lfo->processor, 10, 24000);
		}
		
		// if( keys & KEY_X) set_osc_freq((osc_t*)lfo->processor, 10, 24000);

		// keys = keysCurrent();
		// if(keys & KEY_Y){
		// 	BG_PALETTE_SUB[0] = bg_colour;
		// }
		((adr_t*)(adr->processor))->state = (keysC & KEY_Y);
		set_lpf_freq((lpf_t*)(lpf->processor), (keysC & KEY_B) ? 2900 : 16000, 24000);
		
		
	}
	
	return 0;
}
