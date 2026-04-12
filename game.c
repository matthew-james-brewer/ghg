#include "vol.h"
#include "say.h"
#include <cjson/cJSON.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#else
struct timespec remaining, request = { 0, 0 };
#define Sleep(x) remaining.tv_nsec = x*1000000; request.tv_nsec = x*1000000; nanosleep(&remaining, &request)
#endif

// og = pointer to output string
// ptr = pointer to end of output string
// len = running total size of output string
// nameoitem = string to concat to output string
// itemlen = length of string (don't set)
#define concat_realloc(og,ptr,len,nameoitem,itemlen) itemlen = strlen(nameoitem); og = realloc(og, len + itemlen + 1); ptr = &og[len]; strcpy(ptr,nameoitem); len += itemlen;

bool wait_for_volume_change() {
 vol(50);
 int cv = 50;
 while((cv = *((long*)vol(-1))) == 50) {
  Sleep(200);
 }
 return cv > 50;
}

#define item(cjson, name) cJSON_GetObjectItemCaseSensitive(cjson, name)

#define assume(boolean) if(!boolean) goto R_ERROR
#define assume_strong(boolean) if(!boolean) goto FATAL_ERROR

char* F_BACKPACK_JSON;
char* F_STAGE_TXT;
char* F_CURRENCY_TXT;
char* F_INIT_JSON;

char currency[64];
int money;
cJSON* backpack;

void interpret(cJSON* instructions) {
 FILE* f = fopen(F_BACKPACK_JSON, "r");
 assume_strong(f);
 fseek(f, 0, SEEK_END);
 long fsize = ftell(f);
 fseek(f, 0, SEEK_SET);
 char *bson = malloc(fsize + 1);
 fread(bson, fsize, 1, f);
 fclose(f);
 bson[fsize] = 0;

 cJSON* backpack2 = cJSON_Parse(bson);
 backpack = item(backpack2, "backpack");
 money = item(backpack2, "money")->valueint;

 cJSON* instruction;
 cJSON_ArrayForEach(instruction, instructions) {
  cJSON* itm; // switch is weird about variable definitions, each section does NOT have its own scope.
  int choice = -1;
  char* type = item(instruction, "type")->valuestring;
  switch(*type) {
   case 's':
    if(!strcmp(type, "speak")) {
     say(item(instruction, "value")->valuestring);
    } else if(!strcmp(type, "setstage")) {
     FILE* stage = fopen(F_STAGE_TXT, "w");
     assume_strong(stage);
     fprintf(stage, "%d", item(instruction, "value")->valueint);
     fclose(stage);
    } else {
     goto R_ERROR;
    }
    break;
   case 'r': assume(!strcmp(type, "random"));
    // someone told me that the modulo trick doesn't get good distribution, but I do not care.
    choice = (rand() % item(instruction, "chance")->valueint) < 1;
    break;
   case 'c': assume(!strcmp(type, "choice"));
    choice = wait_for_volume_change();
    break;
   case 'm': assume(!strcmp(type, "money"));
    money += item(instruction, "value")->valueint;
    break;
   case 'd': assume(!strcmp(type, "delitem"));
    char* name = item(instruction, "value")->valuestring;
    choice = false;
    cJSON_ArrayForEach(itm, backpack) {
     if(!strcmp(itm->valuestring, name)) {
      choice = true;
      cJSON_DetachItemViaPointer(backpack, itm);
      cJSON_Delete(itm);
      break;
     }
    }
    break;
   case 'a': assume(!strcmp(type, "additem"));
    cJSON_AddItemToArray(backpack, cJSON_CreateString(item(instruction, "value")->valuestring));
    break;
   case 'i': assume(!strcmp(type, "inventory"));
    char* invento = strdup("You take inventory. You have ");
    size_t inv_len = strlen(invento); // bytes allocated to invento so far
    char* inv_ptr = &invento[inv_len]; // pointer to strcpying end of invento
    size_t itom_len;

    cJSON_ArrayForEach(itm, backpack) {
     char* itom = itm->valuestring;
     concat_realloc(invento,inv_ptr,inv_len,itom, itom_len);
     concat_realloc(invento,inv_ptr,inv_len,", ", itom_len);
    }

    char m2[10];
    snprintf(&m2[0], sizeof(m2), "%d", money);
    size_t fsize = 7 + strlen(m2) + strlen(currency);
    char* s = malloc(fsize);
    snprintf(s, fsize, " and %s %s.", m2, currency);

    concat_realloc(invento,inv_ptr,inv_len,s,itom_len);

    say(invento);
    free(invento);
    break;
   default:
    goto R_ERROR;
  }
  if(choice >= 0) {
   if(choice) {
    interpret(item(instruction, "true"));
   } else {
    interpret(item(instruction, "false"));
   }
  }
  continue;
  FATAL_ERROR:
   say("Fatal error.");
   perror("FATAL ERROR");
   exit(-1);
  R_ERROR:
   say("Error in decoding.");
   wait_for_volume_change();
 }
  cJSON* bpjso = cJSON_CreateObject();
  cJSON_AddItemToObject(bpjso, "backpack", backpack);
  cJSON_AddItemToObject(bpjso, "money", cJSON_CreateNumber((double)money));
  FILE* bpf = fopen(F_BACKPACK_JSON,"w");
  assume_strong(bpf);
  fputs(cJSON_Print(bpjso), bpf);
  fclose(bpf);
}

int main(int argc, char ** argv) {
 if(argc != 2) {
  printf("Error: game directory not selected. Usage: %s /path/to/GameDirectory.\n", argv[0]);
  return -1;
 }

 char* gd = argv[1];
 size_t gdlen = strlen(gd);

 // set file names

 F_BACKPACK_JSON =        malloc(gdlen + 15);
 sprintf(F_BACKPACK_JSON, "%s/backpack.json", gd);
 F_CURRENCY_TXT =         malloc(gdlen + 14);
 sprintf(F_CURRENCY_TXT,  "%s/currency.txt", gd);
 F_STAGE_TXT =         malloc(gdlen + 11);
 sprintf(F_STAGE_TXT,  "%s/stage.txt", gd);
 F_INIT_JSON =         malloc(gdlen + 11);
 sprintf(F_INIT_JSON,  "%s/init.json", gd);

 FILE* cf = fopen(F_CURRENCY_TXT, "r");
 assume_strong(cf);
 fgets(&currency[0], sizeof(currency), cf);
 fclose(cf);
 srand(time(NULL)); // call srand in main because only call it once

 FILE* stage = fopen(F_STAGE_TXT, "r");

 FILE* ijson;

 if(stage) {
  char line[8]; // games should have less than 10,000,000 stages.
  fgets(&line[0], sizeof(line), stage);
  fclose(stage);
  ijson = fopen(line, "r");
 } else {
  ijson = fopen(F_INIT_JSON, "r");
 }
 assume_strong(ijson);
 fseek(ijson, 0, SEEK_END);
 long fsize = ftell(ijson);
 fseek(ijson, 0, SEEK_SET);
 char *ison = malloc(fsize + 1);
 fread(ison, fsize, 1, ijson);
 fclose(ijson);
 ison[fsize] = 0;

 cJSON* it = cJSON_Parse(ison);
 cJSON* inthis;
 if(stage) {
  inthis = it;
 } else {
  inthis = item(it, "value");
 }

 interpret(inthis);

 // This stage has been completed. run main again.

 main(argc, argv);

   FATAL_ERROR:
   say("Fatal Error.");
   perror("FATAL ERROR");
   exit(-1);
}
