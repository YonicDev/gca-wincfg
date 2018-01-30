#include <nan.h>
#include <v8.h>
#include <iostream>
#include <sstream>

#include "libwdi.h"


using namespace Nan;

struct wdi_device_info *device, *list;
struct wdi_options_create_list options;
struct wdi_options_prepare_driver driver_options;
struct wdi_options_install_driver installer_options;

const short WIIU_VID = 0x057E;
const short WIIU_PID = 0x0337;

NAN_METHOD(GetAdapterDriver) {
	if (info.Length() > 0) {
		std::stringstream ss;
		ss << "GetAdapterDriver has " << info.Length() << " parameters, when it only accepts 0";
		v8::Local<v8::String> message = New<v8::String>(ss.str()).ToLocalChecked();
		ThrowTypeError(message);
		return;
	}
	options.list_all = true;
	if (wdi_create_list(&list, &options) == WDI_SUCCESS) {
		for (device = list; !(device->vid == WIIU_VID && device->pid == WIIU_PID) && device != NULL; device = device->next);
		if (device != NULL) {
			v8::Local<v8::String> return_value = New<v8::String>(device->driver).ToLocalChecked();
			info.GetReturnValue().Set(return_value);
		} else
			ThrowError("No compatible Gamecube Adapter has been found");
		wdi_destroy_list(list);
	}
}

NAN_METHOD(PrepareAdapterDriver) {
	if (info.Length() != 2) {
		std::stringstream ss;
		ss << "GetAdapterDriver has " << info.Length() << " parameters, when it only accepts 2";
		v8::Local<v8::String> message = New<v8::String>(ss.str()).ToLocalChecked();
		ThrowTypeError(message);
		return;
	} else if (!info[0]->IsString()) {
		ThrowTypeError("Expected a String in arg 0 of PrepareAdapterDriver.");
		return;
	} else if (!info[1]->IsString()) {
		ThrowTypeError("Expected a String in arg 1 of PrepareAdapterDriver.");
		return;
	}
	if (wdi_create_list(&list, &options) == WDI_SUCCESS) {
		driver_options.driver_type = WDI_WINUSB;
		for (device = list; !(device->vid == WIIU_VID && device->pid == WIIU_PID) && device != NULL; device = device->next);
		if (device != NULL) {
			v8::String::Utf8Value path(info[0]->ToString());
			v8::String::Utf8Value name(info[1]->ToString());
			int errcode = wdi_prepare_driver(device, *path, *name, &driver_options);
			v8::Local<v8::Number> return_value = New<v8::Number>(errcode);
			info.GetReturnValue().Set(return_value);
		} else
			ThrowError("No compatible Gamecube Adapter has been found");
		wdi_destroy_list(list);
	} else
		ThrowError("Windows Driver Installer could not find any USB device.");
}

NAN_METHOD(InstallAdapterDriver) {
	int timeout;
	if (info.Length() != 2) {
		std::stringstream ss;
		ss << "GetAdapterDriver has " << info.Length() << " parameters, when it only accepts 2 or 3.";
		v8::Local<v8::String> message = New<v8::String>(ss.str()).ToLocalChecked();
		ThrowTypeError(message);
		return;
	}
	else if (!info[0]->IsString()) {
		ThrowTypeError("Expected a String in arg 0 of InstallAdapterDriver.");
		return;
	}
	else if (!info[1]->IsString()) {
		ThrowTypeError("Expected a String in arg 1 of InstallAdapterDriver.");
		return;
	}
	timeout = info[2]->IsUndefined() || !info[2]->IsNumber()? 30000 : info[2]->Int32Value();;
	if (wdi_create_list(&list, &options) == WDI_SUCCESS) {
		installer_options.pending_install_timeout = timeout;
		driver_options.driver_type = WDI_WINUSB;
		for (device = list; !(device->vid == WIIU_VID && device->pid == WIIU_PID) && device != NULL; device = device->next);
		if (device != NULL) {
			v8::String::Utf8Value path(info[0]->ToString());
			v8::String::Utf8Value name(info[1]->ToString());
			int errcode = wdi_install_driver(device, *path, *name, &installer_options);
			v8::Local<v8::Number> return_value = New<v8::Number>(errcode);
			info.GetReturnValue().Set(return_value);
		}
		else
			ThrowError("No compatible Gamecube Adapter has been found. Make sure you have one plugged in.");
		wdi_destroy_list(list);
	}
}

NAN_MODULE_INIT(Init) {
	NAN_EXPORT(target, GetAdapterDriver);
	NAN_EXPORT(target, PrepareAdapterDriver);
	NAN_EXPORT(target, InstallAdapterDriver);
}

NODE_MODULE(gca_wincfg, Init)