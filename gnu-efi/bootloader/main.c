#include <efi.h>
#include <efilib.h>

EFI_FILE* LoadFile(EFI_FILE* Directory){
	
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"bootloader online \r\n");
	Print(L"boot finished exiting \r\n");
return EFI_SUCCESS; // Exit the UEFI application
}
