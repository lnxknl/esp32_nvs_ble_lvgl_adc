#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_DISCONNECTED
#define LV_ATTRIBUTE_IMG_IMG_DISCONNECTED
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_DISCONNECTED uint8_t img_disconnected_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x02, 0x02, 0x02, 0xff, 	/*Color of index 1*/

  0x03, 0x00, 0x00, 
  0x39, 0xbf, 0xc0, 
  0x3d, 0x9f, 0xc0, 
  0x30, 0xc0, 0xc0, 
  0x36, 0x66, 0xc0, 
  0x36, 0x66, 0xc0, 
  0x30, 0x30, 0xc0, 
  0x3f, 0xb3, 0xc0, 
  0x3f, 0xd9, 0xc0, 
  0x00, 0x0c, 0x00, 
};

const lv_img_dsc_t img_disconnected = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 20,
  .header.h = 10,
  .data_size = 38,
  .data = img_disconnected_map,
};
