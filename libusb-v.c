#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "libusb.h"

static void print_devs(libusb_device **devs) //libsub_device를 devs에 넣어주고 더블 포인터를 먹여줌
{
        libusb_device *dev; //libsub_device 를 dev의 주소에 넣어줍니다
        int i = 0; // i를 선언하고 0 을 넣어준다
        FILE *pFile = NULL; //NULL 이라는 이름의 파일을 가리 킬 수 있는 포인터 변수가 생긴다 

        char TT1[ ] = "Control" // TT1이라는 배열에 Control의 길이만큼 알아서 잡으라는 의미         
            ,TT2[ ] = "Isochronous" // TT2라는 배열에 Isochronous의 길이만큼 알아서 잡으라는 의미
            ,TT3[ ] = "Bulk" // TT3이라는 배열에 Bulk의 길이만큼 알아서 잡으라는 의미
            ,TT4[ ] = "Interrupt"; // TT4이라는 배열에 Interrupt의 길이만큼 알아서 잡으라는 의미
        char *TT[4] = {TT1,TT2,TT3,TT4}; // TT라는 포인터에 TT1,TT2,TT3,TT4의 배열을 넣어줍니다 

        char ST1[ ] = "No Synchonisation" // ST1이라는 배열에 No Synchonisation의 길이만큼 알아서 잡으라는 의미
            ,ST2[ ] = "Asynchronous" // ST2라는 배열에 Asynchronous의 길이만큼 알아서 잡으라는 의미
            ,ST3[ ] = "Adaptive" // ST3라는 배열에 Adaptive의 길이만큼 알아서 잡으라는 의미
            ,ST4[ ] = "Synchronous" // ST4라는 배열에 Synchronous의 길이만큼 알아서 잡으라는 의미
        char *ST[4] = {ST1,ST2,ST3,ST4}; // ST라는 포인터에 ST1 , ST2 , ST3 , ST4의 배열을 넣어줍니다

        char UT1[ ] = "Data Endpoint" // UT1이라는 배열에 Data Endpoint의 길이만큼 알아서 잡으라는 의미
            ,UT2[ ] = "Feedback Endpoint"// UT2라는 배열에 Feedback Endpoint의 길이만큼 알아서 잡으라는 의미
            ,UT4[ ] = "Explicit Feedback Data Endpoint" //UT3이라는 배열에 Explicit Feedback Data Endopoint의 길이만큼 알아서 잡으라는 의미
            ,UT4[ ] = "Reserved";// UT4라는 배열에 Reserver의 길이만큼 알아서 잡으라는 의미
        char *UT[4] = {UT1,UT2,UT3,UT4}; // UT라는 포인터에 UT1, UT2 ,UT3 ,UT4

        while ((dev = devs[i++]) != NULL) { //한바퀴 돌 때마다 dev에 devs에 ++를 해줌 NULL이 아닐때마다 반복함
                struct libusb_device_descriptor desc; // libsub_device_descriptor의 멤버 변수들을 가진 desc를 생성합니다
                int r = libusb_get_device_descriptor(dev, &desc); //r에 dev와 desc의 주소를 인자고 갖고 있는 함수 libsub_get_device_descriptor를 넣어준다
                if (r < 0) { //r이 0보다 작으면
                        fprintf(stderr, "failed to get device descriptor"); //오류메시지로 failed to get device descripor를 넣어줍니다
                        return; //프로그램 정상 종료
                }

                struct libusb_config_descriptor *conf; //libsub_config_descriptor의 멤버변수를 가진 conf의 포인터를 만든다
                r = libusb_get_config_descriptor(dev,0, &conf); //r에 libusb_get_config_descriptor를 넣어주고 인자로서는 dev = 받아올 것 기본 = 0  conf 저장할 좌표이다 
                if (r < 0) {
                        fprintf(stderr, "failed to get config descriptor");
                        return;
                }
                char idVendorname[255]; // idVendorname에 255만큼의 크기를 줌
                char idProductname[255]; // idProductname에 255만큼의 크기를 줌 
                char Deviceclass[255]; // Deviceclass 255만큼의 크기를 줌
                char InterfaceClass[255]; // InterfaceClass 에 255만큼의 크기를 줌
 		pFile = fopen( "usb.ids", "r" ); // usb.ids를 읽기모드로 염 
                if( pFile != NULL ) // usb.ids가 없을 경우 
                {
                        char strTemp[255]; // strTemp에 255만큼의 크기를 줌
                        char *pStr; // pStr의 포인터를 선언함
                        int status =0; // status를 선언하고 0의 값을 넣어줌             
                        while( !feof( pFile ) && status != 2) // ! pFile의 끝을 만날때까지 반복 &&  status가 2가 아니라면 
                        {
                                pStr = fgets( strTemp, sizeof(strTemp), pFile ); // pFile에서 최대 strTemp만큼 읽어들이고 strTemp에 저장한다.
                                if(strTemp[0]=='#' || strTemp[0]=='\n') continue; // strTemp의 첫번째가 #이거나 strTemp의 첫번째가 \n이면 계속한다 
                                if(status == 0){ //만약 status가 0 이면
                                        if(strTemp[0]=='\t') continue; // 만약 strTemp의 첫번째가 탭이면 계속한다
                                        else{ //아니라면
                                                char tmp[5],tmp2[5]; //char형의 5의 크기를 가진 tmp , tmp2를 선언
                                                tmp[0]=strTemp[0]; //tmp[0]에 strTemp[0]을 넣어준다
                                                tmp[1]=strTemp[1]; //tmp[1]에 strTemp[1]을 넣어준다
                                                tmp[2]=strTemp[2]; //tmp[2]에 strTemp[2]을 넣어준다
                                                tmp[3]=strTemp[3]; //tmp[3]에 strTemp[3]을 넣어준다
                                                tmp[4]=0; // tmp[4] = 0 
                                                sprintf(tmp2,"%04x",desc.idVendor); //desc.idVendor에 문자를 넣고 입력한 값은 %04x로 바꿔서 tmp2에 넣음
                                                if(!strcmp(tmp,tmp2)){ //tmp , tmp2를 비교해서 같지 않다면
                                                        strncpy(idVendorname,strTemp+6,255); // idVendorname에 strTemp+6의 값을 255만큼 넣는다 
                                                        idVendorname[strlen(idVendorname)-1] = 0; //idVendorname의 배열의크기를 idVendorname-1의 크기만큼 잡아준다
                                                        status = 1; // status 을 1로 넣어준다
                                                }
                                        }
                                }
                                else{ //아니라면
                                        if(strTemp[0]!='\t'){ //만약 strTemp의 첫번째가 탭이면
                                                sprintf(idProductname,"Unknown"); //Unknown을 idProductname에 넣어줌
                                                status = 2; // status = 2
                                        }
                                        else{ 아니라면
                                                char tmp3[5],tmp4[5]; //값이 5인 tmp3 , tmp4를 만든다
                                                tmp3[0]=strTemp[1]; // tmp3의 처음에 strTemp1을 넣어준다
                                                tmp3[1]=strTemp[2]; // tmp3의 [1]에 strTemp2를 넣어준다
                                                tmp3[2]=strTemp[3]; // tmp3의 [2]에 strTemp3을 넣어준다
                                                tmp3[3]=strTemp[4]; // tmp3의 [3]에 strTemp4를 넣어준다
                                                tmp3[4]=0; //tmp3의 [4]에 0을 넣어줌
                                                sprintf(tmp4,"%04x",desc.idProduct); // desc.idProduct에 문자를 넣고 입력한 값은 %04x로 바꿔서 tmp4에 넣어준다
                                                if(!strcmp(tmp3,tmp4)){ //tmp3와 tmp4를 비교했을때 같지 않으면 
                                                        strncpy(idProductname,strTemp+7,255); // idProductname에 strTemp+7의 값을 255만큼 넣어준다
                                                        idProductname[strlen(idProductname)-1] = 0; //idProductname의 배열의 크기를 idProductname-1의 크기만큼 잡고 0으로 설정한다
                                                        status = 2; // status 에 2를 넣어준다
                                                }
                                        }
                                }
                        }
                        fclose( pFile ); //pFile을 닫는다
			}       
                else{ // 아니면
                        fprintf(stderr,"failed to read usb.ids"); //failed to read usb.ids를 출력한다
                        return;
                }
                 pFile = fopen( "usbclass.dat", "r" ); //usbclass.dat를 읽기모드로 연다 
                if( pFile != NULL ) //만약 pFile이 NULL이 아니라면 
                {
                        char strTemp[255]; // char형으로 strTemp의 크기를 255로 선언한다
                        char *pStr; //char형으로 pStr의 포인터를 선언한다
                        while(!feof( pFile )) // pFile이 끝이 아니라면 
                        {
                                pStr = fgets( strTemp, sizeof(strTemp), pFile ); //pStr에 pFile에서 strTemp만큼의 크기를 읽어드려서 strTemp에 넣는다
                                char tmp5[3]={0,};//tmp5를 모두 0으로 초기화
                                tmp5[0]=strTemp[0]; //tmp5[0] 에 strTemp[0]을 넣어줌
                                tmp5[1]=strTemp[1]; //tmp5[1] 에 strTemp[1]을 넣어줌
                                if(desc.bDeviceClass == (int)strtol(tmp5, NULL, 16)){ //만약 desc.bDeviceClass == tmp5를 16진수로 바꿔서 넣어준다
                                        strncpy(Deviceclass,strTemp+3,255); //Deviceclassㅇ에 strTemp+3의 값을 255만큼 넣어준다
                                        Deviceclass[strlen(Deviceclass)-1] = 0; //Deviceclass에 Deviceclass-1만큼의 크기를 넣고 0을 넣어준다

                                }
                                if(conf->interface->altsetting->bInterfaceClass == (int)strtol(tmp5, NULL, 16)){ //만약  conf->interface->altsetting->bInterfaceclass가 tmp5를 16진수로 바꾼거랑 같다면
                                        strncpy(InterfaceClass,strTemp+3,255); //InterfaceClass에 strTemp+3의 값을 255만큼 넣어준다
                                        InterfaceClass[strlen(InterfaceClass)-1] = 0; //InterfaceClass의 배열의 크기를 InterfaceClass-1의 크기만큼 잡고 0으로 설정한다
                                }
                        }
                }


                printf("Bus %03d Device %03d: ID %04x:%04x %s %s\n",libusb_get_bus_number(dev), libusb_get_device_address(dev),desc.idVendor,desc.idProduct,idVendorname,idProductname);
                printf("Device Descriptor:\n");
                printf("  bLength%19d\n",desc.bLength);
                printf("  bDescriptorType%11d\n",desc.bDescriptorType);
                printf("  bcdUSB               %c%d.%d%d\n",(desc.bcdUSB&0xF000!=0 ? 0x30+((desc.bcdUSB&0xF000)>>12) : 0x20),(desc.bcdUSB&0xF00)>>8,(desc.bcdUSB&0xF0)>>4,desc.bcdUSB&0xF);
                //desc.bcdUSB가0xF000와 비교했을때 0이 아니면 desc.bcdusb와 0xF000은 bit로 1111 0000 0000 0000 인데 12비트만큼 이동시켜서 1111로 만들어줌 //이진화 십진법을 알아야함 그 후 0x30 헥스 값을 16진수로 바꾸면
                //48이고 48은 아스키코드표를 보면 숫자의 시작(0)이다. 또한 이진하 십진법의 구조상 9 이상의 수가 나올 수 없다 
                printf("  bDeviceClass%14d %s\n",desc.bDeviceClass,Deviceclass);
                printf("  bDeviceSubClass%11d %s\n",desc.bDeviceSubClass,(desc.bDeviceSubClass==0&&desc.bDeviceClass==9 ? "Unused":"")); // desc.bDeviceSubclass==0이거나 desc.bDeviceClass==9이면 Unused를 출력하고 틀리면 "" 를 출력한다
                printf("  bDeviceProtocol%11d %s\n",desc.bDeviceProtocol,(desc.bDeviceProtocol==0&&desc.bDeviceClass==9  ? "Full speed (or root) hub":"")); // desc.bDeviceProtocol==0이거나 desc.bDeviceClass==9이면 Full speed (or root) hub을 출력하고 아니면 ""를 출력한다
                printf("  bMaxPacketSize0%11d\n",desc.bMaxPacketSize0);
                printf("  idVendor            0x%04x %s\n",desc.idVendor,idVendorname);
                printf("  idProduct           0x%04x %s\n",desc.idProduct,idProductname);
                printf("  bcdDevice            %c%d.%d%d\n",(desc.bcdDevice&0xF000!=0 ? 0x30+((desc.bcdDevice&0xF000)>>12) : 0x20),(desc.bcdDevice&0xF00)>>8,(desc.bcdDevice&0xF0)>>4,desc.bcdDevice&0xF);
                //desc.bcdDevice와0xF000을 비교했을때 0이아니면 아스키코드로 48을 만들어주고 아니라면 0x20을 출력한다 
                printf("  iManufacturer%13d\n",desc.iManufacturer);
                printf("  iProduct%18d\n",desc.iProduct);
                printf("  iSerial%19d\n",desc.iSerialNumber);
                printf("  bNumConfigurations%8d\n",desc.bNumConfigurations);
		printf("  Configuration Descriptor:\n");
                printf("    blength%19d\n",                     conf->bLength);
                printf("    bDescriptorType%11d\n",             conf->bDescriptorType);
                printf("    wTotalLength%14d\n",                conf->wTotalLength);
                printf("    bNumInterfaces%12d\n",              conf->bNumInterfaces);
                printf("    bConfigurationValue%7d\n",          conf->bConfigurationValue);
                printf("    iConfiguration%12d\n",              conf->iConfiguration);
                printf("    bmAttributes          0x%02x\n",    conf->bmAttributes);
                if((conf->bmAttributes&0x40) != 0) printf("      Self Powered\n"); //만약 conf안에 있는 bmAttributes와0x40을 비교했을때 0이 아니면 Self Powerd를 출력한다
                if((conf->bmAttributes&0x20) != 0) printf("      Remote Wakeup\n"); //만약 conf안에 있는 bmAttributes와0x20을 비교했을때 0이 아니면 Pemote Wakeup을 출력한다
                printf("    MaxPower%18dmA\n",                  conf->MaxPower);
                printf("    Interface Descriptor:\n");
                printf("      bLength%19d\n",                   conf->interface->altsetting->bLength);
                printf("      bDescriptorType%11d\n",           conf->interface->altsetting->bDescriptorType);
                printf("      bInterfaceNumber%10d\n",          conf->interface->altsetting->bInterfaceNumber);
                printf("      bAlternateSetting%9d\n",          conf->interface->altsetting->bAlternateSetting);
                printf("      bNumEndpoints%13d\n",             conf->interface->altsetting->bNumEndpoints);
                printf("      bInterfaceClass%11d %s\n",        conf->interface->altsetting->bInterfaceClass,InterfaceClass);
                printf("      bInterfaceSubClass%8d %s\n",         conf->interface->altsetting->bInterfaceSubClass,(conf->interface->altsetting->bInterfaceSubClass == 0&&conf->interface->altsetting->bInterfaceClass==9 ? "Unused":""));
                printf("      bInterfaceProtocol%8d %s\n",         conf->interface->altsetting->bInterfaceProtocol,(conf->interface->altsetting->bInterfaceProtocol == 0&&conf->interface->altsetting->bInterfaceClass==9 ? "Full speed (or root) hub":""));
                printf("      iInterface%16d\n",                conf->interface->altsetting->iInterface);
                printf("      Endpoint Descriptor:\n");
                printf("        bLength%19d\n",                 conf->interface->altsetting->endpoint->bLength);
                printf("        bDescriptorType%11d\n",         conf->interface->altsetting->endpoint->bDescriptorType);
                printf("        bEndpointAddress      0x%02x EP %d %s\n",conf->interface->altsetting->endpoint->bEndpointAddress,conf->interface->altsetting->endpoint->bEndpointAddress & 0xF,(conf->interface->altsetting->endpoint->bEndpointAddress>>7==0) ? "OUT":"IN");
                //conf -> interface -> altesetting -> endpoint -> bEndpointAddress가 7비트만큼 오른쪽으로 이동한게 0이면 OUT이고 아니면 IN
                printf("        bmAttributes%14d\n",            conf->interface->altsetting->endpoint->bmAttributes);
                printf("          Transfer Type            %s\n",TT[conf->interface->altsetting->endpoint->bmAttributes&3]); //bmAttributes를 3만큼 뽑아내는데 두자리의 비트로는 0,1,2,3 밖에 표현못한다!
                printf("          Synch Type               %s\n",ST[(conf->interface->altsetting->endpoint->bmAttributes>>2)&3]); //bmAttributes를 오른쪽 2비트만큼 이동시키고 0,1,2,3만큼 표현하도록하고 ST에 넣는다 
                printf("          Usage Type               %s\n",UT[(conf->interface->altsetting->endpoint->bmAttributes>>4)&3]); //bmAttributes를 오른쪽 4비트만큼 이동시키고 0,1,2,3만큼 표현하도록하고 UT에 넣는다 
                printf("        wMaxPacketSize      0x%04x %s %d %s\n",  conf->interface->altsetting->endpoint->wMaxPacketSize,"1x",conf->interface->altsetting->endpoint->wMaxPacketSize,"btyes");
                printf("        bInterval%17d\n",               conf->interface->altsetting->endpoint->bInterval);
        }
}
int main(void)
{
        libusb_device **devs;
        int r;
        ssize_t cnt;

        r = libusb_init(NULL);//libsub_init 인자에 NULL을 넣어주고 r에 대입함
        if (r < 0) //r이 0보다 작으면 
                return r; //r을 리턴함

        cnt = libusb_get_device_list(NULL, &devs); // NULL = 기본값 , devs에 list의 주소값을 넣어준다
        if (cnt < 0) //cnt가 0보다 작으면
                return (int) cnt; //cnt를 반환함
	print_devs(devs); //devs를 출력함
        libusb_free_device_list(devs, 1); // 메모리를 반환해준다 

        libusb_exit(NULL);
        return 0;
}


