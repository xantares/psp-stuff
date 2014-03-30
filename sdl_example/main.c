#include <stdio.h>
#include <stdlib.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 


#define printf pspDebugScreenPrintf

PSP_MODULE_INFO("SDL_image", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int SetupCallbacks(void);
int exit_callback(int arg1, int arg2, void *common);
int CallbackThread(SceSize args, void *argp);


/* Main function */
int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *ecran = NULL;
	SDL_Surface *image = NULL;
	ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 10, 80, 100)); 
	image = IMG_Load("image.png");
	SDL_Rect coordonnee_image;
	coordonnee_image.x = ecran->w / 2 - image->w / 2;
	coordonnee_image.y = ecran->h / 2 - image->h / 2;
	int continuer = 1;
	pspDebugScreenInit();
	SetupCallbacks();
	SceCtrlData pad;
	while (continuer)
	{
		sceCtrlReadBufferPositive (&pad, 1);
		if (pad.Buttons & PSP_CTRL_UP)
		{
			coordonnee_image.y--;
		}
		else if (pad.Buttons & PSP_CTRL_DOWN)
		{
			coordonnee_image.y++;
		}
		if (pad.Buttons & PSP_CTRL_RIGHT)
		{
			coordonnee_image.x++;
		}
		else if (pad.Buttons & PSP_CTRL_LEFT)
		{
			coordonnee_image.x--;
		} 
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(image, NULL, ecran, &coordonnee_image);
		SDL_Flip(ecran);
	}
	SDL_FreeSurface(image);
	SDL_FreeSurface(ecran);
	SDL_Quit();
	sceKernelSleepThread();
	return 0;
}


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	return 0;
}


/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}


/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}
