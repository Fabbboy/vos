#include "../string.h"

uint64_t strlen(const char* str){
  uint64_t len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
};

bool strcmp(const char* str1, const char* str2){
  uint64_t len1 = strlen(str1);
  uint64_t len2 = strlen(str2);
  if (len1 != len2) {
    return false;
  }
  for (uint64_t i = 0; i < len1; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
};