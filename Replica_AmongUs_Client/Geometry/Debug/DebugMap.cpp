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
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, 1, 1, 0, 0, 0);
	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));
}

void DebugMap::Render()
{
	//IA stage
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	//VertexData업데이트하고 랜더링
	vbUpdateAndDraw("CafeTeria");
	vbUpdateAndDraw("Admin");
	vbUpdateAndDraw("AdminLoby");
	vbUpdateAndDraw("O2");
	vbUpdateAndDraw("O2Loby");
	vbUpdateAndDraw("Security");
	vbUpdateAndDraw("SecurityLoby");

	
}

/*********************************************************************************
	함수 : vbUpdateAndDraw
	목적 : 맵의 선 데이터를 받아 버텍스 버퍼를 업데이트하고 그리는 걸 반복하는 함수
	매개변수
		1.mapName - MapManager의 맵의 테두리 꼭짓점이 들어있는 Map에 Key값이 string이므로 이를 통해 가져오고싶은 구역의 테두리 꼭짓점을 가져와 랜더링한다
*********************************************************************************/
void DebugMap::vbUpdateAndDraw(string mapName)
{
	//1. Key값에 맞는 구역 테두리 꼭짓점 가져오기
	vector<vector<D3DXVECTOR3>> test = MapManager::Get()->GetMapBorder(mapName);

	//2. 한구역의 검사 파트가 몇부분인지
	int tempAreaSize = test.size();
	for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

		int tempLineIndexSize = test.at(areaPart).size();
		for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1하는 이유는 index+1연산이 들어가서임

			//3 VertexData 업데이트

			//3.1 변경 할 구조체 데이터 변경
			mVertexData.GetData()->at(0).position = test.at(areaPart).at(lineIndex);
			mVertexData.GetData()->at(1).position = test.at(areaPart).at(lineIndex + 1);

			//3.2 버텍스버퍼 업데이트 (map, unmap)
			mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

			//3.3 세팅
			mBufferInterface.SetVertexBuffer(&mVertexBuffer);

			//4. Draw한다
			mBufferInterface.Draw();
		}
	}
}
