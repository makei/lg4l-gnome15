#ifndef GINPUT_H_INCLUDED
#define GINPUT_H_INCLUDED		1

struct ginput_data {
  struct input_dev * input_dev; /* the input_dev for this data */
  struct hid_device * hdev;     /* the parent hid device */
  
  int key_count;                /* no of keys in the kernel keymap */
  int * scancode_state;         /* length = key_count */
  int * keycode;                /* length = 3 * key_count */

  u8 curkeymap;                 /* current macro keymap index */
  u8 keymap_switching;          /* kernel keymap switch enable flag */

  /* pointer to a keymap switch notification function of the parent driver, or NULL */
  void (*notify_keymap_switched)(struct ginput_data * ginput_data, 
                                 unsigned int index);

  spinlock_t * lock;            /* lock from the gNN_data structure */
};

/* functions exposed by the module */

int ginput_alloc(struct ginput_data * data, int key_count);
void ginput_free(struct ginput_data * data);


void ginput_handle_key_event(struct ginput_data *data,
                             int scancode,
                             int value);

int ginput_setkeycode(struct input_dev * dev,
                      const struct input_keymap_entry * ke,
                      unsigned int * old_keycode);
int ginput_getkeycode(struct input_dev *dev,
                      struct input_keymap_entry *ke);

ssize_t ginput_set_keymap_index(struct ginput_data *data, unsigned k);
ssize_t ginput_keymap_index_show(struct device *dev,
                                 struct device_attribute *attr,
                                 char *buf);
ssize_t ginput_keymap_index_store(struct device *dev,
                                  struct device_attribute *attr,
                                  const char *buf, size_t count);


ssize_t ginput_keymap_show(struct device *dev,
                           struct device_attribute *attr,
                           char *buf);
ssize_t ginput_keymap_store(struct device *dev,
                            struct device_attribute *attr,
                            const char *buf, size_t count);


ssize_t ginput_set_keymap_switching(struct ginput_data *data, unsigned k);
ssize_t ginput_keymap_switching_show(struct device *dev,
                                     struct device_attribute *attr,
                                     char *buf);
ssize_t ginput_keymap_switching_store(struct device *dev,
                                      struct device_attribute *attr,
                                      const char *buf, size_t count);


#endif 
