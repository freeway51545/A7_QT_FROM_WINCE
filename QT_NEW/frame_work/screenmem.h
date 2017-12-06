#ifndef _SCREEN_MEM_H
#define _SCREEN_MEM_H

extern "C"{
	void *zhw_malloc(int size);
	char *zhw_clone_str(char *);
	void zhw_free_handle(void**);
#define ZHW_FREE(a) if(a!=NULL)zhw_free_handle((void**)(&(a)));
};

#endif