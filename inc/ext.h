#pragma once

/*
* | ext.h - intellectual property of Rohan Shashank (jammy3662)
* |
* | A header-only software library called Ext, featuring
* | a series of extensions for c and c++ functionality.
* | Includes doubly-linked-list, array, string, and other
* | wrappers for common constructs, among other things.
* |
* | EXT IS LICENSED AS PRIVATE SOFTWARE.
* | Copying, modifying, or redistributing this software is NOT PERMISSIBLE.
* | This licensing is SUBJECT TO CHANGE WITHOUT NOTICE.
* |
* | Ext is planned to eventually be relicensed under a more permissive open-source license,
* | such as the GNU LGPL, or something similar. For now, it remains private.
*/

// TODO: add preprocessor options to compile c-friendly code
// (currently only valid in c++)

#ifndef EXT_H
#define EXT_H

#include <stdlib.h>
#include <string.h>

#include <math.h>

#define int8   char
#define int16  short
#define int32  int
#define int64  long

#define uint8  unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long

typedef char* str;

/* --- ASCII CHARACTERS --- */
#define VT 11  // vertical tab
#define FF 12  // new page
#define CR 13  // carriage return
#define DL 127 // backspace/delete

// iterate over range _MIN_ to _MAX_
#define fromto(ID, MIN, MAX) for (int ID = MIN; ID < MAX; ID++)
// iterate over each element in stack array
#define forls(ID, LST, BLOCK) { typeof(*LST) ID; for (int i = 0; i < (sizeof(LST)/sizeof(*LST)); i++) { ID = LST[i]; { BLOCK } } }
// iterate over each element in Ext array
#define forin(ID, LST, BLOCK) { typeof(*LST.data) ID; for (int i = 0; i < LST.size; i++) { ID = LST[i]; { BLOCK } } }

#ifndef PI
#define PI M_PI
#endif

// get rid of code without commenting it out
// (for syntax highlighting)
#define __cancel(BLOCK)

#ifdef ZEXT_IO
	#include <stdio.h>
	#ifdef ZEXT_SILENCE_PRINTF
		#define printf(...)
	#endif
	#ifdef ZEXT_CONTROL_PRINTF
		#define printf(...) ZALGO_EXT::conditional_printf(__VA_ARGS__)
	#endif
#endif


namespace ZALGO_EXT
{
	// Set i to 0 to silence printf
	int (*conditional_printf) (const char*, ...) = printf;
	int silent_printf(const char* _, ...) { return 0; }
	void printf_verbosity(int verbose)
	{
		if (!verbose) conditional_printf = silent_printf;
		else conditional_printf = printf;
	}
};

// type based allocation (using malloc)
#define alloc(TYPE) (TYPE*)malloc(sizeof(TYPE))
#define talloc(SIZE, TYPE) (TYPE*)malloc(SIZE * sizeof(TYPE))
#define tcalloc(SIZE, TYPE) (TYPE*)calloc(SIZE, sizeof(TYPE))
#define trealloc(PTR, SIZE, TYPE) (TYPE*)realloc(PTR, SIZE * sizeof(TYPE))

// returns whether _str2_ begins with the entirety of _str1_
bool strmatch(char* str1, char* str2)
{
	while (*str1 != 0)
	{
		if (*str2 == 0) return false;
		if (*str1 != *str2) return false;
		str1++; str2++;
	}
	return true;
}

// returns whether _str1_ exactly matches _str2_
bool streq(char* str1, char* str2)
{
	while (*str1 != 0 and *str2 != 0)
	{
		if (!(*str1 == *str2)) return 0;
		str1++; str2++;
	}
	return (*str1 == *str2);
}

// returns true if _str_ contains EXACTLY 1 or EXACTLY 0 characters (followed by implicit null terminator)
bool str1char(char* str)
{
	if (*str == 0) return true;
	else if (*(++str) == 0) return true;
	return false;
}

