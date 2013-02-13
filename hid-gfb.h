#ifndef GFB_PANEL_H_INCLUDED
#define GFB_PANEL_H_INCLUDED		1

#define GFB_PANEL_TYPE_160_43_1		0
#define GFB_PANEL_TYPE_320_240_16	1

#include <linux/fb.h>

/* Per device data structure */
struct gfb_data {
	struct hid_device *hdev;
	struct kref kref;

	/* Framebuffer stuff */
	int panel_type;         /* GFB_PANEL_TYPE_160_43_1 or GFB_PANEL_TYPE_320_240_16 */

	struct fb_info *fb_info;

	struct fb_deferred_io fb_defio;
	u8 fb_update_rate;

	u8 *fb_bitmap;          /* device-dependent bitmap */
	u8 *fb_vbitmap;         /* userspace bitmap */
        int fb_vbitmap_busy;    /* soft-lock for vbitmap; protected by fb_urb_lock */
	size_t fb_vbitmap_size; /* size of vbitmap */

	struct delayed_work free_framebuffer_work;

        /* USB stuff */
	struct urb *fb_urb;
	spinlock_t fb_urb_lock;

        /* Userspace stuff */
        int fb_count;      /* open file handle counter */
        bool virtualized;  /* true when physical device not present */

	/* atomic_t usb_active; /\* 0 = update virtual buffer, but no usb traffic *\/ */
};

ssize_t gfb_fb_node_show(struct device *dev,
                         struct device_attribute *attr,
                         char *buf);

ssize_t gfb_fb_update_rate_show(struct device *dev,
                                struct device_attribute *attr,
                                char *buf);

ssize_t gfb_fb_update_rate_store(struct device *dev,
                                 struct device_attribute *attr,
                                 const char *buf, size_t count);

struct gfb_data * gfb_probe(struct hid_device *hdev, const int panel_type);

void gfb_remove(struct gfb_data *data);

#endif
