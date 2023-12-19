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

char* strcat(char* dest, const char* src){
  uint64_t dest_len = strlen(dest);
  uint64_t src_len = strlen(src);
  for (uint64_t i = 0; i < src_len; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + src_len] = '\0';
  return dest;
};