// KRoleInfomation.h: interface for the KRoleInfomation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KROLEINFOMATION_H__AECE97BE_EEC0_48CE_AFA1_C55FCFE87C3E__INCLUDED_)
#define AFX_KROLEINFOMATION_H__AECE97BE_EEC0_48CE_AFA1_C55FCFE87C3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MAX_ROLEINFORMATION_SIZE 50000
#define MAXSIZE_ROLENAME 100
#include "windows.h"
#pragma warning(disable:4786)
#include "s3dbinterface.h"
#include "KroleDBHeader.h"
#include "CriticalSection.h"
#include "..\MultiServer\Common\tstring.h"

#include <list>
#include <map>
using namespace std;

struct TGetRoleInfoFromDB
{
	unsigned long	nNetId;
	char	szRoleName[MAXSIZE_ROLENAME];
	unsigned long	ulIdentity;
	unsigned char	nSaveCmd;
};

class KRoleInfomation  
{
public:
	KRoleInfomation();
	virtual ~KRoleInfomation();
	void	Clear();			//清除所有数据
	BYTE *	GetRoleInfoBuffer(size_t & nRoleInfoSize);
	TCmd *	CreateRoleInfoTCmdData(size_t &nRoleInfoSize);
	BOOL	CopyRoleInfoBuffer(BYTE * pBuffer ,size_t & nRoleInfoSize);
	BOOL	GetBaseRoleInfo(TRoleBaseInfo * pRoleBaseInfo);
	BOOL	SetRoleInfoBuffer(BYTE * pRoleInfoBuffer, size_t nRoleInfoSize);
	BOOL	GetRoleName(char * pName, size_t& nLen);
	BOOL	CheckRoleInfoValid(const char * szRoleName);	//验证Buffer数据是否为RoleName的数据
	BOOL	CheckRoleInfoValid();	
	BOOL	IsValid();
	size_t  GetBufferSize();
	
	int		m_nSaveCmdCount;	//从客户端获得的通知存档的次数
	int		m_nSaveDBCount;		//实际向数据库存档的次数
	int		m_nLoadCmdCount;	//从客户端获得的通知取档的次数
	DWORD	m_nLastSaveTime;	
	int		m_nUnModifyTime;
	BOOL	m_bModify;			//是否更改了，也就是是否需要向数据库内存档
private:
	BYTE	m_RoleInfoBuffer[MAX_ROLEINFORMATION_SIZE];
	size_t	m_nRoleInfoSize;	//实际数据的长度
	OnlineGameLib::Win32::CCriticalSection m_cs;
};


//按照角色登入的顺序存入的玩家列表，用于自动保存的顺序
extern list<KRoleInfomation*> g_RoleInfoList;

//以角色姓名作为关键名，存放玩家的列表，用于在客户端读取档快速检索
extern map<OnlineGameLib::Win32::_tstring , KRoleInfomation * > g_RoleInfoMap;
//存取档必须互斥!
#endif // !defined(AFX_KROLEINFOMATION_H__AECE97BE_EEC0_48CE_AFA1_C55FCFE87C3E__INCLUDED_)
