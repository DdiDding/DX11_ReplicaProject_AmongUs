#include "../Line.h"
#include "DebugMap.h"


DebugMap::DebugMap()
{
	
}

DebugMap::~DebugMap()
{
}

void DebugMap::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, 1, 1, 0, 0, 0);
	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));
}

void DebugMap::Render()
{
	//IA stage
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	//VertexData������Ʈ�ϰ� ������
	vbUpdateAndDraw("CafeTeria");
	vbUpdateAndDraw("Admin");
	vbUpdateAndDraw("AdminLoby");
	vbUpdateAndDraw("O2");
	vbUpdateAndDraw("O2Loby");
	vbUpdateAndDraw("Security");
	vbUpdateAndDraw("SecurityLoby");

	
}

/*********************************************************************************
	�Լ� : vbUpdateAndDraw
	���� : ���� �� �����͸� �޾� ���ؽ� ���۸� ������Ʈ�ϰ� �׸��� �� �ݺ��ϴ� �Լ�
	�Ű�����
		1.mapName - MapManager�� ���� �׵θ� �������� ����ִ� Map�� Key���� string�̹Ƿ� �̸� ���� ����������� ������ �׵θ� �������� ������ �������Ѵ�
*********************************************************************************/
void DebugMap::vbUpdateAndDraw(string mapName)
{
	//1. Key���� �´� ���� �׵θ� ������ ��������
	vector<vector<D3DXVECTOR3>> test = MapManager::Get()->GetMapBorder(mapName);

	//2. �ѱ����� �˻� ��Ʈ�� ��κ�����
	int tempAreaSize = test.size();
	for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

		int tempLineIndexSize = test.at(areaPart).size();
		for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1�ϴ� ������ index+1������ ������

			//3 VertexData ������Ʈ

			//3.1 ���� �� ����ü ������ ����
			mVertexData.GetData()->at(0).position = test.at(areaPart).at(lineIndex);
			mVertexData.GetData()->at(1).position = test.at(areaPart).at(lineIndex + 1);

			//3.2 ���ؽ����� ������Ʈ (map, unmap)
			mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

			//3.3 ����
			mBufferInterface.SetVertexBuffer(&mVertexBuffer);

			//4. Draw�Ѵ�
			mBufferInterface.Draw();
		}
	}
}