// returns position of first occurence of _c_ in _str_
// if _c_ not found in _str_, returns 0
int strhaschar(char* str, char c)
{
	int pos = 1;
	while (*str != 0)
	{
		if (*str == c) return pos;
		str++; pos++;
	}
	return 0;
}

char* printbin(int bits, char bitc)
{
	char* str = (char*) malloc(bitc + 1);
	str[bitc] = '\0';
	for (int i = 0; i < bitc; i++)
	{
		str[bitc - 1 - i] = '0' + (0 != (bits & (1 << i)));
	}
	return str;
}

int binint(char* n)
{
	int ret = 0;
	int i = 0;
	for (char* bit = n; *bit != '\0'; bit++)
	{
		if (*bit - '0') ret |= 1 << i;
		i++;
	}
	return ret;
}

#define flagset(field, bit) (field |= 1 << bit)
#define flagclear(field, bit) (field &= ~(1 << bit))
#define flag(field, bit) (field & (1 << bit))

inline float rad(float deg) {
	return deg * PI / 180;
}

inline float deg(float rad) {
	return rad * 180 / PI;
}

constexpr float RAD(float DEG) {
	return DEG * PI / 180;
}

constexpr float DEG(float RAD) {
	return RAD * 180 / PI;
}

#define min(A, B) ((A < B) ? A : B)
#define max(A, B) ((A > B) ? A : B)

