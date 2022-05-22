#include <nds/ndstypes.h>
#include <nds.h>
#include <gl2d.h>
#include "gfx.h"
#include "tt.h"

// struct Anim {
//     Texture2D tex;
//     Rectangle src;
//     Rectangle dest;
//     Vector2 orig;
//     Color tint;
//     int32 rot;
//     int32 scale;

//     int animating;
//     int frames;
//     int tilesx;
//     int tilesy;
//     int frameCtr;
//     int animSpeed;
//     int timeCtr;

//     int32 velx;
//     int32 vely;
//     int32 velrot;
//     int tp;
//     int dead;
// } ;

// struct Anim sprites[256];
// const unsigned int screenWidth = 240;
// const unsigned int screenHeight = 160;

// void initAnim(struct Anim *a,char *texture, int tilesx, int tilesy){

//     if(texture != NULL) a->tex = LoadTexture(texture);

//     a->frames = tilesx*tilesy;
//     a->tilesx = tilesx;
//     a->tilesy = tilesy;

//     a->src = (Rectangle){0.0f, 0.0f, a->tex.width / a->tilesx, a->tex.height / a->tilesy};
//     a->dest = (Rectangle){0.0f, 0.0f, a->src.width, a->src.height};
//     a->orig = (Vector2){(float) a->src.width/2.0f ,(float)a->src.height / 2.0f};
    
//     a->frameCtr = 0;
//     a->animating = 1;
//     a->tint = WHITE;
//     a->animSpeed = 15;
//     a->velx = 0.0f;
//     a->vely = 0.0f;
//     a->velrot  = 0.0f;
//     a->scale = 1.0f;
//     a->tp = 1;
    
// }

// void nextFrame(struct Anim* a){
//     a->timeCtr++;;
//     if(a->timeCtr > a->animSpeed && a->animating) {
//         a->timeCtr = 0;
//         a->frameCtr++;
//         if(a->frameCtr >= a->frames){
//             a->frameCtr = 0;
//         }
//     }
    
//     int f = a->frameCtr;
//     int yoff = (f/a->tilesx);
// 	int xoff = (f-(yoff*a->tilesx));

//     a->src.x = a->src.width * xoff;
//     a->src.y = a->src.height * yoff;
//     a->rot    += a->velrot;
//     a->dest.width = a->scale * a->src.width;
//     a->dest.height = a->scale * a->src.height;
//     a->orig.x = a->dest.width/2;
//     a->orig.y = a->dest.height/2;
//     a->dest.x += (a->velx*a->scale);
//     a->dest.y += (a->vely*a->scale);
    

//     if(a->tp == 1){
//         if(a->dest.x < 0 - screenBounds/2)      { a->dest.x = (screenWidth + screenBounds/2) - 1;}
//         else if(a->dest.x > screenWidth + screenBounds/2) { a->dest.x = (1 - screenBounds/2);  a->frameCtr = (float)(rand()%a->frames);}
//         //if(a->dest.y < -50.0f)                          { a->dest.y = (float)screenHeight + 50.0f;}
//         //if(a->dest.y > (float)screenHeight)     { a->dest.y = -50.0f;}
        
//     } 
    
// }

// void drawAnim(struct Anim *a){
//     if(!a->dead)
//     {
//         DrawTexturePro(a->tex, a->src, a->dest, a->orig, a->rot, a->tint);
//     }
// }

// void stars(){ 
//     for(int i=0; i<32; i++){
//         //sprites[j].tex = starstex;
//         //initAnim(&sprites[j],NULL,5,1);
//         //spritesCount++;
//         sprites[i].dest.x = (float)(rand()%screenWidth);
//         sprites[i].dest.y = (float)(rand()%screenHeight);
//         //sprites[j].frameCtr = (float)(rand()%sprites[j].frames);
//         //sprites[j].velrot  = VEL_SPEED_ROT;
//         //j += 1;
//     }
//     transition();
//     #define FOV 4.0f
//     screenBounds = screenWidth*1.3;
    

