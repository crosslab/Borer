
printf("aaaa");
printf("aaaa");
printf("aaaa");
printf("aaaa");
//≤‚ ‘œÓ£∫
                                  #include "ITCommon.h"
                                  
                                  #ifndef _ITEST_MAIN_ENTRY_
                                  #define _ITEST_MAIN_ENTRY_
                                  ////ADD YOUR HEADFILE
                                  
                                  int main(void)
                                  #else
                                  ////ADD YOUR HEADFILE
                                  
                                  int subFunction(void)
                                  #endif
                                  {
                                  //////////////////////////////////
                                  char ccc[256];
                                  
                                  sprintf(ccc,"Enter %s",_ThisFile_());
                                  ITTrace(ccc);
                                                                    ///////////////////////////////////
                                  //// Add your specialized code here
                                  
                                  
                                  
                                  ///////////////////////////////////
                                  sprintf(ccc,"Sucess! Leave %s",_ThisFile_());
                                  ITTrace(ccc);
                                                                    ///////////////////////////////////
                                  return 0;
                                  }
                                  
ITExEnd();

printf("aaaa");
printf("aaaa");
printf("aaaa");

