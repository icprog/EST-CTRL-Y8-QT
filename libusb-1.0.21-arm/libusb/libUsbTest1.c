#include <stdio.h>
#include <stdlib.h>
#include </opt/works/libusb-1.0.21/libusb/libusb.h>

void print_endpoint(struct libusb_endpoint_descriptor *endpoint)
{
printf(" bEndpointAddress: %02xh\n", endpoint->bEndpointAddress);
printf(" bmAttributes: %02xh\n", endpoint->bmAttributes);
printf(" wMaxPacketSize: %d\n", endpoint->wMaxPacketSize);
printf(" bInterval: %d\n", endpoint->bInterval);
printf(" bRefresh: %d\n", endpoint->bRefresh);
printf(" bSynchAddress: %d\n", endpoint->bSynchAddress);
}


void print_altsetting(struct libusb_interface_descriptor *interface)
{
int i;

printf(" bInterfaceNumber: %d\n", interface->bInterfaceNumber);
printf(" bAlternateSetting: %d\n", interface->bAlternateSetting);
printf(" bNumEndpoints: %d\n", interface->bNumEndpoints);
printf(" bInterfaceClass: %d\n", interface->bInterfaceClass);
printf(" bInterfaceSubClass: %d\n", interface->bInterfaceSubClass);
printf(" bInterfaceProtocol: %d\n", interface->bInterfaceProtocol);
printf(" iInterface: %d\n", interface->iInterface);

for (i = 0; i < interface->bNumEndpoints; i++)
print_endpoint(&interface->endpoint[i]);
}


void print_interface(struct libusb_interface *interface)
{
int i;

for (i = 0; i < interface->num_altsetting; i++)
print_altsetting(&interface->altsetting[i]);
}


void print_configuration(struct libusb_config_descriptor *config)
{
int i;

printf(" wTotalLength: %d\n", config->wTotalLength);
printf(" bNumInterfaces: %d\n", config->bNumInterfaces);
printf(" bConfigurationValue: %d\n", config->bConfigurationValue);
printf(" iConfiguration: %d\n", config->iConfiguration);
printf(" bmAttributes: %02xh\n", config->bmAttributes);
printf(" MaxPower: %d\n", config->MaxPower);

for (i = 0; i < config->bNumInterfaces; i++)
print_interface(&config->interface[i]);
}


int main(void)
{
	struct usb_bus *bus;
	struct usb_device *dev;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	printf("bus/device idVendor/idProduct\n");
	/*
	for (bus = usb_busses; bus; bus = bus->next) {
		for (dev = bus->devices; dev; dev = dev->next) 
		{
			int ret, i;
			char string[256];
			usb_dev_handle *udev;

			printf("%s/%s %04X/%04X\n", bus->dirname, dev->filename,
			dev->descriptor.idVendor, dev->descriptor.idProduct);

			udev = usb_open(dev);
			if (udev) {
			if (dev->descriptor.iManufacturer) {
			ret = usb_get_string_simple(udev, dev->descriptor.iManufacturer, string, sizeof(string));
			if (ret > 0)
			printf("- Manufacturer : %s\n", string);
			else
			printf("- Unable to fetch manufacturer string\n");
			}

			if (dev->descriptor.iProduct) {
			ret = usb_get_string_simple(udev, dev->descriptor.iProduct, string, sizeof(string));
			if (ret > 0)
			printf("- Product : %s\n", string);
			else
			printf("- Unable to fetch product string\n");
			}

			if (dev->descriptor.iSerialNumber) {
			ret = usb_get_string_simple(udev, dev->descriptor.iSerialNumber, string, sizeof(string));
			if (ret > 0)
			printf("- Serial Number: %s\n", string);
			else
			printf("- Unable to fetch serial number string\n");
			}

			usb_close (udev);
			}

			if (!dev->config) {
				printf(" Couldn't retrieve descriptors\n");
				continue;
			}

			for (i = 0; i < dev->descriptor.bNumConfigurations; i++)
				print_configuration(&dev->config[i]);
			}
		}
	*/
	libusb_device_handle *dev_handle;  
	 libusb_context *ctx=NULL;  
	 struct  libusb_device_descriptor desc;  
	 int r;  
	 ssize_t cnt;  
	 r=libusb_init(&ctx);  
	 if(r<0)  
	 {  
	     printf("init error");  
	     //QMessageBox::about(this,"haha","initialerror");  
	     return ;  
	 }  
	 libusb_set_debug(ctx,3);  

	dev_handle=libusb_open_device_with_vid_pid(ctx,0x0079,0x0006); 

	return 0;
}
