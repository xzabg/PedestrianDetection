#define SHOW_DEBUG_INFO	

#include <stdio.h>  // for snprintf
#include <string>
#include <vector>
#include <math.h>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

//#include "CompressiveTracker.h"
#include "caffe.hpp"
using namespace caffe;

#define max(a, b) (((a)>(b)) ? (a) :(b))
#define min(a, b) (((a)<(b)) ? (a) :(b))

#define OBJDETTRACK_SUCESS 1
#define OBJDETTRACK_FAIL -1

struct ObjResult
{
	float left;
	float top;
	float right;
	float bottom;

	float fg_prob;
	float bg_prob;

	cv::RotatedRect bbox;	//�������ڼ�¼���Ļع�Ľ�����˺���ʹ�ã����ο��λ��ֱ�Ӵ洢�ı�
	int classIndex;
};

struct DhpRect
{
	DhpRect();
	DhpRect(float left, float top, float right, float bottom)
	{
		m_left = left;
		m_right = right;
		m_top = top;
		m_bottom = bottom;
	}

	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
};

//////////////////////////////////////////////////////////////////////////

class ObjDet
{
public:
	ObjDet();
	~ObjDet();
	int ProcessSingleImg(Mat& currImg, vector<ObjResult>& detResult);
	int Initial();

private:

	int Load();
	int PrepInputData();
	int ClearInputData();

	//���к�ѡ����ļ��
	int ProposalNetRun();

	//��ȡproposal�����
	int ProposalExtract();

	//�������ľ�����Ӧ��ê��λ��
	int CalcPropsalAnchors();

	//��proposal��������лع�
	int ProposalRegression();

	//�߽���
	int ProposalBoundDetect();

	//�˳�С�ߴ��ѡ��
	int RemoveSmallBox();

	//�˳��������ʹ��ߵĺ�ѡ��
	int RemoveBackBox();

	int ShowPropsalResult();

	//----------------------------------------

	//׼�������ڷ��������
	int PrepareClassifyData();

	//�Ժ�ѡ����зǼ�ֵ����
	int NonMaximalSuppression();

	//����Ŀ���ʶ��
	int ClassifyNetRun();

	int ClassifyExtract();

	int ClassifyRegression();

	//�߽���
	int ClassifyBoundDetect();

	//�˳�С�ߴ��ѡ��
	int RemoveSmallClassifyBox();

	int NonMaximalSuppression_classify();

	//��ʾ���
	int ShowClassifyResult();

private:

	boost::shared_ptr< Net<float> > m_proposal_net_;
	boost::shared_ptr< Net<float> > m_classify_net_;

	boost::shared_ptr<caffe::Blob<float>> m_blob_bbox;
	boost::shared_ptr<caffe::Blob<float>> m_blob_prob;

	Mat m_oriImg;
	Mat m_oriImg32f;
	Mat m_resizedImg32f;
	//����������Ϊ�������ݵ��ڴ�
	float* m_data_buf;

	int m_oriWidth;
	int m_oriHeight;
	int m_resizedWidth;
	int m_resizedHeight;

	//ͼ������ű���
	float m_img_scale;

	//��ѡ��
	vector<ObjResult> m_objVec;
	//���ռ����
	vector<ObjResult> m_classifyVec;

	//�Ǽ�ֵ����֮ǰ�ĺ�ѡ�������Ŀ���������Ŷ�����
	int m_per_nms_topN;
	//�����ֵ����ʱ�Ĵ��ڽ�������
	float m_nms_overlap_thres;
	//���յĺ�ѡ��������Ŀ
	int m_after_nms_topN;
	int m_use_gpu;
	//���ʱͼ����С�ߵĳ���	
	float  m_min_input_side;

	//����ʱ���Ŷȵ���ֵ
	float m_CONF_THRESH;
	//�������ķǼ�ֵ���ƴ��ڽ�������
	float m_NMS_THRESH;

	//�������ɹ����еĸ��ֲ������������һ�������
	int m_propNum;
	int m_propChannel;
	int m_propHeight;
	int m_propWidth;

	//ê���׼����
	vector<DhpRect> m_ori_anchors_vec;
	int m_ori_anchors_cnt;
	vector<DhpRect> m_prop_anchors_vec;
	int m_prop_anchors_cnt;
	//����ê��λ��ʱ������
	int m_anchor_stride;

	//��ѡ�����С�ߴ�
	int m_prop_min_width;
	int m_prop_max_width;
	int m_prop_max_height;

};