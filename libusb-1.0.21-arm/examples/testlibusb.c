/*
* Test suite program based of libusb-0.1-compat testlibusb
* Copyright (c) 2013 Nathan Hjelm <hjelmn@mac.ccom>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <stdio.h>
#include <string.h>

#include "libusb.h"

int verbose = 0;


int main() {
    libusb_device **devs;          //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL;    //a libusb session
    int r;                         //for return values
    ssize_t cnt;                   //holding number of devices in list
    r = libusb_init(&ctx);         //initialize a library session
    if(r < 0) {
        printf("Init Error");
        return 1;
    }
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) {
        printf("Get Device Error");
    }

    libusb_device_handle *dev_handle;         //a device handle
    dev_handle = libusb_open_device_with_vid_pid(ctx, 0x0079, 0x0006); //open mouse
    if(dev_handle == NULL) {
        printf("Cannot open device");
        libusb_free_device_list(devs, 1); //free the list, unref the devices in it
        libusb_exit(ctx);                 //close the session
        return 0;
    } else {
        printf("Device Opened");
        libusb_free_device_list(devs, 1);                     //free the list, unref the devices in it
        if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
            printf("Kernel Driver Active");
            if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
                printf("Kernel Driver Detached!");
        }
        r = libusb_claim_interface(dev_handle, 0);            //claim interface 0 (the first) of device (mine had jsut 1)
        if(r < 0) {
            printf("Cannot Claim Interface");
            return 1;
        }
        printf("Claimed Interface");
        int size;
        unsigned char datain[1024]="\0";
        unsigned char dataBak[1024]="\0";

        //for(i=0;i<300;i++)
        while(1)
        {
            int rr = libusb_interrupt_transfer(dev_handle,
                                               0x81,
                                               datain,
                                               0x0008,
                                               &size,
                                               1000);
            //printf("libusb_interrupt_transfer rr: ");
            //std::cout<<"libusb_interrupt_transfer rr: "<<rr<<endl;
            //cout<<"size: "<<size<<endl;
            //printf("size");

            int j;
            int bPrint = 0;
            for(j=0; j<size; j++)
            {
                if(  dataBak[j] != datain[j])
                    bPrint = 1;
            }

            if(!bPrint)
                continue;

            printf("data: ");

            for(j=0; j<size; j++)
                printf("%02x ", (unsigned char)(datain[j]));

            printf("\n");
            usleep(100000);

            for(j=0; j<size; j++)
                dataBak[j] = datain[j];
        }

        r = libusb_release_interface(dev_handle, 0); //release the claimed interface
        if(r!=0) {
            printf("Cannot Release Interface");
            return 1;
        }

        printf("Released Interface");
        libusb_attach_kernel_driver(dev_handle, 0);
        libusb_close(dev_handle);
        libusb_exit(ctx); //close the session
        return 0;
    }
}
