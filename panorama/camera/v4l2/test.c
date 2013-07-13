#include "v4l2.h"

v4l2_device vd;


void main()
{
	v4l2_open(DEFAULT_DEVICE,&vd);
	v4l2_show_support_fmt(&vd);
	v4l2_set_capture_fmt(&vd);
	v4l2_apply_capture_buffer(&vd);
	v4l2_set_capture_buffer(&vd);

	v4l2_get_frame_yuyv(&vd);


	v4l2_release_capture_buffer(&vd);
	v4l2_close(&vd);
}
