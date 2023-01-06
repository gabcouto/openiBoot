#include "openiboot.h"
#include "commands.h"
#include "nvram.h"
#include "hfs/common.h"
#include "hfs/bdev.h"
#include "hfs/fs.h"
#include "hfs/hfsplus.h"
#include "printf.h"
#include "util.h"

uint8_t *script_load_hfs_file(int part, char *path, uint32_t *size)
{
	Volume* volume;
	io_func* io;
	io = bdev_open(part);
	if(io == NULL) {
		bufferPrintf("fs: cannot read partition!\r\n");
		return NULL;
	}

	volume = openVolume(io);
	if(volume == NULL) {
		bufferPrintf("fs: cannot openHFS volume!\r\n");
		return NULL;
	}

	HFSPlusCatalogRecord* record;
	char *name;
	uint8_t *address;
	uint32_t sz = 0;
	record = getRecordFromPath(path, volume, &name, NULL);
	if(record != NULL)
	{
		if(record->recordType == kHFSPlusFolderRecord)
			bufferPrintf("scripting: That path leads to a directory!\n");
		else
			sz = readHFSFile((HFSPlusCatalogFile*)record, &address, volume);
	}
	else
		bufferPrintf("scripting: No such file or directory %s.\n", path);

	closeVolume(volume);
	CLOSE(io);

	if(address)
	{
		*size = sz;
		return address;
	}

	return NULL;
}

uint8_t *script_load_file(char *id, uint32_t *size)
{
	if(*id == '(') // In format (hdX,Y)/some/path
	{
		char *ptr = strdup(id+1);
		char *devEnd = strchr(ptr, ')');
		if(devEnd)
		{
			*devEnd = 0;
			devEnd++;

			int part = 0;
			char *partStart = strchr(ptr, ',');
			if(partStart)
			{
				*partStart = 0;
				partStart++;

				part = parseNumber(partStart);
			}

			int device = parseNumber(ptr);
			uint8_t *ret = script_load_hfs_file(device+part, devEnd, size); // TODO: Hahahah! I should really fix this. -- Ricky26

			free(ptr);

			return ret;
		}
	}
	else if(*id == '/') // In format /some/path of the system partition
	{
		return script_load_hfs_file(0, id, size);
	}
	else if(*id >= '0' && *id <= '9')
	{
		char *ptr = strdup(id);
		char *extent = strchr(ptr, '+');
		uint8_t *ret = NULL;

		if(extent)
		{
			*extent = 0;
			extent++;

			uint32_t sz = parseNumber(extent);
			uint32_t addr = parseNumber(id);
			*size = sz;
			ret = (uint8_t*)addr;
		}
		else
			bufferPrintf("scripting: Invalid memory location, must be in the format location+size.\n");

		free(ptr);
		return ret;
	}

	bufferPrintf("scripting: Badly formatted URI, %s\n", id);
	return NULL;
}

char **script_split_file(char *_data, uint32_t _sz, uint32_t *_count)
{
	int count = 0;
	char *ptr = _data;
	char *end = ptr + _sz;
	while(ptr < end)
	{
		switch(*ptr)
		{
		case '\n':
			*ptr = '\0';

			// Fall through
		case '\0':
			count++;
			break;
		}

		ptr++;
	}	

	char **ret = malloc(sizeof(char**)*count);
	ptr = _data;
	ret[0] = ptr;
	int i = 1;
	while(ptr < end)
	{
		if(*ptr == 0)
		{
			ret[i] = ptr+1;
			i++;
		}
	
		ptr++;
	}

	*_count = count;
	return ret;
}

int script_run_command(char* command)
{
    int argc;
	char** argv = command_parse(command, &argc);
	int success = command_run(argc, argv);
	free(argv);
	return success;
}

int script_run_commands(char** cmds, uint32_t count)
{
	int i;
	for(i = 0; i < count; i++)
	{
		bufferPrintf("scripting: %s\n", cmds[i]);
		int ret = script_run_command(cmds[i]);
		if(ret != 0)
		{
			bufferPrintf("scripting: Failed to run command '%s'.\n", cmds[i]);
			return ret;
		}
	}

	return 0;
}

int script_run_file(char *path)
{
	uint32_t size, count;

	char *data = (char*)script_load_file(path, &size);
	if(!data)
	{
		bufferPrintf("scripting: Failed to load file '%s'.\n", path);
		return -1;
	}

	char **cmds = script_split_file(data, size, &count);
	if(!cmds)
	{
		bufferPrintf("scripting: Failed to parse script '%s'.\n", path);
		free(data);
		return -1;
	}
	
	int ret = script_run_commands(cmds, count);
	free(cmds);
	free(data);
	return ret;
}