template <class T>
T clamp(T min, T val, T max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

//#define clamp(MIN, VAL, MAX) ((((VAL < MIN) ? MIN : VAL) > MAX) ? MAX : VAL)

#define stint int
#define string string
struct string
{
	char* data = 0x0;
	stint size = 0;
	stint last = 0;
	
	/*
	// burn in fucking hell, c++
	string(char* _1, stint _2, stint _3)
	{
		data = _1;
		size = _2;
		last = _3;
	}
	*/
	
	// initialize empty string
	string()
	{
		data = 0x0;
		size = 0;
		last = 0;
	}

	// initialize string with specific size
	string(stint s)
	{
		size = s;
		data = talloc(s, char);
		last = 0;
		data[0] = 0; // null terminator
	}

	// initialize string with specific data
	string(char* str)
	{
		size = strlen(str);
		data = talloc(size, char);
		memcpy(data, str, size);
		last = size - 1;
		data[last] = 0;
	}

	// initialize string with specific data and size
	string(char* str, stint s)
	{
		stint strl = strlen(str);
		size = max(s, strl);
		data = talloc(size, char);
		memcpy(data, str, strl);
		last = strl - 1;
		data[last] = 0;
	}
	
	// initialize string with another string and specific size
	// (faster than raw char pointer because skip the call to 'strlen')
	string(string str, stint s)
	{
		size = max(s, str.size);
		data = talloc(size, char);
		memcpy(data, str.data, str.size);
		last = str.last;
	}
	
	// returns a copy of this string with independent data
	string clone()
	{
		char* str = talloc(size, char);
		memcpy(str, data, size);
		
		// i fucking hate you c++
		// burn eternally in the flames of fucking hell, c++
		string ret = *this;
		ret.data = data;
		return ret;
	}
	
	void clear()
	{
		free(data);
		size = 0;
	}

	char& operator[] (stint idx)
	{
		#ifdef ZALGO_EXT_ERR
			if (idx >= capacity) fprintf(stderr, "string %p: out of bounds index %i\n", this, idx);
		#endif
		return data[idx];
	}
	
	inline int space()
	{
		// last is zero-indexed while size is not
		return size - last - 1;
	}
	
	void append(char c)
	{
		if (space()) goto write;
		
		data = trealloc(data, size + 1, char);
		
		write:
		data[last] = c;
		last++;
		data[last] = 0;
	}
	
	void append(char* str)
	{
		stint strl = strlen(str);
		if (space() >= strl) goto write;
		
		data = trealloc(data, size + strl, char);
		
		write:
		memcpy(data + last, str, strl);
		last += strl;
		data[last] = 0;
	}
	
	// writes data to the end of this string
	// resizes to fit exactly
	void append(string str)
	{
		if (space() >= str.size) goto write;
		
		data = trealloc(data, size + str.size, char);
		
		write:
		memcpy(data + last, str.data, str.size);
		last += str.size;
	}
	
	// increases size by factor of 2
	void grow()
	{
		size = size << 1;
		data = trealloc(data, size, char);
	}
	
	// frees unused characters
	void trim()
	{
		data = trealloc(data, last + 1, char);
	}
	
	// shrink array by _s_ characters
	void cut(int s)
	{
		data = trealloc(data, size - s, char);
		last = size - 1;
		data[last] = 0;
	}
	
	// get substring of this string
	string substr(stint from, stint to)
	{
		string ret;
		
		ret.size = to - from + 2;
		ret.last = ret.size - 1;
		ret.data = talloc(size, char);
		memcpy(ret.data, data + from, ret.size);
		ret.data[size - 1] = 0;
		
		return ret;
	}
};

template <class T>
struct dlnode { // Doubly linked node
	T value;
	dlnode* next = NULL;
	dlnode* prev = NULL;
};

template <class T>
struct List {

	dlnode<T>* first;
	dlnode<T>* last;
	int size;

	List() {
		first = NULL;
		last = NULL;
		size = 0;
	}

	int append(T val) {
		size++;
		dlnode<T>* add = new dlnode<T>;
		add->value = val;
		if (first == NULL) {
			first = add;
			last = add;
			return size;
		}
		last->next = add;
		add->prev = last;
		last = add;
		return size;
	}

	int prepend(T val) {
		size++;
		dlnode<T>* add = new dlnode<T>;
		add->value = val;
		if (last == NULL) {
			first = add;
			last = add;
			return size;
		}
		first->prev = add;
		add->next = first;
		first = add;
		return size;
	}

	void insert(T val, int idx) {
		if (idx < 0 or idx > size - 1) return;
		size++;
		dlnode<T>* add = new dlnode<T>;
		add->value = val;
		if (first == NULL) {
			first = add;
			last = add;
			return;
		}
		dlnode<T>* current = first;
		for (int i = 0; i < idx - 1; i++) {
			current = current->next;
		}
		dlnode<T>* following = current->next;
		current->next = add;
		add->prev = current;
		add->next = following;
		following->prev = add;
	}

	int remove(int idx) {
		if (idx < 0 or idx > size - 1) return -1;
		size--;
		dlnode<T>* current = first;
		for (int i = 0; i < idx; i++) {
			current = current->next;
		}
		T val = current->value;
		if (current->prev == NULL) {
			if (current->next == NULL) {
				first = NULL;
				last = NULL;
				free(current);
				return idx;
			}
			first = current->next;
			current->next->prev = NULL;
			free(current);
			return idx;
		}
		if (current->next == NULL) {
			if (current->prev == NULL) {
				first = NULL;
				last = NULL;
				free(current);
				return idx;
			}
			last = current->prev;
			current->prev->next = NULL;
			free(current);
			return idx;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		free(current);
		return size;
	}

	int find(T val) {
		if (size == 0) return -1;
		dlnode<T>* current = first;
		for (int idx = 0; current != NULL; idx++) {
			if (current->value == val) return idx;
			current = current->next;
		}
		return -1;
	}

	T get(int idx) {
		if (idx < 0 or idx > size - 1 or size == 0) return NULL;
		dlnode<T>* current = first;
		for (int i = 0; i < idx; i++) {
			if (current != NULL) current = current->next;
		}
		if (current == NULL) return NULL;
		return current->value;
	}

	T operator[](int idx)
	{
		return get(idx);
	}

};

template <class T>
struct Array {
	T* data;
	unsigned int size;
	Array() {
		data = NULL;
		size = 0;
	}
	// use an existing data block
	Array(T* ptr, int s) {
		data = ptr;
		size = s;
	}
	// create an empty array of given size
	void allocate(int capacity)
	{
		data = (T*) malloc(capacity * sizeof(T));
		if (data == NULL) return;
		size = capacity;
	}
	// completely overwrites array buffer with a given byte
	void fill(int value)
	{
		memset(data, value, size * sizeof(T));
	}
	// returns size of array data in bytes
	int blocksize()
	{
		return size * sizeof(T);
	}
	// returns -1 for not enough memory
	int append(T value) {
		T* attempt = (T*) realloc(data, sizeof(T) * (size + 1));
		if (!attempt) return -1;
		data = attempt;
		data[size] = value;
		size++;
		return size - 1;
	}
	// returns -1 for not enough memory
	int prepend(T value) {
		T* attempt = (T*) realloc(data, sizeof(T) * (size + 1));
		if (!attempt) return -1;
		data = attempt;
		memmove(data, data + 1, sizeof(T) * size);
		data[0] = value;
		size++;
		return 0;
	}
	// append an entire array to the end of this one
	// (does not free memory of concatenated array)
	int concatenate(Array<T> array)
	{
		if (! realloc(data, (this->size + array.size) * sizeof(T)) )
			return -1;
		
		memcpy((data + size), array.data, array.size * sizeof(T));
		size += array.size;
		return size;
	}
	// returns -1 for not enough memory
	int insert(T value, int idx) {
		T* attempt = (T*) realloc(data, sizeof(T) * (size + 1));
		if (!attempt) return -1;
		memmove(data + idx, data + idx + 1, size - idx);
		data[idx] = value;
		size++;
		return idx;
	}
	// returns new size of array
	int remove(int idx) {
		memmove(data + idx + 1, data + idx, size - 1 - idx);
		data = (T*) realloc(data, sizeof(T) * (size - 1));
		size--;
		return size;
	}
	// removes all elements and frees/nulls data pointer
	void empty()
	{
		free(data);
		data = 0x0;
		size = 0;
	}
	// returns NULL for invalid index
	inline T & get(int idx) {
		return data[idx];
	}

	T & operator[](int idx)
	{
		return data[idx];
	}

	// does nothing for invalid index
	inline void set(int idx, T value) {
		if (idx < 0 or idx > size - 1) return;
		data[idx] = value;
	}
	// returns index of first matching value
	// -1 = not found
	// -2 = array empty
	int find(T value) {
		if (size < 1) return -2;
		for (int idx = 0; idx < size; idx++) {
			if (data[idx] == value) return idx;
		}
		return -1;
	}
	#ifdef ZALGO_EXT_IO
	void dump() {
		for (int i = 1; i < size; i++) {
			printf("index %i, value %i\n",i,get(i - 1));
		}
	}
	#endif
};

/*
template <int size, class T>
struct Table
{
	T data[size];
	int next = 0;
	int last = 0;

	void add(T item)
	{
		data[next] = item;
	}
};
*/

struct nenum: Array<char*>
{
	nenum() {}

	nenum(char** keys, int ct)
	{
		int keybytes = sizeof(char*) * ct;
		allocate(ct);
		memcpy(data, keys, keybytes);
	}

	inline int operator[](char* key)
	{
		for (int i = 0; i < size; i++)
		{
			if (strcmp(key, data[i]) == 0) return i;
		}
		return -1;
	}
};

/*
template <class K, class V>
struct Dict
{
	struct Pair
	{
		K key;
		V value;
	}
	
	Array<Pair> entries;

	void add(char* key, T value)
	{
		keys.append(key);
		values.append(value);
	}

	// removes first element with 'key'
	void remove(char* key)
	{
		for (int i = 0; i < keys.size; i++)
		{

		}
	}

	// returns index of first element matching 'key'
	// returns -1 if key not found
	int find(K key)
	{
		for (int i = 0; i < keys.size; i++)
		{
			if (strcmp(keys[i], key) == 0) return i;
		}
		return -1;
	}

	// returns index of first element matching 'value'
	// returns -1 if value not found
	int find(V value)
	{
		for (int i = 0; i < values.size; i++)
		{
			if (values[i] == value) return i;
		}
		return -1;
	}
};
*/

#endif