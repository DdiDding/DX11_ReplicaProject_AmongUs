#include "Shader.h"

Shader::Shader()
{
	
}


Shader::~Shader()
{
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_pixelShader);
	SAFE_RELEASE(m_inputLayout);
}


void Shader::Render()
{
	//InputLayout을 IA단계에 세팅한다
	GETDC->IASetInputLayout(m_inputLayout);

	//셰이더를 각 단계에 세팅한다
	GETDC->VSSetShader(m_vertexShader, NULL, 0);
	GETDC->PSSetShader(m_pixelShader, NULL, 0);

	
	return;
}


