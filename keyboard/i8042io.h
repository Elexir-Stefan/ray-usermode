/*
 * i8042io.h
 *
 *  Created on: May 20, 2010
 *      Author: stefan
 */

#ifndef I8042IO_H_
#define I8042IO_H_

#define KBD_PORT_DATA	0x60
#define KBD_PORT_CMD	0x64
#define KBD_PORT_DIS	0x61

static inline UINT8 I8042ReadStatus(void) {
	UINT8 ret;
	InPortB(KBD_PORT_CMD, ret);
	return ret;
}

static inline UINT8 I8042ReadData(void) {
	UINT8 ret;
	//while((I8042ReadStatus() & I8042_STR_OBF) == 0);

	InPortB(KBD_PORT_DATA, ret);
	return ret;
}

#define I8042WriteData(val) OutPortB(KBD_PORT_DATA, val)
#define I8042WriteCommand(val) OutPortB(KBD_PORT_CMD, val)


#endif /* I8042IO_H_ */
