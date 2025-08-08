#pragma once
#include "../extern.h"
#pragma pack(push, 1)

enum EDID_Extension_Flag{
	EDID_Standard = 0
};

typedef struct {

	u8  header[8]; 		// Fixed header pattern: 00 FF FF FF FF FF FF 00
	u16 manufacturer_id; 	// Legacy PnP ID, big-endian
	u16 product_code; 		// Little-endian
	uint32_t serial_number; 	// Little-endian
	u8  week_of_manufacture; 	// Or 0xFF for model year
	u8  year_of_manufacture; 	// Year - 1990, or model year if week_of_manufacture is 0xFF
	u8  edid_version; 		// Usually 0x01
	u8  edid_revision; 	// Usually 0x03 or 0x04
	
	u8  video_input_parameters;// Analog/Digital, bit depth, interface type
	u8  h_screen_size_cm; 	// Or aspect ratio if v_screen_size_cm is 0
	u8  v_screen_size_cm; 	// Or aspect ratio if h_screen_size_cm is 0
	u8  gamma; 		// (gamma * 100) - 100
	u8  features_bitmap; 	// DPMS support, display type, color space, preferred timing
	
	u8  chromaticity_coordinates[10]; 	// 10-bit CIE xy coordinates for red, green, blue, and white point
	
	u8  established_timings[3]; 	// Bitmap for established timing modes
	
	struct {
	    u8 x_resolution_minus_31; 	// (datavalue + 31) * 8
	    u8 aspect_ratio_v_freq; 	// Bits 7-6: Aspect Ratio, Bits 5-0: Vertical Frequency (datavalue + 60)
	} standard_timings[8]; 			// Up to 8 standard timing modes
	
	union {
	    struct{
		u16 pixel_clock;
    		u8  h_active_lsb;
		u8  h_blanking_lsb;
		u8  h_active_blanking_msb; // Bits 7-4: HActive MSB, Bits 3-0: HBlanking MSB
		u8  v_active_lsb;
		u8  v_blanking_lsb;
		u8  v_active_blanking_msb; // Bits 7-4: VActive MSB, Bits 3-0: VBlanking MSB
		u8  h_sync_offset_lsb;
		u8  h_sync_pulse_width_lsb;
		u8  v_sync_offset_pulse_width_lsb; // Bits 7-4: VSync Offset LSB, Bits 3-0: VSync Pulse Width LSB
		// Bits 7-6: HSync Offset MSB, Bits 5-4: HSync Pulse Width MSB, Bits 3-2: VSync Offset MSB, Bits 1-0: VSync Pulse Width MSB
		u8  h_v_sync_offset_pulse_width_msb;
		u8  h_image_size_lsb;
		u8  v_image_size_lsb;
		u8  h_v_image_size_msb; // Bits 7-4: HImageSize MSB, Bits 3-0: VImageSize MSB
		u8  h_border;
		u8  v_border;
		u8  features_bitmap;
	    }dtd;
	    struct{
    		u16 reserved1; // Should be 0x0000
    		u8  reserved2; // Should be 0x00
    		u8  descriptor_type;
    		u8  reserved3; // Should be 0x00, except for Display Range Limits Descriptor
    		u8  data[13];
	    }mon;
	} descriptor_blocks[4]; 		// Four 18-byte blocks for DTDs or monitor descriptors
	
	u8  extension_flag; 		// Number of extension blocks to follow (0 if none)
	u8  checksum; 			// Sum of all 128 bytes should be 0 (mod 256)

}Display_EDID_Standard;


#pragma pack(pop)
