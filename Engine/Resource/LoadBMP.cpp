#include <Resource/LoadTexture.h>

std::pair<Texture*, u8*> LoadBMP(const String& path) {
	FILE* fp = fopen(path.c_str(), "rb");
	
	if (!fp)
		throw RuntimeException("Failed to open '" + path + "'");
	
	#define BMP_HEADER_SIZE 54
	
	unsigned char header[BMP_HEADER_SIZE];
	
	if (fread(header, 1, BMP_HEADER_SIZE, fp) != BMP_HEADER_SIZE)
		throw RuntimeException("'" + path + "' is not a valid .bmp file");
		
	if (header[0] != 'B' || header[1] != 'M')
		throw RuntimeException("'" + path + "' does not have a valid .bmp signature");
	
	u32 datapos	= *(int*)&(header[0x0A]);
    u32 size       = *(int*)&(header[0x22]);
    u32 width      = *(int*)&(header[0x12]);
    u32 height     = *(int*)&(header[0x16]);
    
    fseek(fp, datapos, SEEK_SET);
    
    unsigned char* data = new unsigned char[size];
    if (fread(data, 1, size, fp) != size)
		throw RuntimeException("'" + path + "' is not a valid .bmp file");
		
	fclose(fp);
	
	return std::make_pair(new Texture(Vec2i(width, height)), data);
}
