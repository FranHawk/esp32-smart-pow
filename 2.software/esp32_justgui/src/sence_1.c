#include "sence_1.h"
#include "images.h"
#include <stdlib.h>
#include "lv_port_fatfs.h"


void lv_test_gui(void)
{
    lv_obj_t* img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(img1, &abc);
	//lv_img_set_src(img1, "S:abc.bin");
	lv_obj_align(img1,LV_ALIGN_CENTER, 0, 0);
}