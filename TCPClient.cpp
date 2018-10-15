#include "stdafx.h"
#include "TCPClient.h"

using namespace std;

TCPClient::TCPClient()
{
	//�����׽���
	mServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (mServerSocket == INVALID_SOCKET)
	{
		cout << "�����׽���ʧ�ܣ�" << endl;
		return;
	}

	//����������IP�Ͷ˿ں�
	mServerAddr.sin_family = AF_INET;
	mServerAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	mServerAddr.sin_port = htons((u_short)SERVER_PORT);

	//���ӵ�������
	if (::connect(mServerSocket, (struct sockaddr*)&mServerAddr, sizeof(mServerAddr)))
	{
		::closesocket(mServerSocket);
		cout << "���ӷ�����ʧ�ܣ�" << endl;
		return;
	}
}

TCPClient::~TCPClient()
{
	::closesocket(mServerSocket);
	cout << "�ر�TCP�ͻ��˳ɹ���" << endl;
}

void TCPClient::run(char* imagename)
{
//	for (;;)
//	{	//�������ݰ�
		NetPacket_Test1 msg;
		FILE *fpPhoto;
		char szBuf[NET_PACKET_DATA_SIZE];
		//char name[100];
		//static int namenum = 0;
		//namenum += 1;
		//sprintf(name, "E:\\%d.jpg", namenum);
		//sprintf(name, "D:\\CaffeProgram\\13FastRcnn\\tu\\%d.jpg", namenum);
		int iRead;
		//fpPhoto = fopen("E:\\1.jpg", "rb");
		fpPhoto = fopen(imagename, "rb");
		iRead = fread(szBuf, 1, sizeof(szBuf), fpPhoto);
		//iRead = img.imageSize;
		CopyMemory(msg.arrMessage, szBuf, iRead);
		//CopyMemory(msg.arrMessage, img.imageData , iRead);
		fclose(fpPhoto);
		bool bRet = SendData(NET_TEST1, (const char*)&msg, iRead);
		//һ��ע��˴���Ҫ���ݵ��ֽ�����ΪiRead+4���ֽ��������˻����
		if (bRet)
		{	cout << "�������ݳɹ���" << endl;		}
		else
		{	cout << "��������ʧ�ܣ�" << endl;		}
//	}
}

bool TCPClient::SendData(unsigned short nOpcode,const char* pDataBuffer,const unsigned int& nDataSize)
{
	NetPacketHeader* pHead = (NetPacketHeader*)m_cbSendBuf;
	pHead->wOpcode = nOpcode;

	//���ݷ��
	if ((nDataSize >= 0) && (pDataBuffer != 0))
	{
		CopyMemory(pHead + 1, pDataBuffer, nDataSize);
	}

	//������Ϣ
	//const unsigned short nSendSize = nDataSize + sizeof(NetPacketHeader);
	const unsigned int nSendSize = nDataSize + sizeof(NetPacketHeader);
	pHead->wDataSize = nSendSize;
	int ret = ::send(mServerSocket, m_cbSendBuf, nSendSize, 0);

	//int ret;
	//int restdata = nDataSize;
	//int senddatalen = 10000;
	//while (restdata > 0)
	//{
	//	int len = (restdata < senddatalen) ? restdata : senddatalen;
	//	//���ݷ��
	//	if ((restdata >= 0) && (pDataBuffer != 0))
	//	{
	//		CopyMemory(pHead + 1, pDataBuffer+nDataSize-restdata, len);
	//	}

	//	//������Ϣ
	//	const unsigned short nsendsize = len + sizeof(NetPacketHeader);
	//	pHead->wDataSize = nDataSize + sizeof(NetPacketHeader);
	//	pHead->wOpcode = nOpcode;
	//	ret = ::send(mServerSocket, m_cbSendBuf, nsendsize, 0);
	//	restdata -= senddatalen;
	//}
	
	return(ret > 0) ? true : false;
}