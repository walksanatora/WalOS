#include <efi.h>
#include <efilib.h>

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){
	EFI_FILE* LoadedFile;

	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid,(void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Directory == NULL){
		FileSystem->OpenVolume(FileSystem,&Directory);
	}
	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path,EFI_FILE_MODE_READ,EFI_FILE_READ_ONLY);
	if (s != EFI_SUCCESS){
		return NULL;
	} 
	return LoadedFile;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"bootloader online \r\n");
	if(LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable) == NULL){
		Print(L"! UNABLE TO LOAD KERNEL ! \r\n");
	} else
	{
		Print(L"Kernel loaded properly");
	}
	
	Print(L"boot finished exiting \r\n");
return EFI_SUCCESS; // Exit the UEFI application
}
