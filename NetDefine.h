#pragma once
#define NET_PACKET_DATA_SIZE 100000
#define NET_PACKET_SIZE (sizeof(NetPacketHeader)+NET_PACKET_DATA_SIZE)+5000
//�������ݰ���ͷ
struct NetPacketHeader
{
	unsigned int		wDataSize;		//���ݰ���С���������ͷ�ͷ�����ݴ�С
	unsigned short		wOpcode;		//������
};
/// ���������
enum eNetOpcode
{
	NET_TEST1 = 1,
};
/// ����1���������ݰ�����
struct NetPacket_Test1
{
	char	arrMessage[NET_PACKET_DATA_SIZE];
};