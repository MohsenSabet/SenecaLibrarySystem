/*
  Module: Utils
  Description: This module contains utility functions and classes that
  are used across the Seneca Library Application. These utilities include
  common routines for input validation, formatting, and other helper functions
  essential for the operation of the application.
  Author: Mohsen Sabet
*/


#include "Utils.h"
namespace sdds {
	void strcpy(char* des, const char* src) {
		int i = 0;
		while (src[i] != '\0') {
			des[i] = src[i];
			i++;
		}
		des[i] = '\0';

	}
	void strnCpy(char* des, const char* src, int len) {
		int i;
		for (i = 0; i < len && src[i] != '\0'; i++) {
			des[i] = src[i];
		}
		if (i < len) {
			des[i] = '\0';
			i++;
		}
	}
	int strCmp(const char* s1, const char* s2) {
		while (*s1 != '\0' && *s2 != '\0') {
			if (*s1 != *s2) {
				return *s1 - *s2;
			}
			s1++;
			s2++;
		}
		return *s1 - *s2;
	}
	int strnCmp(const char* s1, const char* s2, int len) {
		for (int i = 0; i < len; i++) {
			if (s1[i] != s2[i]) {
				return s1[i] - s2[i];
			}
			if (s1[i] == '\0' || s2[i] == '\0') {
				return s1[i] - s2[i];
			}
		}
		return 0;
	}
	int strlen(const char* s) {
		int len = 0;
		while (s[len] != '\0') {
			len++;
		}
		return len;
	}


	void strCat(char* des, const char* src) {
		while (*des != '\0') {
			des++;
		}

		while (*src != '\0') {
			*des = *src;
			des++;
			src++;
		}
		*des = '\0';
	}

}