#include <stdio.h>
#include <stdlib.h>

#include "engine.h"


#ifdef _PSP_FW_VERSION
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

PSP_MODULE_INFO("Showfoot", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf


int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0;
}


int CallbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}


int SetupCallbacks(void) {
  int thid = 0;
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0) {
    sceKernelStartThread(thid, 0, 0);
  }
  return thid;
}

#endif

int main() {
  engine_st engine;

  SDL_Init (SDL_INIT_VIDEO);

#ifdef _PSP_FW_VERSION
  pspDebugScreenInit();
  SetupCallbacks();
#endif

  engineInit (&engine);
  engineRun (&engine);
  engineQuit (&engine);

  SDL_Quit ();
#ifdef _PSP_FW_VERSION
  sceKernelSleepThread();
#endif
  return 0;
}

