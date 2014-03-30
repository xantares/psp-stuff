#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("Hello World", 0, 1, 1);
// #define printf pspDebugScreenPrintf

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






#include <vector>
#include <new>
#include <iostream>

class Michel
{
public:
  Michel() {}
  
};

int main() {
  pspDebugScreenInit();
  SetupCallbacks();
  
  std::cout << "Hello World" << std::endl;

  
  Michel * instance = new Michel;
  delete instance;
  
  std::vector<int> vec(2);
  vec.resize(4);  
  
  sceKernelSleepThread();
  return 0;
}

