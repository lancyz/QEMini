
#ifndef _IMCMDPACKER_H
#define _IMCMDPACKER_H

#include "imCmdHeader.h"

class CIMCmdPacket
{
public:
	CIMCmdPacket();
	CIMCmdPacket(UINT uiSendID);
	~CIMCmdPacket();

	int SetupDataPkt(char * szBuf,ULONG ulMsgId, UCHAR ucCmdID, UINT uiRecvID, UCHAR ucType, char *data, UINT uiDataLen);

	VOID SetSendID(UINT uiSendID);
protected:
	VOID SetupHeaderData(char * szBuf, ULONG ulMsgId,UCHAR ucCmdID, UINT uiRecvID, UCHAR ucType);
	VOID CopyData(char * szBuf, UCHAR ucType, char *data, DWORD length);
	
private:
	UINT m_uiSendID;
};

#endif