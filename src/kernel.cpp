#include "multiboot.h"
#include "video.h"
#include "memory.h"

extern "C" void _main(multiboot_info_t *mbd, unsigned int magic);

void _main(multiboot_info_t *mbd, unsigned int magic)
{
	__memory.initialize(mbd, magic);
	//__memory.showfullmap();

	char *str = (char*)__memory.alloc(sizeof(char)*27, 0);
	if (str != NULL)
	{
		for (int x = 0; x < 26; x++)
		{
			str[x] = 97 + x;
		}
		str[26] = '\n';
		__video.writestr(str);
	}

	char *str2 = (char*)__memory.alloc(sizeof(char)*11, 0);
	if (str2 != NULL)
	{
		for (int x = 0; x < 10; x++)
		{
			str2[x] = 97 + x;
		}
		str2[10] = '\n';
		__video.writestr(str2);
	}

	//__memory.showfreemap();

	__memory.free(str);

	//__memory.showfreemap();

	__memory.free(str2);

	__memory.showfreemap();
}
