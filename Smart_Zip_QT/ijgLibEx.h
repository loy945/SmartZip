#pragma once
#include<string>
#include "jpeglib.h"


struct safe_jpeg_error_mgr{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

typedef safe_jpeg_error_mgr *safe_jpeg_error_mgr_ptr;
void safe_jpeg_error_exit(j_common_ptr cinfo){
	safe_jpeg_error_mgr_ptr myerr = (safe_jpeg_error_mgr_ptr)cinfo->err;
};