//         BeginTextureMode(outputCanvas);
//         //DrawRectangle(0, 0, screenWidth, screenHeight, (Color) {0,0,0,32} );          
//         ClearBackground(BLACK);
//         for(int i=0; i<spritesCount; i++){
            
            
//             if(i >= 32){
//                 if(sprites[i].dest.x > -50 && sprites[i].dest.x < screenWidth + 250){
//                     sprites[i].scale =  FOV + (  ((float)(screenWidth) - sprites[i].dest.x) / (float)(screenWidth)*(1.0f - FOV));
//                 }
//                 else sprites[i].scale = 1.0f;
//                 //int tint = 127 + (int) ( 127.0f * (sprites[i].dest.x+50.0f / (float)(screenWidth+100.f)));
//                 //sprites[i].tint = (Color){tint,tint,tint,255};
//             }
//             else{
//                 sprites[i].scale = 0.5f;
//             }


//             drawAnim(&sprites[i]);
//             nextFrame(&sprites[i]);
//         }
        
//         EndTextureMode();
//         DrawScreen();
    

// }
glImage* tex;
s16 xx;

void initFrame(){
    xx = 0;
    //set mode 5, enable BG0 and set it to 3D
	videoSetMode( MODE_5_3D );
	videoSetModeSub( MODE_0_2D  );

	consoleDemoInit();
	// Initialize GL in 3d mode
	glScreen2D();
	// Set  Bank A to texture (128 kb)
	vramSetBankA( VRAM_A_TEXTURE );

	// Allocate VRAM bank for all the palettes
	vramSetBankE(VRAM_E_TEX_PALETTE);  


	//use this to load sprites which are irregular sizes in one sheet ie 4x4 then 2x4 etc
	// const unsigned int coords[] = {
	// 	0,0,16,16,
	// 	16,0,16,16,
	// 	0,16,16,16,
	// 	16,16,16,16
	// };

    // int tid = 
	// 	glLoadSpriteSet( tex,			// pointer to glImage array
	// 				   4,				
	// 				   coords,
	// 				   GL_RGB256,		// texture type for glTexImage2D() in videoGL.h
	// 				   TEXTURE_SIZE_32,	// sizeX for glTexImage2D() in videoGL.h
	// 				   TEXTURE_SIZE_32,	// sizeY for glTexImage2D() in videoGL.h
	// 				   GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
	// 				   16,					// Length of the palette to use (16 colors)
	// 				   (u16*)ttPal,		// Load our 256 color tiles palette
	// 				   (u8*)ttBitmap // image data generated by GRIT
	// 				 );
	

	//important, tex must be pointer or prealocated space w*h * frames count !!!!
	 int tid = 
		glLoadTileSet( tex,			// pointer to glImage array
					   16,				// sprite width
					   16,				// sprite height
					   32,				// bitmap image width
					   32,				// bitmap image height
					   GL_RGB256,		// texture type for glTexImage2D() in videoGL.h
					   TEXTURE_SIZE_32,	// sizeX for glTexImage2D() in videoGL.h
					   TEXTURE_SIZE_32,	// sizeY for glTexImage2D() in videoGL.h
					   GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
					   16,					// Length of the palette to use (16 colors)
					   (u16*)ttPal,		// Load our 256 color tiles palette
					   (u8*)ttBitmap // image data generated by GRIT
					 );
}

void onFrame(){
    glBegin2D();

    const int v = (1<<12);
    int c = 16 + (sinLerp(xx+=256)>>8);

    glBoxFilledGradient( 0, 0, 255, 191,
								 RGB15(c,0,0),
								 0,
								 RGB15(c,0,0),
                                 0
                               );

	glSpriteScale(30,30,1<<14,GL_FLIP_NONE,&tex[3]);

    glEnd2D();
    glFlush(0);
}