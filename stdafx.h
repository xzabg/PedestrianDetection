// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "NetDefine.h"

#define SERVER_PORT		20000
#define SERVER_IP		"101.201.211.87"//������
//#define SERVER_IP		"192.168.1.114"
//#define SERVER_IP		"192.168.0.102"//169.254.169.148"//�ҵĵ��Բ�������
//#define SERVER_IP		"127.0.0.1"//�ҵĵ���������
//#define SERVER_IP		"192.168.1.131"//�ҵ�̨ʽ��


class WinSocketSystem
{
public:
	WinSocketSystem()
	{
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR)
		{
			exit(-1);
		}
	}
	~WinSocketSystem()
	{
		WSACleanup();
	}
protected:
	WSADATA wsaData;
};

static WinSocketSystem g_winsocketsystem;
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