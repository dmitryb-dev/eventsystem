#ifndef READ_WRITE_BUF_MAN_H
#define READ_WRITE_BUF_MAN_H

/*
 * It provides you instrument to manage your external buffer.
 * Example of cyclic buffer:
 *
 * int buf[3];
 *
 * if (bufMan_hasSpace(&man))
 * {
 *     buf[man.writePos] = 42;
 *     bufMan_writeStep(&man, 3);
 * }
 * if (bufMan_hasNew(&man))
 * {
 *     int read = buf[man.readPos]; // 42
 *     bufMan_readStep(&man, 3);
 * }
 */
typedef struct ReadWriteBufManager
{
	char readCount;
	char writtenCount;
	unsigned char readPos;
	unsigned char writePos;
} ReadWriteBufManager;

int bufMan_hasNew(ReadWriteBufManager *man)
{
	return man->readCount != man->writtenCount;
}

int bufMan_hasSpace(ReadWriteBufManager *man)
{
	return man->readPos != man->writePos || !bufMan_hasNew(man);
}

void bufMan_writeStep(ReadWriteBufManager *man, char bufSize)
{
	if (++man->writePos >= bufSize) {
		man->writePos = 0;
	}
	man->writtenCount++;
}

void bufMan_readStep(ReadWriteBufManager *man, char bufSize)
{
	if (++man->readPos >= bufSize) {
		man->readPos = 0;
	}
	man->readCount++;
}

#endif
